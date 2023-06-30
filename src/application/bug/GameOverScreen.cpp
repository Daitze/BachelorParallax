/*
 * Copyright (C) 2018-2022 Heinrich-Heine-Universitaet Duesseldorf,
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

#include "GameOverScreen.h"
#include "lib/util/graphic/Fonts.h"
#include "lib/util/game/Game.h"
#include "lib/util/game/GameManager.h"
#include "BugDefender.h"

GameOverScreen::GameOverScreen(bool won) : won(won) {
    setKeyListener(*this);
}

void GameOverScreen::update(double delta) {}

void GameOverScreen::initializeBackground(Util::Game::Graphics2D &graphics) {
    auto charWidth = ((Util::Graphic::Fonts::TERMINAL_FONT.getCharWidth()) / Util::Game::GameManager::getAbsoluteResolution().getX()) * 2;
    graphics.clear();
    graphics.setColor(Util::Graphic::Colors::WHITE);

    if (won) {
        graphics.drawString(Util::Math::Vector2D(-(16 * charWidth) / 2, 0.1), "Congratulations!");
        graphics.drawString(Util::Math::Vector2D(-(36 * charWidth) / 2, 0), "You have stopped the alien invasion!");
    } else {
        graphics.drawString(Util::Math::Vector2D(-(16 * charWidth) / 2, 0.1), "Oh noooooo!");
        graphics.drawString(Util::Math::Vector2D(-(39 * charWidth) / 2, 0), "Your planet has been invaded by aliens!");
    }

    graphics.drawString(Util::Math::Vector2D(-(70 * charWidth) / 2, -0.75), "Press SPACE to fight the next invasion, or ESC to run like a coward...");
}

void GameOverScreen::keyPressed(Util::Io::Key key) {
    switch (key.getScancode()) {
        case (Util::Io::Key::ESC) :
            Util::Game::GameManager::getGame().stop();
            break;
        case (Util::Io::Key::SPACE) :
            auto &game = Util::Game::GameManager::getGame();
            game.pushScene(new BugDefender());
            game.switchToNextScene();
    }
}

void GameOverScreen::keyReleased(Util::Io::Key key) {}