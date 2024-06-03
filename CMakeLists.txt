cmake_minimum_required(VERSION 3.27)
project(2024_I2P2_TowerDefense_with_answer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

include_directories(.)
include_directories(Resource)

file(COPY Resource/audios DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource/fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource/images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY allegro_monolith-5.2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(2024_I2P2_TowerDefense_with_answer
        Engine/Allegro5Exception.cpp
        Engine/Allegro5Exception.hpp
        Engine/AudioHelper.cpp
        Engine/AudioHelper.hpp
        Engine/GameEngine.cpp
        Engine/GameEngine.hpp
        Engine/Group.cpp
        Engine/Group.hpp
        Engine/IControl.cpp
        Engine/IControl.hpp
        Engine/Collider.cpp
        Engine/Collider.hpp
        Engine/IObject.cpp
        Engine/IObject.hpp
        Engine/IScene.cpp
        Engine/IScene.hpp
        Engine/LOG.cpp
        Engine/LOG.hpp
        Engine/Point.cpp
        Engine/Point.hpp
        Engine/Resources.cpp
        Engine/Resources.hpp
        Engine/Sprite.cpp
        Engine/Sprite.hpp
        Bullet/Bullet.cpp
        Bullet/Bullet.hpp
        Bullet/FireBullet.cpp
        Bullet/FireBullet.hpp
        Bullet/LaserBullet.cpp
        Bullet/LaserBullet.hpp
        Bullet/MissileBullet.cpp
        Bullet/MissileBullet.hpp
        Bullet/EmptyBullet.cpp
        Bullet/EmptyBullet.hpp
        UI/Animation/DirtyEffect.cpp
        UI/Animation/DirtyEffect.hpp
        UI/Animation/ExplosionEffect.cpp
        UI/Animation/ExplosionEffect.hpp
        UI/Component/Image.cpp
        UI/Component/Image.hpp
        UI/Component/ImageButton.cpp
        UI/Component/ImageButton.hpp
        UI/Component/Label.cpp
        UI/Component/Label.hpp
        UI/Animation/Plane.cpp
        UI/Animation/Plane.hpp
        UI/Component/Slider.cpp
        UI/Component/Slider.hpp
        Enemy/Enemy.cpp
        Enemy/Enemy.hpp
        Enemy/SoldierEnemy.cpp
        Enemy/SoldierEnemy.hpp
        Enemy/PlaneEnemy.cpp
        Enemy/PlaneEnemy.hpp
        Enemy/TankEnemy.cpp
        Enemy/TankEnemy.hpp
        Enemy/RoadRollerEnemy.cpp
        Enemy/RoadRollerEnemy.hpp
        Turret/LaserTurret.cpp
        Turret/LaserTurret.hpp
        Turret/MachineGunTurret.cpp
        Turret/MachineGunTurret.hpp
        Turret/MissileTurret.cpp
        Turret/MissileTurret.hpp
        Turret/DeleteTurret.cpp
        Turret/DeleteTurret.hpp
        Turret/EmptyTurret.hpp
        Turret/EmptyTurret.cpp
        Turret/Turret.cpp
        Turret/Turret.hpp
        Turret/TurretButton.cpp
        Turret/TurretButton.hpp
        Scene/LoseScene.cpp
        Scene/LoseScene.hpp
        Scene/PlayScene.cpp
        Scene/PlayScene.hpp
        Scene/StageSelectScene.cpp
        Scene/StageSelectScene.hpp
        Scene/WinScene.cpp
        Scene/WinScene.hpp
        Scene/StartScene.cpp
        Scene/StartScene.hpp
        Scene/SettingsScene.cpp
        Scene/SettingsScene.hpp
        Scene/ScoreScene.hpp
        Scene/ScoreScene.cpp
        main.cpp
)


IF (WIN32)
    target_include_directories(2024_I2P2_TowerDefense_with_answer PUBLIC C:/allegro/include)
    target_link_directories(2024_I2P2_TowerDefense_with_answer PUBLIC C:/allegro/lib)
    target_compile_options(2024_I2P2_TowerDefense_with_answer PUBLIC ${ALLEGRO5_CFLAGS_OTHER})
    target_link_libraries(2024_I2P2_TowerDefense_with_answer liballegro_monolith)
ELSE()
    find_package(PkgConfig)
    pkg_check_modules(ALLEGRO5 REQUIRED allegro-5 allegro_main-5 allegro_font-5 allegro_dialog-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5)
    target_include_directories(2024_I2P2_TowerDefense_with_answer PUBLIC lib)
    target_include_directories(2024_I2P2_TowerDefense_with_answer PUBLIC ${ALLEGRO5_INCLUDE_DIRS})
    target_compile_options(2024_I2P2_TowerDefense_with_answer PUBLIC ${ALLEGRO5_CFLAGS_OTHER})
    target_link_libraries(2024_I2P2_TowerDefense_with_answer ${ALLEGRO5_LIBRARIES})
    target_link_directories(2024_I2P2_TowerDefense_with_answer PUBLIC ${ALLEGRO5_LIBRARY_DIRS})
ENDIF()
