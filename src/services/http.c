//
// Created by mrokita on 20.01.19.
//

#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../include/services/http.h"


size_t write_function(void *ptr, size_t size, size_t nmemb, HttpResponse *r){
    size_t new_len = r->size + size*nmemb;
    r->data= realloc(r->data, new_len+1);
    memcpy(r->data+r->size, ptr, size*nmemb);
    r->data[new_len] = '\0';
    return size*nmemb;
}

HttpResponse * http_response_new(){
    HttpResponse * res = malloc(sizeof(HttpResponse));
    res->size = 0;
    res->data = malloc(res->size+1);
    res->data[res->size] = '\0';
    return res;
};

/**
 * @brief Gets HTTP response for url
 * @param url Site address
 * @return Filled HttpResponse
 */
HttpResponse * http_get(char * url){
    CURL *curl;
    HttpResponse * res = http_response_new();

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        /* example.com is redirected, so we tell libcurl to follow redirection */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, res);

        /* Perform the request, res->code will get the return code */
        res->code = curl_easy_perform(curl);
        /* Check for errors */
        if(res->code != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res->code));
        else {
            /* Print data for debug */
            printf("Data: %s\n", res->data);
        }

        /* Cleanup */
        curl_easy_cleanup(curl);
    }
    return res;
}
