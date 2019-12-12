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

	Instruction getInstruction(int n);
	int getInputParam(vector<int>& intCode, int index, ParamMode mode);
	pair<queue<int>, Day5Part2::Opcode> runProgram(vector<int>& intCode, queue<int> inputs, bool exitOnOutput = false);
};