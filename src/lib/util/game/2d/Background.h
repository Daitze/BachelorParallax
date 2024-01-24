#ifndef BACHELORPARALLAX_BACKGROUND_H
#define BACHELORPARALLAX_BACKGROUND_H
#include "lib/util/collection/Array.h"
#include "Sprite.h"
namespace Util {
    namespace Game {
        class Graphics;
    }  // namespace Game
}  // namespace Util

namespace Util::Game::D2 {

    class Background {

    public:
        Background(const Graphics &graphics, const Array<Sprite> &sprites);
    private:

    };
}
#endif //BACHELORPARALLAX_BACKGROUND_H
