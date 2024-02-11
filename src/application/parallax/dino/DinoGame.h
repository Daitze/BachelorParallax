#ifndef HHUOS_DINOGAME_H
#define HHUOS_DINOGAME_H

#include "lib/util/game/KeyListener.h"
#include "lib/util/collection/ArrayBlockingQueue.h"
#include "Ground.h"
#include "Dino.h"
#include "lib/util/math/Random.h"
#include "lib/util/collection/ArrayList.h"
#include "lib/util/math/Vector2D.h"
#include "lib/util/game/2d/Scene.h"
#include "lib/util/game/2d/Background.h"
#include "application/parallax/dino/BackgroundFar.h"

namespace Util {
namespace Game {
class Graphics;
}  // namespace Game

namespace Io {
class Key;
}  // namespace Io
}  // namespace Util

class DinoGame : public Util::Game::D2::Scene, public Util::Game::KeyListener {

public:
    /**
     * Default Constructor.
     */
    DinoGame();

    /**
     * Copy Constructor.
     */
    DinoGame(const DinoGame &other) = delete;

    /**
     * Assignment operator.
     */
    DinoGame &operator=(const DinoGame &other) = delete;

    /**
     * Destructor.
     */
    ~DinoGame() override = default;

    void update(double delta) override;

    void initializeBackground(Util::Game::Graphics &graphics) override;

    void keyPressed(Util::Io::Key key) override;

    void keyReleased(Util::Io::Key key) override;

private:

    Dino *dino = new Dino(Util::Math::Vector2D(-0.8, 0));

    Util::ArrayBlockingQueue<Ground*> ground = Util::ArrayBlockingQueue<Ground*>(4);
    double currentVelocity = START_VELOCITY;
    static const constexpr double START_VELOCITY = 0.25;
    BackgroundFar *background;

};

#endif
