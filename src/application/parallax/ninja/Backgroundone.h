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

class Backgroundone:public Util::Game::D2::Entity{

public:
    /**
     * Default Constructor.
     */
    explicit Backgroundone(const Util::Math::Vector2D &position, bool right,bool left, double parallaxValue);

    /**
     * Copy Constructor.
     */
    Backgroundone(const Backgroundone &other) = delete;

    /**
     * Assignment operator.
     */
    Backgroundone &operator=(const Backgroundone &other) = delete;

    /**
     * Destructor.
     */
    ~Backgroundone() override = default;

    void initialize() override;

    void onUpdate(double delta) override;

    void onTranslationEvent(Util::Game::D2::TranslationEvent &event) override;

    void onCollisionEvent(Util::Game::D2::CollisionEvent &event) override;

    void draw(Util::Game::Graphics &graphics) override;

    void setKeyboard(bool right,bool left);

    static const constexpr uint32_t TAG = 1;

private:
    bool leftKey;
    bool rightKey;
    double parallaxValue;
    Util::Game::D2::Sprite sprite;
    Util::Game::D2::Background layerOne;
};
#endif //BACHELORPARALLAX_BACKGROUNDONE_H
