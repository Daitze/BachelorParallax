
#ifndef BACHELORPARALLAX_NINJAGAME_H
#define BACHELORPARALLAX_NINJAGAME_H

#include "lib/util/game/KeyListener.h"
#include "lib/util/collection/ArrayBlockingQueue.h"
#include "application/parallax/dino/Ground.h"
#include "Ninja.h"
#include "lib/util/math/Random.h"
#include "lib/util/collection/ArrayList.h"
#include "lib/util/math/Vector2D.h"
#include "lib/util/game/2d/Scene.h"
#include "application/parallax/ninja/Backgroundone.h"

namespace Util {
    namespace Game {
        class Graphics;
    }  // namespace Game

    namespace Io {
        class Key;
    }  // namespace Io
}  // namespace Util

class NinjaGame : public Util::Game::D2::Scene, public Util::Game::KeyListener {

public:
    /**
     * Default Constructor.
     */
    NinjaGame();

    /**
     * Copy Constructor.
     */
    NinjaGame(const NinjaGame &other) = delete;

    /**
     * Assignment operator.
     */
    NinjaGame &operator=(const NinjaGame &other) = delete;

    /**
     * Destructor.
     */
    ~NinjaGame() override = default;

    void update(double delta) override;

    void initializeBackground(Util::Game::Graphics &graphics) override;

    void keyPressed(Util::Io::Key key) override;

    void keyReleased(Util::Io::Key key) override;

private:

    Ninja *ninja = new Ninja(Util::Math::Vector2D(-0.1414, -0.8));
    Util::ArrayBlockingQueue<Backgroundone*> backgroundq = Util::ArrayBlockingQueue<Backgroundone*>(2);

};
#endif //BACHELORPARALLAX_NINJAGAME_H
