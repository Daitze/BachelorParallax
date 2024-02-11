
#include "BackgroundOne.h"

#include "lib/util/game/Graphics.h"
#include "lib/util/game/Collider.h"
#include "lib/util/game/2d/collider/RectangleCollider.h"
#include "lib/util/game/2d/event/TranslationEvent.h"
#include "lib/util/math/Vector2D.h"
#include "lib/util/game/2d/Background.h"

namespace Util {
    namespace Game {
        namespace D2 {
            class CollisionEvent;
        }  // namespace D2
    }  // namespace Game
}  // namespace Util

BackgroundOne::BackgroundOne(const Util::Math::Vector2D &position, double playerVelocity, double parallaxValue):Util::Game::D2::Entity(TAG, position, Util::Game::D2::RectangleCollider(position, Util::Math::Vector2D(0.0, 0.0), Util::Game::Collider::STATIC)),playerVelocity(playerVelocity), parallaxValue(parallaxValue) {
}

void BackgroundOne::initialize() {
    layerOne = Util::Game::D2::Background(Util::Array<Util::Game::D2::Sprite>({
        Util::Game::D2::Sprite("/initrd/dino/cloud1.bmp", 0.6, 0.15, Util::Math::Vector2D(-0.6, 0.7)),
        Util::Game::D2::Sprite("/initrd/dino/cloud2.bmp", 0.6, 0.15, Util::Math::Vector2D(0.8, 0.7)),
        Util::Game::D2::Sprite("/initrd/dino/cloud3.bmp", 0.6, 0.15, Util::Math::Vector2D(0.0, 0.7)),
        Util::Game::D2::Sprite("/initrd/parallax/tree.bmp", 0.8, 1, Util::Math::Vector2D(-0.3, -0.85)),
        Util::Game::D2::Sprite("/initrd/parallax/tree.bmp", 0.8, 1, Util::Math::Vector2D(0.6, -0.85)),
        Util::Game::D2::Sprite("/initrd/parallax/tree.bmp", 0.8, 1, Util::Math::Vector2D(-2, -0.85)),
        Util::Game::D2::Sprite("/initrd/parallax/tree.bmp", 0.8, 1, Util::Math::Vector2D(2, -0.85))
    }),playerVelocity,parallaxValue);
}

void BackgroundOne::onUpdate(double delta) {
    layerOne.setVelocity(playerVelocity);
    layerOne.update(delta);
}
void BackgroundOne::onTranslationEvent(Util::Game::D2::TranslationEvent &event) {
    if (playerVelocity == 0) {
        event.cancel();
    }
}

void BackgroundOne::onCollisionEvent(Util::Game::D2::CollisionEvent &event) {}

void BackgroundOne::draw(Util::Game::Graphics &graphics) {
    layerOne.draw(graphics);
}

void BackgroundOne::setVelocity(double velocity) {
    playerVelocity = velocity;
}


