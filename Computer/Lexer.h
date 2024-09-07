#pragma once
#include <string>
#include <vector>
#include "Token.h"

class Lexer
{
public:
	struct Error
	{
		Error(char _what, int _where) : What(_what), Where(_where) {}
		char What;
		int Where;
	};
	Lexer();
	bool Parse(const std::string& data);
	const std::vector<Token>& GetTokens() const { return m_Tokens; }
	const std::vector<Error>& GetErrors() const { return m_Errors; }
private:
	void ParseNumber(const std::string& data);
	void ParseAction(const std::string& data);
private:
	int m_Offset;
	std::vector<Token> m_Tokens;
	std::vector<Error> m_Errors;
};

