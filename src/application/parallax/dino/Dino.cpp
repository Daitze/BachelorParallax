#include "Dino.h"

#include "lib/util/collection/Array.h"
#include "lib/util/game/Graphics.h"
#include "lib/util/game/2d/Sprite.h"
#include "lib/util/math/Vector2D.h"
#include "lib/util/game/2d/event/CollisionEvent.h"
#include "Ground.h"
#include "lib/util/game/Collider.h"
#include "lib/util/game/2d/collider/RectangleCollider.h"
#include "lib/util/game/2d/event/TranslationEvent.h"


Dino::Dino(const Util::Math::Vector2D &position) : Util::Game::D2::Entity(TAG, position, Util::Game::D2::RectangleCollider(position, Util::Math::Vector2D(0.2, 0.2), Util::Game::Collider::DYNAMIC)) {}

void Dino::initialize() {
    runAnimation = Util::Game::D2::SpriteAnimation(Util::Array<Util::Game::D2::Sprite>({
        Util::Game::D2::Sprite("/initrd/dino/run1.bmp", 0.2, 0.2267, Util::Math::Vector2D(0,0,0)),
        Util::Game::D2::Sprite("/initrd/dino/run2.bmp", 0.2, 0.2267, Util::Math::Vector2D(0,0,0)),
        Util::Game::D2::Sprite("/initrd/dino/run3.bmp", 0.2, 0.2267, Util::Math::Vector2D(0,0,0)),
        Util::Game::D2::Sprite("/initrd/dino/run4.bmp", 0.2, 0.2267, Util::Math::Vector2D(0,0,0)),
        Util::Game::D2::Sprite("/initrd/dino/run5.bmp", 0.2, 0.2267, Util::Math::Vector2D(0,0,0)),
        Util::Game::D2::Sprite("/initrd/dino/run6.bmp", 0.2, 0.2267, Util::Math::Vector2D(0,0,0))}), 0.5);
}


void Dino::onUpdate(double delta) {
    currentAnimation = &runAnimation;
}

void Dino::draw(Util::Game::Graphics &graphics) {
    currentAnimation->draw(graphics, getPosition());
}


void Dino::onTranslationEvent(Util::Game::D2::TranslationEvent &event) {

}

void Dino::onCollisionEvent(Util::Game::D2::CollisionEvent &event) {

}


