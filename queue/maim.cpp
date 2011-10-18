#include <iostream>
#include "queue.cpp"

int main()
{
    Queue<int> m_queue;
    /*
    m_queue.enqueue(1);
    m_queue.enqueue(2);
    m_queue.enqueue(3);
    m_queue.enqueue(4);
    m_queue.enqueue(5);
    m_queue.enqueue(6);
    m_queue.enqueue(7);
    std::cout << m_queue.dequeue() << std::endl;
    std::cout << m_queue.dequeue() << std::endl;
    */

    m_queue.enqueue_list(1);
    m_queue.enqueue_list(2);
    m_queue.enqueue_list(3);
    m_queue.enqueue_list(4);
    m_queue.enqueue_list(5);
    m_queue.enqueue_list(6);
//    m_queue.cout_list();
    std::cout << m_queue.dequeue_list() << std::endl;
    std::cout << m_queue.dequeue_list() << std::endl;
    std::cout << m_queue.dequeue_list() << std::endl;
    std::cout << m_queue.dequeue_list() << std::endl;
    std::cout << m_queue.dequeue_list() << std::endl;
    std::cout << m_queue.dequeue_list() << std::endl;
    std::cout << m_queue.dequeue_list() << std::endl;
    return 0;
}
