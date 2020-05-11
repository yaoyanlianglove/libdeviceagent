#ifndef _HTTP_H_ 
#define _HTTP_H_


#define    MAX_LIST_SIZE      40960
#define    MAX_STAT_SIZE      20

int http_init(void);

long http_get_heart(char *stat, const char *url);
long http_get_list(char *list, const char *url);
double http_down_file(const char *fileName,const char *url);
long http_delete_pic_from_list(const char *url);

void http_clean(void);

#endif