#include <stdio.h>
#include <math.h>
#include <curl/curl.h>
#include "comm.h"
#include "sound.h"
// this function will calculate 1 second of sound samples into 8-pieces of
// slow decibel (ISO standard),this data is calculated as 125ms of samples
// the first half of function is to calculate, the second half is to perform
// libcurl communication

void sendDATA(short s[])
{
	double rms[8], db[8];
	int i, j;
	for (i=0; i<8; i++){
		double sum = 0.0;
		for(j=0; j<2000; j++){
			sum += s[i*2000+j] * s[i*2000+j];
		}
		rms[i] = sqrt(sum/2000);
		db[i] = 20*log10(rms[i]);
	}
	//use libcurl functions to send data
	CURL *c;
	CURLcode res;
	char poststr[128];
	//post string should be in "db=num1;num2;.....;num8" format
	sprintf(poststr, "db=%.2f;%%20%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f",
			db[0],db[1], db[2], db[3],db[4],db[5],db[6],db[7]); // no space in db
#ifdef DEBUG
	printf("poststr = %s\n", poststr);	
#endif
	curl_global_init(CURL_GLOBAL_ALL);
	c = curl_easy_init();
	if(c){
		curl_easy_setopt(c, CURLOPT_URL,URL);
		curl_easy_setopt(c, CURLOPT_POSTFIELDS, poststr);
		res = curl_easy_perform(c);
		if(res != CURLE_OK) printf("communication failed!\n");
		
		curl_easy_cleanup(c);
	}
	curl_global_cleanup();
}
