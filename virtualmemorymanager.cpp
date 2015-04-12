#include "virtualmemorymanager.h"

/**
 * Extract the page number and the offset from the logical
 * address according to the TP3, then save it in the
 * corresponding 'pageNumber' and 'offset' varibles.
 * 
 * L'implémentation utilise un type union pour extraire les données de l'adresse
 * logique.
 */
Command::Command(unsigned int logicAddress): logicalAdd(logicAddress) {
	logical_address_t bleh;

	bleh.logical_address = logicAddress;

	this->logicalAdd = logicAddress;
	this->pageNumber = bleh.fields.page_number;
	this->offset     = bleh.fields.offset;
}

// After reading all commands and storing them in the commandList
// traverse the list to apply each command.
void VirtualMemoryManager::applyCommands(){
    for (list<Command>::iterator it = commandList.begin(); it != commandList.end(); it++){
        Command c = *it;

		// lookup dans le TLB
		int frame_number = this->tlb.findPage (c.pageNumber);

		if (frame_number == -1)
		{
			TLBMissCount++;
			// lookup dans la table de page virtuelle
			if (this->pageTable[c.pageNumber].verificationBit) 
			{
				frame_number = this->pageTable[c.pageNumber].frameNumber;
			} 
			else 
			{
				pageFaultCount++;
				frame_number = this->physicalMemory.demandPageFromBackingStore (c.pageNumber);
			}
		}
		else
		{
			TLBHitCount++;
		}

		if (frame_number == -1)
		{
			std::cerr << "page %i not found in physical memory" << endl;
			continue;
		}

		pageFoundCount++;

		// c'est garanti que la page est chargée dans le frame demandé
		signed char val = this->physicalMemory.getValueFromFrameAndOffset (frame_number, c.offset);
		
        int physicalAddress = 0;

        cout << "Original Addr: " << setw(5) << c.logicalAdd
             << "\tPage: " << setw(3) << c.pageNumber
             << "\tOffset: " << setw(3) << c.offset
             << "\tPhysical Addr: " << setw(5) << physicalAddress
             << "\tValue: " << val << endl;

    }
}

void VirtualMemoryManager::printResults(){
    cout << endl;
    cout << "Page-Faults: " << pageFaultCount << "\tPage founds: " << pageFoundCount << endl;
    cout << "TLB-Hit: " << TLBHitCount << "\tTLB-miss: " << TLBMissCount << endl;
    cout << "Page-Fault rate: " << pageFaultCount/float(pageFaultCount+pageFoundCount) << endl;
    cout << "TLB-Hit rate: " << TLBHitCount/float(TLBHitCount+TLBMissCount) << endl;

    //----------DO NOT CHANGE/ERASE THIS------------------
    physicalMemory.printPhysicalMemory();
    tlb.printTLB();
    //-----------------------------------------------------
}

VirtualMemoryManager::VirtualMemoryManager() :
    pageFaultCount(0), pageFoundCount(0){
}

void VirtualMemoryManager::addCommandFromLogicAddress(unsigned int logicAddres){
    commandList.push_back(Command(logicAddres));
}
