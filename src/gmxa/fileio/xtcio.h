
/** This file contains the source code needed to read the .xtc file **/
#ifndef XTC_GMXA_H
#define XTC_GMXA_H

/** Include gromacs header file　**/
#include "gromacs/fileio/xtcio.h"


/**********************************************/
#define MAX 500
#define FORMAT 6
//typedef (*xp).index[i] Atomid[i]

/** Structures related to molecular dynamics calculations　**/
typedef struct{

    int time;
    int step;
    int natoms; 
    double xbox;
    double ybox;
    double zbox;
}Data;

/** Structure related to coordinates **/
typedef struct{

    char resname[FORMAT];
    int resid;
    int atomid;
    char atomname[FORMAT];
    double x;
    double y;
    double z;
}Index;

typedef struct{

    rvec *crdptr;
    int cnt;
}Opdata;

/** main structure **/
typedef struct{

    char* _fnameGro;
    t_fileio* fio;
    Data data;
    Opdata opdata;
    Index* index;
}XTC;



/**　.xtc file open function, read function, close function　**/
#ifdef __cplusplus
extern "C" {
#endif
    XTC* openXtc(char*, char*);
    bool readXtc(XTC*, int);
    void closeXtc(XTC*);
#ifdef __cplusplus
}
#endif



/** Functions not used within the main function **/
void _readGro(XTC*);
void _readGro_line(XTC*, FILE*, int*, char*, char*, int*, int);
void _setError(XTC*, int);
XTC* _xtc_malloc();
Index* _index_malloc(XTC*, int);
void _xtc_strcpy(XTC* ,char*, char*);
void _swap_fname(XTC*, char**, char**);

#endif