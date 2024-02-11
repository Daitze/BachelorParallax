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
#include "application/parallax/ninja/Backgroundtwo.h"
#include "lib/util/collection/Array.h"
#include "algorithm"

NinjaGame::NinjaGame() {
    //ninjalist.offer(ninja);


    for (uint32_t i = 0; i < 4; i++) {
        auto *newGround = new Ground(Util::Math::Vector2D( - 1.5 + i, -1));
        addObject(newGround);
    }

//    auto *backgroundt = new Backgroundtwo(Util::Math::Vector2D(0.6, -0.8));
//    backgroundw.offer(backgroundt);
//    addObject(backgroundt);
//
//    auto *background = new Backgroundone(Util::Math::Vector2D(0.6, -0.8));
//    backgroundq.offer(background);
//    addObject(background);

    setKeyListener(*this);
}

void NinjaGame::initializeBackground(Util::Game::Graphics &graphics) {
    graphics.clear(Util::Graphic::Color(57, 97, 255));
//    auto array = Util::Array<Util::Game::D2::Sprite>({
//        Util::Game::D2::Sprite("/initrd/dino/saw1.bmp",1, 2, Util::Math::Vector2D(0.5, -0.9, 2)),
//        Util::Game::D2::Sprite("/initrd/dino/cloud3.bmp",0.6, 0.15, Util::Math::Vector2D(0.5, 0.7, 1))})
//    auto background = new Backgroundone(graphics,array);
//    addObject(background);

//    Util::Game::D2::Background(graphics,Util::Array<Util::Game::D2::Sprite>({
//        Util::Game::D2::Sprite("/initrd/dino/treefar.bmp", 1, 2, Util::Math::Vector2D(X, -0.9,1)),
//        Util::Game::D2::Sprite("/initrd/dino/cloud3.bmp", 0.6, 0.15, Util::Math::Vector2D(0.65, 0.7,1)),
//        Util::Game::D2::Sprite("/initrd/dino/cloud4.bmp", 0.45, 0.15, Util::Math::Vector2D(0.65, 0.7,3))
//    }));
    background = new Backgroundone(Util::Math::Vector2D(0,0), right,left, 0.01);
    addObject(background);
    addObject(ninja);
}

void NinjaGame::update(double delta) {
    background->setKeyboard(right,left);
//    auto *background = new Backgroundone(Util::Math::Vector2D(0,0),left);
//    removeObject(backgroundq.poll());
//    backgroundq.offer(background);
//    addObject(background);

//    if(left == true){
//        auto startX = backgroundq.peek()->getPosition().getX();
//        auto *background = new Backgroundone(Util::Math::Vector2D(startX+0.001,-0.8));
//        removeObject(backgroundq.poll());
//        backgroundq.offer(background);
//        addObject(background);
//
//        auto start2X = backgroundw.peek()->getPosition().getX();
//        auto *backgroundt = new Backgroundtwo(Util::Math::Vector2D(start2X+0.01,-0.8));
//        removeObject(backgroundw.poll());
//        backgroundw.offer(backgroundt);
//        addObject(backgroundt);
//    }
//    if(right == true){
//        auto startX = backgroundq.peek()->getPosition().getX();
//        auto *background = new Backgroundone(Util::Math::Vector2D(startX - 0.001,-0.8));
//        removeObject(backgroundq.poll());
//        backgroundq.offer(background);
//        addObject(background);
//
//        auto start2X = backgroundw.peek()->getPosition().getX();
//        auto *backgroundt = new Backgroundtwo(Util::Math::Vector2D(start2X - 0.01,-0.8));
//        removeObject(backgroundw.poll());
//        backgroundw.offer(backgroundt);
//        addObject(backgroundt);
//    }
//    if(left == true) {
//        //ninja->setVelocityX(-0.25);
//        auto newPosition = ninjalist.peek()->getPosition().getX();
//        auto *ninjan = new Ninja(Util::Math::Vector2D(newPosition-0.01,-0.8));
//        removeObject(ninjalist.poll());
//        ninjalist.offer(ninjan);
//        addObject(ninjan);
//    }else if (right == true){
//        //ninja->setVelocityX(0.25);
//        auto newPosition = ninjalist.peek()->getPosition().getX();
//        auto *ninjan = new Ninja(Util::Math::Vector2D(newPosition+0.01,-0.8));
//        removeObject(ninjalist.poll());
//        ninjalist.offer(ninjan);
//        addObject(ninjan);
//    }
}

void NinjaGame::keyPressed(Util::Io::Key key) {
    switch (key.getScancode()) {
        case Util::Io::Key::ESC :
            Util::Game::GameManager::getGame().stop();
            break;
        case Util::Io::Key::LEFT :
            left = true;
            ninja->setVelocityX(-1);
            break;
        case Util::Io::Key::RIGHT :
            right = true;
            ninja->setVelocityX(1);
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
            left = false;
            break;
        case Util::Io::Key::RIGHT:
            if (ninja->getVelocity().getX() > 0) {
                ninja->setVelocityX(0);
            }
            right = false;
            break;
        default:
            break;
    }
}
