#include <stdio.h>
#include <curl/curl.h>

int main(int argc, char **argv){
	CURL *c;
	CURLcode res;
	char id[20], email[40], poststr[100];
	
	if(argc<3){
		printf("Usage: %s [ID] [email]\n",argv[0]);
		return 1; //stop program because lack of arguments
	}

	sprintf(poststr, "ID=%s&email=%s", argv[1], argv[2]);
	curl_global_init(CURL_GLOBAL_ALL);
	c = curl_easy_init();
	if(c){
		curl_easy_setopt(c, CURLOPT_URL, "http://www.cc.puv.fi/~e1800959/appdev/curl.php");
		curl_easy_setopt(c, CURLOPT_POSTFIELDS, poststr);
		res = curl_easy_perform(c);
	if(res != CURLE_OK)
		printf("Error in curl_easy_perform.\n");
	else
		printf("Post data is sent.\n");
	curl_easy_cleanup(c);
	}

	curl_global_cleanup();
	return 0;
}
