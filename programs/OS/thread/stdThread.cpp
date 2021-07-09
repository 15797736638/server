#include <stdio.h>
#include <thread>


void threadproc1(){
    while(true){
        printf("I am a new Thread!\n");
    }
}

void threadproc2(int a,int b){
    while(true){
        printf("I am a new Thread2!\n");
    }
}
int main()
{
    //创建线程1
    std::thread t1(threadproc1);
    std::thread t2(threadproc2,1,2);

    while(true){}
    return 0;
}