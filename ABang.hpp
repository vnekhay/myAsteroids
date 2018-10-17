#ifndef ABang_HPP
#define ABang_HPP
#include "IFlyObj.hpp"

class ABang : public IFlyObj{
protected:
    int _hit;
    int _x;
    int _y;
    int _endX;
    int _endY;
    std::string _type;
    char _symb;

public:
    ABang();
    ABang(ABang const &cpy);
    ~ABang();
    std::string getType() const ;
    int         getHit() const;
    int         getX() const;
    int         getY() const;
    int         getEndX();
    int         getEndY();

    virtual void    setType(std::string type) = 0;
    virtual void    setHit(int hit) = 0;
    virtual void    setSymb(char sym) = 0;

    void    setX(int);
    void    setY(int);
    void    setEndY_EndX(int endY, int endX);

    void    moveY(int);
    void    moveX(int);
    char    getSymbolObj() const;
    ABang   &operator=(ABang const &rhs);
};
#endif