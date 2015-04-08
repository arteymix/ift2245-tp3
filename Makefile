main: main.cpp physicalmemory.cpp virtualmemorymanager.cpp tlb.cpp

rapport.pdf: rapport.md
	pandoc $< -o $@
