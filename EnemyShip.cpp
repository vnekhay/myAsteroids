#include "EnemyShip.hpp"

EnemyShip::EnemyShip() : AShips(10, 1, '^') {
    setCoorY(0);
}

EnemyShip::~EnemyShip() {}

EnemyShip::EnemyShip(EnemyShip const &cpy) { *this = cpy; }

EnemyShip& EnemyShip::operator=(EnemyShip const &rhs) {
    _x = rhs.getCoorX();
    _y = rhs.getCoorY();
    _curLive = getCurLive();
    _numLive = getNumLive();
    _endX = rhs._endX;
    _endY = rhs._endY;
    _symb = rhs.getSymbolObj();
    return *this;
}

Bullet EnemyShip::shot(int sh) {
    Bullet bang;
    if ((this->getCoorY() + 2) < sh - 2 ){
        bang.setY(this->getCoorY() + 2);
        bang.setX(this->getCoorX());
        bang.setType("enemy");
        bang.setSymb('!');
        _sum_b++;
    }
    else
        bang.setSymb(' ');
    return bang;
}

void EnemyShip::setType(int type) { _type = type; }
void EnemyShip::setCurLive(int live) { _curLive = live; }
void EnemyShip::setNumLive(int numlive) { _numLive = numlive; }
void EnemyShip::setSymb(char sym) { _symb = sym; }
void EnemyShip::setBang(ABang const &rhs) {
    _myBang->setSymb(rhs.getSymbolObj());
    _myBang->setHit(rhs.getHit());
    _myBang->setType(rhs.getType());
    _myBang->setX(rhs.getX());
    _myBang->setY(rhs.getY());
}

void EnemyShip::takeDamage(ABang const &rhs) {
    _curLive -= rhs.getHit();
    _numLive -= (_curLive <= 0) ? 1 : 0;
}