
#include "Ninja.h"

#include "lib/util/collection/Array.h"
#include "lib/util/game/Graphics.h"
#include "lib/util/game/2d/Sprite.h"
#include "lib/util/math/Vector2D.h"
#include "lib/util/game/2d/event/CollisionEvent.h"
#include "lib/util/game/2d/component/LinearMovementComponent.h"
#include "application/parallax/dino/Ground.h"
#include "lib/util/game/Collider.h"
#include "lib/util/game/2d/collider/RectangleCollider.h"
#include "lib/util/game/2d/event/TranslationEvent.h"
#include "lib/util/base/String.h"
#include "lib/util/graphic/Colors.h"
#include "lib/util/game/GameManager.h"

Ninja::Ninja(const Util::Math::Vector2D &position) : Util::Game::D2::Entity(TAG, position, Util::Game::D2::RectangleCollider(position, Util::Math::Vector2D(0.0, 0.0), Util::Game::Collider::STATIC)) {
    addComponent(new Util::Game::D2::LinearMovementComponent(*this));
}

void Ninja::initialize() {
    ninja = Util::Game::D2::Sprite("/initrd/ninja/run1.bmp",0.2, 0.2267);
}

void Ninja::onUpdate(double delta) {

}

void Ninja::draw(Util::Game::Graphics &graphics) {
   ninja.draw(graphics,getPosition());

}


void Ninja::onTranslationEvent(Util::Game::D2::TranslationEvent &event) {
}

void Ninja::onCollisionEvent(Util::Game::D2::CollisionEvent &event) {

}


