#ifndef TLB_H
#define TLB_H

#include <ctime>
#include "common.h"

/**
 * Entrée du TLB. 
 */
class TLB_entry
{
public:
    int pageNumber;
    int frameNumber;
	/**
	 * Moment de la dernière utilisation de la page.
	 */ 
    time_t lastUse;
	/**
	 * Moment de l'ajout de la page dans le TLB. 
	 */
    time_t addTime;
	/**
	 * Nombre d'accès à la page depuis qu'elle se trouve dans le TLB. 
	 */
    int access;
    TLB_entry(int page = -1, int frame = -1, time_t last = time(NULL), time_t add = time(NULL), int access = 0);
};

class TLB
{
public:
    TLB_entry TLBTable[TLB_NUM_ENTRIES];

    TLB();
    ~TLB();
    // Looks for the pageNumber in the table, if it finds it it return
    // the coresponding frame if not it returns -1;
    int findPage(int pageNumber);

    //Adds an entry-pair (pageNumber,frameNumber) to the TLB
    //Here you have to implement a replacement technique for
    //when the TLB is full. DONT FORGET to implement two different
    //function for this, even if you only call one of them
    void addEntry(int pageNumber, int frameNumber);


    int nextEntryAvailable;

    //----------DO NOT CHANGE/ERASE THIS------------------
    // this function is neccesary to output the physical
    // memory state at the end of execution. It needs to
    // be generated for evaluation purposes.
    void printTLB();
    //----------------------------------------------------
};

#endif // TLB_H
