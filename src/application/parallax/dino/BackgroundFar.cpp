#include "BackgroundFar.h"
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

BackgroundFar::BackgroundFar(const Util::Math::Vector2D &position, double playerVelocity, double parallaxValue):Util::Game::D2::Entity(TAG, position, Util::Game::D2::RectangleCollider(position, Util::Math::Vector2D(0.0, 0.0), Util::Game::Collider::STATIC)),playerVelocity(playerVelocity), parallaxValue(parallaxValue) {
}

void BackgroundFar::initialize() {
    layerOne = Util::Game::D2::Background(Util::Array<Util::Game::D2::Sprite>({
        Util::Game::D2::Sprite("/initrd/parallax/tree.bmp", 0.8, 1, Util::Math::Vector2D(-1.5, -0.85)),
        Util::Game::D2::Sprite("/initrd/parallax/tree.bmp", 0.8, 1, Util::Math::Vector2D(-0.5, -0.85)),
        Util::Game::D2::Sprite("/initrd/parallax/tree.bmp", 0.8, 1, Util::Math::Vector2D(0.5, -0.85)),
        Util::Game::D2::Sprite("/initrd/parallax/tree.bmp", 0.8, 1, Util::Math::Vector2D(1.5, -0.85)),
        Util::Game::D2::Sprite("/initrd/parallax/tree.bmp", 0.8, 1, Util::Math::Vector2D(-2, -0.85)),
        Util::Game::D2::Sprite("/initrd/parallax/tree.bmp", 0.8, 1, Util::Math::Vector2D(2, -0.85))
    }),getPosition().getX(),playerVelocity,parallaxValue);
}

void BackgroundFar::onUpdate(double delta) {
    layerOne.setVelocity(playerVelocity);
    layerOne.setCameraPosition(cameraPosition);
    layerOne.update(delta);

}
void BackgroundFar::onTranslationEvent(Util::Game::D2::TranslationEvent &event) {
    if (playerVelocity == 0) {
        event.cancel();
    }
}

void BackgroundFar::onCollisionEvent(Util::Game::D2::CollisionEvent &event) {}

void BackgroundFar::draw(Util::Game::Graphics &graphics) {
    layerOne.draw(graphics);
}

void BackgroundFar::setVelocity(double velocity) {
    playerVelocity = velocity;
}

void BackgroundFar::setCameraPosition(double position){
    cameraPosition = position;
}