#include "libraries.h"
#include "Day5.h"

using namespace std;

int
runAmplifiers(vector<int>& intCode, vector<int> phaseSeq, int signal)
{
	for (const auto& phase : phaseSeq)
	{
		queue<int> inputs;
		inputs.push(phase);
		inputs.push(signal);

		auto output = Day5Part2::runProgram(intCode, inputs, true);
		signal = output.first.front();
	}
	return signal;
}

int
runAmplifiersInFeedbackLoop(vector<int>& intCode, vector<int> phaseSeq, int signal)
{
	optional<int> lastSignalFromLastAmplifier;
	while (true)
	{
		for (int i=0; i<phaseSeq.size(); ++i)
		{
			const auto& phase = phaseSeq[i];
		
			queue<int> inputs;
			inputs.push(phase);
			inputs.push(signal);

			auto output = Day5Part2::runProgram(intCode, inputs, true);
			if (output.second == Day5Part2::Opcode::Exit)
			{
				if (lastSignalFromLastAmplifier)
				{
					return lastSignalFromLastAmplifier.value();
				}
				else { /* TODO: throw */ }
			}

			signal = output.first.front();
			if (i == phaseSeq.size() - 1)
			{
				lastSignalFromLastAmplifier = signal;
			}
		}
	}
}

int
Part1(vector<int> intCode, int signal)
{
	auto phaseSeq = vector<int>{ 0, 1, 2, 3, 4 };

	vector<int> results;
	do
	{
		auto currentResult = runAmplifiers(intCode, phaseSeq, signal);
		results.push_back(currentResult);
	} while (next_permutation(phaseSeq.begin(), phaseSeq.end()));

	return *max_element(results.begin(), results.end());
}

int
Part2(vector<int> intCode, int signal)
{
	auto phaseSeq = vector<int>{ 5, 6, 7, 8, 9 };

	vector<int> results;
	do
	{
		auto currentResult = runAmplifiersInFeedbackLoop(intCode, phaseSeq, signal);
		results.push_back(currentResult);
	} while (next_permutation(phaseSeq.begin(), phaseSeq.end()));

	return *max_element(results.begin(), results.end());
}
