
#ifndef BACHELORPARALLAX_BACKGROUNDTWO_H
#define BACHELORPARALLAX_BACKGROUNDTWO_H
#include <cstdint>

#include "lib/util/game/2d/Entity.h"
#include "lib/util/game/2d/Sprite.h"
#include "lib/util/game/2d/Background.h"

namespace Util {
    namespace Game {
        class Graphics;
        namespace D2 {
            class CollisionEvent;
            class TranslationEvent;
        }  // namespace D2
    }  // namespace Game
    namespace Math {
        class Vector2D;
    }  // namespace Math
}  // namespace Util

class BackgroundTwo : public Util::Game::D2::Entity {

public:
    /**
     * Default Constructor.
     */
    explicit BackgroundTwo(const Util::Math::Vector2D &position, double playerVelocity, double parallaxValue);

    /**
     * Copy Constructor.
     */
    BackgroundTwo(const BackgroundTwo &other) = delete;

    /**
     * Assignment operator.
     */
    BackgroundTwo &operator=(const BackgroundTwo &other) = delete;

    /**
     * Destructor.
     */
    ~BackgroundTwo() override = default;

    void initialize() override;

    void onUpdate(double delta) override;

    void onTranslationEvent(Util::Game::D2::TranslationEvent &event) override;

    void onCollisionEvent(Util::Game::D2::CollisionEvent &event) override;

    void draw(Util::Game::Graphics &graphics) override;

    void setVelocity(double velocity);

    static const constexpr uint32_t TAG = 1;

private:
    double playerVelocity;
    double parallaxValue;
    Util::Game::D2::Background layerOne;
};
#endif //BACHELORPARALLAX_BACKGROUNDTWO_H
