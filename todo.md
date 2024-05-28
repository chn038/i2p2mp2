[Reminder] after modifying the Resource, one has to run cmake again

# CMakeLists.txt:
- ** TODO: [HACKATHON-1-SCENE] (2/4) Add the new scene source files here

# main.cpp:
- ** TODO: [HACKATHON-1-SCENE] (3/4): Register Scenes here
- ** TODO: [HACKATHON-1-SCENE] (4/4): Change the start scene
- ** TODO: [STARTSCENE] startscene not implement yet

# UI/Component/Slider.cpp:
- ** TODO: [HACKATHON-3-BUG] (4/5): Draw the nested components here, so they are displayed correctly
- ** TODO: [HACKATHON-3-BUG] (5/5): Fix the function, so it can set the slider value correctly
- [Modify] change the constructor of the slider to allow a initial value, which fix the position of the dragbar

# Scene/WinScene.cpp:
- ** TODO: [BUG] The back button won't works due to no instance of startscene
    - ** set the scene to settings temp

# Scene/PlayScene.cpp:
- ** TODO: [HACKATHON-3-BUG] (1/5): There's a bug in this file, which crashes the game when you lose. Try to find it.
- ** TODO: [HACKATHON-3-BUG] (2/5): Find out the cheat code to test. (The cheat code is a vector name code)
- ** TODO: [HACKATHON-3-BUG] (2/5): It should generate a Plane, and add 10000 to the money, but it doesn't work now.
- ** TODO: [HACKATHON-3-BUG] (3/5): Trace the code to know how the enemies are created.
- ** TODO: [HACKATHON-3-BUG] (3/5): There is a bug in these files, which let the game only spawn the first enemy, try to fix it.
- ** TODO: [BFS PathFinding] (1/1): Implement a BFS starting from the most right-bottom block in the map.
- // TODO: [CUSTOM-ENEMY]: You need to modify 'Resource/enemy1.txt', or 'Resource/enemy2.txt' to spawn the 4th enemy.
- // TODO: [CUSTOM-ENEMY]: Enable the creation of the enemy.
- // TODO: [CUSTOM-TURRET]: Make specific key to create the turret.
- // TODO: [CUSTOM-TURRET]: Create a button to support constructing the turret.
- // TODO: [CUSTOM-TURRET]: On callback, create the turret.

# Scene/LoseScene.cpp:
- ** TODO: [HACKATHON-1-SCENE] (1/4): You can imitate the 2 files: 'LoseScene.hpp', 'LoseScene.cpp' to implement your start scene.

# Turret/MachineGunTurret.cpp:
- // TODO: [CUSTOM-TOOL] You can imitate the 2 files: 'MachineGunTurret.hpp', 'MachineGunTurret.cpp' to create a new turret.

# Enemy/RoadRollerEnemy.cpp:
# Enemy/RoadRollerEnemy.hpp:
- // TODO: [CUSTOM-TOOL] The RoadRollerEnemy should temporarly increase the movement speed of the enemy.

# Bullet/FireBullet.cpp:
- // TODO: [CUSTOM-TOOL] You can imitate the 2 files: 'FireBullet.hpp', 'FireBullet.cpp' to create a new bullet.

# BUGS:
- segmentation fault when pressing too much key at the same time
    - a problem about allegro?

# FEATURE:
- a way to delete turret
- add new turret
- add scoreboard

