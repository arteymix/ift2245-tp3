#include "physicalmemory.h"

PhysicalMemory::PhysicalMemory(){
    //Open the BACKING_STORE file to being able to read from it afterwards
    backingStoreFile.open("../VirtualMemoryManager/BACKING_STORE.txt",ios::in );

    // fills the PhysicalMemory with spaces ' '
    for (int i=0; i<PHYSICAL_MEMORY_SIZE; ++i)
        physicalMemoryData[i] = ' ';
}

PhysicalMemory::~PhysicalMemory(){
    //Close the BACKING_STORE file
    backingStoreFile.close();
}

//Looks for a free frame to store the page read from the BACKING_STORE file
int PhysicalMemory::findFreeFrame(){
    /// --------TP3__TO_DO---------
    ///
    ///

	

		
    return 0;
}

int PhysicalMemory::demandPageFromBackingStore(unsigned int pageNumber){
    /// --------TP3__TO_DO---------
    ///
    ///

	this->backingStoreFile.seekg (pageNumber * 256);

	unsigned int free_frame = this->findFreeFrame ();

	if (free_frame == -1)
	{
		std::cerr << "no more free frame in physical memory" << endl;
		return -1;
	}

	this->backingStoreFile.read(&this->physicalMemoryData[free_frame * 256], 256);

	frames_used++;
	
    return free_frame;
}

char PhysicalMemory::getValueFromFrameAndOffset(unsigned int frameNumber, unsigned int offset)
{
	return physicalMemoryData[frameNumber * 256 + offset];
}




//----------DO NOT CHANGE/ERASE THIS------------------
// this function is neccesary to output the physical
// memory state at the end of execution. It needs to
// be generated for evaluation purposes.
void PhysicalMemory::printPhysicalMemory(){
    ofstream physicalMemoryFile("PhysicalMemory.txt",ios::out );
    for (int i=0; i<PHYSICAL_MEMORY_SIZE; ++i)
        physicalMemoryFile << physicalMemoryData[i];
    physicalMemoryFile.close();
}

