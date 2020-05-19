#include "../../catch2/catch.hpp"
#include "../IShape/CPoint.h"

TEST_CASE("class declaration")
{
	WHEN("declaration of variable without values")
	{
		CPoint point;
		CHECK(point.x == 0);
		CHECK(point.y == 0);
	}

	WHEN("declaration of variable with values")
	{
		CPoint point(1, 2);
		CHECK(point.x == 1);
		CHECK(point.y == 2);
	}
}

TEST_CASE("output check string")
{
	CPoint point(1.1234, 2.1234);
	CHECK(point.ToString() == "1.12, 2.12");
}