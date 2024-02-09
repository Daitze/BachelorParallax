#include "Backgroundone.h"

#include "lib/util/game/Graphics.h"
#include "lib/util/game/Collider.h"
#include "lib/util/game/2d/collider/RectangleCollider.h"
#include "lib/util/game/2d/event/TranslationEvent.h"
#include "lib/util/graphic/Colors.h"
#include "lib/util/math/Vector2D.h"

namespace Util {
    namespace Game {
        namespace D2 {
            class CollisionEvent;
        }  // namespace D2
    }  // namespace Game
}  // namespace Util

Backgroundone::Backgroundone(const Util::Math::Vector2D &position) : Util::Game::D2::Entity(TAG, position, Util::Game::D2::RectangleCollider(position, Util::Math::Vector2D(0.0, 0.0), Util::Game::Collider::STATIC)){}

void Backgroundone::initialize() {
    sprite = Util::Game::D2::Sprite("/initrd/dino/cloud1.bmp", 0.6, 0.15);
}

void Backgroundone::onUpdate(double delta) {

}

void Backgroundone::onTranslationEvent(Util::Game::D2::TranslationEvent &event) {
}

void Backgroundone::onCollisionEvent(Util::Game::D2::CollisionEvent &event) {}

void Backgroundone::draw(Util::Game::Graphics &graphics) {
    sprite.draw(graphics,Util::Math::Vector2D(getPosition().getX(),getPosition().getY()));
}
