#include "PlayerShip.hpp"

PlayerShip::PlayerShip() : AShips(30, 3, 'W'){
    _game_over = false;
}

PlayerShip::~PlayerShip() {}

PlayerShip::PlayerShip(PlayerShip const &cpy) { *this = cpy; }

PlayerShip& PlayerShip::operator=(PlayerShip const &rhs) {
    _x = rhs.getCoorX();
    _y = rhs.getCoorY();
    _curLive = getCurLive();
    _numLive = getNumLive();
    _endX = rhs._endX;
    _endY = rhs._endY;
    _symb = rhs.getSymbolObj();
    return *this;
}

Bullet PlayerShip::shot() {
    Bullet bang;
    if ((this->getCoorY() - 1) > 2){
        bang.setY(this->getCoorY() - 1);
        bang.setX(this->getCoorX());
        bang.setType("player");
        bang.setSymb('|');
        _sum_b++;
    }
    else
        bang.setSymb(' ');
    return bang;
}

void PlayerShip::setSum_b(int s) {
    _sum_b -= s;
    if (_sum_b < 0)
        _sum_b = 0;
}

void PlayerShip::setType(int type) { _type = type; } // 0
void PlayerShip::setCurLive(int live) { _curLive = live; }
void PlayerShip::setNumLive(int numlive) { _numLive = numlive; }
void PlayerShip::setSymb(char sym) { _symb = sym; }
void PlayerShip::setBang(ABang const &rhs) {
    _myBang->setSymb(rhs.getSymbolObj());
    _myBang->setHit(rhs.getHit());
    _myBang->setType(rhs.getType());
    _myBang->setX(rhs.getX());
    _myBang->setY(rhs.getY());
}

bool PlayerShip::getStatusGame() const { return this->_game_over; }

void PlayerShip::takeColison() {
    _numLive -= 1;
    if (_numLive <= 0)
        _game_over = true;
}

void PlayerShip::takeDamage(ABang const &rhs) {
    (void)rhs;
    _numLive -= 1;
    if (_numLive <= 0)
        _game_over = true;
}