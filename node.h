#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

template <class T>
class Node{
private:
    Node<T>* next;
    Node<T>* previous;

    float cost;

    T data;
public:
    Node();
    Node(T&);

    void setNext(Node<T>*);
    void setPrevious(Node<T>*);
    void setData(T&);

    void setCost(float);

    float getCost();

    Node<T>* getNext();
    Node<T>* getPrev();

    T& getData();

};



//Public

template<class T>
Node<T>::Node()
{
    next = nullptr;
    previous = nullptr;
    cost = 1;
}

template<class T>
Node<T>::Node(T& e) : Node()
{
    data = e;
}

template<class T>
void Node<T>::setNext(Node<T>* p)
{
    next = p;
}

template<class T>
void Node<T>::setPrevious(Node<T>* p)
{
    previous = p;
}

template<class T>
void Node<T>::setData(T& e)
{
    data = e;
}

template<class T>
void Node<T>::setCost(float c){
    cost = c;
}

template<class T>
float Node<T>::getCost(){
    return cost;
}

template<class T>
Node<T>* Node<T>::getNext()
{
    return next;
}


template<class T>
Node<T>* Node<T>::getPrev()
{
    return previous;
}


template<class T>
T& Node<T>::getData()
{
    return data;
}


#endif // NODE_H_INCLUDED
