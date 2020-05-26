#include "comm_dev.h"
#include "http.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "sg_sdk.h"
#include "cJSON.h"

extern int userId;
extern pthread_mutex_t userId_mutex_lock;
extern st_SG_DEV dev;

char *glist;
int timeoutCounter = 0;
int flagSnapPicCallBack = 0;
char resUpJpg[64];
static void set_dev_status(bool status)
{
    if(status)
    {
        pthread_mutex_lock(&userId_mutex_lock);
        userId = 1;
        dev.bStatus = true;
        pthread_mutex_unlock(&userId_mutex_lock);
    }
    else
    {
        pthread_mutex_lock(&userId_mutex_lock);
        userId = 0;
        dev.bStatus = false;
        pthread_mutex_unlock(&userId_mutex_lock);
    }
}

static int split_list(fileListDef *fileList, cJSON *json, int listLen)
{
    cJSON *arrayItem, *itemFilename, *itemUrl, *itemToken; 
    
    int i;
    int res = 0;
    for(i = 0; i < listLen; i++)  
    {    
        arrayItem = cJSON_GetArrayItem(json, i); 
        if(arrayItem == NULL)
        {
            printf("arrayItem  is null\n");
            break;
        }
        itemFilename = cJSON_GetObjectItem(arrayItem, "filename");
        if(itemFilename == NULL)
        {
            printf("itemFilename  is null\n");
            break;
        }
        else  
        {
            memset(fileList->filename[res], 0, FILENAME_LEN);
            memcpy(fileList->filename[res], itemFilename->valuestring, strlen(itemFilename->valuestring));
        }  
             
        itemUrl = cJSON_GetObjectItem(arrayItem, "url");
        if(itemUrl == NULL)
        {
            printf("itemUrl  is null\n");
            break;
        }
        else  
        {
            memset(fileList->url[res], 0, URL_LEN);  
            memcpy(fileList->url[res], itemUrl->valuestring, strlen(itemUrl->valuestring));
        }   
        itemToken = cJSON_GetObjectItem(arrayItem, "token");
        if(itemToken == NULL)
        {
            printf("itemToken  is null\n");
            break;
        }
        else 
        {
            memset(fileList->token[res], 0, TOKEN_LEN);  
            memcpy(fileList->token[res], itemToken->valuestring, strlen(itemToken->valuestring)); 
        } 
        res++;
    }
    return res;
}

static int upload_jpg(char *filedir, int size)
{
    int dataType = 0;
    if(flagSnapPicCallBack == 0)
        return -2;
    snapPic(userId, dataType, filedir, size, resUpJpg);
    printf("%s\n", resUpJpg);
    if(!strstr(resUpJpg, "o"))
        return -1;
    return 0;
}
static int handle_jpg(char *list)
{
    if(list == NULL)
        return -1;
    cJSON *json=cJSON_Parse(list);
    if(json == NULL)
        return -1;
    int listLen = cJSON_GetArraySize(json);
    printf("listLen  is  %d \n", listLen);
    if(listLen == 0)
    {
        cJSON_Delete(json);
        return -1;
    }
    fileListDef fileList;
    int count = 0;
    int i = 0;
    char filepath[100];
    char filedir[200];
    memset(filepath, 0, 100);
    memset(filedir, 0, 100);
    count = split_list(&fileList, json, listLen);
    if(count <= 0)
    {
        printf("split_list failed\n");
        cJSON_Delete(json);
        return -1;
    }
    strcpy(filepath, "/tmp/");
    for(i = 0; i < count; i++)
    {
        sprintf(filedir, "%s%s", filepath, fileList.filename[i]);
        double sizeJpg;
        sizeJpg = http_down_file(filedir, fileList.url[i]);
        printf("sizeJpg is %d\n", (int)sizeJpg);
        if(sizeJpg > 0)
        {
            int resUpload;
            resUpload = upload_jpg(filedir, (int)sizeJpg);
            if( resUpload == 0)
            {
                char url[100];
                memset(url, 0 , 100);
                sprintf(url, "http://192.168.1.101/list?token=%s", fileList.token[i]);
                long code = 0;
                int errNum = 0;
                while(code != 200 && errNum < 3)
                {
                    //需要程序对失败数据进行处理，发送三次
                    errNum++;
                    code = http_delete_pic_from_list(url);
                    printf("http_delete_pic_from_list code is %ld\n", code);
                }
            }
            else if(resUpload == -1)
            {
                printf("upload_jpg failed\n");
            } 
            else if(resUpload == -2)
            {
                printf("SnapPicCallBack unregister\n");
            }
        }
        else
        {
            printf("http_down_file failed\n");
        }
    }
    cJSON_Delete(json);
    return 0;
}
long handle_heart(char *data)
{
    if(strstr(data, "200"))
        return 200;
    else if(strstr(data, "201"))
        return 201;
    else
        return 0;
}
void* comm_dev_thread(void *arg)
{
    long statusCode = 0;
    char status[MAX_STAT_SIZE];
    memset(status, 0, MAX_STAT_SIZE);
    while(1)
    {
        printf("%s\n", (char*)arg);
        statusCode = http_get_heart(status, "http://192.168.1.101/heartbeat");
        if(statusCode == 200)
        {
            printf("status is %s\n", status);
            statusCode = handle_heart(status);
        }
        if(statusCode == 200 || statusCode == 201)
        {
            timeoutCounter = 0;
            set_dev_status(true);
            if(statusCode == 201)
            {
                glist = (char *) malloc (MAX_LIST_SIZE);
                if(glist == NULL)
                {
                    printf("LIST malloc failed\n");
                    continue;
                }
                memset(glist, 0, MAX_LIST_SIZE);
                if(http_get_list(glist, "http://192.168.1.101/list") == 200)
                {
                    printf("--------------\n%s\n--------------\n%ld\n", glist, strlen(glist));
                    handle_jpg(glist);
                }
                if(glist)
                    free(glist);
            }
        }
        else
        {
            if(timeoutCounter < 2)
                timeoutCounter++;
            else
            {
                set_dev_status(false);
            }
        }
        sleep(5);
    }
}
