#include <iostream>
#include <future>
#include <shared_mutex>
#include <thread>
#include <stdio.h>


class ReadWriteLock
{
    std::shared_mutex read_mutex;
    std::shared_mutex global_mutex;
    int count = 0;

public:

    void BeginRead()
    {
        read_mutex.lock();
        count++;
        if (count == 1) 
            global_mutex.lock();
        read_mutex.unlock();
    }

    void EndRead()
    {
        read_mutex.lock();
        count--;
        if (count == 0) 
            global_mutex.unlock();
        read_mutex.unlock();
    }

    void BeginWrite()
    {
        global_mutex.lock();
    }

    void EndWrite()
    {
        global_mutex.unlock();
    }
};

int main()
{
    ReadWriteLock rwLocker;
    int count = 10;
    int sahred_var = 0;

    auto future1 = std::async(std::launch::async, [&] {
        for (int i = 0; i < count; ++i) {
            rwLocker.BeginWrite();
            printf("-------begin write\n");
            printf("Increment Value:%i->%i, time: %i\n", sahred_var++, sahred_var, clock());
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            printf("--------end write\n");
            rwLocker.EndWrite();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    });

    auto future0 = std::async(std::launch::async, [&] {
        for (int i = 0; i < count; ++i) {
            rwLocker.BeginWrite();
            printf("-------begin write\n");
            printf("Decrement Value:%i->%i, time:%i\n", sahred_var--, sahred_var, clock());
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            printf("--------end write\n");
            rwLocker.EndWrite();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    });

    auto future2 = std::async(std::launch::async, [&] {
        for (int i = 0; i < count; ++i) {
           rwLocker.BeginRead();
           printf("1 Read Value:%i, time:%i\n", sahred_var, clock());
           rwLocker.EndRead();
           std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });

    auto future3 = std::async(std::launch::async, [&] {
        for (int i = 0; i < count; ++i) {
            rwLocker.BeginRead();
            printf("2 Read Value:%i, time:%i\n", sahred_var, clock());
            rwLocker.EndRead();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });

    auto future4 = std::async(std::launch::async, [&] {
        for (int i = 0; i < count; ++i) {
            rwLocker.BeginRead();
            printf("3 Read Value:%i, time:%i\n", sahred_var, clock());
            rwLocker.EndRead();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });

    auto future5 = std::async(std::launch::async, [&] {
        for (int i = 0; i < count; ++i) {
            rwLocker.BeginRead();
            printf("4 Read Value:%i, time:%i\n", sahred_var, clock());
            rwLocker.EndRead();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });
    

    return 0;
}
