#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

#include <iostream>

#include "node.h"

using namespace std;

template<class T> class Vertex;

template<class T>
class Edge {
private:
    Node<Vertex<T>>* destination;
    float weight;

public:
    Edge();
    Edge(Node<Vertex<T>>*, float);
    Edge(Node<Vertex<T>>*);
    Edge(Edge&);

    void setDestiny(Node<Vertex<T>>*);
    void setWeight(float);

    Node<Vertex<T>>* getDestiny();
    float getWeight();

    template<class X> friend bool operator == (Edge<T>&, Edge<T>&);
    template<class X> friend bool operator != (Edge<T>&, Edge<T>&);

    template<class Y> friend ostream& operator << (ostream&, Edge<Y>&);
    template<class Y> friend istream& operator >> (istream&, Edge<Y>&);

};

template<class T>
Edge<T>::Edge()
{
    this->destination = nullptr;
    weight = 1.0;
}


template<class T>
Edge<T>::Edge(Node<Vertex<T>>* p, float w)
{
    this->destination = p;
    weight = w;
}

template<class T>
Edge<T>::Edge(Node<Vertex<T>>* p) : Edge()
{
    this->destination = p;
}

template<class T>
Edge<T>::Edge(Edge& e)
{
    this->destination = e.getDestiny();
    this->weight = e.getWeight();
}

template<class T>
void Edge<T>::setDestiny(Node<Vertex<T>>* p)
{
    this->destination = p;
}

template<class T>
void Edge<T>::setWeight(float w)
{
    weight = w;

}

template<class T>
Node<Vertex<T>>* Edge<T>::getDestiny()
{
    return this->destination;
}

template<class T>
float Edge<T>::getWeight()
{
    return weight;
}

template<class X>
bool operator == (Edge<X>& a, Edge<X>& b){
    if(a.getDestiny() == b.getDestiny() and a.getWeight() == b.getWeight()){
        return true;
    }
    else return false;
}

template<class X>
bool operator != (Edge<X>& a, Edge<X>& b){
    if(a == b){
        return false;
    }
    else return true;
}

template<class Y> ostream& operator << (ostream& os, Edge<Y>& e) {
    os << "->";
    os << e.getDestiny()->getData().getTag();
    //os << ",";

       return os;
}

template<class Y> istream& operator >> (istream& is, Edge<Y>& e) {

    return is;
}

#endif // EDGE_H_INCLUDED
