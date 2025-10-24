



CXX		=  clang++
CC  		=  clang
CCFLAGS11	=  -std=c11
CXXFLAGS17	=  -std=c++17


LIB_DIR		=  ./lib
TARGET		=  $(LIB_DIR)/libgmxa.a


MSD_CPP_SOURCES		=./src/gmxa/msd/msd.cpp
VECTOR_CPP_SOURCES  =./src/gmxa/utility/vector.cpp
DATE_CPP_SOURCES	=./src/gmxa/utility/date.cpp
DFS_CPP_SOURCES	    =./src/gmxa/graph/dfs.cpp

XTC_C_SOURCES		=./src/gmxa/fileio/xtcio.c
FIND_C_SOURCES		=./src/gmxa/utility/find.c
DATE_C_SOURCES		=./src/gmxa/utility/date.c
PBC_C_SOURCES		=./src/gmxa/utility/pbc.c


GMXA_INDIR	=  -I./src/

### Please change to the directory environment within your computer ############

GROMACS_INDIR   =  -I/write/your/directory

## If you use the gromacs version after 2022
#GROMACS_INDIR_VEC = -I/write/your/directory

GROMACS_LIBDIR	=  -L/write/your/directory

################################################################################
GROMACS_LIBS	=  -lgromacs




OBJ_DIR				=  ./obj

MSD_CPP_OBJECT      =  $(OBJ_DIR)/msd.cpp.o
VECTOR_CPP_OBJECT   =  $(OBJ_DIR)/vector.cpp.o
DATE_CPP_OBJECT		=  $(OBJ_DIR)/date.cpp.o
DFS_CPP_OBJECT		=  $(OBJ_DIR)/dfs.cpp.o

XTC_C_OBJECT      	=  $(OBJ_DIR)/xtcio.c.o
FIND_C_OBJECT     	=  $(OBJ_DIR)/find.c.o
DATE_C_OBJECT 		=  $(OBJ_DIR)/date.c.o
PBC_C_OBJECT 		=  $(OBJ_DIR)/pbc.c.o

OBJECTS				=  $(MSD_CPP_OBJECT) $(VECTOR_CPP_OBJECT) $(XTC_C_OBJECT) $(FIND_C_OBJECT) $(DATE_C_OBJECT) $(DATE_CPP_OBJECT) $(DFS_CPP_OBJECT) $(PBC_C_OBJECT)



$(TARGET): $(OBJECTS)
	ar rcs $(TARGET) $(OBJECTS)


$(MSD_CPP_OBJECT): $(MSD_CPP_SOURCES)
	$(CXX) $(GMXA_INDIR) $(MSD_CPP_SOURCES) -o $(MSD_CPP_OBJECT) -c

$(VECTOR_CPP_OBJECT): $(VECTOR_CPP_SOURCES)
	$(CXX) $(GMXA_INDIR) $(VECTOR_CPP_SOURCES) -o $(VECTOR_CPP_OBJECT) -c

$(DATE_CPP_OBJECT): $(DATE_CPP_SOURCES)
	$(CXX) $(GMXA_INDIR) $(DATE_CPP_SOURCES) -o $(DATE_CPP_OBJECT) -c

$(DFS_CPP_OBJECT): $(DFS_CPP_SOURCES)
	$(CXX) $(GMXA_INDIR) $(DFS_CPP_SOURCES) -o $(DFS_CPP_OBJECT) -c $(CXXFLAGS17)


$(XTC_C_OBJECT): $(XTC_C_SOURCES) $(FIND_C_SOURCES)
	$(CXX) $(GMXA_INDIR) $(GROMACS_INDIR) $(GROMACS_LIBDIR) $(GROMACS_LIBS) $(XTC_C_SOURCES) -o $(XTC_C_OBJECT) -c
	
$(FIND_C_OBJECT): $(FIND_C_SOURCES)
	$(CC) $(GMXA_INDIR) $(FIND_C_SOURCES) -o $(FIND_C_OBJECT) -c

$(DATE_C_OBJECT): $(DATE_C_SOURCES)
	$(CXX) $(GMXA_INDIR) $(DATE_C_SOURCES) -o $(DATE_C_OBJECT) -c

$(PBC_C_OBJECT): $(PBC_C_OBJECT)
	$(CC) $(GMXA_INDIR) $(PBC_C_SOURCES) -o $(PBC_C_OBJECT) -c $(CCFLAGS11)




.PHONY: clean touch_all

# make the directories to output file
build:
	mkdir -p obj lib

# Clean up generated files
clean:
	 rm $(TARGET) $(OBJECTS)

# Update timestamps of all source and object files
touch_all:
	find ./src -type f -exec touch {} +
	find ./obj -type f -exec touch {} +

