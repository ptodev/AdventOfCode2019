#include "libraries.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

auto
getAsteroidLocations(string map)
{
    vector<pair<int, int>> result;
    vector<string> map2 = ranges::views::split(map, '\n');
    
    for (int row = 0; row < map2.size(); ++row)
    {
        for (int col = 0; col < map2[0].size(); ++col)
        {
            if (map2[row][col] == '#')
            {
                result.push_back(make_pair(col, row));
            }
        }
    }

    return result;
}

auto
getAngle(pair<int, int> pos1, pair<int, int> pos2)
{
    double dx = pos2.first - pos1.first;
    double dy = pos2.second - pos1.second;

    auto angle = atan(abs(dy / dx)) * 180.0 / M_PI;

    if (dx > 0 && dy > 0)
    {
        // Lower right quadrant
        angle += 270;
    }
    else if (dx <= 0 && dy >= 0)
    {
        // Lower left quadrant
        angle += 180;
    }
    else if (dx < 0 && dy < 0)
    {
        // Upper left quadrant
        angle += 90;
    }
    else if (dx < 0 && dy > 0)
    {
        // Upper right quadrant, do nothing
    }

    return angle;
}

int
countSeenAsteroids(pair<int, int> currentLocation, vector<pair<int, int>> asteroidList)
{
    vector<double> relativeAsteroidLocations =
        asteroidList |
        ranges::views::remove_if(
            [currentLocation](const auto& coord)
            {
                // Do not count the central asteroid as a seen one
                return (coord == currentLocation) ? true : false;
            }) |
        ranges::views::transform(
            [currentLocation](auto otherLocation)
            {
                //TODO: this does too many combinations of the same asteroids
                return getAngle(currentLocation, otherLocation);
            });

    vector<double> seenAsteroids =
        ranges::actions::sort(relativeAsteroidLocations) |
        ranges::views::unique(
            [](const auto & val1, const auto & val2)
            {
                return (abs(val1 - val2) < 0.000000001) ? true : false;
            });

    return seenAsteroids.size();
}

auto
Part1(string map)
{
    auto asteroidList = getAsteroidLocations(map);

    auto maxSeenAsteroids = ranges::accumulate(
        asteroidList | ranges::views::transform(
            [asteroidList](auto asteroidLocation)
            {
                return countSeenAsteroids(
                    asteroidLocation, 
                    asteroidList | 
                    ranges::views::remove_if(
                        [asteroidLocation, asteroidList](const auto& asteroid) 
                        {
                            return asteroid == asteroidLocation; 
                        })
                );
            }),
        -1,
        [](const auto& currentMax, const auto& currentItem)
        {
            return currentItem > currentMax ? currentItem : currentMax;
        });

    return maxSeenAsteroids;
}