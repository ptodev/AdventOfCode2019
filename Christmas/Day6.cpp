#include "libraries.h"

using namespace std;

//TODO: rewrite this with immutable data structures
struct Planet
{
	Planet(string name_, shared_ptr<Planet> planetToOrbit_) :
		name(name_),
		planetToOrbit(planetToOrbit_)
	{}

	const string name;
	//TODO: Ideally this should also be const
	shared_ptr<Planet> planetToOrbit;
};

shared_ptr<Planet>
findPlanetInVector(vector<shared_ptr<Planet>> planets, string planetName)
{
	for (auto p : planets)
	{
		if (p->name == planetName) return p;
	}
	return nullptr;
}

vector<shared_ptr<Planet>>
constructPlanets(vector<pair<string, string>> orbits)
{
	vector<shared_ptr<Planet>> result;

	auto centerOfMass = make_shared<Planet>("COM", nullptr);
	result.push_back(centerOfMass);

	//TODO: rewrite this with a fold
	for (const auto& orbit : orbits)
	{
		auto planetToOrbit = orbit.first;
		auto currentPlanetName = orbit.second;

		auto currentPlanet = make_shared<Planet>(currentPlanetName, nullptr);
		result.push_back(currentPlanet);
	}

	for (const auto& orbit : orbits)
	{
		auto planetToOrbit = orbit.first;
		auto currentPlanetName = orbit.second;

		auto currentPlanet = findPlanetInVector(result, currentPlanetName);
		currentPlanet->planetToOrbit = findPlanetInVector(result, planetToOrbit);
	}

	return result;
}

int
getNumberOfOrbits(shared_ptr<Planet> planet1, shared_ptr<Planet> planet2)
{
	int result = 0;

	while (planet1->planetToOrbit != planet2)
	{
		++result;
		planet1 = planet1->planetToOrbit;
	}

	return result;
}

shared_ptr<Planet>
getFirstCommonPlanet(shared_ptr<Planet> planet1, shared_ptr<Planet> planet2)
{
	vector<shared_ptr<Planet>> seq1;
	vector<shared_ptr<Planet>> seq2;

	while (planet1->planetToOrbit != nullptr)
	{
		seq1.push_back(planet1->planetToOrbit);
		planet1 = planet1->planetToOrbit;
	}

	while (planet2->planetToOrbit != nullptr)
	{
		seq2.push_back(planet2->planetToOrbit);
		planet2 = planet2->planetToOrbit;
	}

	for (int i = 0; i < seq1.size(); ++i)
	{
		if ( find(seq2.begin(), seq2.end(), seq1[i]) != seq2.end() )
		{
			return seq1[i];
		}
	}

	return nullptr;
}

int
PartOne(vector<pair<string, string>> orbits)
{
	auto planets = constructPlanets(orbits);

	auto totalNumOfOrbits =
		ranges::accumulate(
			planets |
			ranges::views::transform(
				[] (shared_ptr<Planet> planet)
				{
					return getNumberOfOrbits(planet, nullptr);
				})
			, 0);

	return totalNumOfOrbits;
}

int
PartTwo(vector<pair<string, string>> orbits)
{
	auto planets = constructPlanets(orbits);

	auto myOrbit = findPlanetInVector(planets, "YOU")->planetToOrbit;
	auto santaOrbit = findPlanetInVector(planets, "SAN")->planetToOrbit;
	auto commonOrbit = getFirstCommonPlanet(myOrbit, santaOrbit);

	auto numOfOrbits1 = getNumberOfOrbits(myOrbit, commonOrbit) + 1;
	auto numOfOrbits2 = getNumberOfOrbits(santaOrbit, commonOrbit) + 1;

	return numOfOrbits1 + numOfOrbits2;
}
