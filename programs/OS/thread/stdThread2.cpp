#include <stdio.h>
#include <thread>

void func(){
    while(true){
        printf("I am a new Thread!\n");
    }
}
void creatThread(){
    std::thread t(func);
    //看起来没什么问题，但实际上会崩溃，因为std::thread对象在线程函数运行期间必须是有效的
    //这里线程t销毁，而func还在继续执行
    //std::thread对象提供了一个detach方法，通过这个方法可以让线程对象与线程函数脱离关系，即使线程对象被销毁，也不影响线程函数的运行。
}
int main()
{
    creatThread();
    return 0;
}