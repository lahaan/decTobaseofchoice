#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int enterBase();
int readingNumbers(FILE *, int *);
char *convert(int, int);
void writingNumbers(FILE *, int, int *, int);

int main() {
    int base = enterBase();
	FILE *fp;
    int *list = NULL;
    int count = 0;

    fp = fopen("F1.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(0);
    }

    list = readingNumbers(fp, &count);
    
    fclose(fp);
	
	FILE *fpW;
	fpW = fopen("F2.txt", "w");
	if (fpW == NULL){
		printf("Error opening file\n");
		exit(0);
	}
	
	writingNumbers(fpW, base, list, count);
	
	fclose(fpW);
	
	free(list);
	
    return 0;
}

char *convert(int num, int base) {
    static char number_types[]= "0123456789ABCDEF";
    static char buffer[50];
    char *ptr;

    ptr = &buffer[49];
    *ptr = '\0';

    do{
        *--ptr = number_types[num%base];
        num /= base;
    }while(num != 0);
	
    return(ptr);
}

int readingNumbers(FILE *fp, int *count){
    int num;
    int *list = NULL;

    while (fscanf(fp, "%d", &num) == 1) {
        (*count)++;
        list = (int*) realloc(list, (*count) * sizeof(int));
        if (list == NULL) {
            printf("Error allocating memory\n");
            exit(0);
        }
        list[(*count) - 1] = num;
    }
    return list;
}

int enterBase(){
	int base;
	printf("Enter base: ");
    scanf("%d", &base);
    if ((base < 2) || (base > 16))
	{
		printf("Invalid input, base has to be bigger than 1 and smaller than 17\n");
		return enterBase();
	}
    return base;
}

void writingNumbers(FILE *fpW, int base, int *list, int count){
	int i;
	for (i = 0; i < count; i++){
		fprintf(fpW, "Number %d in base %d -> %s\n", list[i], base, convert(list[i], base));
	}
}
