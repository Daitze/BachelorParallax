#include <cstdint>

#include "lib/util/game/Engine.h"
#include "lib/util/base/System.h"
#include "lib/util/base/ArgumentParser.h"
#include "lib/util/io/stream/PrintStream.h"
#include "lib/util/io/file/File.h"
#include "lib/util/graphic/LinearFrameBuffer.h"
#include "lib/util/game/GameManager.h"
#include "lib/util/game/Game.h"
#include "application/parallax/dino/DinoGame.h"
#include "application/parallax/ninja/NinjaGame.h"

int32_t main(int32_t argc, char *argv[]) {
    auto argumentParser = Util::ArgumentParser();
    argumentParser.setHelpText("Dino and Ninja");

    if (!argumentParser.parse(argc, argv)) {
        Util::System::error << argumentParser.getErrorString() << Util::Io::PrintStream::endl << Util::Io::PrintStream::flush;
        return -1;
    }
    auto arguments = argumentParser.getUnnamedArguments();
    auto demo = arguments[0];

    auto lfbFile = Util::Io::File("/device/lfb");
    auto lfb = Util::Graphic::LinearFrameBuffer(lfbFile);
    auto engine = Util::Game::Engine(lfb, 60);


    if (demo == "dino"){
        Util::Game::GameManager::getGame().pushScene(new DinoGame());
    }else if (demo == "ninja"){
        Util::Game::GameManager::getGame().pushScene(new NinjaGame());
    }


    engine.run();

    return 0;
}