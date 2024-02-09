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
#include "application/parallax/ninja/Backgroundone.h"


NinjaGame::NinjaGame() {
    //ninja->addComponent(new Util::Game::D2::LinearMovementComponent(*ninja));
    //ninja->addComponent(new Util::Game::D2::GravityComponent(*ninja, 1.25, 0));
    addObject(ninja);

    for (uint32_t i = 0; i < 4; i++) {
        auto *newGround = new Ground(Util::Math::Vector2D( - 1.5 + i, -1));
        addObject(newGround);
    }

    auto *background = new Backgroundone(Util::Math::Vector2D(0.6, 0.7));
    backgroundq.offer(background);
    addObject(background);

    setKeyListener(*this);
}

void NinjaGame::initializeBackground(Util::Game::Graphics &graphics) {
    graphics.clear(Util::Graphic::Color(57, 97, 255));

    /*Util::Game::D2::Background(graphics,Util::Array<Util::Game::D2::Sprite>({
        Util::Game::D2::Sprite("/initrd/dino/treefar.bmp", 1, 2, Util::Math::Vector2D(ninja -> getPosition().getX()-0.1, -0.9,2)),
        Util::Game::D2::Sprite("/initrd/dino/cloud3.bmp", 0.6, 0.15, Util::Math::Vector2D(ninja -> getPosition().getX()-0.2, 0.7,1)),
    }));*/
}

void NinjaGame::update(double delta) {

    auto *background = new Backgroundone(Util::Math::Vector2D(ninja->getPosition().getX(),0.7));
    removeObject(backgroundq.poll());
    backgroundq.offer(background);
    addObject(background);
}

void NinjaGame::keyPressed(Util::Io::Key key) {
    switch (key.getScancode()) {
        case Util::Io::Key::ESC :
            Util::Game::GameManager::getGame().stop();
            break;
        case Util::Io::Key::LEFT :
            ninja->setVelocityX(-1.0);

            break;
        case Util::Io::Key::RIGHT :
            ninja->setVelocityX(1.0);
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
