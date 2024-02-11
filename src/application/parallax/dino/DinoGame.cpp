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

#include "DinoGame.h"

#include <cstdint>

#include "application/dino/Dino.h"
#include "lib/util/io/key/Key.h"
#include "lib/util/game/2d/component/LinearMovementComponent.h"
#include "lib/util/game/2d/component/GravityComponent.h"
#include "lib/util/game/GameManager.h"
#include "application/dino/Ground.h"
#include "lib/util/game/Game.h"
#include "lib/util/game/Graphics.h"
#include "lib/util/graphic/Color.h"
#include "lib/util/math/Vector2D.h"
#include "application/parallax/dino/BackgroundFar.h"


DinoGame::DinoGame() {
    dino->addComponent(new Util::Game::D2::LinearMovementComponent(*dino));
    dino->addComponent(new Util::Game::D2::GravityComponent(*dino, 1.25, 0));


    for (uint32_t i = 0; i < 4; i++) {
        auto *newGround = new Ground(Util::Math::Vector2D(getCamera().getPosition().getX() - 1.5 + i, -1));
        ground.offer(newGround);
        addObject(newGround);
    }

    setKeyListener(*this);
}

void DinoGame::initializeBackground(Util::Game::Graphics &graphics) {
    graphics.clear(Util::Graphic::Color(57, 97, 255));
    background = new BackgroundFar(Util::Math::Vector2D(getCamera().getPosition().getX(),0), dino->getVelocity().getX(), 0.01);
    addObject(background);
    addObject(dino);
}

void DinoGame::update(double delta) {
    background->setVelocity(dino->getVelocity().getX());
    background->setCameraPosition((static_cast<uint32_t>((getCamera().getPosition().getX() + 1.5) * 10) / 5) * 5 / 10.0 );

    dino->setVelocityX(currentVelocity);


    getCamera().setPosition(Util::Math::Vector2D(dino->getPosition().getX() + 0.8, 0));

    if (ground.peek()->getPosition().getX() < getCamera().getPosition().getX() - 2.5) {
        auto positionX = (static_cast<uint32_t>((getCamera().getPosition().getX() + 1.5) * 10) / 5) * 5 / 10.0 ;
        auto *newGround = new Ground(Util::Math::Vector2D(positionX, -1));
        removeObject(ground.poll());
        ground.offer(newGround);
        addObject(newGround);
    }

}

void DinoGame::keyPressed(Util::Io::Key key) {
    switch (key.getScancode()) {
        case Util::Io::Key::ESC :
            Util::Game::GameManager::getGame().stop();
            break;

    }
}

void DinoGame::keyReleased(Util::Io::Key key) {}
