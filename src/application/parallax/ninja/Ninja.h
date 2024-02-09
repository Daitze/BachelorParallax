
#ifndef BACHELORPARALLAX_NINJA_H
#define BACHELORPARALLAX_NINJA_H
#include <cstdint>

#include "lib/util/game/2d/SpriteAnimation.h"
#include "lib/util/game/2d/Entity.h"

namespace Util {
    namespace Math {
        class Vector2D;
    }  // namespace Math

    namespace Game {
        class Graphics;
        namespace D2 {
            class CollisionEvent;
            class TranslationEvent;
        }  // namespace D2
    }  // namespace Game
}  // namespace Util

class Ninja : public Util::Game::D2::Entity {

public:
    /**
     * Default Constructor.
     */
    explicit Ninja(const Util::Math::Vector2D &position);

    /**
     * Copy Constructor.
     */
    Ninja(const Ninja &other) = delete;

    /**
     * Assignment operator.
     */
    Ninja &operator=(const Ninja &other) = delete;

    /**
     * Destructor.
     */
    ~Ninja() override = default;

    void initialize() override;

    void onUpdate(double delta) override;


    void onTranslationEvent(Util::Game::D2::TranslationEvent &event) override;

    void onCollisionEvent(Util::Game::D2::CollisionEvent &event) override;

    void draw(Util::Game::Graphics &graphics) override;

    static const constexpr uint32_t TAG = 0;

private:

    bool onGround = false;

    double time = 0;
    Util::Game::D2::Sprite ninja;

};
#endif //BACHELORPARALLAX_NINJA_H
