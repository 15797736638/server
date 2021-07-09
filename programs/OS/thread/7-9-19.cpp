/*
    除c++ 11的线程库提供的std::thread 类对线程函数签名没有特殊要求外，无论是Linux还是Windows的线程函数签名
都必须是指定的格式，即参数和返回值必须是规定的格式
    如果使用C++面向对象的方式对线程函数进行封装，线程函数就不能是类的实例方法了，必须是类的静态方法
    因为类的实例方法会将this指针传入给函数，这样就不符合线程函数的签名要求了。
    如果使用C++ 11的std::thread类，就没有这个限制了，但必须显示地将this指针作为构造函数参数传递给std::thread
*/

//在实际开发中往往会在创建线程时将当前对象的地址（this指针）传递给线程线程函数
//然后在线程函数中将该指针转换为原来的类实例，再通过这个类实例就可以访问类的所有方法了。
#include <thread>
#include <memory>
#include <stdio.h>
#include <iostream>

class Thread{
public:
    Thread(){}
    ~Thread(){}
    void Start(){
        m_stopped = false;
        //threadFunc是类的非静态方法
        //所以作为线程函数，第一个参数必须传递类实例的地址，即this指针
        m_spThread.reset(new std::thread(&Thread::threadFunc,this,8888,9999));
    }
    void stop(){
        m_stopped = true;
        if(m_spThread){
            if(m_spThread->joinable())
                m_spThread->join();
        }
    }
    
private:
    void threadFunc(int arg1,int arg2){
        while(!m_stopped){
            printf("Thread function use instance method.\n");
        }
    }
    
private:
    std::shared_ptr<std::thread> m_spThread;
    bool m_stopped;
};

int main()
{
    Thread mythread;
    mythread.Start();

    while(true){

    }
    return 0;
}