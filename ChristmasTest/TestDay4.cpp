#include "libraries.h"
#include "../Christmas/Day4.cpp"

TEST(TestDay4, PartOne)
{
	auto result = generateValidPasswords(307237, 769058);
	EXPECT_EQ(result.size(), 889);
}

TEST(TestDay4, PartTwo)
{
	EXPECT_EQ(isInvalidPassword2(112233), false);
	EXPECT_EQ(isInvalidPassword2(123444), true);
	EXPECT_EQ(isInvalidPassword2(111122), false);

	auto result = generateValidPasswords2(307237, 769058);
	EXPECT_EQ(result.size(), 589);
}
