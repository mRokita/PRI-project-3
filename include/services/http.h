//
// Created by mrokita on 20.01.19.
//

#ifndef PRI3_HTTP_H
#define PRI3_HTTP_H

typedef struct HttpResponse {
    char * data;
    size_t size;
    CURLcode code;
} HttpResponse;

size_t write_function(void *ptr, size_t size, size_t nmemb, HttpResponse *r);

HttpResponse * http_get(char * url);
#endif //PRI3_HTTP_H
