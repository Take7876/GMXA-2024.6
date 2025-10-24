#include <stdio.h>
#include <stdbool.h>
#include "gmxa/utility/find.h"

int main(void){

   if(find("hom homhomt homhhomuhomt", "home")) printf("OK!\n");
   else printf("miss!\n");

   return 0;
}
