#include <iostream>
using namespace std;
#include "node.h"
#include "debug.h"
/*
note from a non-class(cs3510) source:
There are seven types of statements: 
1) expression statement
2) compound statement
3) selection statement
4) iteration statement
5) jump statement
6) declaration statement
7) try block*/

Node::~Node(){}
void Node::Interpret(){}
void Node::Code(InstructionsClass &machinecode){}

ProgramNode::ProgramNode(BlockNode *node){this->mBlockNode=node;}
ProgramNode::~ProgramNode(){delete mBlockNode;NCMSG("ProgramNode Deleted");}
void ProgramNode::Interpret(){mBlockNode->Interpret();}
void ProgramNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded ProgramNode");
	mBlockNode->Code(machinecode);
}

BlockNode::BlockNode(StatementGroupNode *node, SymbolTableClass *SymbolTable)
{
	this->mStatementGroupNode=node;
	this->mSymbolTable=SymbolTable;
}
BlockNode::~BlockNode()
{
	NCMSG("BlockNode Deleted");
	delete mStatementGroupNode;
}
void BlockNode::Interpret()
{
	mSymbolTable->PushScope();
	mStatementGroupNode->Interpret();
	mSymbolTable->PopScope();
}
void BlockNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded BlockStatmentNode");
	mSymbolTable->PushScope();
	mStatementGroupNode->Code(machinecode);
	mSymbolTable->PopScope();
}

StatementGroupNode::StatementGroupNode(){}
StatementGroupNode::~StatementGroupNode()
{
	for(unsigned int i=0;i<mStatementGroupNodeVector.size();i++)
	{
		mStatementGroupNodeVector.erase(mStatementGroupNodeVector.begin()+i);
	}
	NCMSG("StatementGroupNode Deleted");
}
void StatementGroupNode::AddStatement(StatementNode *node){mStatementGroupNodeVector.push_back(node);}
void StatementGroupNode::Interpret()
{
	for(unsigned int i=0;i<mStatementGroupNodeVector.size();i++)
	{
		StatementNode *sm=mStatementGroupNodeVector.at(i);
		sm->Interpret();
	}
}
void StatementGroupNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded StatmentGroupNode");
	for(unsigned int i=0;i<mStatementGroupNodeVector.size();i++){mStatementGroupNodeVector.at(i)->Code(machinecode);}
}

IfStatementNode::IfStatementNode(ExpressionNode *enode, StatementNode *snode)
{
	this->mExpressionNode=enode;
	this->mStatementNode=snode;
	this->isElse=false;
}
IfStatementNode::~IfStatementNode()
{
	delete mExpressionNode;
	delete mStatementNode;
	NCMSG("IfStatementNode Deleted");
}
void IfStatementNode::Interpret() 
{ 
	if(this->mExpressionNode->Evaluate()!=0) 
	{ 
		this->mStatementNode->Interpret(); 
	}
	else if(this->mExpressionNode->Evaluate()==0) 
	{
		if(isElse)
		{
			this->mStatementNodeElse->Interpret();
		}
	}
}
void IfStatementNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded IfStatmentNode");
	mExpressionNode->Code(machinecode);
	unsigned char *InsertAddress=machinecode.SkipIfZeroStack();
	unsigned char *FromAddress=machinecode.GetAddress();
	
	if(!this->isElse){this->mStatementNode->Code(machinecode);}
	else if(this->isElse)
	{
		if(this->mExpressionNode->Evaluate()!=0) 
		{
			this->mStatementNode->Code(machinecode);
		}
		else
		{
			this->mStatementNodeElse->Code(machinecode);
		}
	}

	unsigned char *ToAddress=machinecode.GetAddress();
	machinecode.SetOffset(InsertAddress,ToAddress-FromAddress);
}
void IfStatementNode::SetElse(){this->isElse=true;}
bool IfStatementNode::GetElse(){return this->isElse;}
void IfStatementNode::SetElseNode(StatementNode *snode){this->mStatementNodeElse=snode;}

WhileStatementNode::WhileStatementNode(ExpressionNode *enode, StatementNode *snode)
{
	this->mExpressionNode=enode;
	this->mStatementNode=snode;
}
WhileStatementNode::~WhileStatementNode()
{
	delete mExpressionNode;
	delete mStatementNode;
	NCMSG("WhileStatementNode Deleted");
}
void WhileStatementNode::Interpret()
{
	while(this->mExpressionNode->Evaluate()!=0)
	{
		this->mStatementNode->Interpret();
	}
}
void WhileStatementNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded WhileStatmentNode");
	unsigned char *Address0=machinecode.GetAddress();
	mExpressionNode->Code(machinecode);
	unsigned char *Offset1=machinecode.SkipIfZeroStack();
	unsigned char *Address1=machinecode.GetAddress();
	mStatementNode->Code(machinecode);
	unsigned char *Offset2=machinecode.Jump();
	unsigned char *Address2=machinecode.GetAddress();
	
	machinecode.SetOffset(Offset2,(Address0-Address2));//return to begining
	machinecode.SetOffset(Offset1,(Address2-Address1));//while loop has ended
}



RepeatStatementNode::RepeatStatementNode(int count, ExpressionNode *enode, StatementNode *snode)
{
	this->mCount=count;
	this->mExpressionNode=enode;
	this->mStatementNode=snode;
}
RepeatStatementNode::~RepeatStatementNode()
{
	delete mExpressionNode;
	delete mStatementNode;
	NCMSG("RepeatStatementNode Deleted");
}
void RepeatStatementNode::Interpret()
{
	for(int i=0;i<this->mCount;i++)
	{
		this->mStatementNode->Interpret();
	}
}
void RepeatStatementNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded RepeatStatementNode");
	unsigned char *Address0=machinecode.GetAddress();
	mExpressionNode->Code(machinecode);
	unsigned char *Offset1=machinecode.SkipIfZeroStack();
	unsigned char *Address1=machinecode.GetAddress();
	mStatementNode->Code(machinecode);
	unsigned char *Offset2=machinecode.Jump();
	unsigned char *Address2=machinecode.GetAddress();
	
	machinecode.SetOffset(Offset2,(Address0-Address2));//return to begining
	machinecode.SetOffset(Offset1,(Address2-Address1));//while loop has ended
}



StartNode::StartNode(ProgramNode *node){this->mProgramNode=node;}
StartNode::~StartNode(){delete mProgramNode;NCMSG("StartNode Deleted");}
void StartNode::Interpret(){mProgramNode->Interpret();}
void StartNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded StartNode");
	mProgramNode->Code(machinecode);
}

StatementNode::StatementNode(){}
StatementNode::~StatementNode(){NCMSG("StatementNode Deleted");}

DeclarationStatementNode::DeclarationStatementNode(IdentifierNode *node){this->mIdentifierNode=node;}
DeclarationStatementNode::~DeclarationStatementNode(){NCMSG("DeclarationStatementNode Deleted");}
void DeclarationStatementNode::Interpret(){mIdentifierNode->DeclareVariable();};
void DeclarationStatementNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded DeclarationStatmentNode");
	mIdentifierNode->DeclareVariable();
}

CoutStatementNode::CoutStatementNode(){}
CoutStatementNode::~CoutStatementNode(){NCMSG("CoutStatementNode Deleted");}
void CoutStatementNode::Interpret()
{
	for(unsigned int i=0;i<mExpressionNodeVec.size();i++)
	{
		if(!(mExpressionNodeVec.at(i)==NULL)) {cout<<mExpressionNodeVec.at(i)->Evaluate();}
		else {cout<<""<<endl;}
	}
}
void CoutStatementNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded CoutStatmentNode");
	for(unsigned int i=0 ; i < mExpressionNodeVec.size() ; i++)
	{
		if(!(mExpressionNodeVec.at(i)==NULL))
		{
			mExpressionNodeVec.at(i)->Code(machinecode);
			machinecode.PopAndWrite();
		}
		else{machinecode.WriteEndl();}
	}
}
void CoutStatementNode::addExpression(ExpressionNode *e){mExpressionNodeVec.push_back(e);}

ExpressionNode::ExpressionNode(){}
ExpressionNode::~ExpressionNode(){}
int ExpressionNode::Evaluate(){return this->mInt;}
void ExpressionNode::Code(InstructionsClass &machinecode){}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode *inode, ExpressionNode *enode)
{
	this->mIdentifierNode=inode;
	this->mExpressionNode=enode;
}
AssignmentStatementNode::~AssignmentStatementNode(){NCMSG("AssignmentStatementNode Deleted");}
void AssignmentStatementNode::Interpret()
{
	int id = mExpressionNode->Evaluate();
	mIdentifierNode->SetValue(id);
}
void AssignmentStatementNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded AssignmentStatmentNode");
	mExpressionNode->Code(machinecode);
	int index=mIdentifierNode->GetIndex();
	machinecode.PopAndStore(index);
}

PlusEqualNode::PlusEqualNode(IdentifierNode *mIdentifierNode, ExpressionNode *mExpressionNode)
	: AssignmentStatementNode(mIdentifierNode, mExpressionNode){}
PlusEqualNode::~PlusEqualNode(){NCMSG("PlusEqualNode Deleted");}
void PlusEqualNode::Interpret()
{
	int id = (mIdentifierNode->Evaluate()+mExpressionNode->Evaluate());
	mIdentifierNode->SetValue(id);
}
void PlusEqualNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded PlusEqualNode");
	int index=mIdentifierNode->GetIndex();
	machinecode.PushVariable(index);
	mExpressionNode->Code(machinecode);
	machinecode.PopPopAddPush();
	machinecode.PopAndStore(index);
}

MinusEqualNode::MinusEqualNode(IdentifierNode *mIdentifierNode, ExpressionNode *mExpressionNode)
	: AssignmentStatementNode(mIdentifierNode, mExpressionNode){}
MinusEqualNode::~MinusEqualNode(){NCMSG("MinusEqualNode Deleted");}
void MinusEqualNode::Interpret()
{
	int id = (mIdentifierNode->Evaluate()-mExpressionNode->Evaluate());
	mIdentifierNode->SetValue(id);
}
void MinusEqualNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded MinusEqualNode");
	int index=mIdentifierNode->GetIndex();
	machinecode.PushVariable(index);
	mExpressionNode->Code(machinecode);
	machinecode.PopPopSubPush();
	machinecode.PopAndStore(index);
}


TimesEqualNode::TimesEqualNode(IdentifierNode *mIdentifierNode, ExpressionNode *mExpressionNode)
	: AssignmentStatementNode(mIdentifierNode, mExpressionNode){}
TimesEqualNode::~TimesEqualNode(){NCMSG("TimesEqualNode Deleted");}
void TimesEqualNode::Interpret()
{
	int id = (mIdentifierNode->Evaluate()*mExpressionNode->Evaluate());
	mIdentifierNode->SetValue(id);
}
void TimesEqualNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded TimesEqualNode");
	int index=mIdentifierNode->GetIndex();
	machinecode.PushVariable(index);
	mExpressionNode->Code(machinecode);
	machinecode.PopPopMulPush();
	machinecode.PopAndStore(index);
}


NegateNode::NegateNode(IdentifierNode *mIdentifierNode, ExpressionNode *mExpressionNode)
	: AssignmentStatementNode(mIdentifierNode, mExpressionNode){}
NegateNode::~NegateNode(){NCMSG("NegateNode Deleted");}
void NegateNode::Interpret()
{
	int id = (mIdentifierNode->Evaluate()-mExpressionNode->Evaluate());
	mIdentifierNode->SetValue(id);
}
void NegateNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded NegateNode");
	int index=mIdentifierNode->GetIndex();
	machinecode.PushVariable(index);
	mExpressionNode->Code(machinecode);
	machinecode.PopPopSubPush();
	machinecode.PopAndStore(index);
}
/*
NegateNode::NegateNode(ExpressionNode *left, ExpressionNode *right)
	: BinaryOperatorNode(left,right) {}
NegateNode::~NegateNode(){NCMSG("NegateNode Deleted");}
int NegateNode::Evaluate()
{
	int x=mLeft->Evaluate();
	int y=mRight->Evaluate();
	return 0 - mRight->Evaluate();
}
void NegateNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded NegateNode");
	mLeft->Code(machinecode);
	mRight->Code(machinecode);
	machinecode.PopPopAddPush();
}*/




IntegerNode::IntegerNode(int integer){this->mInteger=integer;}
IntegerNode::~IntegerNode(){}
int IntegerNode::Evaluate(){return this->mInteger;}
void IntegerNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded IntegerNode");
	machinecode.PushValue(mInteger);
}


BooleanNode::BooleanNode(bool boolean){this->mBool=boolean;}
BooleanNode::~BooleanNode(){}
int BooleanNode::Evaluate(){return this->mBool;}
void BooleanNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded BooleanNode");
	machinecode.PushValue(mBool);
	//machinecode.PushBool(mBool);
}



IdentifierNode::IdentifierNode(string label, SymbolTableClass *SymbolTable)
{
	this->mLabel=label;
	this->mSymbolTable=SymbolTable;
}
IdentifierNode::~IdentifierNode(){NCMSG("IdentifierNode Deleted");}
void IdentifierNode::SetValue(int value)
{
	mSymbolTable->SetValue(mLabel,value);
}
void IdentifierNode::DeclareVariable()
{
	mSymbolTable->AddEntry(mLabel);
}
int IdentifierNode::Evaluate()
{
	return mSymbolTable->GetValue(mLabel);
	return 0;
}
int IdentifierNode::GetIndex(){return mSymbolTable->GetIndex(mLabel);}
void IdentifierNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded IdentifierNode");
	int index=mSymbolTable->GetIndex(mLabel);
	machinecode.PushVariable(index);
}

OrNode::OrNode(ExpressionNode *c,ExpressionNode *c2)
{
	this->mLeft=c;
	this->mRight=c2;
}
OrNode::~OrNode(){}
int OrNode::Evaluate() { return mLeft->Evaluate() || mRight->Evaluate(); }
void OrNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded OrNode");
	mLeft->Code(machinecode);
	mRight->Code(machinecode);
	machinecode.PopPopOrPush();
}

AndNode::AndNode(ExpressionNode *c,ExpressionNode *c2)
{
	this->mLeft=c;
	this->mRight=c2;
}
AndNode::~AndNode(){}
int AndNode::Evaluate(){return mLeft->Evaluate() && mRight->Evaluate();}
void AndNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded AndNode");
	mLeft->Code(machinecode);
	mRight->Code(machinecode);
	machinecode.PopPopAndPush();
}

BinaryOperatorNode::BinaryOperatorNode(ExpressionNode *left, ExpressionNode *right)
{
	this->mLeft=left;
	this->mRight=right;
}
BinaryOperatorNode::~BinaryOperatorNode(){}

PlusNode::PlusNode(ExpressionNode *left, ExpressionNode *right)
	: BinaryOperatorNode(left,right) {}
PlusNode::~PlusNode(){NCMSG("PlusNode Deleted");}
int PlusNode::Evaluate(){return mLeft->Evaluate() + mRight->Evaluate();}
void PlusNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded PlusNode");
	mLeft->Code(machinecode);
	mRight->Code(machinecode);
	machinecode.PopPopAddPush();
}

MinusNode::MinusNode(ExpressionNode *left, ExpressionNode *right)
	: BinaryOperatorNode(left,right) {}
MinusNode::~MinusNode(){NCMSG("MinusNode Deleted");}
int MinusNode::Evaluate(){return mLeft->Evaluate() - mRight->Evaluate();}
void MinusNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded MinusNode");
	mLeft->Code(machinecode);
	mRight->Code(machinecode);
	machinecode.PopPopSubPush();
}

TimesNode::TimesNode(ExpressionNode *left, ExpressionNode *right)
	: BinaryOperatorNode(left,right) {}
TimesNode::~TimesNode(){NCMSG("TimesNode Deleted");}
int TimesNode::Evaluate(){return mLeft->Evaluate() * mRight->Evaluate();}
void TimesNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded TimesNode");
	mLeft->Code(machinecode);
	mRight->Code(machinecode);
	machinecode.PopPopMulPush();
}

DivideNode::DivideNode(ExpressionNode *left, ExpressionNode *right)
	: BinaryOperatorNode(left,right) {}
DivideNode::~DivideNode(){NCMSG("DivideNode Deleted");}
int DivideNode::Evaluate(){return mLeft->Evaluate() / mRight->Evaluate();}
void DivideNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded DivideNode");
	mLeft->Code(machinecode);
	mRight->Code(machinecode);
	machinecode.PopPopDivPush();
}

LessNode::LessNode(ExpressionNode *left, ExpressionNode *right)
	: BinaryOperatorNode(left,right) {}
LessNode::~LessNode(){NCMSG("LessNode Deleted");}
int LessNode::Evaluate()
{
	if(mLeft->Evaluate() < mRight->Evaluate()) {return 1;}
	else {return 0;}
}
void LessNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded LessNode");
	mLeft->Code(machinecode);
	mRight->Code(machinecode);
	machinecode.PopPopLessPush();
}

LessEqualNode::LessEqualNode(ExpressionNode *left, ExpressionNode *right)
	: BinaryOperatorNode(left,right){}
LessEqualNode::~LessEqualNode(){NCMSG("LessEqualNode Deleted");}
int LessEqualNode::Evaluate()
{
	if(mLeft->Evaluate() <= mRight->Evaluate()) {return 1;}
	else {return 0;}
}
void LessEqualNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded LessEqualNode");
	mLeft->Code(machinecode);
	mRight->Code(machinecode);
	machinecode.PopPopLessEqualPush();
}

GreaterNode::GreaterNode(ExpressionNode *left, ExpressionNode *right)
	: BinaryOperatorNode(left,right){}
GreaterNode::~GreaterNode(){NCMSG("GreaterNode Deleted");}
int GreaterNode::Evaluate()
{
	if(mLeft->Evaluate() > mRight->Evaluate()) {return 1;}
	else {return 0;}
}
void GreaterNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded GreaterNode");
	mLeft->Code(machinecode);
	mRight->Code(machinecode);
	machinecode.PopPopGreaterPush();
}

GreaterEqualNode::GreaterEqualNode(ExpressionNode *left, ExpressionNode *right)
	: BinaryOperatorNode(left,right){}
GreaterEqualNode::~GreaterEqualNode(){NCMSG("GreaterEqualNode Deleted");}
int GreaterEqualNode::Evaluate()
{
	if(mLeft->Evaluate() >= mRight->Evaluate()) {return 1;}
	else {return 0;}
}
void GreaterEqualNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded GreaterEqualNode");
	mLeft->Code(machinecode);
	mRight->Code(machinecode);
	machinecode.PopPopGreaterEqualPush();
}

EqualNode::EqualNode(ExpressionNode *left, ExpressionNode *right)
	: BinaryOperatorNode(left,right){}
EqualNode::~EqualNode(){NCMSG("EqualNode Deleted");}
int EqualNode::Evaluate()
{
	if(mLeft->Evaluate() == mRight->Evaluate()) {return 1;}
	else {return 0;}
}
void EqualNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded EqualNode");
	mLeft->Code(machinecode);
	mRight->Code(machinecode);
	machinecode.PopPopEqualPush();
}

NotEqualNode::NotEqualNode(ExpressionNode *left, ExpressionNode *right)
	: BinaryOperatorNode(left,right){}
NotEqualNode::~NotEqualNode(){NCMSG("NotEqualNode Deleted");}
int NotEqualNode::Evaluate()
{
	if(mLeft->Evaluate() != mRight->Evaluate()) {return 1;}
	else {return 0;}
}
void NotEqualNode::Code(InstructionsClass &machinecode)
{
	NCMSG("Coded NotEqualNode");
	mLeft->Code(machinecode);
	mRight->Code(machinecode);
	machinecode.PopPopNotEqualPush();
}



