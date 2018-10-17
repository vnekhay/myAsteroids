#include "ABang.hpp"

ABang::ABang() {}

ABang::~ABang() {}

ABang::ABang(ABang const &cpy) { *this = cpy; }

ABang& ABang::operator=(ABang const &rhs) {
    _hit = rhs.getHit();
    _type = rhs.getType();
    _x = rhs.getX();
    _y = rhs.getY();
    return *this;
}

void ABang::setX(int x) { _x = x; }
void ABang::setY(int y) { _y = y; }
void ABang::setEndY_EndX(int endY, int endX) {
    _endY = endY;
    _endX = endX;
}

int ABang::getEndX() { return _endX; }
int ABang::getEndY() { return  _endY; }

int ABang::getHit() const { return  this->_hit; }
std::string ABang::getType() const { return  this->_type; }
int ABang::getX() const { return this->_x; }
int ABang::getY() const { return this->_y; }

void ABang::moveX(int x) {
    _x += x;
}

void ABang::moveY(int y) {
    _y += y;
}

char ABang::getSymbolObj() const { return this->_symb; }