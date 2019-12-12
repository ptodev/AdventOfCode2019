#include "libraries.h"

using namespace std;

//TODO: Use move semantics and immutable types instead of a reference
void runProgram(vector<int>& intCode)
{
	for (int pos = 0; pos < intCode.size(); pos += 4)
	{
		constexpr int EXIT_CODE = 99;
		constexpr int ADDITION_CODE = 1;
		constexpr int MULTIPLICATION_CODE = 2;

		if (intCode[pos] == EXIT_CODE)
		{
			return;
		}
		else if (intCode[pos] == ADDITION_CODE)
		{
			auto firstValPos = intCode[pos + 1];
			auto secondValPos = intCode[pos + 2];
			auto resultPos = intCode[pos + 3];
			intCode[resultPos] = intCode[firstValPos] + intCode[secondValPos];
		}
		else if (intCode[pos] == MULTIPLICATION_CODE)
		{
			auto firstValPos = intCode[pos + 1];
			auto secondValPos = intCode[pos + 2];
			auto resultPos = intCode[pos + 3];
			intCode[resultPos] = intCode[firstValPos] * intCode[secondValPos];
		}
	}
}

pair<int, int> findNounAndVerb(vector<int> intCode, const int& expectedResult)
{
	for (int verb = 0; verb < 100; ++verb)
	{
		for (int noun = 0; noun < 100; ++noun)
		{
			auto currentIntCode = intCode;
			currentIntCode[1] = noun;
			currentIntCode[2] = verb;

			runProgram(currentIntCode);

			if (currentIntCode[0] == expectedResult)
			{
				return make_pair(noun, verb);
			}
		}
	}
}