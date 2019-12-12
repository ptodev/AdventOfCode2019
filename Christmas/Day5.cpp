#include "libraries.h"
#include "Day5.h"

using namespace std;

namespace Day5Part1
{
	enum class Opcode
	{
		Addition = 1,
		Multiplication = 2,
		Input = 3,
		Output = 4,
		Exit = 99
	};

	enum class ParamMode
	{
		Positional = 0,
		Immediate = 1
	};

	struct Instruction
	{
		Opcode code;
		vector<ParamMode> paramModes;
	};

	Instruction
		getInstruction(int n)
	{
		Instruction result;

		int rawOpcode = n % 100;
		//TODO: Do we throw if the input ints don't correspond to values in the enums?
		result.code = static_cast<Opcode>(rawOpcode);
		n = n / 100;

		for (const auto& i : { 1,2,3 })
		{
			//TODO: Do we throw if the input ints don't correspond to values in the enums?
			auto mode = static_cast<ParamMode>(n % 10);
			result.paramModes.push_back(mode);
			n = n / 10;
		}

		return result;
	}

	int
		getInputParam(vector<int>& intCode, int index, ParamMode mode)
	{
		if (mode == ParamMode::Positional)
		{
			return intCode[intCode[index]];
		}

		if (mode == ParamMode::Immediate)
		{
			return intCode[index];
		}

		//TODO: throw unknown param mode
	}

	queue<int>
		runProgram(vector<int>& intCode, queue<int> inputs)
	{
		queue<int> output;

		for (int pos = 0; pos < intCode.size();)
		{
			auto currentInstruction = getInstruction(intCode[pos]);

			switch (currentInstruction.code)
			{
			case Opcode::Exit:
			{
				return output;
			}
			case Opcode::Addition:
			{
				auto firstVal = getInputParam(intCode, pos + 1, currentInstruction.paramModes[0]);
				auto secondVal = getInputParam(intCode, pos + 2, currentInstruction.paramModes[1]);
				auto resultPos = intCode[pos + 3];
				intCode[resultPos] = firstVal + secondVal;

				pos += 4;
				break;
			}
			case Opcode::Multiplication:
			{
				auto firstVal = getInputParam(intCode, pos + 1, currentInstruction.paramModes[0]);
				auto secondVal = getInputParam(intCode, pos + 2, currentInstruction.paramModes[1]);
				auto resultPos = intCode[pos + 3];
				intCode[resultPos] = firstVal * secondVal;

				pos += 4;
				break;
			}
			case Opcode::Input:
			{
				//TODO: If queue is empty, throw
				auto currentInput = inputs.front();
				inputs.pop();

				auto destPos = intCode[pos + 1];
				intCode[destPos] = currentInput;

				pos += 2;
				break;
			}
			case Opcode::Output:
			{
				auto val = getInputParam(intCode, pos + 1, currentInstruction.paramModes[0]);
				output.push(val);

				pos += 2;
				break;
			}
			}
		}
	}
};

Day5Part2::Instruction
Day5Part2::getInstruction(int n)
{
	Instruction result;

	int rawOpcode = n % 100;
	//TODO: Do we throw if the input ints don't correspond to values in the enums?
	result.code = static_cast<Opcode>(rawOpcode);
	n = n / 100;

	for (const auto& i : { 1,2,3 })
	{
		//TODO: Do we throw if the input ints don't correspond to values in the enums?
		auto mode = static_cast<ParamMode>(n % 10);
		result.paramModes.push_back(mode);
		n = n / 10;
	}

	return result;
}

int
Day5Part2::getInputParam(vector<int>& intCode, int index, ParamMode mode)
{
	if (mode == ParamMode::Positional)
	{
		return intCode[intCode[index]];
	}

	if (mode == ParamMode::Immediate)
	{
		return intCode[index];
	}

	//TODO: throw unknown param mode
}

pair<queue<int>, Day5Part2::Opcode>
Day5Part2::runProgram(vector<int>& intCode, queue<int> inputs, bool exitOnOutput)
{
	queue<int> output;

	for (int pos = 0; pos < intCode.size();)
	{
		auto currentInstruction = getInstruction(intCode[pos]);

		switch (currentInstruction.code)
		{
		case Opcode::Exit:
		{
			return make_pair(output, Opcode::Exit);
		}
		case Opcode::Addition:
		{
			auto firstVal = getInputParam(intCode, pos + 1, currentInstruction.paramModes[0]);
			auto secondVal = getInputParam(intCode, pos + 2, currentInstruction.paramModes[1]);
			auto resultPos = intCode[pos + 3];
			intCode[resultPos] = firstVal + secondVal;

			if (resultPos != pos) pos += 4;
			break;
		}
		case Opcode::Multiplication:
		{
			auto firstVal = getInputParam(intCode, pos + 1, currentInstruction.paramModes[0]);
			auto secondVal = getInputParam(intCode, pos + 2, currentInstruction.paramModes[1]);
			auto resultPos = intCode[pos + 3];
			intCode[resultPos] = firstVal * secondVal;

			if (resultPos != pos) pos += 4;
			break;
		}
		case Opcode::Input:
		{
			//TODO: If queue is empty, throw
			auto currentInput = inputs.front();
			inputs.pop();

			auto destPos = intCode[pos + 1];
			intCode[destPos] = currentInput;

			if (destPos != pos) pos += 2;
			break;
		}
		case Opcode::Output:
		{
			auto val = getInputParam(intCode, pos + 1, currentInstruction.paramModes[0]);
			output.push(val);

			if (exitOnOutput) return make_pair(output, Opcode::Output);

			pos += 2;
			break;
		}
		case Opcode::JumpIfTrue:
		{
			auto firstVal = getInputParam(intCode, pos + 1, currentInstruction.paramModes[0]);
			auto secondVal = getInputParam(intCode, pos + 2, currentInstruction.paramModes[1]);

			if (firstVal != 0)
			{
				pos = secondVal;
			}
			else
			{
				pos += 3;
			}

			break;
		}
		case Opcode::JumpIfFalse:
		{
			auto firstVal = getInputParam(intCode, pos + 1, currentInstruction.paramModes[0]);
			auto secondVal = getInputParam(intCode, pos + 2, currentInstruction.paramModes[1]);

			if (firstVal == 0)
			{
				pos = secondVal;
			}
			else
			{
				pos += 3;
			}

			break;
		}
		case Opcode::LessThan:
		{
			auto firstVal = getInputParam(intCode, pos + 1, currentInstruction.paramModes[0]);
			auto secondVal = getInputParam(intCode, pos + 2, currentInstruction.paramModes[1]);
			auto resultPos = intCode[pos + 3];

			if (firstVal < secondVal)
			{
				intCode[resultPos] = 1;
			}
			else
			{
				intCode[resultPos] = 0;
			}

			if (resultPos != pos) pos += 4;
			break;
		}
		case Opcode::Equals:
		{
			auto firstVal = getInputParam(intCode, pos + 1, currentInstruction.paramModes[0]);
			auto secondVal = getInputParam(intCode, pos + 2, currentInstruction.paramModes[1]);
			auto resultPos = intCode[pos + 3];

			if (firstVal == secondVal)
			{
				intCode[resultPos] = 1;
			}
			else
			{
				intCode[resultPos] = 0;
			}

			if (resultPos != pos) pos += 4;
			break;
		}
		}
	}
}