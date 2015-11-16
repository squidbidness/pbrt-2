#include "lib/loops.hpp"
#include "lib/stringer.hpp"
#include "geo/vector.hpp"

#include <iostream>


int main( int argc, char **argv ) {

    using namespace geo;
    using namespace lib;
    using namespace std;

    Vector3 v;
    v.x = 3.0f;

    cout << v.x << endl;

    streamer( cout, 23, " ", 24, ", ", 2+2 );
}
