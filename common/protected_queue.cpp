#include "protected_queue.h"
#include <utility>

template <class T>
ProtectedQueue<T>::ProtectedQueue() : isClosed(false) {}

template <class T>
ProtectedQueue<T>::~ProtectedQueue() {}

template <class T>
void ProtectedQueue<T>::push(T t) {
    std::unique_lock<std::mutex> lk(m);
    queue.push(std::move(t));
}

template <class T>
T ProtectedQueue<T>::pop() {
    std::unique_lock<std::mutex> lk(m);
    if (isClosed) throw ClosedQueueException();
    T t = queue.front();
    queue.pop();
    return std::move(t);
}

template <class T>
void ProtectedQueue<T>::close() {
    std::unique_lock<std::mutex> lk(m);
    isClosed = true;
}

template <class T>
bool ProtectedQueue<T>::isEmpty() {
    std::unique_lock<std::mutex> lk(m);
    return queue.size() == 0;
}
