#include "ray2d_maybe.h"
#include "Box2D.h"
using namespace std;

int main()
{
        Ray alpha(0.0, 0.0, 1.0, 0.0);
        cout << alpha.GetDirect(1) << endl;
        return 0;

}

