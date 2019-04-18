#include <stdio.h>
#include <math.h>
#include "sound.h"
#include "screen.h"
int findPeaks(int d[]){
	int c = 0, i;
	for (i=1; i<80; i++){
		if(d[i] >= 75 && d[i-1] < 75) c++;
	}
	if(d[0] >= 75) c++;
	return c;
}
// this function gets one second of samples (16000), and calculates
// 80 pieces of decibel value, we know we need to calculate one decibel
// value from 200 samples, decibel value is calculated by RMS formula
void displayWAVDATA(short s[]){
	double rms[80];
	int dB[80];			// used to send decibel values to barchart
	short *ptr = s;		// we use a pointer, pointing to the beginning of array
	int i, j;			// for nested loop counters, outer loop repeats 80 times
	for(i=0; i<80; i++){
		double sum = 0;		// accumulate sum of squares
		for(j=0; j<200; j++){
			sum += (*ptr) * (*ptr);
			ptr++;			// pointing to the next sample
		}
		rms[i] = sqrt(sum/200);
#ifdef DEBUG
		printf("rms[%d] = %f\n", i, rms[i]);
#endif
		dB[i] = 20*log10(rms[i]);
	}
#ifndef DEBUG
	barChart(dB);
	int peaks = findPeaks(dB);
	setColors(WHITE, bg(BLACK));
	printf("\033[1;61H");
	printf("Peaks: %d           \n", peaks);
#endif
}
void displayWAVHDR(struct WAVHDR h){
#ifdef DEBUG
	showID("ChunkID", h.ChunkID);
	printf("Chunk size: %d\n", h.ChunkSize);
	showID("Format", h.Format);
	showID("Subchunk1ID", h.Subchunk1ID);
	printf("Subchunk1 size: %d\n", h.Subchunk1Size);
	printf("Audio Format: %d\n", h.AudioFormat);
	printf("Num. of Channels: %d\n", h.NumChannels);
	printf("Sample rate: %d\n", h.SampleRate);
	printf("Byte rate: %d\n", h.ByteRate);
	printf("Block Align: %d\n", h.BlockAlign);
	printf("Bits per sample: %d\n", h.BitsPerSample);
	showID("Subchunk2ID: ", h.Subchunk2ID);
	printf("Subchunk2 size: %d\n", h.Subchunk2Size);
#else
	setColors(WHITE, bg(RED));
	printf("\033[1;1H");
	printf("test.wav            ");
	setColors(YELLOW, bg(BLUE));
	printf("\033[1;21H");
	printf("Sample rate:%dHz    ",h.SampleRate);
	setColors(CYAN, bg(MAGENTA));
	printf("\033[1;41H");
	printf("Duration:%.2fsec    ",(float)h.Subchunk2Size/h.ByteRate);
	setColors(RED, bg(YELLOW));
#endif
}
void fillID(char *dst, const char *m){
	for(int i =0; i<4;i++)
		*dst++ = *m++; // copy m to dst*
}
void testTone(int c, int f, float d){
	if(f<30 || f> 16000){
		printf("frequency is out of range. \n");
		return;
	}
	if(c<1 || c>2){
		printf("number of channel is not okay\n");
		return;
	}
	if(d<1 || d>10){
		printf("duration is not okay.\n");
		return;
	}
	printf("%d %d %f\n", f, c, d);
	struct WAVHDR h; // we need to prepare a WAV header
	fillID(h.ChunkID, "RIFF");
	fillID(h.Format, "WAVE");
	fillID(h.Subchunk1ID, "fmt ");
	fillID(h.Subchunk2ID, "data");
	h.Subchunk1Size = 16; //for PCM
	h.AudioFormat = 1; 
	h.NumChannels = c;
	h.SampleRate = 44100;
	h.BitsPerSample = 16;
	if(c==1){ // mono channel
		h.ByteRate = h.SampleRate * c * h.BitsPerSample/ 8;
		h.BlockAlign = c * h.BitsPerSample/ 8;
		h.Subchunk2Size = d * h.SampleRate * h.BlockAlign;
		h.ChunkSize = h.Subchunk2Size + 36;
	}
	// prepare sound data
	short data[441000]; //[d * h.SampleRate];
	for(int i =0; i<d*h.SampleRate; i++){
		data[i] = 32767.0 * sin(2 * PI * i * f /44100);
	}
	FILE *fp = fopen("testTone.wav", "w");
	if(fp == NULL){
		printf("We cannot open the file\n");
		return;
	}
	fwrite(&h, sizeof(h), 1, fp); // write the header
	fwrite(data, d*h.SampleRate*sizeof(short), 1, fp);
	fclose(fp);
	printf("testTone is generated!\n");
}
