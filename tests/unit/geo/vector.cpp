#include "geo/vector.hpp"

#include <iostream>

#include <gtest/gtest.h>

using namespace std;


namespace geo {

	TEST( Vector, operator_subscript ) {
		Vector<float, 5> vec;
		vec[0] = 0.1;
		vec[1] = 1.1;
		vec[2] = 2.1;
		vec[3] = 3.1;
		vec[4] = 4.1;

		EXPECT_EQ( 0.1, vec[0] );
		EXPECT_EQ( 1.1, vec[1] );
		EXPECT_EQ( 2.1, vec[2] );
		EXPECT_EQ( 3.1, vec[3] );
		EXPECT_EQ( 4.1, vec[4] );
	}
}
