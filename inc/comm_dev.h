#ifndef _COMM_DEV_H_ 
#define _COMM_DEV_H_


#define    MAX_PIC_NUM    100
#define    FILENAME_LEN   64
#define    URL_LEN        96
#define    TOKEN_LEN      16
typedef struct
{
    char filename[MAX_PIC_NUM][FILENAME_LEN];
    char url[MAX_PIC_NUM][URL_LEN];
    char token[MAX_PIC_NUM][TOKEN_LEN]; 
}fileListDef;
void* comm_dev_thread(void *arg);

#endif
