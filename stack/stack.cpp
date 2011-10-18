#include "stack.h"
#include <cstdlib>
#include <iostream>

template <class Type>
Stack<Type>::Stack()
{
    m_list = new StackItem<Type>();
    m_list->m_next = NULL;
}


template <class Type>
void Stack<Type>::push(const Type& tvalue)
{
    StackItem<Type>* mm_ptr = m_list->m_next;
    StackItem<Type>* mm_item = new StackItem<Type>();
    mm_item->m_data = tvalue;
    mm_item->m_min = tvalue;
    mm_item->m_max = tvalue;
    if(mm_ptr != NULL)
    {
        mm_item->m_max = mm_ptr->m_max;
        mm_item->m_min = mm_ptr->m_min;
        if(tvalue > mm_ptr->m_max)
            mm_item->m_max = tvalue;
        if(tvalue < mm_ptr->m_min)
            mm_item->m_min = tvalue;
    }
    mm_item->m_next = mm_ptr;
    m_list->m_next = mm_item;
}


template <class Type>
Type Stack<Type>::pop()
{
    Type mm_data;
    StackItem<Type> *mm_ptr = m_list->m_next;
    if(mm_ptr != NULL)
    {
        mm_data = mm_ptr->m_data;
        m_list = mm_ptr;
        delete mm_ptr;
    }
    return mm_data;
}

template<class Type>
Type Stack<Type>::minimum()
{
    if(m_list->m_next != NULL)
        return m_list->m_next->m_min;
    return NULL;
}

template<class Type>
Type Stack<Type>::maximum()
{
    if(m_list->m_next != NULL)
        return m_list->m_next->m_max;
    return NULL;
}

