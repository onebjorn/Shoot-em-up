#include "ray2d_maybe.h"
#include "Box2D.h"
#include <iostream>

using namespace std;

int main()
{
        Ray alpha(0.0, 0.0, 1.0, 0.0);

        Box2D obj1(1,1,2,2);
        Box2D obj2(3,3,4,4);
        obj2.getBox2D(obj2);
        obj1.getBox2D(obj1);

obj1.boxCrossing(obj1,obj2);

        return 0;
}

