#include "libraries.h"

using namespace std;
using Layer = vector<vector<char>>;

enum class Pixel : char
{
	Black = 0,
	White = 1,
	Transparent = 2
};

vector<Layer>
getLayers(vector<char> encodedImage, int width, int height)
{
	auto layers =
		encodedImage |
		ranges::views::chunk(width * height) |
		ranges::views::transform( ranges::views::chunk(width) );

	return layers;
}

int
countDigitInLayer(Layer l, char digit)
{
	auto digitsToCount =
		l |
		ranges::views::move |
		ranges::actions::join |
		ranges::actions::remove_if( [digit](auto n) { return n != digit; } );
		
	return digitsToCount.size();
}

auto
Part1(vector<char> encodedImage, int width, int height)
{
	auto layers = getLayers(encodedImage, width, height);

	auto numOfZerosInEachLayer =
		layers |
		ranges::views::transform(
			[](auto layer)
	{
		return countDigitInLayer(layer, 0);
	}) |
		ranges::views::enumerate;

	auto layerIdWithFewestZeros = ranges::accumulate(
		numOfZerosInEachLayer,
		make_pair(numOfZerosInEachLayer[0].first, numOfZerosInEachLayer[0].second),
		[](const auto& acc, const auto& currentElement)
		{
			if (currentElement.second < acc.second) return make_pair(currentElement.first, currentElement.second);
			else return acc;
		}).first;

	auto result =
		countDigitInLayer(layers[layerIdWithFewestZeros], 1) *
		countDigitInLayer(layers[layerIdWithFewestZeros], 2);

	return result;
}

auto
foldTwoPixels(char topPixel, char bottomPixel)
{
	if (topPixel == static_cast<char>(Pixel::Transparent))
	{
		return bottomPixel;
	}
	return topPixel;
}

vector<char>
foldTwoRows(vector<char> topRow, vector<char> bottomRow)
{
	return ranges::views::zip_with(foldTwoPixels, topRow, bottomRow);
}

Layer
foldTwoLayers(const Layer& topLayer, const Layer& bottomLayer)
{
	return ranges::views::zip_with(foldTwoRows, topLayer, bottomLayer);
}

auto
printLayer(const Layer& l)
{
	string result;
	for (const auto& row : l)
	{
		for (const auto& p : row)
		{
			if (p == static_cast<char>(Pixel::Transparent))
			{
				result += " ";
			}
			else if (p == static_cast<char>(Pixel::White))
			{
				result += "+";
			}
			else if (p == static_cast<char>(Pixel::Black))
			{
				result += "#";
			}
		}
		result += "\n";
	}
	return result;
}

auto
Part2(vector<char> encodedImage, int width, int height)
{
	auto layers = getLayers(encodedImage, width, height);
	
	// The starting accumulator image should be transparent
	Layer acc(height, vector<char>(width, static_cast<char>(Pixel::Transparent)));

	auto decodedImage = ranges::accumulate(
		layers,
		acc,
		[](const auto& acc, const auto& currentLayer)
		{
			return foldTwoLayers(acc, currentLayer);
		}
	);

	return printLayer(decodedImage);
}
