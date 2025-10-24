#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "gmxa/utility/find.h"

char* _strdup_add_null(char* prev_ptr){
    
    char* new_ptr = (char*)malloc(strlen(prev_ptr) + 1);
    if(new_ptr == NULL){
        fprintf(stderr, "\n# [GMXA, find.c] Error: Memory allocation failed!\n");
        exit(0);
    }
    strcpy(new_ptr, prev_ptr);
    new_ptr[strlen(prev_ptr)] = '\0';

    return new_ptr;
}

int _compstr(const char* _srcptr, const char* _tgtptr){

    for(;*_srcptr != *_tgtptr; *_srcptr ++) if(*_srcptr == '\0') return -1;

    while(*_srcptr == *_tgtptr){

        if(*(++_tgtptr) == '\0') return 1;
        else if(*(++_srcptr) == '\0') return -1;
    }

    return 0;
}

bool find(char* srcptr, char* tgtptr){

    srcptr = _strdup_add_null(srcptr);
    char* head_srcptr = srcptr;

    tgtptr = _strdup_add_null(tgtptr);
    char* head_tgtptr = tgtptr;

    while(1){

        tgtptr = head_tgtptr;

        int check = _compstr(srcptr, tgtptr);
        if(check == 1){
            
            free(head_srcptr);
            free(head_tgtptr);
            return true;
        }
        else if(check == -1){

            free(head_srcptr);
            free(head_tgtptr);
            return false;
        }

        *srcptr ++;
    }

    fprintf(stderr, "\n# [GMXA, find.c] Error: An error has occurred! : findStr function\n");
    exit(0);
}
