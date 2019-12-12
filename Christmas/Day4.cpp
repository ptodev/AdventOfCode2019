#include "libraries.h"

using namespace std;

vector<int>
generateValidPasswords(int min, int max)
{
	auto isInvalidPassword = [](int n)
	{
		n = abs(n);
		optional<int> previousDigit;
		bool areTwoAdjacentDigitsSame = false;

		while (n > 0)
		{
			int currentDigit = n % 10;

			if (previousDigit)
			{
				if (previousDigit < currentDigit)
				{
					return true;
				}
				else if (previousDigit == currentDigit)
				{
					areTwoAdjacentDigitsSame = true;
				}
			}

			previousDigit = currentDigit;
			n = n / 10;
		}

		if (!areTwoAdjacentDigitsSame)
		{
			return true;
		}

		return false;
	};

	vector<int> result =
		ranges::views::ints(min, max + 1) |
		ranges::views::remove_if(isInvalidPassword);

	return result;
}

bool
isInvalidPassword2(int n)
{
	n = abs(n);
	optional<int> previousDigit;
	int matchingStreak = 1;
	bool isMatchingStreakAchieved = false;
	int requiredMatchingStreak = 2;

	while (n > 0)
	{
		int currentDigit = n % 10;

		if (previousDigit)
		{
			if (previousDigit < currentDigit)
			{
				return true;
			}
			else if (previousDigit == currentDigit)
			{
				++matchingStreak;
			}
			else
			{
				if (matchingStreak == requiredMatchingStreak)
				{
					isMatchingStreakAchieved = true;
				}

				matchingStreak = 1;
			}
		}

		previousDigit = currentDigit;
		n = n / 10;
	}

	if (matchingStreak == requiredMatchingStreak)
	{
		isMatchingStreakAchieved = true;
	}

	if (!isMatchingStreakAchieved)
	{
		return true;
	}

	return false;
};

vector<int>
generateValidPasswords2(int min, int max)
{
	vector<int> result =
		ranges::views::ints(min, max + 1) |
		ranges::views::remove_if(isInvalidPassword2);

	return result;
}

