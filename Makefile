#////////////////////////////////////////////////
#// Name: Kyle Wiskel & Nayan Prakash
#// ID #: 1540485 & 1533064
#// CMPUT 275, Winter 2019
#//
#// CMPUT 275 Final Project -- Digital Image Processing Suite
#////////////////////////////////////////////////

# set C Compiler
CC := g++
# set Compilation flags
LFLAGS=-O2 -L/usr/X11R6/lib -lm -lpthread -lX11
CCFLAGS :=-c -std=c++11
# define object files
OBJS=hslModification.o main.o fourier.o masking.o kernelConvolve.o dithering.o colorspaceModification.o
# define executable files
EXE=main

# main target to make main executable
$(EXE): $(OBJS)
	$(CC) $(OBJS) -o $(EXE) $(LFLAGS)

# create main object file
main.o: main.cpp hslModification.h fourier.h  masking.h kernelConvolve.h dithering.h colorspaceModification.h
	$(CC) $(CCFLAGS)  main.cpp -o main.o  $(LFLAGS)

# create hslModification object file
hslModification.o: hslModification.cpp hslModification.h
	$(CC) $(CCFLAGS)  hslModification.cpp -o hslModification.o $(LFLAGS)

# create fourier object file
fourier.o: fourier.cpp fourier.h
	$(CC) $(CCFLAGS)  fourier.cpp -o fourier.o $(LFLAGS)

# create masking object file
masking.o: masking.cpp masking.h
	$(CC) $(CCFLAGS)  masking.cpp -o masking.o $(LFLAGS)

# create kernelConvolve object file
kernelConvolve.o: kernelConvolve.cpp kernelConvolve.h
	$(CC) $(CCFLAGS)  kernelConvolve.cpp -o kernelConvolve.o $(LFLAGS)

# create dithering object file
dithering.o: dithering.cpp dithering.h
	$(CC) $(CCFLAGS)  dithering.cpp -o dithering.o $(LFLAGS)

# create colorspaceModification object file
colorspaceModification.o: colorspaceModification.cpp colorspaceModification.h
	$(CC) $(CCFLAGS)  colorspaceModification.cpp -o colorspaceModification.o $(LFLAGS)

# create target to clean object files and executable
clean:
	@rm -f $(OBJS) $(EXE)
