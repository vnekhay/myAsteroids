#ifndef SPACES_HPP
#define SPACES_HPP
#include "IFlyObj.hpp"

class Spaces : public IFlyObj{
private:
    int    _x;
    int    _y;
    char   _sym;
public:
    Spaces();
    ~Spaces();
    Spaces(Spaces const & cpy);
    Spaces &operator=(Spaces const & rhs);

    char    getSymbolObj() const;
    void    moveY(int y);
    void    moveX(int x);


    int     getX() const;
    int     getY() const;
};

#endif