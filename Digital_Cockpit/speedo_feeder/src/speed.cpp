#include "../headers/speed.hpp"


Speed::Speed() :  _speed(0)
{
}

Speed::~Speed() {}

int Speed::getInput()
{
    return _input;
}

void Speed::forward()
{
    // std::cout << "forward speed " << std::endl;
    if (_speed < 300)
        _speed += 10;
}


void Speed::bbreak()
{
    if (_speed != 0)
    {
        if (_speed > 0 )
            _speed -= 10;
    }
}

int Speed::getSpeed()
{
    return _speed;
}
