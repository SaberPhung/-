/* <DESC>
 * simple HTTP POST using the easy interface
 * </DESC>
 */ 
#include <stdio.h>
#include <curl/curl.h>
 
int main(int argc, char **argv)
{
	CURL *c;
	CURLcode res;
	char id[20], email[40], poststr[100];
	if(argc <3){
		printf("Usage: %s [ID] [email]\n", argv[0]);
		return 1; //program stops because the user has not given enough info
	}
	sprintf(poststr,"ID=%s&email=%s", argv[1], argv[2]);

	/* In windows, this will init the winsock stuff */ 
	curl_global_init(CURL_GLOBAL_ALL);
	c= curl_easy_init(); 

	/* get a curl handle */ 
	if(c) {
	/* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */ 
	curl_easy_setopt(c, CURLOPT_URL, "http://www.cc.puv.fi/~e1800920/curl.php");
	/* Now specify the POST data */ 
	curl_easy_setopt(c, CURLOPT_POSTFIELDS, "ID=e1800920&email=giao.pnq92@gmail.com");
 
	/* Perform the request, res will get the return code */ 
	res = curl_easy_perform(c);
	/* Check for errors */ 
	if(res != CURLE_OK)
		printf("Error in curl_easy_perform().\n");
	else
		printf("Post data is sent\n");
	curl_easy_cleanup(c);	
	}
	curl_global_cleanup();
	return 0;
}
