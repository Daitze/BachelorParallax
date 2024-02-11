#ifndef BACHELORPARALLAX_BACKGROUNDONE_H
#define BACHELORPARALLAX_BACKGROUNDONE_H
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
    namespace Io {
        class Key;
    }  // namespace Io
}  // namespace Util

class BackgroundOne:public Util::Game::D2::Entity{

public:
    /**
     * Default Constructor.
     */
    explicit BackgroundOne(const Util::Math::Vector2D &position, double playerVelocity, double parallaxValue);

    /**
     * Copy Constructor.
     */
    BackgroundOne(const BackgroundOne &other) = delete;

    /**
     * Assignment operator.
     */
    BackgroundOne &operator=(const BackgroundOne &other) = delete;

    /**
     * Destructor.
     */
    ~BackgroundOne() override = default;

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
#endif //BACHELORPARALLAX_BACKGROUNDONE_H
