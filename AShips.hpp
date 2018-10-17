#ifndef ASHIPS_HPP
#define ASHIPS_HPP
#include "IFlyObj.hpp"
#include "ABang.hpp"
#include <ncurses.h>

class ABang;

class AShips : public IFlyObj{
protected:
    int     _x;
    int     _x_2;
    int     _x_3;
    int     _y;
    int     _curLive;
    int     _numLive;
    int     _endX;
    int     _endY;
    char    _symb;
    int     _type;
    int     _sum_b;
    ABang*  _myBang;
public:
    AShips();
    AShips(int, int , char);
    AShips(AShips const & cpy);
    ~AShips();

    void             setEndY_EndX(int endY, int endX);
    void             setCoorX(int x);
    void             setCoorX_2(int);
    void             setCoorX_3(int);
    void             setCoorY(int y);
    virtual void     setCurLive(int live) = 0;
    virtual void     setNumLive(int numLive) = 0;
    virtual void     setSymb(char sym) = 0;
    virtual void     setBang(ABang const &) = 0;
    virtual void     setType(int) = 0;
    //


    //virtual ABang*   shot() = 0;//

    //
    int              getCurLive() const;
    int              getSub_b() const;
    int              getType() const;
    int              getNumLive() const;
    int              getCoorX() const;
    int              getCoorX_2() const;
    int              getCoorX_3() const;
    int              getCoorY() const;
    virtual void     takeDamage(ABang const &) = 0;

    char             getSymbolObj() const;
    void             moveY(int y);
    void             moveX(int x);

    AShips  &operator=(AShips const &rhs);
};
#endif