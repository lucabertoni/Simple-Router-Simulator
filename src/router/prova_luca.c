#include <stdio.h>
#include "../lib/common.h"
void main(){
	FILE *fd;
	char *riga_file;
	char **aRow;
	fd = fopen("./routingtable.txt","r");
	while(fgets(riga_file,100,fd)){
		printf("DENTRO|%s|\n",riga_file);
		aRow = explode(riga_file,'|');
		printf("|COSTO%s|\n", aRow[2]);
	}
}