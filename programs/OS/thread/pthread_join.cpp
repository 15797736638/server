//pthread_join函数：等待线程退出并接收它的返回值
//pthread_join函数在等待目标线程退出期间会挂起当前线程，被挂起的线程处于等待状态，不会消耗任何CPU时间片。
//直到目标线程退出后，调用pthread_join的线程才会被唤醒，继续执行接下来的逻辑。

#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define TIME_FILENAME "time.txt"
void* fileThreadFunc(void *arg){
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    char timeStr[32] = {0};
    snprintf(timeStr,32,"%04d/%02d/%02d %02d:%02d:%02d",
        t->tm_year+1900,
        t->tm_mon+1,
        t->tm_mday,
        t->tm_hour,
        t->tm_min,
        t->tm_sec);
    FILE* fp = fopen(TIME_FILENAME,"w");
    
    if(fp == NULL){
        printf("Failed to create time.txt.\n");
        return NULL;
    }
    
    size_t sizeToWrite = strlen(timeStr)+1;
    size_t ret = fwrite(timeStr,1,sizeToWrite,fp);
    if(ret != sizeToWrite){
        printf("Write file error.\n");
    }
    fclose(fp);
    return NULL;
}

int main()
{
    pthread_t fileThreadID;
    int ret = pthread_create(&fileThreadID,NULL,fileThreadFunc,NULL);
    if(ret != 0){
        printf("Fail to create fileThread.\n");
        return -1;
    }
    int* retval;
    pthread_join(fileThreadID,(void**)&retval);
    //使用r选项，要求文件必须存在
    FILE* fp = fopen(TIME_FILENAME,"r");
    if(fp == NULL){
        printf("open file error.\n");
        return -2;
    }
    char buf[32] = {0};
    int sizeRead = fread(buf,1,32,fp);
    if(sizeRead == 0){
        printf("read file error.\n");
        fclose(fp);
        return -3;
    }
    printf("Current Time is: %s.\n",buf);
    fclose(fp);
    return 0;
}