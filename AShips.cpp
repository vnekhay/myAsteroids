#include "AShips.hpp"

AShips::AShips() { _myBang = nullptr; }

AShips::~AShips() {
}

AShips::AShips(int cL, int nL, char s) {
    _curLive = cL;
    _numLive = nL;
    _symb = s;
    _sum_b = 0;
}

AShips::AShips(AShips const &cpy) { *this = cpy; }

AShips& AShips::operator=(AShips const &rhs) {
    _x = rhs.getCoorX();
    _y = rhs.getCoorY();
    _curLive = rhs.getCurLive();
    _numLive = rhs.getNumLive();
    _symb = rhs.getSymbolObj();
    return *this;
}

void AShips::setEndY_EndX(int endY, int endX) {
    _endY = endY;
    _endX = endX;
}

void AShips::setCoorX(int x) {
    _x = x;
}

void AShips::setCoorX_2(int x) { _x_2 = x; }

void AShips::setCoorX_3(int x) { _x_3 = x; }

void AShips::setCoorY(int y) {
    _y = y;
}


int AShips::getCoorX_2() const { return this->_x_2; }
int AShips::getCoorX_3() const { return this->_x_3; }
int AShips::getSub_b() const { return this->_sum_b; }
int AShips::getType() const { return  this->_type; }
int AShips::getCurLive() const { return this->_curLive; }
char AShips::getSymbolObj() const { return this->_symb; }
int AShips::getNumLive() const { return this->_numLive; }
int AShips::getCoorX() const { return this->_x; }
int AShips::getCoorY() const { return  this->_y; }

void AShips::moveY(int y) {
    if (_y + y < _endY)
        _y += y;
}

void AShips::moveX(int x) {
    if (_x + x < _endX)
        _x += x;
}
