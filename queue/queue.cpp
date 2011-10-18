#include "queue.h"
#include <cstdio>
#include <iostream>

template <class Type>
Queue<Type>::Queue()
{
    m_size = 5;
    m_head = m_tail = 0;
    m_queue = new Type[m_size]();
    m_list = new QueueItem<Type>();
    m_list->next = NULL;
    m_list_tail = m_list;
}

template <class Type>
Queue<Type>::Queue(int isize)
{
    m_size = isize;
    m_head = m_tail = 0;
    m_queue = new Type[m_size]();
    m_list = new QueueItem<Type>();
    m_list->next = NULL;
    m_list_tail = m_list;
}

template <class Type>
bool Queue<Type>::isEmpty()
{
    return m_head%m_size == m_tail%m_size;
}

template <class Type>
bool Queue<Type>::isFull()
{
    return (m_tail+1)%m_size == m_head%m_size;
}

template <class Type>
void Queue<Type>::enqueue(const Type& tvalue)
{
    if(!isFull())
    {
        m_queue[m_tail] = tvalue;
        m_tail = (m_tail+1)%m_size;
#ifdef NDEBUG
        std::cout << m_tail << m_queue[m_tail-1] << tvalue << std::endl;
#endif
    }
}

template <class Type>
Type Queue<Type>::dequeue()
{
    Type mm_value;
    if(!isEmpty())
    {
        mm_value = m_queue[m_head];
        m_head = (m_head+1)%m_size;
#ifdef NDEBUG
        std::cout << m_head << mm_value << std::endl;
#endif
    }
    return mm_value;
}

template <class Type>
int Queue<Type>::length()
{
    return m_size;
}

template <class Type>
void Queue<Type>::enqueue_list(const Type& tvalue)
{
    QueueItem<Type> *item= new QueueItem<Type>();
    item->m_value = tvalue;
    item->next = NULL;
    m_list_tail->next = item;
    m_list_tail = m_list_tail->next;
#ifdef NDEBUG
    std::cout << m_list_tail->m_value << std::endl;
#endif
}

template <class Type>
Type Queue<Type>::dequeue_list()
{
    QueueItem<Type> *pointer = m_list->next;
#ifdef NDEBUG
    std::cout << pointer->m_value << std::endl;
#endif
    if(NULL != pointer)
    {
        m_list->next = pointer->next;
        if(pointer == m_list_tail)
            m_list_tail = m_list;
        return pointer->m_value;
    }
}

template <class Type>
void Queue<Type>::cout_list()
{
    QueueItem<Type> *pointer = m_list->next;
    while(pointer == m_list_tail)
    {
        std::cout << pointer->m_value << std::endl;
        pointer = pointer->next;
    }
}
