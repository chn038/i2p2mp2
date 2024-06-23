# I2P2 Final Project

## Introduction

    This is a PvE game where players can place defense towers in specific areas to fend off enemy soldiers. Unlike traditional tower defense games, our game leans more towards RTS gameplay. 
    In the game, the soldiers on both sides depend on the defense towers they possess. Each defense tower has its unique attack power, range, and the type of soldiers it can produce, including melee soldiers, ranged soldiers, tanks, heavily armed tanks, standard aircraft, and fighter jets. When one of your soldiers reaches the enemy base, the opponent's health will decrease by 1 point. You win when the opponent's health drops to zero. Conversely, if the opponent's soldiers reach your base and reduce your health to zero, you lose.
    Every soldiers spawn in the position of the tower, and each tower spawns its soldiers seperately, so to get a strong flow of your soldiers, it's necessary to decide where and when to put your towers. Beside that, each soldier has its strengh and weakness, which means that there's no go-to type but only a good combination of the soldiers.
    To beat the opponent, you have to have a great understanding of your soldiers, and, upgrade them at the right time.

## Tower and Soldier
| **Tower**                      | **soldier that can produce** |
| :----------------------------- | :--------------------------: |
| machine gun                    |         melee soldiers       |
| long-range machine gun         |         ranged soldiers      |
| Gatling gun                    |         tanks                |
| accurate sniper turret         |         standard aircraft    |
| barracks              |  heavily armed tanks & fighter jets   |

| **Soldier**                      | **Fly or Ground** | **what type it can hit** |
| :------------------------------- | :---------------: | :----------------------: |
| melee soldiers                   |      Ground       |         Ground           |
| ranged soldiers                  |      Ground       |         Ground & Fly     |
| tanks                            |      Ground       |         Ground           |
| standard aircraft                |      Fly          |         Ground           |
| heavily armed tanks              |      Ground       |         Ground           |
| fighter jets                     |      Fly          |         Fly              |

# Work distribution

陳宜和：PlayScene, Team, Tower
廖得竣：Instance, Bullet, Art design

