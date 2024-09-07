#include "Token.h"

std::string Token::TokenTypeToString(TokenType type)
{
	switch (type)
	{
	case TokenType::INVALID: return "INVALID";
	case TokenType::EXP: return "EXPRESSION";
	case TokenType::NUMBER: return "NUMBER";
	case TokenType::ADD: return "ADD";
	case TokenType::SUB: return "SUB";
	case TokenType::MUL: return "MUL";
	case TokenType::DIV: return "DIV";
	case TokenType::LPARENT: return "LPARENT";
	case TokenType::RPARENT: return "RPARENT";
	case TokenType::EOL: return "EOL";
	default: return "Unknown Token";
	}
}
