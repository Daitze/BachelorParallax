#ifndef BACHELORPARALLAX_BACKGROUND_H
#define BACHELORPARALLAX_BACKGROUND_H

#include "lib/util/collection/Array.h"
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
        Background();

        Background(const Array<Sprite> &sprites, bool right,bool left, double parallaxValue);

        void update(double delta);

        void draw(const Graphics &graphics);

        void setKeyboard(bool right,bool left);
    private:
        Array<Sprite> spriteList;
        bool leftKey;
        bool rightKey;
        double parallaxValue;
    };
}
#endif //BACHELORPARALLAX_BACKGROUND_H
