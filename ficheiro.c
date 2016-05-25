#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "header.h"

void verifica_ficheiros(){
	if (access("listas.txt",F_OK)==-1){
    	FILE *f1;
    	f1=fopen("listas.txt","w");
    	fclose(f1);
	}
}


