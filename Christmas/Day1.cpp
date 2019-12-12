#include "libraries.h"

using namespace std;

int calculateOneFuel(int mass)
{
	if (mass <= 0)
	{
		return 0;
	}

	static map<int, int> memory;
	if (memory.find(mass) != memory.end())
	{
		return memory[mass];
	}

	int result = mass / 3 - 2;
	memory[mass] = result;
	return result;
}

int calculateOneTotalFuel(int mass)
{
	if (mass <= 0)
	{
		return 0;
	}

	static map<int, int> memory;
	if (memory.find(mass) != memory.end())
	{
		return memory[mass];
	}

	int currentFuel = calculateOneFuel(mass);
	int result = currentFuel + calculateOneTotalFuel( currentFuel );

	result = result > 0 ? result : 0;
	memory[mass] = result;
	return result;
}

int calculateAllFuelPartOne(const vector<int>& masses)
{
	// TODO: Use accumulator?
	int totalFuel = 0;
	for (const auto& mass : masses)
	{
		totalFuel += calculateOneFuel(mass);
	}
	return totalFuel;
}

int calculateAllFuelPartOne2(const vector<int>& masses)
{
	auto totalFuel = ranges::accumulate
	(
		masses | ranges::views::transform(calculateOneFuel),
		0
	);

	return totalFuel;
}

int calculateAllFuelPartTwo(const vector<int>& masses)
{
	// TODO: Use accumulator?
	int totalFuel = 0;
	for (const auto& mass : masses)
	{
		totalFuel += calculateOneTotalFuel(mass);
	}
	return totalFuel;
}

