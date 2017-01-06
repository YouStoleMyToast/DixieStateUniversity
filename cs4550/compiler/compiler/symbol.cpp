#include <cstdlib>
using namespace std;
#include "symbol.h"

SymbolTableClass::SymbolTableClass(){}

bool SymbolTableClass::Exists(string var)
{
	for(unsigned int i=mScopevec.back();i<mSymbolvec.size();i++)
	{
		if(mSymbolvec[i].first==var) {return true;}
	}
	return false;
}
void SymbolTableClass::AddEntry(string var)
{
	if (Exists(var))
	{
		cerr<<"variable "<<var<<" already exist in the current scope\n";
		exit(1);
		return;
	}
	pair<string,int> couple;
	couple=make_pair(var,0);
	mSymbolvec.push_back(couple);
	return;
}
int SymbolTableClass::GetValue(string var)
{
	for(int i=mSymbolvec.size()-1;i>=0;i--)
	{
		if(mSymbolvec[i].first==var) 
		{
			return mSymbolvec[i].second;
		}
	}
	cerr<<"variable "<<var<<" doesn't exist\n";exit(1);
}
void SymbolTableClass::SetValue(string var, int val)
{
	for(int i=mSymbolvec.size()-1;i>=0;i--)
	{
		if(mSymbolvec[i].first==var) 
		{
			mSymbolvec[i].second=val;
			return;
		}
	}
	cerr<<"variable "<<var<<" doesn't exist\n";exit(1);
}
int SymbolTableClass::GetIndex(string var)
{
	for(int i=mSymbolvec.size()-1;i>=0;i--)
	{
		if(mSymbolvec[i].first==var){return i;}
	}
	cerr<<"variable "<<var<<" doesn't exist\n";exit(1);
}
int SymbolTableClass::GetCount() {return mSymbolvec.size();}


void SymbolTableClass::PushScope()
{
	mScopevec.push_back(mSymbolvec.size());
}
void SymbolTableClass::PopScope()
{
	unsigned int varCount = mScopevec.back();
	while (mSymbolvec.size() > varCount)
	{
		mSymbolvec.pop_back();
	}
	mScopevec.pop_back();
}
