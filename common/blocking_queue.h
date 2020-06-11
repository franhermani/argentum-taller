#ifndef TP2_BLOCKINGQUEUE_H
#define TP2_BLOCKINGQUEUE_H
#include <condition_variable>
#include <mutex>
#include <queue>



class ClosedQueueException : public std::exception {
public:
    const char* what() {
        return "Queue is closed";
    }
};
template <class T> class BlockingQueue {
private:
    std::mutex m;
    std::queue<T> queue;
    std::condition_variable cv;
public:
    bool isClosed;
    BlockingQueue();
    void push(T t);
    T pop();
    void close();
    ~BlockingQueue();
};
template class BlockingQueue<std::string>;


#endif //TP2_BLOCKINGQUEUE_H
