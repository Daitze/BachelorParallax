
#ifndef BACHELORPARALLAX_BACKGROUNDFAR_H
#define BACHELORPARALLAX_BACKGROUNDFAR_H
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

class BackgroundFar:public Util::Game::D2::Entity{

public:
    /**
     * Default Constructor.
     */
    explicit BackgroundFar(const Util::Math::Vector2D &position, double playerVelocity, double parallaxValue);

    /**
     * Copy Constructor.
     */
    BackgroundFar(const BackgroundFar &other) = delete;

    /**
     * Assignment operator.
     */
    BackgroundFar &operator=(const BackgroundFar &other) = delete;

    /**
     * Destructor.
     */
    ~BackgroundFar() override = default;

    void initialize() override;

    void onUpdate(double delta) override;

    void onTranslationEvent(Util::Game::D2::TranslationEvent &event) override;

    void onCollisionEvent(Util::Game::D2::CollisionEvent &event) override;

    void draw(Util::Game::Graphics &graphics) override;

    void setVelocity(double velocity);

    void setCameraPosition(double position);

    static const constexpr uint32_t TAG = 1;

private:

    double playerVelocity;
    double parallaxValue;
    double cameraPosition;
    Util::Game::D2::Sprite sprite;
    Util::Game::D2::Background layerOne;
};
#endif //BACHELORPARALLAX_BACKGROUNDFAR_H
