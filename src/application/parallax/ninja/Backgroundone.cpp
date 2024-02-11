
#include "Backgroundone.h"

#include "lib/util/game/Graphics.h"
#include "lib/util/game/Collider.h"
#include "lib/util/game/2d/collider/RectangleCollider.h"
#include "lib/util/game/2d/event/TranslationEvent.h"
#include "lib/util/graphic/Colors.h"
#include "lib/util/math/Vector2D.h"
#include "lib/util/game/2d/Background.h"
#include "lib/util/io/key/Key.h"
#include "lib/util/game/KeyListener.h"
#include "lib/util/game/GameManager.h"


namespace Util {
    namespace Game {
        namespace D2 {
            class CollisionEvent;
        }  // namespace D2
    }  // namespace Game
}  // namespace Util

Backgroundone::Backgroundone(const Util::Math::Vector2D &position, bool right, bool left, double parallaxValue):Util::Game::D2::Entity(TAG, position, Util::Game::D2::RectangleCollider(position, Util::Math::Vector2D(0.0, 0.0), Util::Game::Collider::STATIC)),rightKey(right),leftKey(left), parallaxValue(parallaxValue) {
}

void Backgroundone::initialize() {
    layerOne = Util::Game::D2::Background(Util::Array<Util::Game::D2::Sprite>({
        Util::Game::D2::Sprite("/initrd/dino/treefar.bmp", 1, 2, Util::Math::Vector2D(-1.5, -0.8)),
        Util::Game::D2::Sprite("/initrd/dino/treefar.bmp", 1, 2, Util::Math::Vector2D(-0.5, -0.8)),
        Util::Game::D2::Sprite("/initrd/dino/treefar.bmp", 1, 2, Util::Math::Vector2D(0.5, -0.8))
    }),rightKey,leftKey,parallaxValue);
}

void Backgroundone::onUpdate(double delta) {
//    if(left == true){
//        layerOne.setKeyboard(true);
//    }else if(right == true){
//        layerOne.setKeyboard(true);
//    } else{
//        layerOne.setKeyboard(false);
//    }
    //layerOne.setKeyboard(keyboard);
    layerOne.setKeyboard(rightKey,leftKey);
    layerOne.update(delta);
}
void Backgroundone::onTranslationEvent(Util::Game::D2::TranslationEvent &event) {
    const auto targetX = event.getTargetPosition().getX();
    const auto maxX = Util::Game::GameManager::getRelativeResolution().getX();

    if (targetX > maxX || targetX < -maxX) {
        event.cancel();
    }
}

void Backgroundone::onCollisionEvent(Util::Game::D2::CollisionEvent &event) {}

void Backgroundone::draw(Util::Game::Graphics &graphics) {
    layerOne.draw(graphics);
}

void Backgroundone::setKeyboard(bool right, bool left) {
    rightKey = right;
    leftKey = left;
}


