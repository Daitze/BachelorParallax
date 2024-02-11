#include "NinjaGame.h"

#include <cstdint>

#include "application/parallax/ninja//Ninja.h"
#include "lib/util/io/key/Key.h"
#include "lib/util/game/Camera.h"
#include "lib/util/game/2d/component/LinearMovementComponent.h"
#include "lib/util/game/2d/component/GravityComponent.h"
#include "lib/util/game/GameManager.h"
#include "application/parallax/dino/Ground.h"
#include "lib/util/game/Game.h"
#include "lib/util/game/Graphics.h"
#include "lib/util/game/2d/Sprite.h"
#include "lib/util/graphic/Color.h"
#include "lib/util/math/Vector2D.h"
#include "lib/util/collection/Iterator.h"
#include "lib/util/math/Vector3D.h"
#include "lib/util/game/2d/Background.h"
#include "application/parallax/ninja/BackgroundOne.h"
#include "application/parallax/ninja/BackgroundTwo.h"
#include "lib/util/collection/Array.h"
#include "algorithm"

NinjaGame::NinjaGame() {
    for (uint32_t i = 0; i < 4; i++) {
        auto *newGround = new Ground(Util::Math::Vector2D( - 1.5 + i, -1));
        addObject(newGround);
    }
    setKeyListener(*this);
}

void NinjaGame::initializeBackground(Util::Game::Graphics &graphics) {
    graphics.clear(Util::Graphic::Color(57, 97, 255));

    backgroundOne = new BackgroundOne(Util::Math::Vector2D(0,0), ninja->getVelocity().getX(), 0.004);
    backgroundTwo = new BackgroundTwo(Util::Math::Vector2D(0,0), ninja->getVelocity().getX(), 0.009);
    addObject(backgroundOne);
    addObject(backgroundTwo);
    addObject(ninja);


}

void NinjaGame::update(double delta) {
    backgroundOne->setVelocity(ninja->getVelocity().getX());
    backgroundTwo->setVelocity(ninja->getVelocity().getX());

    getCamera().setPosition(Util::Math::Vector2D(ninja->getPosition().getX(), 0));
}

void NinjaGame::keyPressed(Util::Io::Key key) {
    switch (key.getScancode()) {
        case Util::Io::Key::ESC :
            Util::Game::GameManager::getGame().stop();
            break;
        case Util::Io::Key::LEFT :
            ninja->setVelocityX(-0.5);
            break;
        case Util::Io::Key::RIGHT :
            ninja->setVelocityX(0.5);
            break;
        default:
            break;
    }
}

void NinjaGame::keyReleased(Util::Io::Key key) {
    switch (key.getScancode()) {
        case Util::Io::Key::LEFT:
            if (ninja->getVelocity().getX() < 0) {
                ninja->setVelocityX(0);
            }
            break;
        case Util::Io::Key::RIGHT:
            if (ninja->getVelocity().getX() > 0) {
                ninja->setVelocityX(0);
            }
            break;
        default:
            break;
    }
}
