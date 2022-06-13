cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME StarWars)
project(${PROJECT_NAME})

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/modules)

set(CMAKE_CXX_STANDARD 17)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(ZLIB REQUIRED)
find_package(SDL_mixer REQUIRED)

include_directories (${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS}  ${SDL_MIXER_INCLUDE_DIRS} )

add_executable(${PROJECT_NAME} main.cpp
        GameFramework/Game.cpp GameFramework/Game.h
        GameFramework/TextureManager.cpp GameFramework/TextureManager.h
        GameFramework/Vector2D.cpp GameFramework/Vector2D.h
        GameFramework/InputHandler.cpp GameFramework/InputHandler.h
        GameFramework/GameState.cpp GameFramework/GameState.h
        GameFramework/GameStateMachine.cpp GameFramework/GameStateMachine.h
        GameFramework/GameObjectFactory.cpp GameFramework/GameObjectFactory.h
        GameFramework/StateParser.cpp GameFramework/StateParser.h
        GameFramework/LevelParser.cpp GameFramework/LevelParser.h
        GameFramework/Callback.h GameFramework/Collision.h
        GameFramework/CollisionManager.cpp GameFramework/CollisionManager.h
        GameFramework/ScrollingBackground.cpp GameFramework/ScrollingBackground.h
        GameFramework/SoundManager.cpp GameFramework/SoundManager.h

        GameFramework/GameObject.h
        GameObjects/Player.cpp GameObjects/Player.h
        GameObjects/Enemy.h
        GameFramework/LoaderParams.h
        GameObjects/ShooterObject.cpp GameObjects/ShooterObject.h
        GameObjects/MenuButton.cpp GameObjects/MenuButton.h
        GameFramework/AnimatedGraphic.cpp GameFramework/AnimatedGraphic.h
        GameObjects/Bullet.h GameObjects/BulletHandler.cpp
        GameObjects/BulletHandler.h
        GameObjects/Eskeletor.h
        GameObjects/Glider.h
        GameObjects/Level1Boss.h
        GameObjects/RoofTurret.h
        GameObjects/ShotGlider.h

        States/MenuState.h
        States/PlayState.cpp States/PlayState.h
        States/PauseState.cpp States/PauseState.h
        States/GameOverState.cpp States/GameOverState.h
        States/MainMenuState.cpp States/MainMenuState.h

        Levels/Level.cpp Levels/Level.h
        Levels/Layer.h Levels/TileLayer.cpp
        Levels/TileLayer.h
        Levels/ObjectLayer.cpp Levels/ObjectLayer.h

        # tinyxml
        xmlparsing/tinystr.cpp
        xmlparsing/tinystr.h
        xmlparsing/tinyxml.cpp
        xmlparsing/tinyxml.h
        xmlparsing/tinyxmlerror.cpp
        xmlparsing/tinyxmlparser.cpp
        # decoding
        Base64/base64.cpp Base64/base64.h
        )

target_link_libraries (${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARY} ${SDL_MIXER_LIBRARY} ZLIB::ZLIB)

