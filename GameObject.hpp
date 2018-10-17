#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include "AShips.hpp"
#include "PlayerShip.hpp"
#include "EnemyShip.hpp"
#include "Bullet.hpp"
#include "Spaces.hpp"
#include <unistd.h>
#include <math.h>
#include <time.h>

#define HEIGHT 50
#define WIDTH  100

class  GameObject{

private:
    Bullet        _bull[500];//bullets
    PlayerShip    _pl;//player
    EnemyShip     _enm[50];//enemy
    Spaces        _spc[100];
    WINDOW*         _win;
    int             _score;
    int             _y_map;
    int             _x_map;
    int             _cnt;
    int             _total_cnt_cycle;
    bool            _drop;
    time_t      _start_t, _end_t;

public:
    GameObject();
    ~GameObject();
    int     init_game();
    void    createWindow();
    int     initPlayer();
    int     start_game();
    void    init_spaces();
    void    moveSpace();
    void    createEnemy();
    void    moveEnemy();
    void    makeShot();
    void    moveShot();
    void    Colision();
    void    enemyAtack();
    GameObject(GameObject const & cpy);
    GameObject &operator = (GameObject const & rhs);
};

#endif