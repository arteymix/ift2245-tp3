#include "virtualmemorymanager.h"

int main()
{
    ifstream commands(COMMANDS_FILE, ios::in);

    VirtualMemoryManager vm;

    int logicAddres;
    do
    {
        commands >> logicAddres;
        vm.addCommandFromLogicAddress(logicAddres);
    }
    while(commands.good());

    vm.applyCommands();
    vm.printResults();

    commands.close();

    return EXIT_SUCCESS;
}

