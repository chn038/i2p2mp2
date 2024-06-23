# I2P2 Final Project

## Introduction
### This is a PvE game where players can place defense towers in specific areas to fend off enemy soldiers. Unlike traditional tower defense games, our game leans more towards RTS gameplay. In the game, the soldiers on both sides depend on the defense towers they possess. Each defense tower has its unique attack power, range, and the type of soldiers it can produce, including melee soldiers, ranged soldiers, tanks, heavily armed tanks, standard aircraft, and fighter jets. When one of your soldiers reaches the enemy base, the opponent's health will decrease by 1 point. You win when the opponent's health drops to zero. Conversely, if the opponent's soldiers reach your base and reduce your health to zero, you lose.

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
| standard aircraft                |      Fly          |         Ground & Fly     |
| heavily armed tanks              |      Ground       |         Ground           |
| fighter jets                     |      Fly          |         Fly              |

