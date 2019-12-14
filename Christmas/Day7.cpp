#include "libraries.h"
#include "Day5.h"

using namespace std;

int
runAmplifiers(vector<long long>& intCode, vector<long long> phaseSeq, int signal)
{
	for (const auto& phase : phaseSeq)
	{
		queue<long long> inputs;
		inputs.push(phase);
		inputs.push(signal);

		auto output = Day5Part2::runProgram(intCode, inputs, true);
		signal = output.first.front();
	}
	return signal;
}

int
runAmplifiersInFeedbackLoop(vector<long long>& intCode, vector<long long> phaseSeq, long long signal)
{
	optional<long long> lastSignalFromLastAmplifier;
	while (true)
	{
		for (int i=0; i<phaseSeq.size(); ++i)
		{
			const auto& phase = phaseSeq[i];
		
			queue<long long> inputs;
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
Part1(vector<long long> intCode, int signal)
{
	auto phaseSeq = vector<long long>{ 0, 1, 2, 3, 4 };

	vector<long long> results;
	do
	{
		auto currentResult = runAmplifiers(intCode, phaseSeq, signal);
		results.push_back(currentResult);
	} while (next_permutation(phaseSeq.begin(), phaseSeq.end()));

	return *max_element(results.begin(), results.end());
}

int
Part2(vector<long long> intCode, int signal)
{
	auto phaseSeq = vector<long long>{ 5, 6, 7, 8, 9 };

	vector<long long> results;
	do
	{
		auto currentResult = runAmplifiersInFeedbackLoop(intCode, phaseSeq, signal);
		results.push_back(currentResult);
	} while (next_permutation(phaseSeq.begin(), phaseSeq.end()));

	return *max_element(results.begin(), results.end());
}
