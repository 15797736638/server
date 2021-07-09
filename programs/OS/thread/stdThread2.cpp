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
    //std::thread对象提供了一个detach方法，通过这个方法可以让线程对象与线程函数脱离关系，即使线程对象被销毁，也不影响线程函数的运行,方法如下。
    //然后实际开发并不推荐这样做，因为可能需要使用线程对象去控制和管理线程的运行和生命周期。所以，应该尽量保证线程对象在运行期间有效而不是
    //单纯地调用detach方法使线程对象和线程函数的运行分离
    t.detach();
}
int main()
{
    creatThread();
    return 0;
}