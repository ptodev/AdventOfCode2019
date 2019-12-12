#include "libraries.h"

using namespace std;

class CanvasElement
{
private:
	char data;
	int m_stepNum;

public:
	CanvasElement(char c = '.') : data(c), m_stepNum(-1) {}

	bool isJunction() const
	{
		if (data == 'X') return true;
		return false;
	}

	int getStepNumber() const
	{
		return m_stepNum;
	}

	void placeWire(char wireId, int stepNum)
	{
		if (data == '.')
		{
			data = wireId;
			m_stepNum = stepNum;
		}
		else if (data != '.' && data != wireId)
		{
			//TODO: use constexpr instead of magic chars
			data = 'X';
			m_stepNum += stepNum;
		}
		else
		{
			//TODO: throw
		}
	}
};

class Canvas
{
private:
	int m_minY;
	int m_minX;
	vector<vector<CanvasElement>> m_data;

	//TODO: should we use a shared pointer?
	//TODO: when is it ok to return a reference?
	CanvasElement&
	element(int x, int y)
	{
		auto& e = m_data[y - m_minY][x - m_minX];
		return e;
	}

	pair<int, int>
	getScaledCoordinates(int x, int y)
	{
		return make_pair(x + m_minX, y + m_minY);
	}

public:
	Canvas( size_t height, size_t width, int minY, int minX ) : 
		m_minY(minY),
		m_minX(minX),
		m_data(height, vector<CanvasElement>(width))
	{}

	void placeWire(int x, int y, char wireId, int stepNum)
	{
		element(x, y).placeWire(wireId, stepNum);
	}

	vector<pair<int, int>>
		getJunctions()
	{
		vector<pair<int, int>> result;
		for (int y = 0; y < m_data.size(); ++y)
		{
			for (int x = 0; x < m_data[0].size(); ++x)
			{
				if (m_data[y][x].isJunction())
				{
					result.push_back(getScaledCoordinates(x, y));
				}
			}
		}
		return result;
	}

	vector<pair<pair<int, int>, int>>
	getJunctionsAndStepNumbers()
	{
		vector<pair<pair<int, int>, int>> result;
		for (int y = 0; y < m_data.size(); ++y)
		{
			for (int x = 0; x < m_data[0].size(); ++x)
			{
				if (m_data[y][x].isJunction())
				{
					result.push_back(
						make_pair(
							getScaledCoordinates(x, y), m_data[y][x].getStepNumber()
						)
					);
				}
			}
		}
		return result;
	}
};

unsigned
distanceBetweenPoints(pair<int, int> p1, pair<int, int> p2)
{
	return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

auto
getRequiredMinMaxCanvasCoordinates(
	const vector<pair<int, int>>& coordinates)
{
	//TODO: If the the input vector is empty throw

	auto result = vector<pair<int, int>> {
		make_pair(coordinates[0].first, coordinates[0].second),
		make_pair(coordinates[0].first, coordinates[0].second)
	};

	auto& upperRightPoint = result[1];
	auto& downLeftPoint = result[0];

	auto& largestX = upperRightPoint.first;
	auto& largestY = upperRightPoint.second;

	auto& smallestX = downLeftPoint.first;
	auto& smallestY = downLeftPoint.second;

	for (const auto& c : coordinates)
	{
		// Largest X coordinate
		if (c.first  > largestX)  largestX  = c.first;
		// Smallest X coordinate
		if (c.first  < smallestX) smallestX = c.first;
		// Largest Y coordinate
		if (c.second > largestY)  largestY  = c.second;
		// Smallest Y coordinate
		if (c.second < smallestY) smallestY = c.second;
	}

	return result;
}

//TODO: Use variadic templates
auto
drawPlainCanvas(
	vector<pair<int, int>> coordinates1,
	vector<pair<int, int>> coordinates2)
{
	auto minMax1 = getRequiredMinMaxCanvasCoordinates( coordinates1 );
	auto minMax2 = getRequiredMinMaxCanvasCoordinates( coordinates2 );

	auto totalMinMax = getRequiredMinMaxCanvasCoordinates(
		vector<pair<int, int>>{ minMax1[0], minMax1[1], minMax2[0], minMax2[1] }
	);

	auto width = totalMinMax[1].first - totalMinMax[0].first;
	auto heigth = totalMinMax[1].second - totalMinMax[0].second;

	return Canvas(heigth+1, width+1, totalMinMax[0].second, totalMinMax[0].first);
}

auto
drawWireOnCanvas(
	Canvas canvas,
	const vector<pair<int, int>>& wireCoordinates,
	char wireId)
{
	for (int i=0; i< wireCoordinates.size(); ++i)
	{
		auto c = wireCoordinates[i];
		canvas.placeWire(c.first, c.second, wireId, i);
	}

	return canvas;
}

auto
advancePoint(const pair<int, int>& startingPoint, const pair<int, int>& direction)
{
	const pair<int, int> newPoint = make_pair(
		startingPoint.first + direction.first,
		startingPoint.second + direction.second
	);

	return newPoint;
}

auto
generateWireCoordinates(const pair<int, int>& startingPoint, vector<string> instructions)
{
	vector<pair<int, int>> result;

	auto currentPoint = startingPoint;
	result.push_back(currentPoint);

	for (const auto& i : instructions)
	{
		char directionChar = i[0];
		pair<int, int> directionVector;
		if (directionChar == 'U') directionVector = pair<int, int>{ 0, 1 };
		else if (directionChar == 'D') directionVector = pair<int, int>{ 0,-1 };
		else if (directionChar == 'L') directionVector = pair<int, int>{-1, 0 };
		else if (directionChar == 'R') directionVector = pair<int, int>{ 1, 0 };
		else {/* TODO: throw */}

		auto distance = stoi(
			static_cast<string>(
				i | ranges::views::drop(1)
			)
		);

		for (int counter = 0; counter < distance; ++counter)
		{
			currentPoint = advancePoint(currentPoint, directionVector);
			result.push_back(currentPoint);
		}
	}

	return result;
}

auto
getClosestJuntionDistance(
	Canvas canvas,
	const pair<int, int>& centralPoint)
{
	auto juntionList = canvas.getJunctions();

	auto currentClosestDistance = distanceBetweenPoints(centralPoint, juntionList[0]);
	auto currentClosestPoint = juntionList[0];

	for (int i = 1; i < juntionList.size(); ++i)
	{
		if (centralPoint.first == juntionList[i].first &&
			centralPoint.second == juntionList[i].second)
		{
			continue;
		}

		auto currentDistance = distanceBetweenPoints(centralPoint, juntionList[i]);
		if (currentDistance < currentClosestDistance)
		{
			currentClosestDistance = currentDistance;
			currentClosestPoint = juntionList[i];
		}
	}

	return currentClosestDistance;
}

int
getClosestJuntionInTime(
	Canvas canvas,
	const pair<int, int>& centralPoint)
{
	auto juntionList = canvas.getJunctionsAndStepNumbers();
	vector<int> allStepDistances;
	for (const auto& j : juntionList)
	{
		if (centralPoint.first == j.first.first &&
			centralPoint.second == j.first.second)
		{
			continue;
		}

		allStepDistances.push_back(j.second);
	}
	return *min_element(allStepDistances.begin(), allStepDistances.end());
}