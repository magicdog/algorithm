template <class Type>
class QueueItem
{
public:
    Type m_value;
    QueueItem *next;
};

template <class Type>
class Queue
{
public:
    Queue();
    Queue(int);
    void enqueue(const Type&);
    void enqueue_list(const Type&);
    Type dequeue();
    Type dequeue_list();
    int length();
    void cout_list();
private:
    bool isEmpty();
    bool isFull();
    Type *m_queue;
    int m_size;
    int m_head;
    int m_tail;
    QueueItem<Type>* m_list;
    QueueItem<Type>* m_list_tail;
};
