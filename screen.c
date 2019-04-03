#include<stdio.h>
#include"screen.h"

void barChart(int a[])
{
	int i,j;  // counters
	for(i =0; i<80; i++){ // for 80 columns
		for(j=0; j<a[i]/3; j++){
			printf("\033[%d;%dH" , 35-j, i+1);
#ifdef UNICODE  // conditional compiling
			printf("%s", "\u2590");
#else
			printf("%c", ' ');
#endif
		}
	}
}

void clearScreen(void)
{
	printf("\033[2J");
	fflush(stdout); //output the escape sequence immediately
}
void setColors(short fg, short bg)
{
	printf("\033[%d;%d;1m", fg, bg);
	fflush(stdout);
}

void resetColors(void)
{
	printf("\033[0m");
	fflush(stdout);
}
