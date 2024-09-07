#pragma once
#include "Lexer.h"

class Parser 
{
public:
	struct AbstractSyntaxTreeNode
	{
		AbstractSyntaxTreeNode(const Token& _token) : Token(_token), Left(nullptr), Right(nullptr) {}

		const Token& Token;
		AbstractSyntaxTreeNode* Left;
		AbstractSyntaxTreeNode* Right;
	};
	Parser(const std::vector<Token>& tokens);
	~Parser();
	void Compile();
	double Evaluate();
private:
	AbstractSyntaxTreeNode* ParseExpression();
	AbstractSyntaxTreeNode* ParseTerm();
	AbstractSyntaxTreeNode* ParseFactor();
	void FreeAbstractSyntaxTree(AbstractSyntaxTreeNode* node);

	double EvaluateNode(AbstractSyntaxTreeNode* node);
private:
	AbstractSyntaxTreeNode* m_AbstractSyntaxTree;
	int m_Offset;
	const std::vector<Token>& m_Tokens;
};