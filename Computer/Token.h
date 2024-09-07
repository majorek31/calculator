#pragma once
#include <iostream>

struct Token
{
public:
	enum class TokenType
	{
		INVALID = -1,
		EXP = 0,
		NUMBER,
		ADD,
		SUB,
		MUL,
		DIV,
		LPARENT,
		RPARENT,
		EOL,
	};
	Token(TokenType _type) : Type(_type), Data(0) {}
	Token(TokenType _type, double _data) : Type(_type), Data(_data) {}

	static std::string TokenTypeToString(TokenType type);
	TokenType Type;
	double Data;
};

