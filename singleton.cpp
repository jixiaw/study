#include <stdio.h>
#include <iostream>
#include <mutex>
using namespace std;


class Singleton
{
private:
    static Singleton* instance;
    static std::mutex mutex_;
private:
    Singleton() {}
public:
    static Singleton* GetInstance() {
        if (!instance) {
            std::unique_lock<std::mutex> lock(mutex_);
            if (!instance)
                instance = new Singleton();
        }
        return instance;
    }

};
Singleton* Singleton::instance = NULL;
std::mutex Singleton::mutex_;

class Singleton2
{
private:
    static Singleton2* instance;
private:
    Singleton2() {}

public:
    static Singleton2* GetInstance() {
        return instance;
    }
};
Singleton2* Singleton2::instance = new Singleton2();

int main() {
    Singleton* a = Singleton::GetInstance();
    Singleton* b = Singleton::GetInstance();

    Singleton2* c = Singleton2::GetInstance();
    Singleton2* d = Singleton2::GetInstance();
    std::cout<<(*a==*b)<<std::endl;
    std::cout<<(*c==*d)<<std::endl;
    return 0;

}


