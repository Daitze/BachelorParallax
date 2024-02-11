#ifndef BACHELORPARALLAX_BACKGROUND_H
#define BACHELORPARALLAX_BACKGROUND_H

#include "lib/util/collection/ArrayList.h"
#include "lib/util/game/2d/Sprite.h"
#include "lib/util/game/Camera.h"
#include "lib/util/game/Scene.h"
#include "lib/util/game/2d/Entity.h"

namespace Util {
    namespace Game {
        class Graphics;
    }  // namespace Game
}  // namespace Util

namespace Util::Game::D2 {
    class Background{

    public:
        /**
        * Constructor.
        */
        Background();
        /**
        * Constructor.
        */
        Background(const Array<Sprite> &sprites, double playerVelocity, double parallaxValue);
        /**
        * Constructor.
        */
        Background(const Array<Sprite> &sprites, double cameraPosition, double playerVelocity, double parallaxValue);


        void update(double delta);

        void draw(const Graphics &graphics);

        void setVelocity(double velocity);

        void setCameraPosition(double position);

    private:
        Array<Sprite> spriteList;
        Array<Sprite> newSpriteList;
        double playerVelocity;

        double parallaxValue;
        double cameraPosition;
    };
}
#endif //BACHELORPARALLAX_BACKGROUND_H
