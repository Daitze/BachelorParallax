
#ifndef BACHELORPARALLAX_BACKGROUNDTWO_H
#define BACHELORPARALLAX_BACKGROUNDTWO_H
#include <cstdint>

#include "lib/util/game/2d/Entity.h"
#include "lib/util/game/2d/Sprite.h"


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

class Backgroundtwo : public Util::Game::D2::Entity {

public:
    /**
     * Default Constructor.
     */
    explicit Backgroundtwo(const Util::Math::Vector2D &position);

    /**
     * Copy Constructor.
     */
    Backgroundtwo(const Backgroundtwo &other) = delete;

    /**
     * Assignment operator.
     */
    Backgroundtwo &operator=(const Backgroundtwo &other) = delete;

    /**
     * Destructor.
     */
    ~Backgroundtwo() override = default;

    void initialize() override;

    void onUpdate(double delta) override;

    void onTranslationEvent(Util::Game::D2::TranslationEvent &event) override;

    void onCollisionEvent(Util::Game::D2::CollisionEvent &event) override;

    void draw(Util::Game::Graphics &graphics) override;

    static const constexpr uint32_t TAG = 1;

private:

    Util::Game::D2::Sprite sprite;
};
#endif //BACHELORPARALLAX_BACKGROUNDTWO_H
