#include "Background.h"
#include "algorithm"
#include "Sprite.h"
#include "lib/util/collection/Array.h"
#include "lib/util/game/Camera.h"
#include "lib/util/game/Scene.h"
namespace Util::Game::D2 {
    Background::Background(const Graphics &graphics, const Array<Sprite> &sprites){
        auto list = sprites;
        int len = list.length();
        /*std::sort(std::begin(sprites),std::end(sprites),[](Sprite &sp1, Sprite &sp2){
            return sp1.getPosition().getLayerPosition()>sp2.getPosition().getLayerPosition();}
            );*/
        //Sort List by Descending LayerPosition. For back to front drawing.
        for (int m = 0; m <= len-1; m++){
            for (int n = 0; n < len - 1 - m; ++n) {
                if(list[n].getPosition().getLayerPosition() < list[n+1].getPosition().getLayerPosition()){
                    auto temp = list[n];
                    list[n] = list[n+1];
                    list[n+1] = temp;
                }
            }
        }
        for (int i = 0; i <= len-1; ++i) {
            /*if(list[i].getPosition().getLayerPosition() == 1) {
                auto newX = list[i].getPosition().getX() + 0.5;
                auto newPosition = Util::Math::Vector2D(camera.getPosition().getX(), list[i].getPosition().getY());
                list[i].draw(graphics,newPosition);
            }*/
            list[i].draw(graphics,list[i].getPosition());
        }

    }
}
