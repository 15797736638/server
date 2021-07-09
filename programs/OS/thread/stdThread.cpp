#include <stdio.h>
#include <iostream>
#include <thread>


void threadproc1(){
    printf("I am a new Thread!\n");
    std::cout<<pthread_self()<<std::endl;
    printf("%d\n",pthread_self());
}

void threadproc2(int a,int b){
    printf("I am a new Thread2!\n");
}
int main()
{
    //创建线程1
    std::thread t1(threadproc1);
    std::thread t2(threadproc2,1,2);

    while(true){}
    return 0;
}