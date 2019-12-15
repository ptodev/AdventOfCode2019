#include "libraries.h"
#include "../Christmas/Day10.cpp"

TEST(TestDay10, getAngle)
{
    EXPECT_EQ(getAngle(make_pair(2, 2), make_pair(4, 2)), 0);
    EXPECT_EQ(getAngle(make_pair(2, 2), make_pair(4, 0)), 45);
    EXPECT_EQ(getAngle(make_pair(2, 2), make_pair(2, 0)), 90);
    EXPECT_EQ(getAngle(make_pair(2, 2), make_pair(0, 0)), 135);
    EXPECT_EQ(getAngle(make_pair(2, 2), make_pair(0, 2)), 180);
    EXPECT_EQ(getAngle(make_pair(2, 2), make_pair(0, 4)), 225);
    EXPECT_EQ(getAngle(make_pair(2, 2), make_pair(2, 4)), 270);
    EXPECT_EQ(getAngle(make_pair(2, 2), make_pair(4, 4)), 315 );
}

TEST(TestDay10, countSeenAsteroids)
{
    string map = ".#..#\n.....\n#####\n....#\n...##\n";
    auto asteroidList = getAsteroidLocations(map);
    EXPECT_EQ(countSeenAsteroids(make_pair(1, 0), asteroidList), 7);
    EXPECT_EQ(countSeenAsteroids(make_pair(4, 0), asteroidList), 7);
    EXPECT_EQ(countSeenAsteroids(make_pair(0, 2), asteroidList), 6);
    EXPECT_EQ(countSeenAsteroids(make_pair(1, 2), asteroidList), 7);
    EXPECT_EQ(countSeenAsteroids(make_pair(3, 2), asteroidList), 7);
    EXPECT_EQ(countSeenAsteroids(make_pair(4, 2), asteroidList), 5);
    EXPECT_EQ(countSeenAsteroids(make_pair(4, 3), asteroidList), 7);
    EXPECT_EQ(countSeenAsteroids(make_pair(3, 4), asteroidList), 8);
    EXPECT_EQ(countSeenAsteroids(make_pair(4, 4), asteroidList), 7);
}

TEST(TestDay10, countSeenAsteroids2)
{
    string map = ".#...\n.....\n..#..\n.....\n...#.\n";
    auto asteroidList = getAsteroidLocations(map);
    EXPECT_EQ(countSeenAsteroids(make_pair(1, 0), asteroidList), 1);
    EXPECT_EQ(countSeenAsteroids(make_pair(2, 2), asteroidList), 2);
    EXPECT_EQ(countSeenAsteroids(make_pair(3, 4), asteroidList), 1);
}

TEST(TestDay10, Basic1)
{
    string map = ".#..#\n.....\n#####\n....#\n...##\n";
    EXPECT_EQ(Part1(map), 8);
}

TEST(TestDay10, PartOne)
{
    string map = ".###.#...#.#.##.#.####..\n.#....#####...#.######..\n#.#.###.###.#.....#.####\n##.###..##..####.#.####.\n###########.#######.##.#\n##########.#########.##.\n.#.##.########.##...###.\n###.#.##.#####.#.###.###\n##.#####.##..###.#.##.#.\n.#.#.#####.####.#..#####\n.###.#####.#..#..##.#.##\n########.##.#...########\n.####..##..#.###.###.#.#\n....######.##.#.######.#\n###.####.######.#....###\n############.#.#.##.####\n##...##..####.####.#..##\n.###.#########.###..#.##\n#.##.#.#...##...#####..#\n##.#..###############.##\n##.###.#####.##.######..\n##.#####.#.#.##..#######\n...#######.######...####\n#....#.#.#.####.#.#.#.##\n";
    EXPECT_EQ(Part1(map), 280);
}

