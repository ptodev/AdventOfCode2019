#pragma once

#include "libraries.h"

using namespace std;

namespace Day5Part2
{
	enum class Opcode
	{
		Addition = 1,
		Multiplication = 2,
		Input = 3,
		Output = 4,
		JumpIfTrue = 5,
		JumpIfFalse = 6,
		LessThan = 7,
		Equals = 8,
		RelativeBaseOffset = 9,
		Exit = 99
	};

	enum class ParamMode
	{
		Positional = 0,
		Immediate = 1,
		Relative = 2
	};

	struct Instruction
	{
		Opcode code;
		vector<ParamMode> paramModes;
	};

	//TODO: Make Intcode templated so that it doesn't have to store just "long long"
	class Intcode
	{
	private:
		vector<long long> data;

	public:
		// The constructor is implicit on purpose
		Intcode(vector<long long> data_) :
			data(data_) 
		{};

		size_t size() const
		{
			return data.size();
		}

		//TODO: Infer size_t?
		long long at(size_t i) const
		{
			if (i < data.size())
			{
				return data[i];
			}
			return 0;
		}

		void set(size_t i, long long code)
		{
			if (i < data.size())
			{
				data[i] = code;
			}
			else
			{
				size_t required_extention = i - data.size() + 1;
				//data.reserve( ( data.size() + required_extention) * 5 );
				for (int i = 0; i < required_extention - 1; ++i)
				{
					data.push_back(0);
				}
				data.push_back(code);
			}
		}
	};

	Instruction getInstruction(long long n);
	long long getInputParam(Intcode& intCode, int index, ParamMode mode, long long relativeBase);
	long long setOutputParam(Intcode& intCode, int index, ParamMode mode, long long relativeBase, long long val);
	pair<queue<long long>, Day5Part2::Opcode> runProgram(Intcode intCode, queue<long long> inputs, bool exitOnOutput = false);
};