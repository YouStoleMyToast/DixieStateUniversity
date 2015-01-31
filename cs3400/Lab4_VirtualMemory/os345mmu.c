// os345mmu.c - LC-3 Memory Management Unit
// **************************************************************************
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
#include "os345.h"
#include "os345lc3.h"

// ***********************************************************************
// mmu variables

// LC-3 memory
unsigned short int memory[LC3_MAX_MEMORY];//main  memory

// statistics
int memAccess;						// memory accesses
int memHits;						// memory hits
int memPageFaults;					// memory faults
int nextPage;						// swap page size
int pageReads;						// page reads
int pageWrites;						// page writes

int getFrame(int);
int getAvailableFrame(void);

int getFrame(int notme)
{
	int frame;
	frame = getAvailableFrame();
	if (frame >=0) return frame;

	// run clock
	else if(frame<-1)
	{
		frame=globalClock();
		return frame;
	}
}

//int nextframe=0;
//global clock - #5 on slide 63
//accesses all global root page tables, user page tables, and data frames
//pa = (FRAME(upte1)<<6) + FRAMEOFFSET(va);
int globalClock()
{
	int ndcount=0;
	int va,pa,i,j,r,tasknum;
	int rpte,rpte1,rpte2;
	int upte,upte1,upte2;
	int frame, page;
	int rwnFlgAdr=PAGE_GET_ADR;
	int rwnFlgOldWrt=PAGE_OLD_WRITE;
	int rwnFlgFree=PAGE_FREE;
	int rwnFlgNewWrt=PAGE_NEW_WRITE;
	int rwnFlgPageRead=PAGE_FREE;
	//sometimes takes twocycles
	for(r=0;r<2;r++)
	{
		//9216 in hex is 2400
		//12288 in hex is 3000
		for (va=9216; va<12288; va+=64)
		{
			for(i=0; i < LC3_FRAME_SIZE; i+=2)
			{
				rpte1 = MEMWORD(LC3_RPT + RPTI(va+i));
				rpte2 = MEMWORD(LC3_RPT + RPTI(va+i) + 1);
				if(DEFINED(rpte1))
				{
					frame=FRAME(rpte1);
					page=SWAPPAGE(rpte2);
					/*
					if(DIRTY(rpte1))
					{
						if(PAGED(rpte2))
						{
							rpte2 = accessPage(page, frame, rwnFlgOldWrt);
							memory[rpte2] = rpte2;
						}
						else if(!PAGED(rpte2)) 
						{
							rpte2 = accessPage(page, frame, rwnFlgNewWrt);
							rpte2 = SET_PAGED(rpte2);
							memory[rpte2] = rpte2;
						}			
					}*/
					if(REFERENCED(rpte1) || PINNED(rpte1))
					{
						CLEAR_REF(rpte1);
					}
					else if(!REFERENCED(rpte1) && !PINNED(rpte1))
					{
						rpte1 = accessPage(page, frame, rwnFlgFree);
						memory[rpte1] = rpte1;
					}
					for(j=0; j < LC3_FRAME_SIZE; j+=2)
					{
						upte1 = MEMWORD((FRAME(rpte1)<<6) + UPTI(va+j));
						upte2 = MEMWORD((FRAME(rpte1)<<6) + UPTI(va+j) + 1);
						if(DEFINED(upte1))
						{
							frame=FRAME(upte1);
							page=SWAPPAGE(upte2);
							/*
							if(DIRTY(upte1))
							{
								if(PAGED(upte2))
								{
									upte2 = accessPage(page, frame, PAGE_OLD_WRITE);
									memory[upte2] = upte2;
								}
								else if(!PAGED(upte2)) 
								{
									upte2 = accessPage(page, frame, PAGE_NEW_WRITE);
									upte2 = SET_PAGED(upte2);
									memory[upte2] = upte2;
								}
							}*/	
							if(REFERENCED(upte1) || PINNED(upte1))
							{
								CLEAR_REF(upte1);
							}
							else if(!REFERENCED(upte1) && !PINNED(upte1))
							{
								upte1 = accessPage(page, frame, rwnFlgFree);
								memory[upte1] = upte1;
							}
							//return upte1 frame
							return frame;
						}
						//return rpte1 frame
						return frame;
					}
				}
			}
			//end (DEFINED(rpte1))
		}
		//end va loop
		//frame not defined
	}
	//end double loop return
	//frame not defined
}



/*
int taskLoc;
int clockLoc;
int uptLoc;
int globalClock(int notme)
{
	int frame, i, j, t, task;
	int rpta, upta;
	int rpte1, rpte2, upte1, upte2;
	bool defExists;
	for(t=0;t<2;t++)
	{
		task = 0;
		if(taskLoc)
		{
			task = taskLoc;
			taskLoc = 0;
		}
		//for all RPTs
		for (task; task<MAX_TASKS; task++)
		{
			if (tcb[task].name)
			{

				i = 0;
				if(clockLoc)
				{
					i = clockLoc;
					clockLoc = 0;
				}
				//for all addresses in that RPT
				for(i; i < LC3_FRAME_SIZE; i+=2)
				{	
					rpta = i + tcb[task].RPT;
					rpte1 = memory[rpta];
					rpte2 = memory[rpta+1];
					//if a UPT is defined at that address
					if(DEFINED(rpte1))
					{
						defExists = FALSE;

						//check for a "left off" point
						j = 0;
						if(uptLoc)
						{
							j = uptLoc;
							uptLoc = 0;
						}
						//for all addresses in the UPT
						//we will now check for a data frame
						//for all data frames in the UPT
						for(j; j < LC3_FRAME_SIZE; j+=2)
						{
							upta = (FRAME(rpte1)<<6) + j;
							upte1 = memory[upta];
							upte2 = memory[upta+1];
							//if there is a valid data frame
							if(DEFINED(upte1))
							{
								//It should have been pinned already
								defExists = TRUE;
								//if the data frame is referenced then
								//it is safe this time (till clock)
								//goes around
								if(REFERENCED(upte1))
								{
									//get rid of the reference bit
									upte1 = CLEAR_REF(upte1);
									upte1 = SET_DIRTY(upte1);
									memory[upta]=upte1;
									rpte1 = SET_DIRTY(rpte1);
									memory[rpta]=rpte1;
								}
								//if it is available to be swapped out
								else if(!REFERENCED(upte1))
								{
									//get the frame number (we are about to change upte1)
									frame = FRAME(upte1);
									if(DIRTY(upte1))
									{
										//if it's already in memory just update it
										if(PAGED(upte2))
										{
											accessPage(SWAPPAGE(upte2), frame, PAGE_OLD_WRITE);
										}
										//otherwise put it somewhere and update the swap address
										else if(!PAGED(upte2)) 
										{
											upte2 = accessPage(SWAPPAGE(upte2), frame, PAGE_NEW_WRITE);
											upte2 = SET_PAGED(upte2);
											memory[upta+1] = upte2;
										}
										
									}
									upte1 = CLEAR_DEFINED(upte1);
									memory[upta] = upte1;
									rpte1 = SET_DIRTY(rpte1);
									memory[rpta] = rpte1;
									taskLoc = task;
									clockLoc = i;
									uptLoc = j+2;
									return frame;
								}
							}
						}
						//if no data frame available we
						//check to see if the UPT is available to 
						//be removed (but not the one asking for a frame)
						if(rpta != notme)
						{
							//if there are no data frames in this UPT
							if(!defExists)
							{
								rpte1 = CLEAR_PINNED(rpte1);
							}
							else if(defExists)
							{
								//just in case
								rpte1 = SET_PINNED(rpte1);
							}
							if(REFERENCED(rpte1))
							{
								rpte1 = CLEAR_REF(rpte1);
								memory[rpta]=rpte1;
							}
							else if(!PINNED(rpte1))
							{
								frame = FRAME(rpte1);
								if(DIRTY(rpte1))
								{
									//if already in memory
									if(PAGED(rpte2))
									{
										accessPage(SWAPPAGE(rpte2), frame, PAGE_OLD_WRITE);
									}
									else
									{
										rpte2 = accessPage(SWAPPAGE(rpte2), frame, PAGE_NEW_WRITE);
										rpte2 = SET_PAGED(rpte2);
										memory[rpta+1] = rpte2;
									}
								}
								rpte1 = CLEAR_DEFINED(rpte1);
								memory[rpta] = rpte1;
								taskLoc = task;
								clockLoc = i+2;
								uptLoc = 0;
								return frame;
							}
						}
					}
				}
			}
		}
	}
}
*/

// **************************************************************************
// **************************************************************************
// LC3 Memory Management Unit
// Virtual Memory Process
// **************************************************************************
//           ___________________________________Frame defined
//          / __________________________________Dirty frame
//         / / _________________________________Referenced frame
//        / / / ________________________________Pinned in memory
//       / / / /     ___________________________
//      / / / /     /                 __________frame # (0-1023) (2^10)
//     / / / /     /                 / _________page defined
//    / / / /     /                 / /       __page # (0-4096) (2^12)
//   / / / /     /                 / /       /
//  / / / /     / 	             / /       /
// F D R P - - f f|f f f f f f f f|S - - - p p p p|p p p p p p p p

#define MMU_ENABLE	1

unsigned short int *getMemAdr(int va, int rwFlg)
{
	unsigned short int pa;
	int rpta, rpte1, rpte2;
	int upta, upte1, upte2;
	int rptFrame, uptFrame;

	//rpta = tcb[curTask].RPT+ RPTI(va);//either one seems to work
	rpta = 0x2400 + RPTI(va);//either one seems to work
	rpte1 = memory[rpta];
	rpte2 = memory[rpta+1];

	// turn off virtual addressing for system RAM
	if (va < 0x3000) return &memory[va];
#if MMU_ENABLE
	if (DEFINED(rpte1))
	{
		// defined
	}
	else
	{
		// fault
		rptFrame = getFrame(-1);
		rpte1 = SET_DEFINED(rptFrame);
		if (PAGED(rpte2))
		{
			accessPage(SWAPPAGE(rpte2), rptFrame, PAGE_READ);
		}
		else
		{
			//rpte1=SET_DIRTY(rpte1);//save dirty for last
			//rpte2=0;//save dirty for last
			memset(&memory[(rptFrame<<6)], 0, 128);
		}
	}


	memory[rpta] = rpte1 = SET_REF(rpte1);
	memory[rpta] = rpte1 = SET_PINNED(rpte1);
	memory[rpta+1] = rpte2;

	upta = (FRAME(rpte1)<<6) + UPTI(va);
	upte1 = memory[upta];
	upte2 = memory[upta+1];

	if (DEFINED(upte1))
	{
		// defined
	}
	else
	{
		// fault
		uptFrame = getFrame(FRAME(memory[rpta]));
		upte1 = SET_DEFINED(uptFrame);
		if (PAGED(upte2))
		{
			accessPage(SWAPPAGE(upte2), uptFrame, PAGE_READ);
		}
		else
		{
			//upte1=SET_DIRTY(upte1);//save dirty for last
			//upte2=0;//save dirty for last
		}
	}

	memory[upta] = SET_REF(upte1);
	memory[upta+1] = upte2;

	return &memory[(FRAME(upte1)<<6) + FRAMEOFFSET(va)];
#else
	return &memory[va];
#endif
} // end getMemAdr


// **************************************************************************
// **************************************************************************
// set frames available from sf to ef
//    flg = 0 -> clear all others
//        = 1 -> just add bits
//
void setFrameTableBits(int flg, int sf, int ef)
{	int i, data;
	int adr = LC3_FBT-1;             // index to frame bit table
	int fmask = 0x0001;              // bit mask

	// 1024 frames in LC-3 memory
	for (i=0; i<LC3_FRAMES; i++)
	{	if (fmask & 0x0001)
		{  fmask = 0x8000;
			adr++;
			data = (flg)?MEMWORD(adr):0;
		}
		else fmask = fmask >> 1;
		// allocate frame if in range
		if ( (i >= sf) && (i < ef)) data = data | fmask;
		MEMWORD(adr) = data;
	}
	return;
} // end setFrameTableBits


// **************************************************************************
// get frame from frame bit table (else return -1)
int getAvailableFrame()
{
	int i, data;
	int adr = LC3_FBT - 1;				// index to frame bit table
	int fmask = 0x0001;					// bit mask

	for (i=0; i<LC3_FRAMES; i++)		// look thru all frames
	{	if (fmask & 0x0001)
		{  fmask = 0x8000;				// move to next work
			adr++;
			data = MEMWORD(adr);
		}
		else fmask = fmask >> 1;		// next frame
		// deallocate frame and return frame #
		if (data & fmask)
		{  MEMWORD(adr) = data & ~fmask;
			return i;
		}
	}
	return -1;
} // end getAvailableFrame



// **************************************************************************
// read/write to swap space
int accessPage(int pnum, int frame, int rwnFlg)
{
   static unsigned short int swapMemory[LC3_MAX_SWAP_MEMORY];

   if ((nextPage >= LC3_MAX_PAGE) || (pnum >= LC3_MAX_PAGE))
   {
      printf("\nVirtual Memory Space Exceeded!  (%d)", LC3_MAX_PAGE);
      exit(-4);
   }
   switch(rwnFlg)
   {
      case PAGE_INIT:                    		// init paging
         nextPage = 0;
         return 0;

      case PAGE_GET_ADR:                    	// return page address
         return (int)(&swapMemory[pnum<<6]);

      case PAGE_NEW_WRITE:                   // new write (Drops thru to write old)
         pnum = nextPage++;

      case PAGE_OLD_WRITE:                   // write
         //printf("\n    (%d) Write frame %d (memory[%04x]) to page %d", p.PID, frame, frame<<6, pnum);
         memcpy(&swapMemory[pnum<<6], &memory[frame<<6], 1<<7);
         pageWrites++;
         return pnum;

      case PAGE_READ:                    // read
         //printf("\n    (%d) Read page %d into frame %d (memory[%04x])", p.PID, pnum, frame, frame<<6);
      	memcpy(&memory[frame<<6], &swapMemory[pnum<<6], 1<<7);
         pageReads++;
         return pnum;

      case PAGE_FREE:                   // free page
         break;
   }
   return pnum;
} // end accessPage
