#include "ray2d_maybe.h"
#include "Box2D.h"
#include <iostream>

using namespace std;

int main()
{
        Box2D obj1(1,1,2,2);
        Box2D obj2(3,3,4,4);

obj1.boxCrossing(obj1,obj2);

cout<< obj1.x1()<<endl;


        return 0;
}

