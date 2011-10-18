template <class Type>
class StackItem
{
public:
    Type m_data;
    Type m_min;
    Type m_max;
    StackItem *m_next;
};

template <class Type>
class Stack
{
public:
    Stack();
    void push(const Type&);
    Type pop();
    Type minimum();
    Type maximum();
private:
    StackItem<Type> *m_list;
};


