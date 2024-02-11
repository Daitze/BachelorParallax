#include "Background.h"
#include "algorithm"
#include "lib/util/game/2d/Sprite.h"
#include "lib/util/collection/Array.h"
#include "lib/util/game/Camera.h"
#include "lib/util/game/Scene.h"
#include "lib/util/game/2d/Entity.h"
#include "lib/util/game/GameManager.h"


namespace Util::Game::D2 {
    Background::Background() : spriteList(0){}

    Background::Background(const Util::Array<Sprite> &sprites,bool right, bool left, double parallaxValue): spriteList(sprites),rightKey(right),leftKey(left),parallaxValue(parallaxValue){}

    void Background::update(double delta){
        setKeyboard(rightKey,leftKey);
        if(leftKey==true){
            for (int i = 0; i < spriteList.length(); ++i) {
                auto startX = spriteList[i].getPosition().getX();
                auto newPositionX = startX + parallaxValue;
                auto newVector = Util::Math::Vector2D(newPositionX,spriteList[i].getPosition().getY());
                spriteList[i] = Util::Game::D2::Sprite(spriteList[i].getPath(),spriteList[i].getSize().getX(),spriteList[i].getSize().getY(),newVector);
            }
        }
        if(rightKey==true){
            for (int i = 0; i < spriteList.length(); ++i) {
                auto startX = spriteList[i].getPosition().getX();
                auto newPositionX = startX - parallaxValue;
                auto newVector = Util::Math::Vector2D(newPositionX,spriteList[i].getPosition().getY());
                spriteList[i] = Util::Game::D2::Sprite(spriteList[i].getPath(),spriteList[i].getSize().getX(),spriteList[i].getSize().getY(),newVector);
            }
        }
    }

    void Background::draw(const Util::Game::Graphics &graphics) {
//        auto spriteList = sprites;
//        int len = spriteList.length();
//        //Sort List by Descending LayerPosition. For back to front drawing.
//        for (int m = 0; m <= len-1; m++){
//            for (int n = 0; n < len - 1 - m; ++n) {
//                if(spriteList[n].getPosition().getLayerPosition() < spriteList[n+1].getPosition().getLayerPosition()){
//                    auto temp = spriteList[n];
//                    spriteList[n] = spriteList[n+1];
//                    spriteList[n+1] = temp;
//                }
//            }
//        }
        for (int i = 0; i < spriteList.length(); ++i) {
            spriteList[i].draw(graphics,spriteList[i].getPosition());
        }
    }

    void Background::setKeyboard(bool right, bool left){
        rightKey = right;
        leftKey = left;
    }

}




