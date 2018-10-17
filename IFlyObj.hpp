#ifndef IFLYOBJ_HPP
#define IFLYOBJ_HPP
#include <iostream>
#include <string>

class  IFlyObj{

public:
    virtual ~IFlyObj() {}
    virtual char getSymbolObj() const = 0;//
    virtual void    moveY(int y) = 0;//
    virtual void    moveX(int x) = 0;//
};

#endif