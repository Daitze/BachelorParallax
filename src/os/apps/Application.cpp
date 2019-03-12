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

#include <apps/BugDefender/BugDefender.h>
#include <devices/timer/Pit.h>
#include <lib/libc/printf.h>
#include <apps/MouseApp/MouseApp.h>
#include <kernel/services/DebugService.h>
#include <apps/Shell/Shell.h>
#include <lib/multiboot/Structure.h>
#include <kernel/threads/Scheduler.h>
#include <kernel/threads/WorkerThread.h>
#include <apps/LoopsAndSound/LoopsAndSound.h>
#include <apps/Mandelbrot/Mandelbrot.h>
#include <apps/MemoryTests/MemoryManagerTest.h>
#include <kernel/memory/manager/FreeListMemoryManager.h>
#include <kernel/memory/manager/BitmapMemoryManager.h>
#include <kernel/memory/manager/BitmapMemoryManager.h>
#include <kernel/memory/SystemManagement.h>
#include <lib/system/SystemCall.h>
#include "apps/LoopsAndSound/Loop.h"
#include "apps/LoopsAndSound/Sound.h"
#include "apps/AntApp/AntApp.h"
#include "lib/libc/snprintf.h"
#include "Application.h"


#define TEST_THREADING 0

Thread *currentApp = nullptr;

uint32_t threadSum = 0;

uint32_t worker(const uint32_t &number) {

    return number * 2;
}

void callback(const Thread &thread, const uint32_t &number) {

    threadSum += number;
}

Application::Application () : Thread ("Menu") {
    graphicsService = Kernel::getService<GraphicsService>();
	timeService = Kernel::getService<TimeService>();
}

Application& Application::getInstance() noexcept {

    static Application instance;

    return instance;
}

void Application::startLoopSoundDemo() {
    TextDriver *stream = graphicsService->getTextDriver();
    stream->init(static_cast<uint16_t>(xres / 8), static_cast<uint16_t>(yres / 16), bpp);

    currentApp = new LoopsAndSound();
    currentApp->start();
}

void Application::startAntDemo() {
    currentApp = new AntApp();

    currentApp->start();
}

void Application::startMandelbrotDemo() {

    currentApp = new Mandelbrot();

    currentApp->start();
}

void Application::startMemoryManagerDemo() {
    TextDriver *stream = graphicsService->getTextDriver();

    stream->init(static_cast<uint16_t>(xres / 8), static_cast<uint16_t>(yres / 16), bpp);

    MemoryManagerTest *tests[5] {
            new MemoryManagerTest(*SystemManagement::getKernelHeapManager(), 1048576, 128, 8192, "KernelHeapMemoryManager"),
            new MemoryManagerTest(*SystemManagement::getInstance().getIOMemoryManager(), 1048576, 128, 8192, "IOMemoryManager"),
            new MemoryManagerTest("FreeListMemoryManager", 1048576, 128, 8192),
            new MemoryManagerTest("BitmapMemoryManager", 1048576, 128, 128),
            new MemoryManagerTest("StaticHeapMemoryManager", 1048576, 128, 8192)
    };

    for(const auto test : tests) {
        test->run();

        delete test;

        stream->clear();
    }

    graphicsService->getLinearFrameBuffer()->init(xres, yres, bpp);

    // Don't use High-Res mode on CGA, as it looks bad.
    if(graphicsService->getLinearFrameBuffer()->getDepth() == 1) {
        graphicsService->getLinearFrameBuffer()->init(320, 200, 2);
    }

    graphicsService->getLinearFrameBuffer()->enableDoubleBuffering();
}

void Application::startMouseApp() {
    graphicsService->getLinearFrameBuffer()->init(640, 480, 16);

    // Don't use High-Res mode on CGA, as it looks bad.
    if(graphicsService->getLinearFrameBuffer()->getDepth() == 1) {
        graphicsService->getLinearFrameBuffer()->init(320, 200, 2);
    }

    graphicsService->getLinearFrameBuffer()->enableDoubleBuffering();

    currentApp = new MouseApp();

    currentApp->start();
}

void Application::startExceptionDemo() {
    Cpu::throwException(Cpu::Exception::ILLEGAL_STATE, "This ist just a test. Please restart your computer!");
}

void Application::startShell() {
    TextDriver *stream = graphicsService->getTextDriver();
    stream->init(static_cast<uint16_t>(xres / 8), static_cast<uint16_t>(yres / 16), bpp);

    currentApp = new Shell();

    currentApp->start();
}

void Application::showMenu () {
    MemoryManager *kernelHeapManager = SystemManagement::getKernelHeapManager();

    uint32_t memory = kernelHeapManager->getEndAddress() - kernelHeapManager->getStartAddress();

    while(true) {

        LinearFrameBuffer *lfb = graphicsService->getLinearFrameBuffer();

        Font &font = lfb->getResY() < 400 ? (Font&) std_font_8x8 : (Font&) sun_font_8x16;

        if(isRunning) {
            uint32_t freeMemory = kernelHeapManager->getFreeMemory();

            Rtc::Date date = timeService->getRTC()->getCurrentDate();

            lfb->placeRect(50, 50, 98, 98, Colors::HHU_LIGHT_GRAY);

            lfb->placeString(font, 50, 8, (const char*) String::format("%02d.%02d.%04d %02d:%02d:%02d", date.dayOfMonth, date.month, date.year, date.hours, date.minutes, date.seconds), Colors::HHU_LIGHT_GRAY);

            lfb->placeString(font, 50, 13, (const char*) String::format("Free memory: %u Bytes", freeMemory), Colors::HHU_LIGHT_GRAY);

            lfb->placeString(font, 50, 16, (const char*) String::format("Used memory: %u Bytes", memory - freeMemory), Colors::HHU_LIGHT_GRAY);

            lfb->placeString(font, 50, 24, "hhuOS main menu", Colors::HHU_BLUE);

            lfb->placeLine(33, 26, 66, 26, Colors::HHU_BLUE_50);

            lfb->placeRect(50, 50, 60, 60, Colors::HHU_LIGHT_GRAY);

            lfb->placeRect(50, 59, 60, 59, Colors::HHU_LIGHT_GRAY);

            for (uint32_t i = 0; i < sizeof(menuOptions) / sizeof(const char *); i++) {
                lfb->placeString(font, 50, static_cast<uint16_t>(36 + i * menuDistance), menuOptions[i],
                                 Colors::HHU_LIGHT_GRAY);
            }

#if (TEST_THREADING == 1)
            lfb->placeString(font, 50, 32, (char*) String::valueOf(threadSum, 10), Colors::WHITE);
#endif

            lfb->placeString(font, 50, 84, menuDescriptions[option], Colors::HHU_BLUE_30);

            lfb->placeString(font, 50, 92, "Please select an option using the arrow keys", Colors::HHU_LIGHT_GRAY);
            lfb->placeString(font, 50, 95, "and confirm your selection using the space key.", Colors::HHU_LIGHT_GRAY);

            lfb->placeRect(50, static_cast<uint16_t>(36 + option * menuDistance), 58, menuDistance,
                           Colors::HHU_BLUE_70);

            lfb->show();

#if (TEST_THREADING == 1)
            WorkerThread<uint32_t, uint32_t > *w1 = new WorkerThread<uint32_t, uint32_t >(worker, 20, callback);
            WorkerThread<uint32_t, uint32_t > *w2 = new WorkerThread<uint32_t, uint32_t >(worker, 40, callback);
            WorkerThread<uint32_t, uint32_t > *w3 = new WorkerThread<uint32_t, uint32_t >(worker, 80, callback);

            w1->start();
            w2->start();
            w3->start();
#endif
        } else {
            startSelectedApp();
        }
    }
}

void Application::startSelectedApp() {
    LinearFrameBuffer *lfb = graphicsService->getLinearFrameBuffer();

    lfb->disableDoubleBuffering();
    lfb->clear();

    switch (option) {
        case 0:
            startShell();
            pause();
            break;
        case 1: {
            Game *game = new BugDefender();
            startGame(game);
            delete game;
            break;
        }
        case 2:
            startAntDemo();
            pause();
            break;
        case 3:
            startMandelbrotDemo();
            pause();
            break;
        case 4:
            startMouseApp();
            pause();
            break;
        case 5:
            startLoopSoundDemo();
            pause();
            break;
        case 6:
            startMemoryManagerDemo();
            isRunning = true;
            break;
        case 7:
            startExceptionDemo();
            pause();
            break;
        default:
            break;
    }

    delete currentApp;
}

void Application::startGame(Game* game){
    LinearFrameBuffer *lfb = graphicsService->getLinearFrameBuffer();

    lfb->init(640, 480, 16);
    lfb->enableDoubleBuffering();

    float currentTime = timeService->getSystemTime() / 1000.0f;
    float acc = 0.0f;
    float delta = 0.01667f; // 60Hz

    while (game->isRunning) {
        float newTime = timeService->getSystemTime() / 1000.0f;
        float frameTime = newTime - currentTime;
        if(frameTime > 0.25f)
            frameTime = 0.25f;
        currentTime = newTime;

        acc += frameTime;

        while(acc >= delta){
            game->update(delta);
            acc -= delta;
        }

        game->draw(lfb);
    }

    graphicsService->getLinearFrameBuffer()->init(xres, yres, bpp);

    // Don't use High-Res mode on CGA, as it looks bad.
    if(graphicsService->getLinearFrameBuffer()->getDepth() == 1) {
        graphicsService->getLinearFrameBuffer()->init(320, 200, 2);
    }

    graphicsService->getLinearFrameBuffer()->enableDoubleBuffering();

    isRunning = true;
}

void Application::pause() {
    Kernel::getService<EventBus>()->unsubscribe(*this, KeyEvent::TYPE);
    Cpu::softInterrupt(SystemCall::SCHEDULER_BLOCK);
}

void Application::resume() {
    isRunning = true;

    graphicsService->getLinearFrameBuffer()->init(xres, yres, bpp);

    // Don't use High-Res mode on CGA, as it looks bad.
    if(graphicsService->getLinearFrameBuffer()->getDepth() == 1) {
        graphicsService->getLinearFrameBuffer()->init(320, 200, 2);
    }

    graphicsService->getLinearFrameBuffer()->enableDoubleBuffering();

    Scheduler::getInstance().deblock(*this);
    Kernel::getService<EventBus>()->subscribe(*this, KeyEvent::TYPE);
}

void Application::run() {

    timeService = Kernel::getService<TimeService>();
    LinearFrameBuffer *lfb = graphicsService->getLinearFrameBuffer();
    Util::Array<String> res = Multiboot::Structure::getKernelOption("resolution").split("x");

    if(res.length() >= 3) {
        xres = static_cast<uint16_t>(strtoint((const char *) res[0]));
        yres = static_cast<uint16_t>(strtoint((const char *) res[1]));
        bpp = static_cast<uint8_t>(strtoint((const char *) res[2]));

        lfb->init(xres, yres, bpp);

        // Don't use High-Res mode on CGA, as it looks bad.
        if(lfb->getDepth() == 1) {
            lfb->init(320, 200, 2);
        }
    } else {
        xres = lfb->getResX();
        yres = lfb->getResY();
        bpp = lfb->getDepth();
    }

    lfb->enableDoubleBuffering();

    Kernel::getService<EventBus>()->subscribe(*this, KeyEvent::TYPE);

    showMenu();
}

void Application::onEvent(const Event &event) {

    auto &keyEvent = (KeyEvent&) event;

    if (!keyEvent.getKey().isPressed()) {
        return;
    }

    switch (keyEvent.getKey().scancode()) {
        case KeyEvent::SPACE:
            isRunning = false;
            break;
        case KeyEvent::DOWN:
            if (option >= sizeof(menuOptions) / sizeof(const char *) - 1) {
                option = 0;
            } else {
                option++;
            }
            break;
        case KeyEvent::UP:
            if (option <= 0) {
                option = sizeof(menuOptions) / sizeof(const char *) - 1;
            } else {
                option --;
            }
            break;
        default:
            break;
    }
}
