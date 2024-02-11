#include "Background.h"
#include "algorithm"
#include "lib/util/game/2d/Sprite.h"
#include "lib/util/collection/Array.h"
#include "lib/util/game/Scene.h"


namespace Util::Game::D2 {
    Background::Background() : spriteList(0), newSpriteList(0){}
    Background::Background(const Util::Array<Sprite> &sprites, double playerVelocity, double parallaxValue): newSpriteList(sprites), spriteList(sprites),playerVelocity(playerVelocity),parallaxValue(parallaxValue){}

    Background::Background(const Util::Array<Sprite> &sprites, double cameraPosition, double playerVelocity, double parallaxValue): newSpriteList(sprites), spriteList(sprites),cameraPosition(cameraPosition),playerVelocity(playerVelocity),parallaxValue(parallaxValue){}

    void Background::update(double delta) {
        setVelocity(playerVelocity);
        setCameraPosition(cameraPosition);

        if (playerVelocity < 0) {
            for (int i = 0; i < spriteList.length(); ++i) {
                auto startX = spriteList[i].getPosition().getX();
                auto newPositionX = startX + parallaxValue;
                auto newVector = Util::Math::Vector2D(newPositionX, spriteList[i].getPosition().getY());
                spriteList[i] = Util::Game::D2::Sprite(spriteList[i].getPath(), spriteList[i].getSize().getX(),spriteList[i].getSize().getY(), newVector);

                if (spriteList[i].getPosition().getX() < cameraPosition - 4 && cameraPosition!=0) {
                    auto positionX = (static_cast<uint32_t>((cameraPosition + 1.5) * 10) / 5) * 5 / 10.0;
                    auto newVector = Util::Math::Vector2D(positionX, spriteList[i].getPosition().getY());
                    spriteList[i] = Util::Game::D2::Sprite(newSpriteList[i].getPath(),newSpriteList[i].getSize().getX(),newSpriteList[i].getSize().getY(), newVector);
                }
            }
        }
        if (playerVelocity > 0) {
            for (int i = 0; i < spriteList.length(); ++i) {
                auto startX = spriteList[i].getPosition().getX();
                auto newPositionX = startX - parallaxValue;
                auto newVector = Util::Math::Vector2D(newPositionX, spriteList[i].getPosition().getY());
                spriteList[i] = Util::Game::D2::Sprite(spriteList[i].getPath(), spriteList[i].getSize().getX(),spriteList[i].getSize().getY(), newVector);

                if (spriteList[i].getPosition().getX() < cameraPosition - 4 && cameraPosition!=0) {
                    auto positionX = (static_cast<uint32_t>((cameraPosition + 1.5) * 10) / 5) * 5 / 10.0;
                    auto newVector = Util::Math::Vector2D(positionX, spriteList[i].getPosition().getY());
                    spriteList[i] = Util::Game::D2::Sprite(newSpriteList[i].getPath(),newSpriteList[i].getSize().getX(),newSpriteList[i].getSize().getY(), newVector);
                }
            }
        }
    }

    void Background::draw(const Util::Game::Graphics &graphics) {
        for (int i = 0; i < spriteList.length(); ++i) {
            spriteList[i].draw(graphics,spriteList[i].getPosition());
        }

    }

    void Background::setVelocity(double velocity){
        playerVelocity = velocity;
    }
    void Background::setCameraPosition(double position){
        cameraPosition = position;
    }

}




