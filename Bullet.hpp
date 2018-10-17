#ifndef BULLET_HPP
#define BULLET_HPP
#include "ABang.hpp"

class Bullet : public ABang{

public:
    int real;
    Bullet();
    ~Bullet();
    Bullet(Bullet const & cpy);
    Bullet &operator=(Bullet const &rhs);

    void    setType(std::string type);
    void    setHit(int hit);
    void    setSymb(char sym);
};

#endif