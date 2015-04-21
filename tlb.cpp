#include "tlb.h"

TLB_entry::TLB_entry(int page, int frame, time_t last, time_t add, int acc) :
pageNumber(page), frameNumber(frame), lastUse(last), addTime(add), access (acc) {
}

/**
 * Lookup a page in the TLB.
 *
 * @return the corresponding frame or -1 if not found
 */
int TLB::findPage(int pageNumber)
{
    for (int i = 0; i < TLB_NUM_ENTRIES; i++)
    {
        if (TLBTable[i].pageNumber == pageNumber)
	{
            TLBTable[i].lastUse = time(NULL);
            TLBTable[i].access++;
            return TLBTable[i].frameNumber;
        }
    }

    return -1;
}

/**
 * Adds an entry-pair (pageNumber,frameNumber) to the TLB
 * Here you have to implement a replacement technique for
 * when the TLB is full. DONT FORGET to implement two different
 * function for this, even if you only call one of them
 */
void TLB::addEntry(int pageNumber, int frameNumber)
{
#ifdef FIFO
    int first = 0;
    time_t add = TLBTable[0].addTime;
    for (int i = 0; i < TLB_NUM_ENTRIES; i++)
    {
        if (TLBTable[i].pageNumber == -1)
	{
            TLBTable[i].frameNumber = frameNumber;
            TLBTable[i].pageNumber = pageNumber;
            TLBTable[i].addTime = time(NULL);
            TLBTable[i].lastUse = time(NULL);
            return;
        }
	else if (TLBTable[i].addTime < add)
	{
            first = i;
            add = TLBTable[i].addTime;
        }
    }
#endif
#ifdef LRU
    int lru = 0;
    time_t least = TLBTable[0].lastUse;
    for (int i = 0; i < TLB_NUM_ENTRIES; i++)
    {
        if (TLBTable[i].pageNumber == -1)
	{
            TLBTable[i].frameNumber = frameNumber;
            TLBTable[i].pageNumber = pageNumber;
            TLBTable[i].addTime = time(NULL);
            TLBTable[i].lastUse = time(NULL);
            return;
        }
	else if (TLBTable[i].lastUse < least)
	{
            lru = i;
            least = TLBTable[i].lastUse;
        }
    }
#endif
#ifdef LFU
    int lfu = 0;
    int acc = TLBTable[0].access;
    for (int i = 0; i < TLB_NUM_ENTRIES; i++)
    {
        if (TLBTable[i].pageNumber == -1)
	{
            TLBTable[i].frameNumber = frameNumber;
            TLBTable[i].pageNumber = pageNumber;
            TLBTable[i].addTime = time(NULL);
            TLBTable[i].lastUse = time(NULL);
            return;
        }
	else if (TLBTable[i].access < acc)
	{
            lfu = i;
            acc = TLBTable[i].access;
        }
    }
#endif
    TLBTable[first].frameNumber = frameNumber;
    TLBTable[first].pageNumber = pageNumber;
    TLBTable[first].addTime = time(NULL);
    TLBTable[first].lastUse = time(NULL);
    TLBTable[first].access = 0;
}

TLB::TLB() : nextEntryAvailable(0) {
}

TLB::~TLB() {
}

//----------DO NOT CHANGE/ERASE THIS------------------
// this function is neccesary to output the TLB state
// at the end of execution. It needs to
// be generated for evaluation purposes.

void TLB::printTLB() {
    ofstream tlbFile("TLB.txt", ios::out);\
     for (int i = 0; i < TLB_NUM_ENTRIES; ++i)
        tlbFile << TLBTable[i].pageNumber << " " << TLBTable[i].frameNumber <<
        " " << TLBTable[i].addTime << " " << TLBTable[i].lastUse << " " <<
               TLBTable[i].access << endl;
    tlbFile.close();
}
