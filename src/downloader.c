#include <curl/curl.h>
#include <stdio.h>

/*
 * download_from_url(char* url, FILE* file)
 * Takes url as char*
 * Takes open file pointer as defined with fopen to write response into.
 */
void download_from_url(char* url, FILE* file) {
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if (curl) {

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) fprintf(stderr, "curl_easy_perform() returned %s\n",
                curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}
