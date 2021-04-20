/*
 * Copyright (C) 2018 Burak Akguel, Christian Gesse, Fabian Ruhland, Filip Krakowski, Michael Schoettner
 * Heinrich-Heine University
 *
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#include "Shell.h"
#include "kernel/event/input/KeyEvent.h"
#include "application/shell/command/Echo.h"
#include "application/shell/command/Cat.h"
#include "lib/file/File.h"
#include "application/Application.h"
#include "kernel/thread/Scheduler.h"
#include "application/shell/command/Ls.h"
#include "application/shell/command/Touch.h"
#include "application/shell/command/Mkdir.h"
#include "application/shell/command/Rm.h"
#include "application/shell/command/Cd.h"
#include "application/shell/command/Shutdown.h"
#include "application/shell/command/Clear.h"
#include "application/shell/command/Insmod.h"
#include "application/shell/command/Ip.h"
#include "application/shell/command/Mount.h"
#include "application/shell/command/Umount.h"
#include "application/shell/command/Head.h"
#include "application/shell/command/Tail.h"
#include "application/shell/command/Uptime.h"
#include "application/shell/command/Date.h"
#include "application/shell/command/History.h"
#include "application/shell/command/Mkfs.h"
#include "application/shell/command/DiskInfo.h"
#include "application/shell/command/MkPart.h"
#include "application/shell/command/MkPartTable.h"
#include "application/shell/command/DelPart.h"
#include "application/shell/command/Rmdir.h"
#include "application/shell/command/Mathexpr.h"
#include "application/shell/command/Pwd.h"
#include "application/shell/command/Ps.h"
#include "lib/graphic/Ansi.h"
#include "application/shell/command/MkVdd.h"
#include "application/shell/command/DelVdd.h"
#include "application/shell/command/BmpView.h"
#include "application/shell/command/WavPlay.h"
#include "application/shell/command/Beep.h"
#include "application/shell/command/License.h"
#include "application/shell/command/Asciimate.h"
#include "device/port/PortEvent.h"
#include "application/shell/command/NetworkTest.h"

extern "C" {
#include "lib/libc/ctype.h"
}

Shell::Shell() : KernelThread("Shell") {
    kernelStreamService = Kernel::System::getService<Kernel::KernelStreamService>();
    graphicsService = Kernel::System::getService<Kernel::GraphicsService>();
    eventBus = Kernel::System::getService<Kernel::EventBus>();

    kernelStreamService->setStdout(this);
    kernelStreamService->setStderr(this);
    kernelStreamService->setStdin(this);

    commands.put("history", new History(*this));
    commands.put("clear", new Clear(*this));
    commands.put("cd", new Cd(*this));
    commands.put("echo", new Echo(*this));
    commands.put("cat", new Cat(*this));
    commands.put("head", new Head(*this));
    commands.put("tail", new Tail(*this));
    commands.put("ls", new Ls(*this));
    commands.put("touch", new Touch(*this));
    commands.put("shutdown", new Shutdown(*this));
    commands.put("mkdir", new Mkdir(*this));
    commands.put("rmdir", new Rmdir(*this));
    commands.put("pwd", new Pwd(*this));
    commands.put("ps", new Ps(*this));
    commands.put("mathexpr", new Mathexpr(*this));
    commands.put("rm", new Rm(*this));
    commands.put("insmod", new Insmod(*this));
    commands.put("ip", new Ip(*this));
    commands.put("mount", new Mount(*this));
    commands.put("umount", new Umount(*this));
    commands.put("mkparttable", new MkPartTable(*this));
    commands.put("mkpart",  new MkPart(*this));
    commands.put("delpart",  new DelPart(*this));
    commands.put("mkvdd",  new MkVdd(*this));
    commands.put("delvdd",  new DelVdd(*this));
    commands.put("mkfs", new Mkfs(*this));
    commands.put("diskinfo", new DiskInfo(*this));
    commands.put("uptime", new Uptime(*this));
    commands.put("date", new Date(*this));
    commands.put("bmpview", new BmpView(*this));
    commands.put("wavplay", new WavPlay(*this));
    commands.put("beep", new Beep(*this));
    commands.put("license", new License(*this));
    commands.put("asciimate", new Asciimate(*this));
    commands.put("nettest", new NetworkTest(*this));

    memset(inputBuffer, 0, sizeof(inputBuffer));
}

Shell::~Shell() {
    for(const auto &string : commands.keySet()) {
        delete commands.get(string);
    }

    kernelStreamService->setStdout(graphicsService->getTextDriver());
    kernelStreamService->setStderr(graphicsService->getTextDriver());
    kernelStreamService->setStdin(nullptr);
}

Directory &Shell::getCurrentWorkingDirectory() {
    return *cwd;
}

void Shell::setCurrentWorkingDirectory(Directory *cwd) {
    delete this->cwd;
    this->cwd = cwd;
}

void Shell::run() {
    cwd = Directory::open("/");

    *this << "Welcome to the hhuOS-Shell! Enter 'help' for a list of all available commands." << endl;
    *this << "\u001b[32;1m[root@hhu \u001b[37;1m/\u001b[32;1m]$\u001b[0m ";
    this->flush();

    currentBase = 14;

    uint16_t x, y;

    while(isRunning) {
        char* input = nullptr;
        *this >> input;

        if(strlen(input) > 0) {
            history.add(input);
        }

        historyIndex = history.size();
        executeCommand(input);

        delete input;

        *this << "\u001b[32;1m[root@hhu \u001b[37;1m" << (cwd->getName().isEmpty() ? "/" : cwd->getName()) << "\u001b[32;1m]$\u001b[0m ";
        this->flush();

        graphicsService->getTextDriver()->getpos(x, y);

        currentBase = x;
    }
}

void Shell::executeCommand(String input) {
    OutputStream *stream = this;

     Util::Array<String> tmp = input.split(">");

    if(tmp.length() == 0) {
        return;
    }

    Util::Array<String> args = String(tmp[0]).split(" ");

    if(args.length() == 0) {
        return;
    }

    if(!commands.containsKey(args[0]) && args[0] != "help" && args[0] != "exit") {
        *this << "Shell: '" << args[0] << "': Command not found!" << endl;
        return;
    }

    if(tmp.length() > 1) {
        // Command shall output to file
        String relativePath = tmp[1];

        // Remove heading whitespaces
        while(relativePath.beginsWith(" ")) {
            relativePath = relativePath.substring(1, relativePath.length());
        }

        // Assemble absolute path
        String absolutePath;

        if(relativePath.beginsWith("/")) {
            // User has already entered an absolute path
            // We don't need to do anything
            absolutePath = relativePath;
        } else {
            // Append relative path to current working directory
            absolutePath = cwd->getAbsolutePath();

            if (!absolutePath.endsWith(Filesystem::SEPARATOR)) {
                absolutePath += Filesystem::SEPARATOR;
            }

            absolutePath += relativePath;
        }

        // Try to open the output file
        File *file = File::open(absolutePath, "w");
        if(file == nullptr) {
            *this << "Shell: '" << relativePath << "': File or Directory not found!" << endl;
            return;
        }

        stream = file;
    }

    if(args[0] == "help") {
        if(args.length() == 1) {
            for (const String &command : commands.keySet()) {
                *stream << command << endl;
            }

            *stream << "help" << endl;
            *stream << "exit" << endl;
        } else {
            if(args[1] == "help") {
                *stream << "Shows either all available commands, or the help message of a specific command." << endl << endl;
                *stream << "Usage: help [Optional: COMMAND]" << endl;
            } else if(args[1] == "exit") {
                *stream << "Exits the shell." << endl << endl;
                *stream << "Usage: exit" << endl;
            } else if(commands.containsKey(args[1])) {
                *stream << commands.get(args[1])->getHelpText() << endl;
            } else {
                *stream << "Command not found '" << args[1] << "'!" << endl;
            }
        }

        return;
    } else if(args[0] == "exit") {
        isRunning = false;
        return;
    }

    kernelStreamService->setStdout(stream);
    kernelStreamService->setStderr(stream);

    commands.get(args[0])->execute(args);

    kernelStreamService->setStdout(this);
    kernelStreamService->setStderr(this);

    if(stream != this) {
        delete stream;
    }
}

void Shell::onEvent(const Kernel::Event &event) {
    char c;

    if(event.getType() == Kernel::KeyEvent::TYPE) {
        Key key = ((Kernel::KeyEvent&) event).getKey();

        switch (key.scancode()) {
            case Kernel::KeyEvent::UP:
                showHistory(UP);
                return;
            case Kernel::KeyEvent::DOWN:
                showHistory(DOWN);
                return;
            default:
                break;
        }

        if(key.valid()) {
            c = key.ascii();
        } else {
            return;
        };
    } else if(event.getType() == "Com1Event") {
        c = ((PortEvent&) event).getChar();
    } else {
        return;
    }

    if(strlen(inputBuffer) == (sizeof(inputBuffer) - 1) && c != '\b') {
        return;
    }

    inputLock.acquire();

    TextDriver *textDriver = graphicsService->getTextDriver();

    if(c == '\n' || c == 13) {
        inputBuffer[strlen(inputBuffer)] = 0;
        *this << endl;

        lastString = String(inputBuffer);
        stringAvailable = true;

        memset(inputBuffer, 0, sizeof(inputBuffer));
    } else if(c == '\b' || c == 127) {
        if(strlen(inputBuffer) > 0) {
            uint16_t x, y;
            textDriver->getpos(x, y);
            textDriver->show(x, y, ' ', bgColor, bgColor);

            if(x != 0) {
                textDriver->show(--x, y, '_', fgColor, bgColor);
                textDriver->setpos(x, y);
            } else {
                textDriver->show(static_cast<uint16_t>(textDriver->getColumnCount() - 1), --y, '_', fgColor, bgColor);
                textDriver->setpos(static_cast<uint16_t>(textDriver->getColumnCount() - 1), y);
            }

            memset(&inputBuffer[strlen(inputBuffer) - 1], 0, sizeof(inputBuffer) - (strlen(inputBuffer) - 1));
        }
    } else {
        lastChar = c;
        charAvailable = true;

        inputBuffer[strlen(inputBuffer)] = c;
        *this << c;
        flush();
    }

    inputLock.release();
}

InputStream &Shell::operator>>(char &c) {
    while(true) {
        inputLock.acquire();

        if(charAvailable) {
            charAvailable = false;
            c = lastChar;

            inputLock.release();
            return *this;
        }

        inputLock.release();
    }
}

InputStream &Shell::operator>>(char *&string) {
    eventBus->subscribe(*this, Kernel::KeyEvent::TYPE);
    eventBus->subscribe(*this, "Com1Event");

    while(true) {
        inputLock.acquire();

        if(stringAvailable) {
            stringAvailable = false;

            string = new char[lastString.length() + 1];
            memcpy(string, (char *) lastString, lastString.length() + 1);

            inputLock.release();

            eventBus->unsubscribe(*this, Kernel::KeyEvent::TYPE);
            eventBus->unsubscribe(*this, "Com1Event");
            return *this;
        }

        inputLock.release();
    }
}

InputStream &Shell::operator>>(OutputStream &outStream) {
    char *string = nullptr;

    *this >> string;
    outStream << string;
    outStream.flush();

    delete string;
    return *this;
}

void Shell::showHistory(HistoryDirection direction) {

    switch (direction) {
        case UP:
            historyIndex--;
            break;
        case DOWN:
            historyIndex++;
            break;
    }

    uint32_t historySize = history.size();

    if (historySize == 0) {

        return;
    }

    TextDriver *textDriver = graphicsService->getTextDriver();

    uint16_t x, y;

    textDriver->getpos(x, y);

    for (uint16_t i = currentBase; i <= x; i++) {

        textDriver->show(i, y, ' ', Colors::BLACK, Colors::BLACK);

        memset(&inputBuffer[strlen(inputBuffer) - 1], 0, sizeof(inputBuffer) - (strlen(inputBuffer) - 1));
    }

    textDriver->setpos(currentBase, y);

    String command;

    if (historyIndex == UINT32_MAX) {

        historyIndex = 0;

    }

    if (historyIndex >= historySize) {

        historyIndex = historySize;

        command = "";

        textDriver->getpos(x, y);

        textDriver->show(x, y, '_', fgColor, bgColor);
    } else {

        command = history.get(historyIndex);
    }

    uint32_t commandLength = command.length();

    char c;

    for (uint32_t i = 0; i < commandLength; i++) {

        c = command[i];

        lastChar = c;

        charAvailable = true;

        inputBuffer[strlen(inputBuffer)] = c;

        *this << c;

        this->flush();
    }
}

void Shell::flush() {
    AnsiOutputStream::flush();

    TextDriver *textDriver = graphicsService->getTextDriver();

    uint16_t x, y;

    textDriver->getpos(x, y);
    textDriver->show(x, y, '_', fgColor, bgColor);
}
