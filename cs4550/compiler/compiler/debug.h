#pragma once
using namespace std;

#define ShowMessages 0
#define ShowNodeClassMessages 0
#define ShowParserClassMessages 0

#include <iostream>

#if ShowMessages
#define MSG(X) cout << X << endl;
#else
#define MSG(X);
#endif

#if ShowNodeClassMessages
#define NCMSG(X) cout << X << endl;
#else
#define NCMSG(X);
#endif

#if ShowParserClassMessages
#define PCMSG(X) cout << X << endl;
#else
#define PCMSG(X);
#endif
