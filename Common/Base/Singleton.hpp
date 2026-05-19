#pragma once
#include<iostream>
#include<mutex>
template<typename T>
class Singleton
{
public:
    static std::shared_ptr<T>instance()
    {
        static std::shared_ptr<T>ins;
        //线程安全
        static std::once_flag flag;               
        std::call_once(flag,[&](){
            ins.reset(new T());
        });
        return ins;
    }
    
    Singleton(){}
    virtual ~Singleton(){
    std::cout<<"~Singleton()"<<typeid(T).name()<<std::endl;
    }
protected:
   
private:
    Singleton(const Singleton&)=delete;
    Singleton& operator=(const Singleton&)=delete;
};