#pragma once
#include <vector>
using namespace std;
#include "symbol.h"
#include "instructions.h"

class Node{
public:
	virtual ~Node();
	virtual void Interpret();
	virtual void Code(InstructionsClass &machinecode);
private:
};
class ExpressionNode{//pure virtual - all inherited delete their own
public:
	ExpressionNode();
	virtual ~ExpressionNode();
	virtual int Evaluate();
	virtual void Code(InstructionsClass &machinecode);
private:
	int mInt;
};
class IdentifierNode: public ExpressionNode{
public:
	IdentifierNode(string label, SymbolTableClass *SymbolTable);
	virtual ~IdentifierNode();
	void DeclareVariable();
	void SetValue(int v);
	int GetIndex();
	virtual int Evaluate();
	virtual void Code(InstructionsClass &machinecode);
private:
	string mLabel;
	SymbolTableClass *mSymbolTable;
};
class StatementNode: public Node{
public:
	StatementNode();
	virtual ~StatementNode();
private:
	vector< StatementNode * > mStatementNodeVector;
};
class StatementGroupNode: public Node{
public:
	StatementGroupNode();
	virtual ~StatementGroupNode();
	virtual void AddStatement(StatementNode *node);
	virtual void Interpret();
	virtual void Code(InstructionsClass &machinecode);
private:
	vector< StatementNode * > mStatementGroupNodeVector; 
};
class IfStatementNode: public StatementNode{
public:
	IfStatementNode(ExpressionNode *enode, StatementNode *snode);
	virtual ~IfStatementNode();
	virtual void Interpret();
	virtual void Code(InstructionsClass &machinecode);
	void SetElse();
	bool GetElse();
	void IfStatementNode::SetElseNode(StatementNode *snode);

private:
	ExpressionNode *mExpressionNode;
	StatementNode *mStatementNode;
	StatementNode *mStatementNodeElse;
	bool isElse;
};
class WhileStatementNode: public StatementNode{
public:
	WhileStatementNode(ExpressionNode *enode, StatementNode *snode);
	virtual ~WhileStatementNode();
	virtual void Interpret();
	virtual void Code(InstructionsClass &machinecode);
private:
	ExpressionNode *mExpressionNode;
	StatementNode *mStatementNode;
};
class CoutStatementNode: public StatementNode{
public:
	CoutStatementNode();
	virtual ~CoutStatementNode();
	virtual void Interpret();
	virtual void Code(InstructionsClass &machinecode);
	void addExpression(ExpressionNode *);
private:
	vector<ExpressionNode *> mExpressionNodeVec;
};
class DeclarationStatementNode: public StatementNode{
public:
	DeclarationStatementNode(IdentifierNode *mIdentifierNode);
	virtual ~DeclarationStatementNode();
	virtual void Interpret();
	virtual void Code(InstructionsClass &machinecode);
private:
	IdentifierNode *mIdentifierNode;
};
class BlockNode: public StatementNode{
public:
	BlockNode(StatementGroupNode *mStatementGroupNode, SymbolTableClass *mSymbolTable);
	virtual ~BlockNode();
	virtual void Interpret();
	virtual void Code(InstructionsClass &machinecode);
private:
	StatementGroupNode *mStatementGroupNode;
	SymbolTableClass *mSymbolTable;
};
class AssignmentStatementNode: public StatementNode{
public:
	AssignmentStatementNode(IdentifierNode *mIdentifierNode, ExpressionNode *mExpressionNode);
	virtual ~AssignmentStatementNode();
	virtual void Interpret();
	virtual void Code(InstructionsClass &machinecode);
protected:
	IdentifierNode *mIdentifierNode;
	ExpressionNode *mExpressionNode;
};
class PlusEqualNode: public AssignmentStatementNode{
public:
	PlusEqualNode(IdentifierNode *mIdentifierNode, ExpressionNode *mExpressionNode);
	virtual ~PlusEqualNode();
	virtual void Interpret();
	virtual void Code(InstructionsClass &machinecode);
private:
};
class MinusEqualNode: public AssignmentStatementNode{
public:
	MinusEqualNode(IdentifierNode *mIdentifierNode, ExpressionNode *mExpressionNode);
	virtual ~MinusEqualNode();
	virtual void Interpret();
	virtual void Code(InstructionsClass &machinecode);
private:
};
class TimesEqualNode: public AssignmentStatementNode{
public:
	TimesEqualNode(IdentifierNode *mIdentifierNode, ExpressionNode *mExpressionNode);
	virtual ~TimesEqualNode();
	virtual void Interpret();
	virtual void Code(InstructionsClass &machinecode);
private:
};


class NegateNode: public AssignmentStatementNode{
public:
	NegateNode(IdentifierNode *mIdentifierNode, ExpressionNode *mExpressionNode);
	virtual ~NegateNode();
	virtual void Interpret();
	virtual void Code(InstructionsClass &machinecode);
private:
};


class ProgramNode: public Node{
public:
	ProgramNode(BlockNode *mBlockNode);
	virtual ~ProgramNode();
	virtual void Interpret();
	virtual void Code(InstructionsClass &machinecode);
private:
	BlockNode *mBlockNode;
};
class StartNode: public Node{
public:
	StartNode(ProgramNode *mProgramNode);
	virtual ~StartNode();
	virtual void Interpret();
	virtual void Code(InstructionsClass &machinecode);
private:
	ProgramNode *mProgramNode;
};
class BooleanNode: public ExpressionNode{
public:
	BooleanNode(bool mbool);
	virtual ~BooleanNode();
	virtual int Evaluate();
	virtual void Code(InstructionsClass &machinecode);
private:
	bool mBool;
};
class IntegerNode: public ExpressionNode{
public:
	IntegerNode(int mInt);
	virtual ~IntegerNode();
	virtual int Evaluate();
	virtual void Code(InstructionsClass &machinecode);
private:
	int mInteger;
};
class OrNode: public ExpressionNode{//from binary is more cool
public:
	OrNode(ExpressionNode *c,ExpressionNode *c2);
	virtual ~OrNode();
	virtual int Evaluate();
	virtual void Code(InstructionsClass &machinecode);
private:
	ExpressionNode *mLeft;
	ExpressionNode *mRight;
};
class AndNode: public ExpressionNode{//from binary is more cool
public:
	AndNode(ExpressionNode *c,ExpressionNode *c2);
	virtual ~AndNode();
	virtual int Evaluate();
	virtual void Code(InstructionsClass &machinecode);
private:
	ExpressionNode *mLeft;
	ExpressionNode *mRight;
};
class BinaryOperatorNode: public ExpressionNode{
public:
	BinaryOperatorNode(ExpressionNode *left, ExpressionNode *right);
	virtual ~BinaryOperatorNode();
protected:
	ExpressionNode *mLeft;
	ExpressionNode *mRight;
};
/*
class NegateNode:public BinaryOperatorNode{
public:
	NegateNode(ExpressionNode *c,ExpressionNode *c2);
	virtual ~NegateNode();
	virtual int Evaluate();
	virtual void Code(InstructionsClass &machinecode);

private:
	ExpressionNode *mLeft;
	ExpressionNode *mRight;
};*/




class PlusNode: public BinaryOperatorNode{
public:
	PlusNode(ExpressionNode *left, ExpressionNode *right);
	virtual ~PlusNode();
	virtual int Evaluate();
	virtual void Code(InstructionsClass &machinecode);
private:
};
class MinusNode: public BinaryOperatorNode{
public:
	MinusNode(ExpressionNode *left, ExpressionNode *right);
	virtual ~MinusNode();
	virtual int Evaluate();
	virtual void Code(InstructionsClass &machinecode);
private:
};
class TimesNode: public BinaryOperatorNode{
public:
	TimesNode(ExpressionNode *left, ExpressionNode *right);
	virtual ~TimesNode();
	virtual int Evaluate();
	virtual void Code(InstructionsClass &machinecode);
private:
};
class DivideNode: public BinaryOperatorNode{
public:
	DivideNode(ExpressionNode *left, ExpressionNode *right);
	virtual ~DivideNode();
	virtual int Evaluate();
	virtual void Code(InstructionsClass &machinecode);
private:
};
class LessNode: public BinaryOperatorNode{
public:
	LessNode(ExpressionNode *left, ExpressionNode *right);
	virtual ~LessNode();
	virtual int Evaluate();
	virtual void Code(InstructionsClass &machinecode);
private:
};
class LessEqualNode: public BinaryOperatorNode{
public:
	LessEqualNode(ExpressionNode *left, ExpressionNode *right);
	virtual ~LessEqualNode();
	virtual int Evaluate();
	virtual void Code(InstructionsClass &machinecode);
private:
};
class GreaterNode: public BinaryOperatorNode{
public:
	GreaterNode(ExpressionNode *left, ExpressionNode *right);
	virtual ~GreaterNode();
	virtual int Evaluate();
	virtual void Code(InstructionsClass &machinecode);
private:
};
class GreaterEqualNode: public BinaryOperatorNode{
public:
	GreaterEqualNode(ExpressionNode *left, ExpressionNode *right);
	virtual ~GreaterEqualNode();
	virtual int Evaluate();
	virtual void Code(InstructionsClass &machinecode);
private:
};
class EqualNode: public BinaryOperatorNode{
public:
	EqualNode(ExpressionNode *left, ExpressionNode *right);
	virtual ~EqualNode();
	virtual int Evaluate();
	virtual void Code(InstructionsClass &machinecode);
private:
};
class NotEqualNode: public BinaryOperatorNode{
public:
	NotEqualNode(ExpressionNode *left, ExpressionNode *right);
	virtual ~NotEqualNode();
	virtual int Evaluate();
	virtual void Code(InstructionsClass &machinecode);
private:
};

class RepeatStatementNode: public StatementNode{
public:
	RepeatStatementNode(int count, ExpressionNode *enode, StatementNode *snode);
	virtual ~RepeatStatementNode();
	virtual void Interpret();
	virtual void Code(InstructionsClass &machinecode);
private:
	int mCount;
	ExpressionNode *mExpressionNode;
	StatementNode *mStatementNode;
};