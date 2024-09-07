#include "Lexer.h"
#include <sstream>

Lexer::Lexer() : 
	m_Offset(0) 
{
}

bool Lexer::Parse(const std::string& data)
{
	for (m_Offset = 0; m_Offset < data.length(); m_Offset++)
	{
		char currentChar = data[m_Offset];
		if (isdigit(currentChar))
			ParseNumber(data);
		else if (currentChar != '\n')
			ParseAction(data);
		else
			m_Tokens.push_back(Token(Token::TokenType::EOL));
	}
	if (m_Errors.empty())
		return true;
	return false;
}

void Lexer::ParseNumber(const std::string& data)
{

	std::stringstream ss;
	char currentChar = data[m_Offset];
	while (isdigit(currentChar) || currentChar == '.')
	{
		ss << currentChar;
		m_Offset++;
		currentChar = data[m_Offset];
	}
	m_Offset--;
	m_Tokens.push_back(Token(Token::TokenType::NUMBER, atof(ss.str().c_str())));
}

void Lexer::ParseAction(const std::string& data)
{
	char currentChar = data[m_Offset];
	if (currentChar == ' ')
		return;
	switch (currentChar)
	{
	case '+':
		m_Tokens.push_back(Token(Token::TokenType::ADD));
		break;
	case '-':
		m_Tokens.push_back(Token(Token::TokenType::SUB));
		break;
	case '*':
		m_Tokens.push_back(Token(Token::TokenType::MUL));
		break;
	case '/':
		m_Tokens.push_back(Token(Token::TokenType::DIV));
		break;
	case '(':
		m_Tokens.push_back(Token(Token::TokenType::LPARENT));
		break;
	case ')':
		m_Tokens.push_back(Token(Token::TokenType::RPARENT));
		break;
	default:
		m_Errors.push_back(Error(currentChar, m_Offset));
	}
}
