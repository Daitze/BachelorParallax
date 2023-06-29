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

#include "Ship.h"
#include "lib/util/game/GameManager.h"
#include "lib/util/game/Game.h"
#include "PlayerMissile.h"
#include "lib/util/game/entity/component/LinearMovementComponent.h"
#include "lib/util/game/entity/event//TranslationEvent.h"

Ship::Ship(const Util::Math::Vector2D &position) : Util::Game::Entity(TAG, position, Util::Game::RectangleCollider(position, Util::Game::Collider::STATIC, SIZE_X, SIZE_Y)) {
    addComponent(new Util::Game::LinearMovementComponent(*this));
}

void Ship::initialize() {
    sprite = Util::Game::Sprite("/initrd/bug/ship.bmp", SIZE_X, SIZE_Y);
}

void Ship::onUpdate(double delta) {}

void Ship::onTranslationEvent(Util::Game::TranslationEvent &event) {}

void Ship::onCollisionEvent(Util::Game::CollisionEvent &event) {

}

void Ship::draw(Util::Game::Graphics2D &graphics) {
    graphics.drawImage(getPosition(), sprite.getImage());
}

void Ship::fireMissile() {
    if (!mayFireMissile) {
        return;
    }

    mayFireMissile = false;
    auto *missile = new PlayerMissile(getPosition() + Util::Math::Vector2D((SIZE_X / 2) + (PlayerMissile::SIZE_X / 2), SIZE_Y), *this);
    Util::Game::GameManager::getCurrentScene().addObject(missile);
    missile->setVelocityY(2.5);
}

void Ship::allowFireMissile() {
    mayFireMissile = true;
}