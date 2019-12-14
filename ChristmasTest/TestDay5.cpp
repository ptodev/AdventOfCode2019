#include "libraries.h"
#include "../Christmas/Day5.cpp"

TEST(TestDay5, PartTwoBasic1)
{
	vector<long long> intCode = { 3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9 };

	auto intCode1 = intCode;
	queue<long long> inputs1;
	inputs1.push(0);
	auto result1 = Day5Part2::runProgram(intCode1, inputs1);
	EXPECT_EQ(result1.first.front(), 0);

	auto intCode2 = intCode;
	queue<long long> inputs2;
	inputs2.push(5);
	auto result2 = Day5Part2::runProgram(intCode2, inputs2);
	EXPECT_EQ(result2.first.front(), 1);
}

TEST(TestDay5, PartTwoBasic2)
{
	vector<long long> intCode = { 3,3,1105,-1,9,1101,0,0,12,4,12,99,1 };

	auto intCode1 = intCode;
	queue<long long> inputs1;
	inputs1.push(0);
	auto result1 = Day5Part2::runProgram(intCode1, inputs1);
	EXPECT_EQ(result1.first.front(), 0);

	auto intCode2 = intCode;
	queue<long long> inputs2;
	inputs2.push(5);
	auto result2 = Day5Part2::runProgram(intCode2, inputs2);
	EXPECT_EQ(result2.first.front(), 1);
}

TEST(TestDay5, PartOneAndTwo)
{
	vector<long long> intCode = { 3, 225, 1, 225, 6, 6, 1100, 1, 238, 225, 104, 0, 101, 20, 183, 224, 101, -63, 224, 224, 4, 224, 1002, 223, 8, 223, 101, 6, 224, 224, 1, 223, 224, 223, 1101, 48, 40, 225, 1101, 15, 74, 225, 2, 191, 40, 224, 1001, 224, -5624, 224, 4, 224, 1002, 223, 8, 223, 1001, 224, 2, 224, 1, 223, 224, 223, 1101, 62, 60, 225, 1102, 92, 15, 225, 102, 59, 70, 224, 101, -885, 224, 224, 4, 224, 1002, 223, 8, 223, 101, 7, 224, 224, 1, 224, 223, 223, 1, 35, 188, 224, 1001, 224, -84, 224, 4, 224, 102, 8, 223, 223, 1001, 224, 2, 224, 1, 223, 224, 223, 1001, 66, 5, 224, 1001, 224, -65, 224, 4, 224, 102, 8, 223, 223, 1001, 224, 3, 224, 1, 223, 224, 223, 1002, 218, 74, 224, 101, -2960, 224, 224, 4, 224, 1002, 223, 8, 223, 1001, 224, 2, 224, 1, 224, 223, 223, 1101, 49, 55, 224, 1001, 224, -104, 224, 4, 224, 102, 8, 223, 223, 1001, 224, 6, 224, 1, 224, 223, 223, 1102, 43, 46, 225, 1102, 7, 36, 225, 1102, 76, 30, 225, 1102, 24, 75, 224, 101, -1800, 224, 224, 4, 224, 102, 8, 223, 223, 101, 2, 224, 224, 1, 224, 223, 223, 1101, 43, 40, 225, 4, 223, 99, 0, 0, 0, 677, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1105, 0, 99999, 1105, 227, 247, 1105, 1, 99999, 1005, 227, 99999, 1005, 0, 256, 1105, 1, 99999, 1106, 227, 99999, 1106, 0, 265, 1105, 1, 99999, 1006, 0, 99999, 1006, 227, 274, 1105, 1, 99999, 1105, 1, 280, 1105, 1, 99999, 1, 225, 225, 225, 1101, 294, 0, 0, 105, 1, 0, 1105, 1, 99999, 1106, 0, 300, 1105, 1, 99999, 1, 225, 225, 225, 1101, 314, 0, 0, 106, 0, 0, 1105, 1, 99999, 1008, 226, 226, 224, 1002, 223, 2, 223, 1005, 224, 329, 1001, 223, 1, 223, 8, 226, 677, 224, 102, 2, 223, 223, 1006, 224, 344, 1001, 223, 1, 223, 1007, 226, 677, 224, 1002, 223, 2, 223, 1005, 224, 359, 101, 1, 223, 223, 1008, 677, 226, 224, 102, 2, 223, 223, 1006, 224, 374, 1001, 223, 1, 223, 1107, 226, 677, 224, 1002, 223, 2, 223, 1006, 224, 389, 1001, 223, 1, 223, 107, 677, 677, 224, 1002, 223, 2, 223, 1006, 224, 404, 101, 1, 223, 223, 1007, 226, 226, 224, 1002, 223, 2, 223, 1006, 224, 419, 101, 1, 223, 223, 7, 677, 226, 224, 1002, 223, 2, 223, 1005, 224, 434, 1001, 223, 1, 223, 1007, 677, 677, 224, 1002, 223, 2, 223, 1006, 224, 449, 101, 1, 223, 223, 107, 226, 226, 224, 1002, 223, 2, 223, 1006, 224, 464, 1001, 223, 1, 223, 1108, 677, 677, 224, 1002, 223, 2, 223, 1005, 224, 479, 101, 1, 223, 223, 8, 677, 226, 224, 1002, 223, 2, 223, 1006, 224, 494, 101, 1, 223, 223, 7, 226, 677, 224, 102, 2, 223, 223, 1005, 224, 509, 1001, 223, 1, 223, 1107, 677, 226, 224, 102, 2, 223, 223, 1005, 224, 524, 1001, 223, 1, 223, 1108, 677, 226, 224, 1002, 223, 2, 223, 1005, 224, 539, 1001, 223, 1, 223, 1108, 226, 677, 224, 102, 2, 223, 223, 1006, 224, 554, 101, 1, 223, 223, 108, 226, 677, 224, 102, 2, 223, 223, 1005, 224, 569, 1001, 223, 1, 223, 8, 677, 677, 224, 1002, 223, 2, 223, 1005, 224, 584, 101, 1, 223, 223, 108, 677, 677, 224, 1002, 223, 2, 223, 1005, 224, 599, 1001, 223, 1, 223, 108, 226, 226, 224, 102, 2, 223, 223, 1006, 224, 614, 101, 1, 223, 223, 1008, 677, 677, 224, 102, 2, 223, 223, 1006, 224, 629, 1001, 223, 1, 223, 107, 226, 677, 224, 102, 2, 223, 223, 1006, 224, 644, 101, 1, 223, 223, 1107, 677, 677, 224, 1002, 223, 2, 223, 1005, 224, 659, 1001, 223, 1, 223, 7, 226, 226, 224, 1002, 223, 2, 223, 1005, 224, 674, 101, 1, 223, 223, 4, 223, 99, 226 };
	
	auto intCode1 = intCode;
	queue<long long> inputs1;
	inputs1.push(1);
	auto result1 = Day5Part1::runProgram(intCode1, inputs1);
	while (result1.front() == 0)
	{
		result1.pop();
	}
	EXPECT_EQ(result1.front(), 13346482);

	auto intCode2 = intCode;
	queue<long long> inputs2;
	inputs2.push(5);
	auto result2 = Day5Part2::runProgram(intCode2, inputs2);
	EXPECT_EQ(result2.first.front(), 12111395);
}
