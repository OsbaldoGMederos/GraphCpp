#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED

#include <iostream>

#include "collection.h"
#include "edge.h"


template<class T>
class Vertex : public Collection<Edge<T>> {
private:
    int tag;

public:
    Vertex();
    Vertex(T&);
    Vertex(Vertex&);

    void setTag(T&);
    T getTag();

    void insertEdge(Edge<T>&);
    void deleteEdge(Node<Edge<T>>*);

    Node<Edge<T>>* findEdge(T&);
    T& retrieveTag(Node<Edge<T>>*);


    template<class X> friend bool operator == (Vertex<X>&, Vertex<X>&);
    template<class X> friend bool operator != (Vertex<X>&, Vertex<X>&);

    template<class Y> friend std::ostream& operator << (std::ostream&, Vertex<Y>&);
    //template<class Y> friend std::istream& operator >> (std::istream&, Vertex<Y>&);

};

template<class T>
Vertex<T>::Vertex() : Collection<Edge<T>>() {}

template<class T>
Vertex<T>::Vertex(T& e) : Collection<Edge<T>>()
{
    this->tag = e;
}

template<class T>                                   //Copy constructor
Vertex<T>::Vertex(Vertex& v) : Collection<Edge<T>>()
{

    Vertex<T>* vPtr = &v;

    if(v.isEmpty()){
        return;
    }

    if(vPtr != nullptr) {

        this->tag = v.tag;

        Node<Edge<T>>* aux = v.firstPos();
        while(aux != v.lastPos()->getNext()) {

            this->enqueue(aux->getData());


            aux = aux->getNext();
        }
    }
    else{
    std::cout << "\nEl vertice no pudo ser copiado\n";
    }
}

template<class T>
void Vertex<T>::setTag(T& e) {
    tag = e;
}

template<class T>
T Vertex<T>::getTag() {
    return tag;
}


template<class X>
bool operator == (Vertex<X>& a, Vertex<X>& b) {
    if(a.getTag() == b.getTag()) {
        return true;
    }
    else return false;
}

template<class X>
bool operator != (Vertex<X>& a, Vertex<X>& b) {
    if(a.getTag() == b.getTag()) {
        return false;
    }
    else return true;
}

template<class Y>
ostream& operator << (ostream& os, Vertex<Y>& v) {
    os << v.getTag();
    os << ", ";

    return os;
}

/*template<class Y>
std::istream& operator >> (std::istream& is, Vertex<Y>& v) {

    Y tmp;

    std::cout << "Dime el identificador del vertice: ";

    std::cin >> tmp;
    std::cin.ignore();
    v.setTag(tmp);

    return is;
}*/




#endif // VERTEX_H_INCLUDED
