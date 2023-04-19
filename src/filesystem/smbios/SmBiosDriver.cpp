/*
 * Copyright (C) 2018-2023 Heinrich-Heine-Universitaet Duesseldorf,
 * Institute of Computer Science, Department Operating Systems
 * Burak Akguel, Christian Gesse, Fabian Ruhland, Filip Krakowski, Michael Schoettner
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

#include "SmBiosDriver.h"

#include "SmBiosVersionNode.h"
#include "SmBiosTableNode.h"
#include "filesystem/memory/MemoryDirectoryNode.h"
#include "device/bios/SmBios.h"
#include "lib/util/collection/Array.h"
#include "lib/util/hardware/SmBios.h"

namespace Filesystem::SmBios {

SmBiosDriver::SmBiosDriver() {
    addNode("/", new SmBiosVersionNode());
    addNode("/", new Memory::MemoryDirectoryNode("tables"));

    for (const auto type : Device::SmBios::getAvailableTables()) {
        addNode("/tables", new SmBiosTableNode(Device::SmBios::getTable<Util::Hardware::SmBios::TableHeader>(type)));
    }
}

bool SmBiosDriver::createNode(const Util::String &path, Util::Io::File::Type type) {
    return false;
}

bool SmBiosDriver::deleteNode(const Util::String &path) {
    return false;
}

}