#ifndef CUBE_H
#define CUBE_H
#include "component.h"

class Cube : public Component
{
public:
    Cube(int id, string componentType, string name);

private:
    int x,y;
    int width,height;
};

#endif // CUBE_H
