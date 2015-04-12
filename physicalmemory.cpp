#include "physicalmemory.h"

PhysicalMemory::PhysicalMemory(){
    //Open the BACKING_STORE file to being able to read from it afterwards
    backingStoreFile.open("BACKING_STORE.txt",ios::in );

	this->frames_used = 0;
	
    // fills the PhysicalMemory with spaces ' '
    for (int i=0; i<PHYSICAL_MEMORY_SIZE; ++i)
        physicalMemoryData[i] = ' ';
}

PhysicalMemory::~PhysicalMemory(){
    //Close the BACKING_STORE file
    backingStoreFile.close();
}

/**
 * Le frame libre correspond toujours à l'indice du nombre de frames utilisés. 
 * 
 * Il n'y a pas de politique de recyclage de frame avec le stockage, alors dès 
 * que tous les frames sont utilisés, cette fonction retournera toujours -1.
 * 
 * @return a free frame index, or -1 if none can be freed
 */
int PhysicalMemory::findFreeFrame()
{
	if (frames_used == NUM_FRAMES)
		return -1;
	
	return this->frames_used;
}

int PhysicalMemory::demandPageFromBackingStore (unsigned int pageNumber)
{
	int free_frame = this->findFreeFrame ();

	if (free_frame == -1)
		return -1;

	// déplacement sur la page à partir du début du fichier
	this->backingStoreFile.seekg (pageNumber * 256, backingStoreFile.beg);

	// lecture du fichier directement en mémoire physique
	this->backingStoreFile.read(&physicalMemoryData[free_frame * 256], 256);

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

