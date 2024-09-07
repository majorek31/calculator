#include "Parser.h"

Parser::Parser(const std::vector<Token>& tokens) :
	m_Tokens(tokens), m_Offset(0), m_AbstractSyntaxTree(nullptr)
{
	m_AbstractSyntaxTree = new AbstractSyntaxTreeNode(Token::TokenType::EXP);
}

Parser::~Parser()
{
	FreeAbstractSyntaxTree(m_AbstractSyntaxTree);
}

void Parser::Compile()
{
	m_AbstractSyntaxTree = ParseExpression();
}

double Parser::Evaluate()
{
	return EvaluateNode(m_AbstractSyntaxTree);
}

Parser::AbstractSyntaxTreeNode* Parser::ParseExpression()
{
	AbstractSyntaxTreeNode* left = ParseTerm();

	while (m_Offset < m_Tokens.size())
	{
		const Token& token = m_Tokens[m_Offset];
		if (token.Type == Token::TokenType::ADD || token.Type == Token::TokenType::SUB)
		{
			m_Offset++;
			AbstractSyntaxTreeNode* right = ParseTerm();
			AbstractSyntaxTreeNode* node = new AbstractSyntaxTreeNode(token);
			node->Left = left;
			node->Right = right;
			left = node;
		}
		else
		{
			break;
		}
	}

	return left;
}

Parser::AbstractSyntaxTreeNode* Parser::ParseTerm()
{
	AbstractSyntaxTreeNode* left = ParseFactor();

	while (m_Offset < m_Tokens.size())
	{
		const Token& token = m_Tokens[m_Offset];
		if (token.Type == Token::TokenType::MUL || token.Type == Token::TokenType::DIV)
		{
			m_Offset++;
			AbstractSyntaxTreeNode* right = ParseFactor();
			AbstractSyntaxTreeNode* node = new AbstractSyntaxTreeNode(token);
			node->Left = left;
			node->Right = right;
			left = node;
		}
		else
		{
			break;
		}
	}

	return left;
}

Parser::AbstractSyntaxTreeNode* Parser::ParseFactor()
{
	const Token& token = m_Tokens[m_Offset];

	if (token.Type == Token::TokenType::LPARENT)
	{
		m_Offset++;
		AbstractSyntaxTreeNode* node = ParseExpression();
		m_Offset++;
		return node;
	}
	m_Offset++;
	return new AbstractSyntaxTreeNode(token);
}

void Parser::FreeAbstractSyntaxTree(AbstractSyntaxTreeNode* node)
{
	if (!node) return;

	FreeAbstractSyntaxTree(node->Left);
	FreeAbstractSyntaxTree(node->Right);

	delete node;
}

double Parser::EvaluateNode(AbstractSyntaxTreeNode* node)
{
	if (!node) return 0;
	if (node->Token.Type == Token::TokenType::NUMBER) return node->Token.Data;

	double left = EvaluateNode(node->Left);
	double right = EvaluateNode(node->Right);

	switch (node->Token.Type)
	{
	case Token::TokenType::ADD:
		return left + right;
	case Token::TokenType::SUB:
		return left - right;
	case Token::TokenType::MUL:
		return left * right;
	case Token::TokenType::DIV:
		return left / right;
	default:
		break;
	}
	return 0;
}
