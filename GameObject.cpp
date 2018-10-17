#include "GameObject.hpp"

GameObject::GameObject() : _score(0) {
    _cnt = -1;
    _drop = false;
    _total_cnt_cycle = 0;
    time(&_start_t);
    init_game();
}

GameObject::GameObject(GameObject const &cpy)
{
    *this = cpy;
}

GameObject& GameObject::operator=(GameObject const &rhs) {
    (void)rhs;
    return *this;
}

GameObject::~GameObject() {
    erase();
    if (_pl.getStatusGame())
        mvprintw(_y_map / 2, _x_map / 2, "YOU DIED C:");
    nodelay(stdscr, false);
    getch();
    endwin();
    system("pkill afplay");
}

void GameObject::createWindow() {
    getmaxyx(stdscr, _y_map, _x_map);
    _win = newwin(_y_map, _x_map, 0, 0);
    box(_win, 0, 0);
    wrefresh(_win);
    attron(COLOR_PAIR(5));
    attron(A_BOLD);
    mvprintw(1, _x_map / 2 - 5, "SCORE:"); //SCORE:%d
    mvprintw(1, _x_map / 2 + 2, "%d", _score);
    mvprintw(1, 2, "Lives:");
    mvprintw(1, _x_map - 20, "Time:");
    mvprintw(1, _x_map - 14, "0");
    mvprintw(1, 9, "<+> <+> <+>");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(5));
}

void GameObject::moveSpace() {
    for (int i = 0; i < 100; ++i) {
        mvaddch(_spc[i].getY(), _spc[i].getX(), ' ');
        _spc[i].moveY(_spc[i].getY() + 1);
        if (_spc[i].getY() >= _y_map - 2)
            _spc[i].moveY(3);
        else
            mvaddch(_spc[i].getY(), _spc[i].getX(), '.');
    }
}

void GameObject::init_spaces() {

    int x, y;
    for (int i = 0; i < 100 ; ++i) {
        x = rand() % (_x_map - 2);
        y = rand() % (_y_map - 2);
        if (x <= 2)
            x += 2;
        if (y <= 2)
            y += 2;
        _spc[i].moveX(x);
        _spc[i].moveY(y);
        mvaddch(_spc[i].getY(), _spc[i].getX(), '.');
    }
}

int GameObject::init_game() {
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    curs_set(0);
    timeout(0);
    cbreak();
    refresh();
    createWindow();
    initPlayer();
    init_spaces();
    start_game();
    return 0;
}

int GameObject::initPlayer() {
    _pl.setCoorY(40);
    _pl.setCoorX_2(WIDTH / 2 - 1);
    _pl.setCoorX(WIDTH / 2 );
    _pl.setCoorX_3(WIDTH / 2 + 1);
    attron(COLOR_PAIR(2));
    attron(A_BOLD);
    mvaddch(_pl.getCoorY(), _pl.getCoorX_2(), '<');
    mvaddch(_pl.getCoorY(), _pl.getCoorX(), 'W');
    mvaddch(_pl.getCoorY(), _pl.getCoorX_3(), '>');
    attroff(A_BOLD);
    attroff(COLOR_PAIR(2));
    return (0);
}

void GameObject::moveEnemy() {
    for (int i = 0; i < 50 && _enm[i].getCoorY() != 0 ; ++i) {
        mvaddch(_enm[i].getCoorY(), _enm[i].getCoorX(), ' ');
        if (_enm[i].getCoorY() >= _y_map - 2) {
            _enm[i].setCoorY(0);
            _drop = true;
        }
        else {
            _enm[i].setCoorY(_enm[i].getCoorY() + 1);
            attron(COLOR_PAIR(3));
            mvaddch(_enm[i].getCoorY(), _enm[i].getCoorX(), _enm[i].getSymbolObj());
            attroff(COLOR_PAIR(3));
        }
    }
}

void GameObject::createEnemy() {
    int i = 0;
    int rd_x = rand() % (_x_map - 2);
    if (rd_x <= 2)
        rd_x += 2;
    while (_enm[i].getCoorY() != 0)
        i++;
    if (i >= 49) {
        _cnt = -1;
        return;
    }
    _enm[i].setCoorY(3);
    _enm[i].setCoorX(rd_x);
    _cnt = i;
}

void GameObject::moveShot() {
    for (int i = 0; i < 500; ++i) {
        mvaddch(_bull[i].getY(), _bull[i].getX(), ' ');
        if ((_bull[i].getY() - 1 <= 2 &&  _bull[i].getSymbolObj() == '|') || !_bull[i].real) {
            _bull[i].real = 0;
        }
        else if ((_bull[i].getY() + 1 >= _y_map - 1 && _bull[i].getSymbolObj() == '!') || !_bull[i].real) {
            _bull[i].real = 0;
        }
        else {
            if (_bull[i].getSymbolObj() == '|')
                _bull[i].setY(_bull[i].getY() - 1);
            if (_bull[i].getSymbolObj() == '!')
                _bull[i].setY(_bull[i].getY() + 1);
            attron(COLOR_PAIR(4));
            attron(A_BOLD);
            mvaddch(_bull[i].getY(), _bull[i].getX(), _bull[i].getSymbolObj());
            attroff(COLOR_PAIR(4));
            attroff(A_BOLD);
        }
    }
}

void GameObject::makeShot() {
    int i = 0;
    for ( ; i < 500 && _bull[i].real != 0; ++i);
    if (i >= 499)
        return;
    _bull[i] = _pl.shot();
    _bull[i].real = 1;
    attron(COLOR_PAIR(4));
    mvaddch(_bull[i].getY(), _bull[i].getX(), _bull[i].getSymbolObj());
    attroff(COLOR_PAIR(4));
}

void GameObject::enemyAtack() {
    int canShot = 0;
    int itr = 0;
    int i = 0;
    for (; i < 50 && _enm[i].getCoorY() != 0 ;  ++i) {
        if (_pl.getCoorX() == _enm[i].getCoorX()) {
            canShot++;
            itr = i;
        }
    }
    if (canShot == 1){
        i = 0;
        for ( ; i < 500 && _bull[i].real != 0 ; ++i);
        if (i >= 499)
            return;
        _bull[i] = _enm[itr].shot(_y_map);
        _bull[i].real = 1;
        mvaddch(_bull[i].getY(), _bull[i].getX(), _bull[i].getSymbolObj());
    }
}

void GameObject::Colision() {
    for (int i = 0; i < 500; ++i) {
        if (_bull[i].real){
            for (int j = 0; j < 50 ; ++j) {
                if (_bull[i].getY() == _enm[j].getCoorY() \
                && _bull[i].getX() == _enm[j].getCoorX()){
                    mvaddch(_enm[j].getCoorY(), _enm[j].getCoorX(), ' ');
                    mvaddch(_bull[i].getY(), _bull[i].getX(), ' ');
                    _enm[j].setCoorY(0);
                    _bull[i].real = 0;
                    _score += 10;
                    attron(COLOR_PAIR(5));
                    attroff(A_BOLD);
                    mvprintw(1, _x_map /2 + 2, "%d", _score);
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(4));
                }
                else if (_bull[i].getY() == _pl.getCoorY() \
                && (_bull[i].getX() == _pl.getCoorX() || _bull[i].getX() == _pl.getCoorX_2() \
                || _bull[i].getX() == _pl.getCoorX_3())){
                    _pl.takeColison();
                    mvaddch(_bull[i].getY(), _bull[i].getX(), ' ');
                    _bull[i].real = 0;
                    if (_pl.getNumLive() == 2){
                        attron(COLOR_PAIR(4));
                        attroff(A_BOLD);
                        mvprintw(1, 9, "<+> <+>     ");
                        mvprintw(1, 9, "<+> <+>");
                        attroff(A_BOLD);
                        attroff(COLOR_PAIR(5));
                    }
                    else if (_pl.getNumLive() == 1){
                        attron(A_BOLD);
                        attron(COLOR_PAIR(5));
                        mvprintw(1, 9, "<+>         ");
                        mvprintw(1, 9, "<+>");
                        attroff(COLOR_PAIR(5));
                        attron(A_BOLD);
                    }
                    return;
                }
            }
        }
    }
    for (int k = 0; k < 50; ++k) {
        if (_pl.getCoorY() == _enm[k].getCoorY() \
        && (_pl.getCoorX() == _enm[k].getCoorX() || _pl.getCoorX_2() == _enm[k].getCoorX() \
        || _pl.getCoorX_3() == _enm[k].getCoorX())){
            _pl.takeColison();
            if (_pl.getNumLive() == 2){
                attron(COLOR_PAIR(5));
                attron(A_BOLD);
                mvprintw(1, 9, "<+> <+>     ");
                mvprintw(1, 9, "<+> <+>");
                attron(A_BOLD);
                attroff(COLOR_PAIR(5));
            }
            else if (_pl.getNumLive() == 1){
                attron(A_BOLD);
                attron(COLOR_PAIR(5));
                mvprintw(1, 9, "<+>         ");
                mvprintw(1, 9, "<+>");
                attroff(A_BOLD);
                attroff(COLOR_PAIR(5));
            }
            mvaddch(_enm[k].getCoorY(), _enm[k].getCoorX(), ' ');
            _enm[k].setCoorY(0);
        }
    }
}


int GameObject::start_game() {
    int quit;
    int x;
    int x_2;
    int x_3;
    int y;
    int cnt_frame = 0;
    int ch = 0;
    system("afplay /Users/kmykhail/Downloads/my.mp3 &");
    while(ch != 27 && !_pl.getStatusGame()){
        ch = getch();
        while ((quit = getch()) > -1 && quit != 27 && quit != ' ');
        enemyAtack();
        if (ch == ' '){
            while ((quit = getch()) > -1 && quit != 27 && quit != ' ');
            makeShot();
        }
        if (_total_cnt_cycle % 2 == 0)
            moveShot();
        if (ch == 'a' || ch == 'd' || ch == 'w' || ch == 's'){
            mvaddch(_pl.getCoorY(), _pl.getCoorX_2(), ' ');
            mvaddch(_pl.getCoorY(), _pl.getCoorX(), ' ');
            mvaddch(_pl.getCoorY(), _pl.getCoorX_3(), ' ');
            x = _pl.getCoorX();
            x_2 = _pl.getCoorX_2();
            x_3 = _pl.getCoorX_3();
            y = _pl.getCoorY();
            if (ch == 'a' && x_2 >= 2) {
                _pl.setCoorX_2(x_2 - 1);
                _pl.setCoorX(x - 1);
                _pl.setCoorX_3(x_3 - 1);
            }
            else if (ch == 'd' && _pl.getCoorX_3() < _x_map - 2) {
                _pl.setCoorX_2(x_2 + 1);
                _pl.setCoorX(x + 1);
                _pl.setCoorX_3(x_3 + 1);
            }
            else if (ch == 'w' && _pl.getCoorY() > 3)
                _pl.setCoorY(y - 1);
            else if (ch == 's' && _pl.getCoorY() < _y_map - 2)
                _pl.setCoorY(y + 1);
            attron(COLOR_PAIR(2));
            attron(A_BOLD);
            mvaddch(_pl.getCoorY(), _pl.getCoorX_2(), '<');
            mvaddch(_pl.getCoorY(), _pl.getCoorX(), 'W');
            mvaddch(_pl.getCoorY(), _pl.getCoorX_3(), '>');
            attroff(A_BOLD);
            attroff(COLOR_PAIR(2));
        }
        if (cnt_frame == 5 ){
            createEnemy();
            cnt_frame = 0;
        }
        else if (_cnt >= 0 && _cnt < 50){
            attron(COLOR_PAIR(3));
            mvaddch(_enm[_cnt].getCoorY(), _enm[_cnt].getCoorX(), _enm[_cnt].getSymbolObj());
            attroff(COLOR_PAIR(3));
            _cnt = -1;
        }
        if (cnt_frame != 5 && _cnt && (_total_cnt_cycle % 8) == 0)
            moveEnemy();
        if ((_total_cnt_cycle % 50) == 0)
            moveSpace();
        Colision();
        usleep(40000);
        time(&_end_t);
        double diff = difftime(_end_t, _start_t);
        attron(COLOR_PAIR(5));
        attron(A_BOLD);
        mvprintw(1, _x_map - 20, "Time:");
        mvprintw(1, _x_map - 14, "%.2lf", diff);
        attroff(A_BOLD);
        attroff(COLOR_PAIR(5));
        attron(COLOR_PAIR(2));
        attron(A_BOLD);
        mvaddch(_pl.getCoorY(), _pl.getCoorX_2(), '<');
        mvaddch(_pl.getCoorY(), _pl.getCoorX(), 'W');
        mvaddch(_pl.getCoorY(), _pl.getCoorX_3(), '>');
        attroff(A_BOLD);
        attroff(COLOR_PAIR(2));
        refresh();
        cnt_frame++;
        _total_cnt_cycle++;
    }
    mvprintw(_y_map/ 2, _x_map / 2, "YOU CAN'T WIN IN THIS GAME");
    return 0;
}