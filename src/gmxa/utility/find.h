#ifndef FIND_GMXA_H
#define FIND_GMXA_H

/** Functions not used within the main function **/
char* _strdup_add_null(char*);
int _compstr(const char*, const char*);


#ifdef __cplusplus
extern "C" {
#endif
    bool find(char*, char*);
#ifdef __cplusplus
}
#endif

#endif
