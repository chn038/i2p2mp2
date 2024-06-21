[Reminder] after modifying the Resource, one has to run cmake again
[Reminder] For linux: cmake -S . -B build --fresh -DCMAKE_EXPORT_COMPILE_COMMAND=1 -DCMAKE_BUILD_TYPE=Debug

# Resource/enemy1.txt
# Resource/enemy2.txt
- need to reconstruct the file
    - format: time type posx posy

# Bullet/Bullet.cpp
# Bullet/Bullet1.cpp
# Bullet/Bullet2.cpp
# Bullet/Bullet3.cpp
# Bullet/Bullet4.cpp
# Bullet/Bullet5.cpp
# Instance/Instance.cpp
# Instance/Instance1.cpp
# Instance/Instance2.cpp
# Instance/Instance3.cpp
# Instance/Instance4.cpp
# Instance/Instance5.cpp
# Instance/Instance6.cpp

[Explaination] Post found Bugs here
# BUGS:

[Explaination] For something that's planning to implement but yet not implemented
# FEATURE:
- The art of all things
    - life bar (instance)
    - progress bar (tower)

# TURRET DATA
- TURRET 1:
    - RNG: 1
    - ATK: 2
    - ASD: 1
    - Money: 50
    - Soldier : A*1
    - Time: 5

- TURRET 2:
    - RNG: 2
    - ATK: 1
    - ASD: 1
    - Money: 50
    - Soldier : B*1
    - Time: 8

- TURRET 3:
    - RNG: 3
    - ATK: 2
    - ASD: 0.5
    - Money: 100
    - Soldier : C*1 
    - Time: 12

- TURRET 4:
    - RNG: 3
    - ATK: 6
    - ASD: 2
    - Money: 100
    - Soldier : D*1 
    - Time: 15

- TURRET 5:
    - RNG: X
    - ATK: X
    - ASD: X
    - Money: 150
    - Soldier : E,F*1
    - Time: 50

# SOLDIER DATA
- Soldier A:
    - RNG: 1
    - HP: 20
    - ATK: 1
    - ASD: 1
    - SPD: 1.5
    - Money:5
    - Ground
    - Target: Ground

- Soldier B:
    - RNG: 3
    - HP: 10
    - ATK: 2
    - ASD: 0.5
    - SPD: 1
    - Money:5
    - Ground
    - Target: Ground, Fly

- Soldier C:
    - RNG: 1
    - HP: 50
    - ATK: 3
    - ASD: 0.5
    - SPD: 0.5
    - Money:10
    - Ground
    - Target: Ground

- Soldier D:
    - RNG: 3
    - HP: 20
    - ATK: 0.5
    - ASD: 0.25
    - SPD: 1
    - Money:10
    - Fly
    - Target: Ground, Fly

- Soldier E:
    - RNG: 1
    - HP: 100
    - ATK: 1
    - ASD: 1
    - SPD: 1
    - Money:20
    - Ground
    - Target: Ground

- Soldier F:
    - RNG: 5
    - HP: 50
    - ATK: 10
    - ASD: 2
    - SPD: 0.5
    - Money:20
    - Fly
    - Target: Fly
