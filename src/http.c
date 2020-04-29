#include "http.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>

static int write_data_to_file(void *ptr, int size, int nmemb, void *stream)
{
    int written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}
static int write_data_to_buff(void *ptr, int size, int nmemb, void *stream)
{
    if(size*nmemb >= MAX_LIST_SIZE)
        return -1;
    else
        memcpy((char *)stream, ptr, size*nmemb);
    return size*nmemb;
}
int http_init(void)
{
    CURLcode res;
    res = curl_global_init(CURL_GLOBAL_ALL);
    if(res != CURLE_OK)
    {
        fprintf(stderr, "curl_global_init() failed: %s\n", curl_easy_strerror(res));
        return -1;
    }
    return 0;
}

void http_clean(void)
{
    curl_global_cleanup();
}
/* 
 * Download a given URL into a local file named fileName.
 */
double http_down_file(const char *fileName, const char *url)
{
    CURL *curl_handle;
    CURLcode res;
    FILE *file;
    /* init the curl session */
    curl_handle = curl_easy_init();
    if(curl_handle)
    {
        /* set URL to get here */
        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        /* Switch on full protocol/debug output while testing */
        curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
        /* disable progress meter, set to 0L to enable it */
        curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
        /* send all data to this function  */
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data_to_file);
        /* open the file */
        file = fopen(fileName, "wb");
        if(file) 
        {
            /* write the page body to this file handle */
            curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, file);
            /* get it! */
            res = curl_easy_perform(curl_handle);
            /* close the header file */
            fclose(file);
            /* Check for errors */
            if(res != CURLE_OK)
            {
                remove(fileName);
                fprintf(stderr, "http_down_file() %s failed: %s\n", fileName, curl_easy_strerror(res));
                curl_easy_cleanup(curl_handle);
                return -1;
            }
            long code;
            double length;
            /* ask for the content-type */
            res = curl_easy_getinfo(curl_handle, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &length);
            if(CURLE_OK == res)
            {
                curl_easy_cleanup(curl_handle);
                if(length < 500)
                {
                    remove(fileName);
                    return -1;
                }
                else
                    return length;
            }
            else
            {
                printf("curl_easy_getinfo failed\n");
            }
        }
        else
        {
            printf("http_down_file open failed\n");
            curl_easy_cleanup(curl_handle);
            return -1;
        }
    }
    /* cleanup curl stuff */
    printf("http_down_file sucess\n");
    curl_easy_cleanup(curl_handle);
    return 0;
}

long http_get_heart(const char *url)
{
    CURL *curl_handle;
    CURLcode res;
    
    curl_handle = curl_easy_init();
    if(curl_handle) 
    {
        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
        res = curl_easy_perform(curl_handle);
        
        if(CURLE_OK == res)
        {
            long code;
            /* ask for the content-type */
            res = curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &code);
            if(CURLE_OK == res)
            {
                printf("We received staus-code: %ld\n", code);
                curl_easy_cleanup(curl_handle);
                return code;
            }
            else
            {
                printf("curl_easy_getinfo failed\n");
            }
        }
        else
        {
            printf("http_get_heart failed\n");
        }
        /* always cleanup */
        curl_easy_cleanup(curl_handle);
    }
    return 0;
}
long http_get_list(char *list, const char *url)
{
    CURL *curl_handle;
    CURLcode res;
    /* init the curl session */
    curl_handle = curl_easy_init();
    if(curl_handle)
    {
        /* set URL to get here */
        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        /* Switch on full protocol/debug output while testing */
        curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
        /* disable progress meter, set to 0L to enable it */
        curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
        /* send all data to this function  */
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data_to_buff);
        /* open the file */
        /* write the page body to this file handle */
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, list);
        /* get it! */
        res = curl_easy_perform(curl_handle);
        /* Check for errors */
        if(res != CURLE_OK)
        {
            fprintf(stderr, "http_get_list() failed: %s\n", curl_easy_strerror(res));
            curl_easy_cleanup(curl_handle);
            return -1;
        }
        long code;
        res = curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &code);
        if(CURLE_OK == res)
        {
            printf("We received staus-code: %ld\n", code);
            curl_easy_cleanup(curl_handle);
            return code;
        }
        else
        {
            printf("curl_easy_getinfo failed\n");
        }
    }
    /* cleanup curl stuff */
    curl_easy_cleanup(curl_handle);
    return 0;
}
long http_delete_pic_from_list(const char *url)
{
    CURL *curl_handle;
    CURLcode res;
    /* init the curl session */
    curl_handle = curl_easy_init();
    if(curl_handle)
    {
        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L); 
        res = curl_easy_perform(curl_handle);
        /* Check for errors */
        if(res != CURLE_OK)
        {
            fprintf(stderr, "http_delete_pic_from_list() failed: %s\n", curl_easy_strerror(res));
            curl_easy_cleanup(curl_handle);
            return -1;
        }
        else
        {
            long code;
            /* ask for the content-type */
            res = curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &code);
            if(CURLE_OK == res)
            {
                printf("We received staus-code: %ld\n", code);
                curl_easy_cleanup(curl_handle);
                return code;
            }
            else
            {
                printf("curl_easy_getinfo failed\n");
            }
        }
    }
    /* cleanup curl stuff */
    curl_easy_cleanup(curl_handle);
    return 0;
}
