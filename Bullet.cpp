#include "Bullet.hpp"

Bullet::Bullet() {
    this->setType("bullet");
    this->setHit(10);
    this->setSymb('|');
    real = 0;
}

Bullet::~Bullet() {}

Bullet::Bullet(Bullet const &cpy) { *this = cpy; }

Bullet& Bullet::operator=(Bullet const &rhs) {
    _hit = rhs.getHit();
    _x = rhs.getX();
    _y = rhs.getY();
    _type = rhs.getType();
    _symb = rhs.getSymbolObj();
    _endX = rhs._endX;
    _endY = rhs._endY;
    return  *this;
}

void Bullet::setType(std::string type) { _type = type; }
void Bullet::setHit(int hit) { _hit = hit; }
void Bullet::setSymb(char sym) { _symb = sym; }

void ABang::setType(std::string type) {_type = type; }
void ABang::setHit(int hit) { _hit = hit; }
void ABang::setSymb(char sym) { _symb = sym; }
