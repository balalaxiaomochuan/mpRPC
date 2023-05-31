#pragma once
#include <queue>
#include <thread>
#include <mutex> // pthread_mutex_t
#include <condition_variable> // pthread_condition_t

// 异步写日志的日志队列
template<typename T>
class LockQueue
{
public:
    // 多个worker线程都写写日志queue
    void Push(const T& data){
        std::lock_guard<std::mutex> lock(m_mutex); // 构造函数中上锁，析构函数解锁
        m_queue.push(data);
        m_condvariable.notify_one(); // 不需要notify_all，因为只有一个线程进行缓冲队列的读写（push pop）
    }

    // 一个线程读日志queue
    T Pop(){
        std::unique_lock<std::mutex> lock(m_mutex);
        while(m_queue.empty()){
            // 日志队列为空，线程进入wait状态(阻塞)
            m_condvariable.wait(lock); // 队列为空，那么需要释放锁mutex，让Push方便操作上锁，当不为空时，Pop上锁，跳出while
        }
        T data = m_queue.front();
        m_queue.pop();
        return data;
    }
private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_condvariable;
};