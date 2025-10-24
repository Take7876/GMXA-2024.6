/********************************************************************/
/* This file contains the source code needed to read the .xtc file. */
/* Use the gromacs source code to read the .xtc file                */
/********************************************************************/

#include <stdio.h>
#include <stdlib.h>

/******* gromacs header *************/
#include "gromacs/fileio/xtcio.h"

/********* original header ***************/
#include "gmxa/fileio/xtcio.h"
#include "gmxa/utility/find.h"



/**　Function to open xtc file　**/
XTC* openXtc(char* fnameXtc, char* fnameGro){

    /**　Allocate memory area to generate structure XTC　**/
    XTC* xp = _xtc_malloc();

    /** If the .xtc file and .gro file are reversed, change them **/
    _swap_fname(xp, &fnameXtc, &fnameGro);
    
    /** fio is a struct pointer, defined in the gromacs header file **/
    (*xp).fio = open_xtc(fnameXtc,"r");

    (*xp)._fnameGro = fnameGro;

    (*xp).index = NULL;

    (*xp).opdata.cnt = 0;

    return xp;
}
void _swap_fname(XTC* xp, char** xptr, char** gptr){
    
    /**  Generates an error if the .xtc file name contains .gro or if the .gro file name contains .xtc　**/
    if(find(*xptr, ".xtc") && !find(*xptr, ".gro") && find(*gptr, ".gro") && !find(*gptr, ".xtc"))return;
    else if(find(*gptr, ".xtc") && !find(*gptr, ".gro") && find(*xptr, ".gro") && !find(*xptr, ".xtc")){

        /** Swap the address of the pointer to the string itself **/
        char* tptr = *xptr;
        *xptr = *gptr;
        *gptr = tptr;
        return;
    }
    else _setError(xp, 8);

    return;
}
XTC* _xtc_malloc(){

    /**　Allocating area with xtc data type　**/
    XTC* xp = (XTC*)malloc(sizeof(XTC));
    if(xp == NULL)_setError(xp, 1);

    return xp;
}



/** readXtc is a bool type function that requires a pointer to the XTC structure as the first argument **/ 
/** 　and the number of steps you want to read as the second argument.                                 **/
bool readXtc(XTC* xp, int t_step){

    /** Declaration of arguments required for read xtcfile. **/ 
    /** These variables and functions are defined within the gromacs header. **/ 
    int natoms;
    int64_t step;
    real time;
    real prec;
    matrix box;
    gmx_bool bOK;



    if((*xp).opdata.cnt == 0){

        /** The function receives the address of "(*xp).data.natoms" and saves the number of atoms. **/
        /** Additionally, memory allocation for "&(*xp).opdata.crdptr" needs to be done only once within the function **/
        /** typically on the first call (read_first_xtc)**/
        read_first_xtc((*xp).fio, &(*xp).data.natoms, &step, &time, box, &(*xp).opdata.crdptr, &prec, &bOK);

        /** Allocation memory only once, and overwrites the same address from the second time onwards **/
        if((*xp).index == NULL) (*xp).index = _index_malloc(xp, (*xp).data.natoms);


        /** Saving coordinate information at once**/
        if(t_step == (int)step){
            (*xp).data.time = (double)time;
            (*xp).data.step = (int)step;
            (*xp).data.xbox = box[0][0];
            (*xp).data.ybox = box[1][1];
            (*xp).data.zbox = box[2][2];

            for(int j = 0; j < (*xp).data.natoms; j++){
                (*xp).index[j].x = (*xp).opdata.crdptr[j][0];
                (*xp).index[j].y = (*xp).opdata.crdptr[j][1];
                (*xp).index[j].z = (*xp).opdata.crdptr[j][2];
            }    
            
            _readGro(xp);

            /** Include this if statement so tht it runs only the first time **/
            (*xp).opdata.cnt ++;
            return true;
        }

        /** Include this if statement so tht it runs only the first time **/
        (*xp).opdata.cnt ++;
    }


    /** Loading from the second time onwards **/
    while(read_next_xtc((*xp).fio, (*xp).data.natoms, &step, &time, box, (*xp).opdata.crdptr, &prec, &bOK)){
        if(t_step == (int)step){
            (*xp).data.time = (double)time;
            (*xp).data.step = (int)step;
            (*xp).data.xbox = box[0][0];
            (*xp).data.ybox = box[1][1];
            (*xp).data.zbox = box[2][2];

            for(int j = 0; j < (*xp).data.natoms; j++){
                (*xp).index[j].x = (*xp).opdata.crdptr[j][0];
                (*xp).index[j].y = (*xp).opdata.crdptr[j][1];
                (*xp).index[j].z = (*xp).opdata.crdptr[j][2];
            }

            _readGro(xp);

            return true;
        }
        else if(t_step < (int)step) _setError(xp, 7);
    }
    

    /** If the .xtc file does not save the despired step number, exit with false **/
    return false;
}


/**　Releasing dynamic memory area secured with malloc　**/
void closeXtc(XTC* xp){

    free((*xp).index);
    close_xtc((*xp).fio);
    free(xp);
    return;
}



/** Below are the functions related to reading the .gro file　**/

void _readGro(XTC* xp){


    /** Generating a FILE type file pointer **/
    FILE *gfp;


    /** Maximum number of characters in string is 499 characters **/
    char title[MAX], line[MAX];

    /** .gro file open **/
    gfp = fopen((*xp)._fnameGro, "r");
    if(gfp == NULL)_setError(xp, 4);


    /** input grofile title and number of atoms ***/
    fgets(title, sizeof(title), gfp);
    fgets(line, sizeof(line), gfp);
    int natoms = atoi(line);


    /** Check if the number of atoms in the .xtc file and the number of atoms in the .gro file are the same **/
    if(natoms != (*xp).data.natoms)_setError(xp, 3);



    for(int i = 0; i < natoms; i++)_readGro_line(xp, gfp, &((*xp).index[i].resid), (*xp).index[i].resname, (*xp).index[i].atomname, &((*xp).index[i].atomid), i+1);

    /**** input pbc box ********/
    fgets(line, sizeof(line), gfp); 

    fclose(gfp);
    return;
}


/** Allocating memory area for Index type　**/
Index* _index_malloc(XTC* xp, int natoms){

    Index* ip = (Index*)malloc(sizeof(Index) * natoms); 
    if(ip == NULL)_setError(xp, 2); 

    return ip;
}


void _readGro_line(XTC *xp, FILE *gfp, int *resid, char *resname, char *atomname, int *atomid, int i){

    int t_resid, t_atomid;
    char t_resname[FORMAT], t_atomname[FORMAT], line[MAX];


    /** Skip unnecessary information with fgets **/
    if(fscanf(gfp, "%5d%5[^\n]%5[^\n]%5d", &t_resid, t_resname, t_atomname, &t_atomid) == EOF)_setError(xp, 6);
    fgets(line, sizeof(line), gfp);


    /**　Remove leading and trailing spaces in a string　**/
    _xtc_strcpy(xp, t_resname, resname);
    _xtc_strcpy(xp, t_atomname, atomname);
    *resid = t_resid; 
    *atomid = i;

    return;
}
void  _xtc_strcpy(XTC* xp, char* pstr, char* astr){
    
    /** Remove spaces from strings **/
    for(;*pstr == ' '; pstr++)if(*pstr == '\0')_setError(xp, 5);

    /** String comparison assignment **/
    while(*astr++ = *pstr++)if(*pstr == ' ')break;
    
    /** Assign \0 to the end of the string　**/
    *astr = '\0';
    return;
}


void _setError(XTC* xp, int num){
    
    fprintf(stderr, "\n");
    switch(num){
        case 1:
            fprintf(stderr, "# [GMXA, xtcio.c] Error: No memory avilable (structure XTC) [function name]: XTC* _xtc_malloc() \n\n");
            exit(1);
            break;
        
        case 2:
            fprintf(stderr, "# [GMXA, xtcio.c] Error: No memory avilable (structure Index) [function name]: Index* _index_malooc() \n\n");
            close_xtc((*xp).fio);
            free(xp);
            exit(1);
            break;  

        case 3:
            fprintf(stderr, "# [GMXA, xtcio.c] Error: The total number of atoms in the .gro file and the total number of atoms in the .xtc file are different \n\n");
            free((*xp).index);
            close_xtc((*xp).fio);
            free(xp); 
            exit(1);
            break;

        case 4:
            fprintf(stderr, "# [GMXA, xtcio.c] Error: Could not open .grofile [function name]: _readGro() \n\n");
            free((*xp).index);
            close_xtc((*xp).fio);
            free(xp);
            exit(1);
            break;

        case 5:
            fprintf(stderr, "# [GMXA, xtcio.c] Error: There is nothing in the given string [function name]: _xtc_strcpy() \n\n");
            free((*xp).index);
            close_xtc((*xp).fio);
            free(xp); 
            exit(1);
            break;

        case 6:
            fprintf(stderr, "# [GMXA, xtcio.c] Error: Failed to read .gro file [function name]: _readGro_line() \n\n");
            free((*xp).index);
            close_xtc((*xp).fio);
            free(xp);
            exit(1);
            break;

        case 7:
            fprintf(stderr, "# [GMXA, xtcio.c] Error: The first number of steps you specified does not exit in the .xtc file \n\n");
            free((*xp).index);
            close_xtc((*xp).fio);
            free(xp);
            exit(1);
            break;

        case 8:
            fprintf(stderr, "# [GMXA, xtcio.c] Error: There may be a mix of .xtc and .gro in the file \n\n");
            free(xp);
            exit(1);
            break; 
    }
    
    return;
}