#include "ray2d_maybe.h"
#include "Box2D.h"
using namespace std;

int main()
{
        Ray alpha(0.0, 0.0, 1.0, 0.0);
        cout << alpha.GetDirect(1) << endl;

        Box2D box1( 1.0, 1.0, 3.0, 3.0);
        Box2D box2 ( 10.0, 10.0, 12.0, 12.0);
        Box2D box3(box1);

        boxCrossing(box1, box2);
        boxCrossing(box3, box2);


        return 0;
}

