#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include "sound.h"

int main(){
	FILE *f;
	short sd[RATE]; // for all samples in 1 sec
	while(1){
		system(CMD);
		f = fopen("test.wav", "r");
		
		clearScreen();
		setColors(YELLOW, bg(BLUE));
		if(f == NULL){
			printf("cannot open the wav file.\n");
			return 1;
		}
		struct WAVHDR h;	// instance of wave header
		fread(&h, sizeof(h), 1, f);	// read wav header to h
		displayWAVHDR(h);	// show wav header information
		fread(&sd, sizeof(sd), 1, f); 
		displayWAVDATA(sd);
		fclose(f);	//close the opened
	}
	resetColors();
}
