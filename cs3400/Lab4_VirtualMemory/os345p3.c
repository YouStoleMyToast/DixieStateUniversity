// os345p3.c - Jurassic Park
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
#include <time.h>
#include <assert.h>
#include "os345.h"
#include "os345park.h"

// ***********************************************************************
// project 3 variables

// Jurassic Park
extern JPARK myPark;
extern Semaphore* parkMutex;						// protect park access
extern Semaphore* fillSeat[NUM_CARS];			// (signal) seat ready to fill
extern Semaphore* seatFilled[NUM_CARS];		// (wait) passenger seated
extern Semaphore* rideOver[NUM_CARS];			// (signal) ride over

Semaphore* needDriver;
Semaphore* driverAssigned;
Semaphore* carLine;
Semaphore* cidLock;
Semaphore* carMutex;
Semaphore* ticketMutex;
Semaphore* cidMutex;
Semaphore* carLock[NUM_CARS];
Semaphore* driverLock[NUM_DRIVERS];
Semaphore* rideDone[NUM_VISITORS+NUM_DRIVERS];
// ***********************************************************************
// project 3 functions and tasks
void CL3_project3(int, char**);
void CL3_dc(int, char**);

//mine////////////////////////////
int ttime[MAX_TASKS];
char* tevent[MAX_TASKS];
int dctasktime;
char* dctaskname;
int timeTaskID;
int numDeltaClock=0;
int numVisitors=0;
int numCars=0;
int numDrivers=0;

int globalCarid;
/////////////////////////////////

// ***********************************************************************
// ***********************************************************************
// project3 command
int P3_project3(int argc, char* argv[])
{
	char buf[32];
	char* newArgv[2];
	int i;

	//resource semaphores
	parkTicket = createSemaphore("parkTicket", COUNTING, MAX_IN_PARK);
	museumTicket = createSemaphore("museumTicket", COUNTING, MAX_IN_MUSEUM);
	carTicket = createSemaphore("carTicket", COUNTING, MAX_TICKETS);
	giftTicket = createSemaphore("giftTicket", COUNTING, MAX_IN_GIFTSHOP);

	////signal semaphores
	needVisitor = createSemaphore("needVisitor", BINARY, 0);
	visitorSeated = createSemaphore("visitorSeated", BINARY, 0);
	visitorReady = createSemaphore("visitorReady", BINARY, 0);
	buyTicket = createSemaphore("buyTicket", BINARY, 0);
	ticketReady = createSemaphore("ticketReady", BINARY, 0);
	driverReady = createSemaphore("driverReady", BINARY, 0);
	carReady = createSemaphore("carReady", BINARY, 0);

	wakeDriver = createSemaphore("wakeDriver", COUNTING, 0);
	needTicket = createSemaphore("needTicket", BINARY, 0);
	needDriver = createSemaphore("needDriver", BINARY, 0);

	takeTicket = createSemaphore("takeTicket", BINARY, 0);
	needCidUpdated= createSemaphore("needCidUpdate", BINARY, 0);
	cidUpdated= createSemaphore("cidUpdated", BINARY, 0);
	cidRecieved= createSemaphore("cidRecieved", BINARY, 0);

	requestTicketMutex= createSemaphore("requestTicketMutex", BINARY, 1);

	cidLock = createSemaphore("cidLock", BINARY, 1);
	for(i=0;i<NUM_DRIVERS;i++)
	{
		sprintf(buf, "driverLock%d", i);
		driverLock[i] = createSemaphore(buf, BINARY, 1);
	}
	for(i=0;i<NUM_CARS;i++)
	{
		sprintf(buf, "carLock%d", i);
		carLock[i] = createSemaphore(buf, BINARY, 1);
	}
	for(i=0;i<(NUM_VISITORS+NUM_DRIVERS);i++)
	{
		sprintf(buf, "rideDone[%d]", i);
		rideDone[i] = createSemaphore(buf, BINARY, 0);
	}
	//
	// start park
	sprintf(buf, "jurassicPark");
	newArgv[0] = buf;
	createTask( buf,				// task name
		jurassicTask,				// task
		MED_PRIORITY,				// task priority
		1,							// task count
		newArgv);					// task argument

	// wait for park to get initialized...
	while (!parkMutex) SWAP;
	printf("\nStart Jurassic Park...");

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "0";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "1";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "2";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "3";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "4";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "5";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "6";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "7";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "8";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "9";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "10";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "11";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "12";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "13";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "14";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "15";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "16";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "17";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "18";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "19";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument
	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "20";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "21";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "22";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "23";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "24";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "25";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "26";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "27";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "28";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "29";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument
	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "30";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "31";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "32";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "33";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "34";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "35";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "36";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "37";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "38";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "39";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument
	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "40";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "41";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "42";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "43";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument

	sprintf(buf, "visitorTask");
	newArgv[0] = buf;
	newArgv[1]= "44";
	createTask( buf,				// task name
		visitorTask,				// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);					// task argument


	sprintf(buf, "driverTask");
	newArgv[0] = buf;
	newArgv[1] = "0";
	createTask( buf,				// task name
		driverTask,					// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);

	sprintf(buf, "driverTask");
	newArgv[0] = buf;
	newArgv[1] = "1";
	createTask( buf,				// task name
		driverTask,					// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);

	sprintf(buf, "driverTask");
	newArgv[0] = buf;
	newArgv[1] = "2";
	createTask( buf,				// task name
		driverTask,					// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);

	sprintf(buf, "driverTask");
	newArgv[0] = buf;
	newArgv[1] = "3";
	createTask( buf,				// task name
		driverTask,					// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);

	sprintf(buf, "carTask");
	newArgv[0] = buf;
	newArgv[1] = "0";
	createTask( buf,				// task name
		carTask,					// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);

	sprintf(buf, "carTask");
	newArgv[0] = buf;
	newArgv[1] = "1";
	createTask( buf,				// task name
		carTask,					// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);

	sprintf(buf, "carTask");
	newArgv[0] = buf;
	newArgv[1] = "2";
	createTask( buf,				// task name
		carTask,					// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);

	sprintf(buf, "carTask");
	newArgv[0] = buf;
	newArgv[1] = "3";
	createTask( buf,				// task name
		carTask,					// task
		MED_PRIORITY,				// task priority
		2,							// task count
		newArgv);
	return 0;
} // end project3

void sleep(Semaphore* sem, int time)
{
	insertDeltaClock(sem,(rand()%(10*time))+1);
	semWait(sem);
	return;
}

int visitorTask(int argc, char* argv[])
{
	char buf[32];
	int vid=atoi(argv[1]);
	int cid;
	Semaphore* timeEvent;

	sprintf(buf,"starting visitor%02d",vid);
	ParkDebug(buf);

	sprintf(buf,"timeEvent%02d",vid);
	timeEvent=createSemaphore(buf,BINARY,0);

	while(1)
	{
		//show up at park at random time
		sleep(timeEvent,10);							SWAP;
		myPark.numOutsidePark++;						SWAP;

		//get in ticket line
		semWait(parkTicket);							SWAP;

		semWait(parkMutex);								SWAP;
		myPark.numOutsidePark--;						SWAP;
		myPark.numInPark++;								SWAP;
		myPark.numInTicketLine++;						SWAP;
		semSignal(parkMutex);							SWAP;
		sleep(timeEvent,2);								SWAP;
		
		//getting a car ticket
		semWait(carTicket);							SWAP;
		semSignal(needTicket);						SWAP;
		semSignal(wakeDriver);						SWAP;
		semWait(takeTicket);						SWAP;

		//get in museum line
		semWait(parkMutex);								SWAP;
		myPark.numTicketsAvailable--;					SWAP;
		myPark.numInTicketLine--;						SWAP;
		myPark.numInMuseumLine++;						SWAP;
		semSignal(parkMutex);							SWAP;
		sleep(timeEvent,2);								SWAP;

		//inside museum
		semWait(museumTicket);							SWAP;
		semWait(parkMutex);								SWAP;
		myPark.numInMuseumLine--;						SWAP;
		myPark.numInMuseum++;							SWAP;
		semSignal(parkMutex);							SWAP;
		sleep(timeEvent,5);								SWAP;
		
		//get in cars line
		semSignal(museumTicket);						SWAP;
		semWait(parkMutex);								SWAP;
		myPark.numInMuseum--;							SWAP;
		myPark.numInCarLine++;							SWAP;
		semSignal(parkMutex);							SWAP;
		sleep(timeEvent,2);								SWAP;

		//car ride
		//wait for car sig
		semWait(carReady);								SWAP;

		//resell ticket
		semSignal(carTicket);							SWAP;
		semWait(parkMutex);								SWAP;
		myPark.numInCarLine--;							SWAP;
		myPark.numInCars++;								SWAP;
		myPark.numTicketsAvailable++;					SWAP;
		semSignal(parkMutex);							SWAP;

		//handshake
		//request carid
		semSignal(needCidUpdated);						SWAP;
		//semwait on carid info say id is ready
		semWait(cidUpdated);							SWAP;
		//set cid from recently updated globalcid
		cid=globalCarid;								SWAP;

		if(myPark.cars[cid].passengerOne==-1)
		{
			myPark.cars[cid].passengerOne=vid;			SWAP;
		}
		else if(myPark.cars[cid].passengerTwo==-1)
		{
			myPark.cars[cid].passengerTwo=vid;			SWAP;
		}
		else if(myPark.cars[cid].passengerThree==-1)
		{
			myPark.cars[cid].passengerThree=vid;		SWAP;
		}
		//signal i have carid
		semSignal(cidRecieved);							SWAP;

		semWait(rideDone[vid]);							SWAP;
	
		//get in giftshop line
		semWait(parkMutex);								SWAP;
		myPark.numInCars--;								SWAP;
		myPark.numInGiftLine++;							SWAP;
		semSignal(parkMutex);							SWAP;
		sleep(timeEvent,2);								SWAP;

		//go inside giftshop
		semWait(giftTicket);							SWAP;
		semWait(parkMutex);								SWAP;
		myPark.numInGiftLine--;							SWAP;
		myPark.numInGiftShop++;							SWAP;
		semSignal(parkMutex);							SWAP;
		sleep(timeEvent,5);								SWAP;
		
		//leave park
		semWait(parkMutex);								SWAP;
		myPark.numInGiftShop--;							SWAP;
		myPark.numInPark--;								SWAP;
		myPark.numExitedPark++;							SWAP;
		semSignal(parkMutex);							SWAP;
		semSignal(giftTicket);							SWAP;
		semSignal(parkTicket);							SWAP;
		break;
	}
	return 0;
}

int carTask(int argc, char* argv[])
{
	char buf[32];
	int i,cid=atoi(argv[1]);
	sprintf(buf,"starting car%02d",cid);
	ParkDebug(buf);
	while(myPark.numExitedPark<NUM_VISITORS)
	{
		semWait(carLock[cid]);								SWAP;
		
		semWait(parkMutex);									SWAP;
		myPark.cars[cid].driver=-1;							SWAP;
		myPark.cars[cid].passengerOne=-1;					SWAP;
		myPark.cars[cid].passengerTwo=-1;					SWAP;
		myPark.cars[cid].passengerThree=-1;					SWAP;
		semSignal(parkMutex);								SWAP;

		for(i=0;i<NUM_SEATS;i++)
		{
			semWait(fillSeat[cid]);							SWAP;//park
			semSignal(carReady);							SWAP;

			//handshake
			//wait on id info request
			semWait(needCidUpdated);						SWAP;
			//wait on mutex
			semWait(cidLock);								SWAP;
			//update globalcid
			globalCarid=cid;								SWAP;
			//signal info is ready
			semSignal(cidUpdated);							SWAP;
			//wait for visitor to say info was recieved
			semWait(cidRecieved);							SWAP;
			//signal mutex
			semSignal(cidLock);								SWAP;

			semSignal(seatFilled[cid]);						SWAP;//park
		}
		//get driver
		semSignal(needDriver);								SWAP;
		semSignal(wakeDriver);								SWAP;

		//handshake
		//wait on id info request
		semWait(needCidUpdated);						SWAP;
		//wait on mutex
		semWait(cidLock);								SWAP;
		//update globalcid
		globalCarid=cid;								SWAP;
		//signal info is ready
		semSignal(cidUpdated);							SWAP;
		//wait for visitor to say info was recieved
		semWait(cidRecieved);							SWAP;
		//signal mutex
		semSignal(cidLock);								SWAP;

		semWait(rideOver[cid]);								SWAP;//park

		semSignal(rideDone[myPark.cars[cid].driver]);			SWAP;
		semSignal(rideDone[myPark.cars[cid].passengerOne]);		SWAP;
		semSignal(rideDone[myPark.cars[cid].passengerTwo]);		SWAP;
		semSignal(rideDone[myPark.cars[cid].passengerThree]);	SWAP;

		semSignal(carLock[cid]);							SWAP;
	}
	return 0;
}

int driverTask(int argc, char* argv[])
{
	char buf[32];
	int i,did=atoi(argv[1]);
	int cid;
	sprintf(buf,"starting car%02d",did);
	ParkDebug(buf);
	while(myPark.numExitedPark<NUM_VISITORS)
	{
		semWait(driverLock[did]);							SWAP;
		semWait(wakeDriver);								SWAP;
		if(semTryLock(needTicket))
		{
			semWait(parkMutex);								SWAP;
			myPark.drivers[did]=-1;							SWAP;
			semSignal(parkMutex);							SWAP;
			
			semSignal(takeTicket);							SWAP;

			semWait(parkMutex);								SWAP;
			myPark.drivers[did]=0;							SWAP;
			semSignal(parkMutex);							SWAP;
		}
		if(semTryLock(needDriver))
		{
			//handshake
			//request carid
			semSignal(needCidUpdated);						SWAP;
			//semwait on carid info say id is ready
			semWait(cidUpdated);							SWAP;
			//set cid from recently updated globalcid
			cid=globalCarid;								SWAP;
			myPark.cars[cid].driver=did;					SWAP;
			myPark.drivers[did]=cid;						SWAP;
			//signal i have carid
			semSignal(cidRecieved);							SWAP;

			semWait(rideDone[NUM_VISITORS+did]);			SWAP;

			semWait(parkMutex);								SWAP;
			myPark.drivers[did]=0;							SWAP;
			semSignal(parkMutex);							SWAP;
		}
		semSignal(driverLock[did]);							SWAP;
	}
	return 0;
}

// ***********************************************************************
// ***********************************************************************
// delta clock command
int P3_dc(int argc, char* argv[])
{
	int i;
	printf("\nDelta Clock");
	for (i=0; i<numDeltaClock; i++)
	{
		printf("\n%4d%4d  %-20s", i, deltaClock[i].time, deltaClock[i].sem->name);
	}
	return 0;
} // end CL3_dc


// ***********************************************************************
// display all pending events in the delta clock list
void printDeltaClock(void)
{
	int i;
	for (i=0; i<MAX_TASKS; i++)
	{
		if(deltaClock[i].time>=0)
		{
			printf("\n%4d%4d  %-20s", i, deltaClock[i].time, deltaClock[i].sem->name);
		}
	}
	return;
}

int insertDeltaClock(Semaphore* dctasksem, int dctasktime)
{
	int i;
	for (i=0; i<MAX_TASKS; i++)
	{
		if(deltaClock[i].time<0)
		{
			deltaClock[i].sem=dctasksem;
			deltaClock[i].time=dctasktime;
			numDeltaClock++;
			return 0;
		}
	}
}

int updateDeltaClock()
{
	int i;
	for(i=0;i<MAX_TASKS;i++)
	{
		deltaClock[i].time=deltaClock[i].time-1;
		if(deltaClock[i].time<=0 && deltaClock[i].sem)
		{
			semSignal(deltaClock[i].sem);
			deltaClock[i].sem=NULL;
			numDeltaClock--;
		}
	}
	return 0;
}
// ***********************************************************************
// monitor the delta clock task
int dcMonitorTask(int argc, char* argv[])
{
	int i, flg;
	char buf[32];

	while (numDeltaClock > 0)
	{
		SEM_WAIT(tics10thsec)
		flg = 0;
		for (i=0; i<10; i++)
		{
			if (event[i]->state ==1)			
			{
				printf("\n  event[%d] signaled", i);
				event[i]->state = 0;
				flg = 1;
			}
		}
		if (flg) printDeltaClock();
	}
	printf("\nNo more events in Delta Clock");

	// kill dcMonitorTask
	tcb[timeTaskID].state = S_EXIT;
	return 0;
} // end dcMonitorTask

// ***********************************************************************
int timeTask(int argc, char* argv[])
{
	char svtime[64];						// ascii current time
	while (1)
	{
		SEM_WAIT(tics10thsec)
		printf("\nTime = %s", myTime(svtime));
	}
	return 0;
} // end timeTask

// ***********************************************************************
// test delta clock
int P3_tdc(int argc, char* argv[])
{
	createTask( "DC Test",			// task name
		dcMonitorTask,		// task
		10,					// task priority
		argc,					// task arguments
		argv);

	//create task returns the tid
	timeTaskID = createTask( "Time",		// task name
		timeTask,	// task
		10,			// task priority
		argc,			// task arguments
		argv);
	return 0;
} // end P3_tdc