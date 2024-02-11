#include "Backgroundtwo.h"

#include "lib/util/game/Graphics.h"
#include "lib/util/game/Collider.h"
#include "lib/util/game/2d/collider/RectangleCollider.h"
#include "lib/util/game/2d/event/TranslationEvent.h"
#include "lib/util/graphic/Colors.h"
#include "lib/util/math/Vector2D.h"
#include "lib/util/game/2d/Background.h"
#include "lib/util/game/Game.h"

namespace Util {
    namespace Game {
        namespace D2 {
            class CollisionEvent;
        }  // namespace D2
    }  // namespace Game
}  // namespace Util

Backgroundtwo::Backgroundtwo(const Util::Math::Vector2D &position) : Util::Game::D2::Entity(TAG, position, Util::Game::D2::RectangleCollider(position, Util::Math::Vector2D(0.0, 0.0), Util::Game::Collider::STATIC)){}

void Backgroundtwo::initialize() {
    sprite = Util::Game::D2::Sprite("/initrd/dino/cloud1.bmp", 0.6, 0.15);
}

void Backgroundtwo::onUpdate(double delta) {

}

void Backgroundtwo::onTranslationEvent(Util::Game::D2::TranslationEvent &event) {
}

void Backgroundtwo::onCollisionEvent(Util::Game::D2::CollisionEvent &event) {}

void Backgroundtwo::draw(Util::Game::Graphics &graphics) {
    sprite.draw(graphics,Util::Math::Vector2D(getPosition().getX(),getPosition().getY()));
//    Util::Game::D2::Background(graphics,Util::Array<Util::Game::D2::Sprite>({
//        Util::Game::D2::Sprite("/initrd/dino/treefar.bmp", 1, 2, Util::Math::Vector2D(0.5, -0.9,1)),
//        Util::Game::D2::Sprite("/initrd/dino/cloud3.bmp", 0.6, 0.15, Util::Math::Vector2D(0.65, 0.7,1)),
//        Util::Game::D2::Sprite("/initrd/dino/cloud4.bmp", 0.45, 0.15, Util::Math::Vector2D(0.65, 0.7,3))
//    }));
}
