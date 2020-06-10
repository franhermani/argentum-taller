
#include "blocking_queue.h"


template <class T>
BlockingQueue<T>::BlockingQueue() : isClosed(false)   {}

template <class T>
void BlockingQueue<T>::push(T t){
    std::unique_lock<std::mutex> lk(m);
    queue.push(t);
    cv.notify_all();
}

template <class T>
T BlockingQueue<T>::pop() {
    std::unique_lock<std::mutex> lk(m);
    while (queue.empty()) {
        if (isClosed) {
            throw ClosedQueueException();
        }
        cv.wait(lk);
    }

    T t = queue.front();
    queue.pop();
    return t;
}

template <class T>
void BlockingQueue<T>::close() {
    std::unique_lock<std::mutex> lk(m);
    isClosed = true;
    cv.notify_all();
}

template <class T>
BlockingQueue<T>::~BlockingQueue() {}


