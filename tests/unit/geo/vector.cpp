#include "geo/vector.hpp"

#include <iostream>

#include <gtest/gtest.h>


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

}
