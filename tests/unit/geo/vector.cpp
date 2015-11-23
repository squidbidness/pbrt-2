#include "geo/vector.hpp"

#include <iostream>

#include <gtest/gtest.h>

using namespace std;

namespace geo {


    TEST( VectorD3, operator_subscript ) {
        VectorD3 vec;
        vec[0] = 0;
        vec[1] = 1;
        vec[2] = 2;

        EXPECT_EQ( 0.0, vec[0] );
        EXPECT_EQ( 1.0, vec[1] );
        EXPECT_EQ( 2.0, vec[2] );
    }

    TEST( Vector3, rnadom ) {
        Vector3 test;
        test[0] = 0.0f;
        test[1] = 1.0f;
        test[2] = 2.0f;

        Vector3 test2;
        test2[0] = 10.0f;
        test2[1] = 11.0f;
        test2[2] = 12.0f;

        cout << test + test2 << endl;
    }

}
