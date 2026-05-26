#pragma once
#include<iostream>
#include<mutex>
#include<memory>
template<typename T>
class Singleton
{
public:
    static T* instance()
    {
        static T* ins = nullptr;
        static std::once_flag flag;
        std::call_once(flag, []() {
            ins = new T(); // 可传入父对象或在构造中设置 parent
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