#include <iostream>
#include <vector>
#include <utility>
#include <string>
using namespace std;
#include "instructions.h"
#include "parser.h"
#include "token.h"
#include "scanner.h"
#include "statemachine.h"
#include "symbol.h"
#include "node.h"
#include "debug.h"

int symboltabletest(SymbolTableClass symtable)
{
	symtable.AddEntry("hello");
	symtable.SetValue("hello",5);
	symtable.AddEntry("hello");
	symtable.SetValue("hello",9);
	symtable.AddEntry("world");
	symtable.SetValue("world",9);

	cout<<symtable.Exists("hello")<<endl;
	cout<<symtable.GetValue("hello")<<endl;
	cout<<symtable.GetIndex("hello")<<endl;
	cout<<symtable.GetCount()<<endl;

	cout<<symtable.Exists("world")<<endl;
	cout<<symtable.GetValue("world")<<endl;
	cout<<symtable.GetIndex("world")<<endl;
	cout<<symtable.GetCount()<<endl;

	cout<<symtable.Exists("bob")<<endl;
	cout<<symtable.GetValue("bob")<<endl;
	cout<<symtable.GetIndex("bob")<<endl;
	cout<<symtable.GetCount()<<endl;
	return 0;
}
/*
int parsetreetest()
{
	StatementGroupNode *statementgroupnode=new StatementGroupNode();//no paramaters-added later

	IdentifierNode *identifiernode=new IdentifierNode("sum");//symboltable address
	IntegerNode *integernode=new IntegerNode(5);
	
	AssignmentStatementNode *assignmentstatementnode=new AssignmentStatementNode(identifiernode,integernode);
	DeclarationStatementNode *declarationstatementnode=new DeclarationStatementNode(identifiernode);
	CoutStatementNode *coutstatementnode=new CoutStatementNode(identifiernode);

	//DS, CS, and AS nodes are nodes added(ones that inherit from statement node)
	statementgroupnode->AddStatement(declarationstatementnode);
	statementgroupnode->AddStatement(assignmentstatementnode);
	statementgroupnode->AddStatement(coutstatementnode);

	PlusNode *plusnode=new PlusNode(integernode,integernode);
	cout<<"plusnode: "<<plusnode->Evaluate()<<endl;

	MinusNode *minusnode=new MinusNode(integernode,integernode);
	cout<<"minusnode: "<<minusnode->Evaluate()<<endl;

	TimesNode *timesnode=new TimesNode(integernode,integernode);
	cout<<"timesnode: "<<timesnode->Evaluate()<<endl;

	DivideNode *dividenode=new DivideNode(integernode,integernode);
	cout<<"dividenode: "<<dividenode->Evaluate()<<endl;

	LessNode *lessnode=new LessNode(integernode,integernode);
	cout<<"lessnode: "<<lessnode->Evaluate()<<endl;

	LessEqualNode *lessequalnode=new LessEqualNode(integernode,integernode);
	cout<<"lessequalnode: "<<lessequalnode->Evaluate()<<endl;

	GreaterNode *greaternode=new GreaterNode(integernode,integernode);
	cout<<"greaternode: "<<greaternode->Evaluate()<<endl;

	GreaterEqualNode *greaterequalnode=new GreaterEqualNode(integernode,integernode);
	cout<<"greaterequalnode: "<<greaterequalnode->Evaluate()<<endl;

	EqualNode *equalnode=new EqualNode(integernode,integernode);
	cout<<"equalnode: "<<equalnode->Evaluate()<<endl;

	NotEqualNode *notequalnode=new NotEqualNode(integernode,integernode);
	cout<<"notequalnode: "<<notequalnode->Evaluate()<<endl;

	BlockNode *blocknode=new BlockNode(statementgroupnode);
	ProgramNode *programnode=new ProgramNode(blocknode);
	StartNode *startnode=new StartNode(programnode);

	delete startnode;
	return 0;
}
*/
int parserclass(ScannerClass *scanner,SymbolTableClass *symtable)
{
	ParserClass pc(scanner,symtable);
	//cout<< pc->Start() <<endl;
	pc.Start();
	return 0;
}
int interpretclass(ScannerClass *scanner,SymbolTableClass *symtable)
{
	ParserClass pc(scanner,symtable);
	StartNode *root=pc.Start();
	root->Interpret();
	delete root;
	return 0;
}
void addtest(int x, int y)
{
	InstructionsClass code;
	code.PushValue(x);
	code.PushValue(y);
	code.PopPopAddPush();
	code.PopAndWrite();
	code.Finish();
	code.Execute();
}
void subtest(int x, int y)
{
	InstructionsClass code;
	code.PushValue(6);
	code.PushValue(5);
	code.PopPopSubPush();
	code.PopAndWrite();
	code.Finish();
	code.Execute();
}
void multest(int x, int y)
{
	InstructionsClass code;
	code.PushValue(6);
	code.PushValue(5);
	code.PopPopMulPush();
	code.PopAndWrite();
	code.Finish();
	code.Execute();
}
void divtest(int x, int y)
{
	InstructionsClass code;
	code.PushValue(100);
	code.PushValue(5);
	code.PopPopDivPush();
	code.PopAndWrite();
	code.Finish();
	code.Execute();
}
void lesstest(int x, int y)
{
	InstructionsClass code;
	code.PushValue(x);
	code.PushValue(y);
	code.PopPopLessPush();
	code.PopAndWrite();
	code.Finish();
	code.Execute();
}
void lessequaltest(int x, int y)
{
	InstructionsClass code;
	code.PushValue(x);
	code.PushValue(y);
	code.PopPopLessEqualPush();
	code.PopAndWrite();
	code.Finish();
	code.Execute();
}
void greatertest(int x, int y)
{
	InstructionsClass code;
	code.PushValue(x);
	code.PushValue(y);
	code.PopPopGreaterPush();
	code.PopAndWrite();
	code.Finish();
	code.Execute();
}
void greaterequaltest(int x, int y)
{
	InstructionsClass code;
	code.PushValue(x);
	code.PushValue(y);
	code.PopPopGreaterEqualPush();
	code.PopAndWrite();
	code.Finish();
	code.Execute();
}
void equaltest(int x, int y)
{
	InstructionsClass code;
	code.PushValue(x);
	code.PushValue(y);
	code.PopPopEqualPush();
	code.PopAndWrite();
	code.Finish();
	code.Execute();
}
void notequaltest(int x, int y)
{
	InstructionsClass code;
	code.PushValue(x);
	code.PushValue(y);
	code.PopPopNotEqualPush();
	code.PopAndWrite();
	code.Finish();
	code.Execute();
}
void asemblytests()
{
	addtest(6, 5);
	subtest(6, 5);
	multest(6, 5);
	divtest(6, 5);

	lesstest(100,5);
	lesstest(5,100);
	lesstest(100,100);

	lessequaltest(100,5);
	lessequaltest(5,100);
	lessequaltest(100,100);

	greatertest(100,5);
	greatertest(5,100);
	greatertest(100,100);

	greaterequaltest(100,5);
	greaterequaltest(5,100);
	greaterequaltest(100,100);

	equaltest(100,5);
	equaltest(5,100);
	equaltest(100,100);

	notequaltest(100,5);
	notequaltest(5,100);
	notequaltest(100,100);
}
int main()
{
	MSG("Starting main");
	const char *file="test4.txt";

	ScannerClass scanner(file);

	SymbolTableClass symtable;

	ParserClass pc(&scanner,&symtable);
	StartNode *root=pc.Start();

	cout<<"Interpret output"<<endl;
	root->Interpret();

	cout<<"Code output"<<endl;
	InstructionsClass ic;
	root->Code(ic);

	ic.Finish();
	ic.Execute();
	return 0;
}