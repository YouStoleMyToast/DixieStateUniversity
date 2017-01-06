#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <string>
using namespace std;
#include "debug.h"

class SymbolTableClass
{
public:
	SymbolTableClass();
	bool Exists(string mVariable);
	void AddEntry(string mVariable);

	int GetValue(string s);
	void SetValue(string s, int v);
	int GetIndex(string s);
	int GetCount();
	void PushScope();
	void PopScope();

private:
	vector < pair < string,int > > mSymbolvec;
	vector < int > mScopevec;
};