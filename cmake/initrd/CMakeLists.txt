# Copyright (C) 2019 Burak Akguel, Christian Gesse, Fabian Ruhland, Filip Krakowski, Michael Schoettner
# Heinrich-Heine University
#
# This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
# License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any
# later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
# warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>

cmake_minimum_required(VERSION 3.7)

project(initrd)
message(STATUS "Project " ${PROJECT_NAME})

add_custom_command(OUTPUT "${CMAKE_BINARY_DIR}/hhuOS.initrd"
        COMMAND tar -C "${HHUOS_ROOT_DIR}/initrd/" --xform s:'./':: -cf "${CMAKE_BINARY_DIR}/hhuOS.initrd" ./)

add_custom_target(initrd DEPENDS "${CMAKE_BINARY_DIR}/hhuOS.initrd")