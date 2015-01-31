// os345p1.c - Command Line Processor
// ***********************************************************************
// **   DISCLAMER ** DISCLAMER ** DISCLAMER ** DISCLAMER ** DISCLAMER   **
// **                                                                   **
// ** The code given here is the basis for the CS345 projects.          **
// ** It comes "as is" and "unwarranted."  As such, when you use part   **
// ** or all of the code, it becomes "yours" and you are responsible to **
// ** understand any algorithm or method presented.  Likewise, any      **
// ** errors or problems become your responsibility to fix.             **
// **                                                                   **
// ** NOTES:                                                            **
// ** -Comments beginning with "// ??" may require some implementation. **
// ** -Tab stops are set at every 3 spaces.                             **
// ** -The function API's in "OS345.h" should not be altered.           **
// **                                                                   **
// **   DISCLAMER ** DISCLAMER ** DISCLAMER ** DISCLAMER ** DISCLAMER   **
// ***********************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>
#include <assert.h>
#include <time.h>
//my includes//////////////////
#include <math.h>
////////////////////////////////
#include "os345.h"
// The 'reset_context' comes from 'main' in os345.c.  Proper shut-down
// procedure is to long jump to the 'reset_context' passing in the
// power down code from 'os345.h' that indicates the desired behavior.
extern jmp_buf reset_context;
// -----
#define NUM_COMMANDS 54
typedef struct								// command struct
{
	char* command;
	char* shortcut;
	int (*func)(int, char**);
	char* description;
} Command;

// ***********************************************************************
// project 1 variables
//
extern long swapCount;					// number of scheduler cycles
extern char inBuffer[];					// character input buffer
extern Semaphore* inBufferReady;		// input buffer ready semaphore
extern bool diskMounted;				// disk has been mounted
extern char dirPath[];					// directory path
Command** commands;						// shell commands

// ***********************************************************************
// project 1 prototypes
Command** P1_init(void);
Command* newCommand(char*, char*, int (*func)(int, char**), char*);

// ***********************************************************************
// myShell - command line interpreter
//
// Project 1 - implement a Shell (CLI) that:
//
// 1. Prompts the user for a command line.
// 2. WAIT's until a user line has been entered.
// 3. Parses the global char array inBuffer.
// 4. Creates new argc, argv variables using malloc.
// 5. Searches a command list for valid OS commands.
// 6. If found, perform a function variable call passing argc/argv variables.
// 7. Supports background execution of non-intrinsic commands.
int P1_shellTask(int argc, char* argv[])
{
	int i,found, newArgc;					// # of arguments
	//my variables start////////////////
	int inlen, signtype, signloc, quotecount,spacecount,nullcount;//my variables
	double math1, math2, equal;
	char str[128];
	char* taskname;
	char* mathstr1;
	char* mathstr2;
	//my variables end//////////////////
	char* firstargv;
	char** newArgv;					// pointers to arguments
	// initialize shell commands
	commands = P1_init();					// init shell commands

	sigAction(mySigContHandler,mySIGCONT);
	sigAction(mySigIntHandler,mySIGINT);
	sigAction(mySigTermHandler,mySIGTERM);
	sigAction(mySigTstpHandler,mySIGTSTP);
	//sigAction(mySigKillHandler,mySIGKILL);

	while (1)
	{
		// output prompt
		if (diskMounted) 
			printf("\n%s>>", dirPath);
		else 
			printf("\n%ld>>", swapCount);
		SEM_WAIT(inBufferReady);			// wait for input buffer semaphore
		if (!inBuffer[0]) 
			continue;			// ignore blank lines
		//printf("\n%s", inBuffer);
		SWAP								// do context switch
		{
			static char *sp, *myArgv[MAX_ARGS];
			// ?? >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			// ?? parse command line into argc, argv[] variables
			// ?? must use malloc for argv storage!
			//start my attempt of the above/////////////////////////
			for (i = 0; i < INBUF_SIZE; i++)
			{
				if(inBuffer[i]==NULL)
				{
					inlen=i;
					i=INBUF_SIZE;
				}
			}
			//case handeling/////////////////////////////////////////
			quotecount=0;
			spacecount=0;
			for(i=0;i<inlen+1;i++)
			{
				if(inBuffer[i]=='"')
				{
					quotecount++;
				}
				if(quotecount%2==0)
				{
					inBuffer[i]=tolower(inBuffer[i]);
				}
			}
			for(i=0;i<inlen+1;i++)
			{
				if(inBuffer[i]==' ')
				{
					spacecount++;
				}
			}
			//end case handeling/////////////////////////////////////
			// init arguments
			newArgc = 1;
			myArgv[0] = sp = inBuffer;				// point to input string
			for (i=1; i<MAX_ARGS; i++)
				myArgv[i] = 0;

			// parse input string
			if(spacecount>0)
			{
				sp=(strchr(myArgv[0], ' '));
				*sp++ = 0;
				myArgv[newArgc++] = sp;
			}
			if(quotecount==0)
			{
				while ((sp = strchr(sp, ' ')))
				{
					*sp++ = 0;
					myArgv[newArgc++] = sp;
				}
			}
			if(quotecount>0)
			{
				while((sp = strchr(sp, '"')))
				{
					*sp++ = 0;
					myArgv[newArgc++] = sp;
				}
			}
			spacecount=newArgc;
			for(i=0;i<spacecount;i++)
			{
				if(myArgv[i][0]!=' ')
				{
					myArgv[newArgc++] = myArgv[i];
				}
				if(myArgv[i][0]==' ')
				{
					while ((myArgv[i] = strchr(myArgv[i], ' ')))
					{
						*myArgv[i]++ = 0;
						myArgv[newArgc++] = myArgv[i];
					}
				}
			}
			newArgc=newArgc-spacecount;
			for(i=0;i<newArgc;i++)
			{
				myArgv[i]=myArgv[i+spacecount];
			}
			nullcount=0;
			for(i=0;i<newArgc;i++)
			{
				if(strcmp(myArgv[i],"")==0)
				{
					SWAP;
					myArgv[i]=NULL;
					nullcount++;
				}
			} 
			for(i=newArgc;i<(newArgc+spacecount);i++)
			{
				SWAP;
				myArgv[i]=NULL;
			}
			for(i=0;i<newArgc;i++)
			{
				while(myArgv[i]==NULL && myArgv[i+1]!=NULL)
				{
					SWAP;
					myArgv[i]=myArgv[i+1];
					myArgv[i+1]=NULL;
					i=0;
				}
			}
			newArgc=newArgc-nullcount;
			newArgv=(char**)malloc(newArgc*sizeof(char*));
			for(i=0;i<newArgc;i++)
			{
				SWAP;
				newArgv[i]=(char*)malloc((strlen(myArgv[i])+1)*sizeof(char));
				strcpy(newArgv[i],myArgv[i]);
			}
			// ?? >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			// look for command
			//start of end chars////////////////////////////////
			if(inBuffer[inlen-1]=='&')//if line ends with ampersand
			{
				strcpy(str, inBuffer);
				taskname=strtok(str, "&");
				if(strcmp(taskname,"count")==0)
				{
					createTask(taskname,	// task name
							P1_countfunction,	// task
							MED_PRIORITY,	// task priority
							argc,			// task arg count
							argv);
				}
			}
			//end of end chars/////////////////////////////////////
			//start of math////////////////////////////////////////
			for(i = 0; i < argc; i++)
			{
				if(inBuffer[0]=='0' && inBuffer[1]=='x')
				{
					int mathlong1,mathlong2;
					mathstr1=strtok(inBuffer, "+");
					mathstr2=strtok(NULL, "+");
					mathlong1=strtol(mathstr1,NULL,0);
					mathlong2=strtol(mathstr2,NULL,0);
					equal=mathlong1+mathlong2;
					printf("\n%f",equal);
				}
			}
			if(inBuffer[1]!='x')
			{
				for (i = 0; i < inlen-1; i++)
				{
					strcpy(str, inBuffer);
					if(inBuffer[i]=='+')
					{
						signloc=i;
						signtype=43;
						mathstr1=strtok(str, "+");
						mathstr2=strtok(NULL, "+");
						math1=atof(mathstr1);
						math2=atof(mathstr2);
						equal=math1+math2;
						printf("\n%f",equal);
					}
					if(inBuffer[i]=='-')
					{
						signloc=i;
						signtype=45;
						mathstr1=strtok(str, "-");
						mathstr2=strtok(NULL, "-");
						math1=atof(mathstr1);
						math2=atof(mathstr2);
						equal=math1-math2;
						printf("\n%f",equal);
					}
					if(inBuffer[i]=='*')
					{
						signloc=i;
						signtype=42;				
						mathstr1=strtok(str, "*");
						mathstr2=strtok(NULL, "*");
						math1=atof(mathstr1);
						math2=atof(mathstr2);
						equal=math1*math2;
						printf("\n%f",equal);
					}
					if(inBuffer[i]=='/')
					{
						signloc=i;
						signtype=47;
						mathstr1=strtok(str, "/");
						mathstr2=strtok(NULL, "/");
						math1=atof(mathstr1);
						math2=atof(mathstr2);
						equal=math1/math2;
						printf("\n%f",equal);
					}
				}
			}
			//end of math/////////////////////////////////////////
			//printf("\n%i last char", inBuffer[inlen-1]);
			//////////////////////////////////////////////////////////////////////////
			for (found = i = 0; i < NUM_COMMANDS; i++)
			{
				if (!strcmp(newArgv[0], commands[i]->command) ||
					 !strcmp(newArgv[0], commands[i]->shortcut))
				{
					// command found
					int retValue = (*commands[i]->func)(newArgc, newArgv);
					if (retValue) printf("\nCommand Error %d", retValue);
					found = TRUE;
					break;
				}
			}
			if (!found)	printf("\nInvalid command!");
			// ?? free up any malloc'd argv parameters
			for(i=0;i<newArgc;i++)
			{
				SWAP
				if(newArgv[i]!=NULL)
				{
					free(newArgv[i]);
				}
			}
			free(newArgv);
			for (i=0; i<INBUF_SIZE; i++) inBuffer[i] = 0;
		}
	}
	return 0;						// terminate task
} // end P1_shellTask

// ***********************************************************************
// ***********************************************************************
// quit command
//
int P1_quit(int argc, char* argv[])
{
	int i;
	// free P1 commands
	for (i = 0; i < NUM_COMMANDS; i++)
	{
		free(commands[i]->command);
		free(commands[i]->shortcut);
		free(commands[i]->description);
	}
	free(commands);
	// powerdown OS345
	longjmp(reset_context, POWER_DOWN_QUIT);
	return 0;
} // end P1_quit

// **************************************************************************
// **************************************************************************
// lc3 command
//
int P1_lc3(int argc, char* argv[])
{
	strcpy (argv[0], "0");
	return lc3Task(argc, argv);
} // end P1_lc3

// ***********************************************************************
// ***********************************************************************
// help command
//
int P1_help(int argc, char* argv[])
{
	int i;
	for (i = 0; i < NUM_COMMANDS; i++)
	{
		int cmp1,cmp2;
		SWAP										// do context switch
		if(argc==2)
		{
			cmp1=strcmp(argv[1],commands[i]->command);
			cmp2=strcmp(argv[1],commands[i]->shortcut);
			if(!(cmp1==0 || cmp2==0))
			{
				continue;
			}
		}
		if (strstr(commands[i]->description, ":")) printf("\n");
		printf("\n%4s: %s", commands[i]->shortcut, commands[i]->description);
	}
	return 0;
} // end P1_help

//start my commands-eb////////////////////////////////////////
int P1_add_args(int argc, char* argv[])
{
	int i,sum,math1;
	sum=0;
	for(i=1;i<argc;i++)
	{
		if(argv[i][0]=='0' && argv[i][1]=='x')
		{
			math1=strtol(argv[i],NULL,0);
			sum=sum+math1;
		}
		else
		{
			math1=atoi(argv[i]);
			sum=sum+math1;
		}
	}
	printf("\n%d",sum);
	return 0;
}

int P1_add_ints(int argc, char* argv[])
{
	int i,length,place,div,addnum,minnum,modnum,sum,mint=atoi(argv[1]);
	length=strlen(argv[1])-1;
	place=length;
	div=pow(10,(double)place);
	sum=mint/div;
	minnum=div*sum;
	modnum=mint-minnum;
	for(i=1;i<length+1;i++)
	{
		place=length-i;
		div=pow(10,(double)place);
		addnum=modnum/div;
		sum=sum+addnum;
		minnum=div*addnum;
		modnum=modnum-minnum;
	}
	printf("\n%d",sum);
	return 0;
}

int P1_args(int argc, char* argv[])
{
	int i;
	for(i=0;i<argc;i++)
	{
		printf("\n%s",argv[i]);
	}
	return 0;
}
int P1_countfunction(int argc, char* argv[])
{
	int inittime,currtime,fintime;
	time_t timeinit;
	time_t timecurr;
	time_t timefin;
	inittime=time(&timeinit);
	currtime=time(&timecurr);
	fintime=inittime+10;
	while(currtime<fintime)
	{
		SWAP
		currtime=time(&timecurr);
		currtime++;
	}
	printf("\n%i",currtime-inittime);
	return 0;
}
int P1_gettime()
{
	time_t currtime;
	time(&currtime);
	printf("\n%s",ctime(&currtime));
	return 0;
}
//end my commands-eb///////////////////////////////////////////


// ***********************************************************************
// ***********************************************************************
// initialize shell commands
//
Command* newCommand(char* command, char* shortcut, int (*func)(int, char**), char* description)
{
	Command* cmd = (Command*)malloc(sizeof(Command));

	// get long command
	cmd->command = (char*)malloc(strlen(command) + 1);
	strcpy(cmd->command, command);

	// get shortcut command
	cmd->shortcut = (char*)malloc(strlen(shortcut) + 1);
	strcpy(cmd->shortcut, shortcut);

	// get function pointer
	cmd->func = func;

	// get description
	cmd->description = (char*)malloc(strlen(description) + 1);
	strcpy(cmd->description, description);

	return cmd;
} // end newCommand


Command** P1_init()
{
	int i  = 0;
	int j  = 0;
	Command** commands = (Command**)malloc(sizeof(Command*) * NUM_COMMANDS);

	// system
	commands[i++] = newCommand("quit", "q", P1_quit, "Quit");
	commands[i++] = newCommand("kill", "kt", P2_killTask, "Kill task");
	commands[i++] = newCommand("reset", "rs", P2_reset, "Reset system");

	// P1: Shell
	//commands[i++] = newCommand("project1", "p1", P1_project1, "P1: Shell");
	commands[i++] = newCommand("help", "he", P1_help, "OS345 Help");
	commands[i++] = newCommand("lc3", "lc3", P1_lc3, "Execute LC3 program");

	//begin my commands-eb///////////////////////////////////////////////////////////////////////////
	commands[i++] = newCommand("count", "cnt", P1_countfunction, "Counts one per second for a time");
	commands[i++] = newCommand("time", "tm", P1_gettime, "The time");
	commands[i++] = newCommand("args","args",P1_args,"prints arguments");
	commands[i++] = newCommand("add","add",P1_add_args,"adds all the numbers");
	commands[i++] = newCommand("addint","addi",P1_add_ints,"adds all the ints");
	//end my commands-eb/////////////////////////////////////////////////////////////////////////////

	// P2: Tasking
	commands[i++] = newCommand("project2", "p2", P2_project2, "P2: Tasking");
	commands[i++] = newCommand("semaphores", "sem", P2_listSems, "List semaphores");
	commands[i++] = newCommand("tasks", "lt", P2_listTasks, "List tasks");
	commands[i++] = newCommand("signal1", "s1", P2_signal1, "Signal sem1 semaphore");
	commands[i++] = newCommand("signal2", "s2", P2_signal2, "Signal sem2 semaphore");

	// P3: Jurassic Park
	commands[i++] = newCommand("project3", "p3", P3_project3, "P3: Jurassic Park");
	commands[i++] = newCommand("deltaclock", "dc", P3_dc, "List deltaclock entries");
	commands[i++] = newCommand("deltaclockMonitorTask", "dcmt", dcMonitorTask, "List deltaclock entries");
	

	// P4: Virtual Memory
	commands[i++] = newCommand("project4", "p4", P4_project4, "P4: Virtual Memory");
	commands[i++] = newCommand("frametable", "dft", P4_dumpFrameTable, "Dump bit frame table");
	commands[i++] = newCommand("initmemory", "im", P4_initMemory, "Initialize virtual memory");
	commands[i++] = newCommand("touch", "vma", P4_vmaccess, "Access LC-3 memory location");
	commands[i++] = newCommand("stats", "vms", P4_virtualMemStats, "Output virtual memory stats");
	commands[i++] = newCommand("crawler", "cra", P4_crawler, "Execute crawler.hex");
	commands[i++] = newCommand("memtest", "mem", P4_memtest, "Execute memtest.hex");
	//commands[i++] = newCommand("displaypage","dp", displayPage, "displaypage");

	commands[i++] = newCommand("frame", "dfm", P4_dumpFrame, "Dump LC-3 memory frame");
	commands[i++] = newCommand("memory", "dm", P4_dumpLC3Mem, "Dump LC-3 memory");
	commands[i++] = newCommand("page", "dp", P4_dumpPageMemory, "Dump swap page");
	commands[i++] = newCommand("virtual", "dvm", P4_dumpVirtualMem, "Dump virtual memory page");
	commands[i++] = newCommand("root", "rpt", P4_rootPageTable, "Display root page table");
	commands[i++] = newCommand("user", "upt", P4_userPageTable, "Display user page table");

	// P5: Scheduling
	commands[i++] = newCommand("project5", "p5", P5_project5, "P5: Scheduling");
//	commands[i++] = newCommand("stress1", "t1", P5_stress1, "ATM stress test1");
//	commands[i++] = newCommand("stress2", "t2", P5_stress2, "ATM stress test2");

	// P6: FAT
	commands[i++] = newCommand("project6", "p6", P6_project6, "P6: FAT");
	commands[i++] = newCommand("change", "cd", P6_cd, "Change directory");
	commands[i++] = newCommand("copy", "cf", P6_copy, "Copy file");
	commands[i++] = newCommand("define", "df", P6_define, "Define file");
	commands[i++] = newCommand("delete", "dl", P6_del, "Delete file");
	commands[i++] = newCommand("directory", "dir", P6_dir, "List current directory");
	commands[i++] = newCommand("mount", "md", P6_mount, "Mount disk");
	commands[i++] = newCommand("mkdir", "mk", P6_mkdir, "Create directory");
	commands[i++] = newCommand("run", "run", P6_run, "Execute LC-3 program");
	commands[i++] = newCommand("space", "sp", P6_space, "Space on disk");
	commands[i++] = newCommand("type", "ty", P6_type, "Type file");
	commands[i++] = newCommand("unmount", "um", P6_unmount, "Unmount disk");

	commands[i++] = newCommand("fat", "ft", P6_dfat, "Display fat table");
	commands[i++] = newCommand("fileslots", "fs", P6_fileSlots, "Display current open slots");
	commands[i++] = newCommand("sector", "ds", P6_dumpSector, "Display disk sector");
	commands[i++] = newCommand("chkdsk", "ck", P6_chkdsk, "Check disk");
	commands[i++] = newCommand("final", "ft", P6_finalTest, "Execute file test");

	commands[i++] = newCommand("open", "op", P6_open, "Open file test");
	commands[i++] = newCommand("read", "rd", P6_read, "Read file test");
	commands[i++] = newCommand("write", "wr", P6_write, "Write file test");
	commands[i++] = newCommand("seek", "sk", P6_seek, "Seek file test");
	commands[i++] = newCommand("close", "cl", P6_close, "Close file test");

	assert(i == NUM_COMMANDS);

	return commands;
} // end P1_init
