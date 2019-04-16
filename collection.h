#ifndef COLLECTION_H_INCLUDED
#define COLLECTION_H_INCLUDED

#include <exception>
#include <iostream>
#include <string>

#include "node.h"

using namespace std;

class CollectionException : public exception {
protected:
    string msg;

public:
    explicit CollectionException(const char* message) : msg(message) {}

    explicit CollectionException(const string& message) : msg(message) {}

    virtual ~CollectionException() throw () {}

};

template<class T>
class Collection {
private:
    Node<T>* header;
    int counter;


public:
    Collection();
    Collection(Collection<T>&);
    ~Collection();

    int getCounter();

    bool isAValidPos(Node<T>*);
    bool isEmpty();

    void insertData(Node<T>*, T&);
    void deleteData(Node<T>*);

    Node<T>* firstPos();
    Node<T>* lastPos();
    Node<T>* previosPos(Node<T>*);
    Node<T>* nextPos(Node<T>*);
    Node<T>* findData(T&);

    T& retrieveData(Node<T>*);

    void print();

    //void quickSort(Node<T>*, Node<T>*);

    void quickSortByCost(Node<T>*, Node<T>*);
    void quickSortByWeight(Node<T>*, Node<T>* );

    void exchange(Node<T>*,Node<T>*);

    void deleteAll();

    //Metodos de pila

    void push(T&);
    T pop();
    T& top();

//Metodos de cola
    void enqueue(T&);
    T dequeue();

    T getFront();

    T operator[](int);
};


//PRIVATE

template<class T>
bool Collection<T>::isAValidPos(Node<T>* p) {
    Node<T>* aux = firstPos();

    while(aux != header) {
        if(aux == p) {
            return true;
        }
        aux = aux->getNext();
    }
    return false;
}


//PUBLIC

template<class T>
Collection<T>::Collection() {
    header = new Node<T>();

    if(header == nullptr) {
        throw CollectionException("La lista no pudo ser inicializada!");
    }

    header->setNext(header);
    header->setPrevious(header);

    counter = 0;
}

template<class T>
Collection<T>::Collection(Collection<T>& c) : Collection()
{
    Node<T>* aux = c.firstPos();

    if(!c.isEmpty()) {

        while(aux != c.lastPos()->getNext()) {
            this->enqueue(aux->getData());

            aux = aux->getNext();
        }
    }
}

template<class T>
Collection<T>::~Collection() {
    deleteAll();
}

template<class T>
int Collection<T>::getCounter() {
    return counter;
}

template<class T>
bool Collection<T>::isEmpty() {
    return header->getNext() == header;
}

template<class T>
void Collection<T>::insertData(Node<T>* p, T& e) {
    if(p != nullptr and !isAValidPos(p)) {
        throw CollectionException("Posicion invalida al insertar!");
    }

    Node<T>* aux = new Node<T>(e);
    if(aux == nullptr) {
        throw CollectionException("Memoria Insuficiente al insertar!");
    }

    if(p == nullptr) {
        p = header;
    }

    aux->setPrevious(p);
    aux->setNext(p->getNext());
    p->getNext()->setPrevious(aux);
    p->setNext(aux);

    counter++;
}


template<class T>
void Collection<T>::deleteData(Node<T>* p) {
    if(isEmpty()) {
        return;
    }

    if(!isAValidPos(p)) {
        throw CollectionException("Posicion invalida al eliminar!");
    }

    p->getPrev()->setNext(p->getNext());
    p->getNext()->setPrevious(p->getPrev());

    delete p;
    counter--;
}

template<class T>
Node<T>* Collection<T>::firstPos() {
    if(isEmpty()) {
        return nullptr;
    }

    return header->getNext();
}

template<class T>
Node<T>* Collection<T>::lastPos() {
    if(isEmpty()) {
        return nullptr;
    }

    return header->getPrev();
}

template<class T>
Node<T>* Collection<T>::previosPos(Node<T>* p) {
    if(!isAValidPos(p)) {
        throw CollectionException("Posicion invalida al recuperar anterior!");
    }

    if(p->getPrev() == header) {
        return header->getPrev();
    } else {
        return p->getPrev();
    }
}

template<class T>
Node<T>* Collection<T>::nextPos(Node<T>* p) {
    if(!isAValidPos(p)) {
        throw CollectionException("Posicion invalida al recuperar siguiente");
    }

    if(p->getNext() == header) {
        return header->getNext();
    } else {
        return p->getNext();
    }
}

template<class T>
Node<T>* Collection<T>::findData(T& e) {
    Node<T>* aux = header->getNext();

    while(aux != header) {
        if(aux->getData() == e) {
            return aux;
        }
        aux = aux->getNext();
    }
    return nullptr;
}

template<class T>
T& Collection<T>::retrieveData(Node<T>* p) {
    if(!isAValidPos(p)) {
        throw CollectionException("Posicion invalida al recuperar!");
    }

    return p->getData();
}

template<class T>
void Collection<T>::print() {
    Node<T>* aux = header->getNext();

    while(aux != header) {

        cout << ' ' << aux->getData();

        aux = aux->getNext();
    }
}

/*template<class T>
void Collection<T>::quickSort(Node<T>* leftExt, Node<T>* rightExt)
{
    if(isEmpty()) {
        return;
    }

    if(leftExt->getPrev() == rightExt or leftExt == rightExt) {
        return;
    }

    exchange(leftExt, rightExt);

    Node<T>* i = leftExt;
    Node<T>* j = rightExt;

    while(i != j) {
        while((i != j) and i->getData() <= rightExt->getData()) {
            i = i->getNext();
        }
        while((i != j) and j->getData() >= rightExt->getData()) {
            j = j->getPrev();
        }
        if(i != j) {
            exchange(i, j);
        }
    }
    if(i != rightExt) {
        exchange(i, rightExt);
    }

    quickSort(leftExt, i->getPrev());
    quickSort(i->getNext(), rightExt);

}*/

template<class T>
void Collection<T>::quickSortByCost(Node<T>* leftExt, Node<T>* rightExt)
{
    if(isEmpty()) {
        return;
    }

    if(leftExt->getPrev() == rightExt or leftExt == rightExt) {
        return;
    }

    exchange(leftExt, rightExt);

    Node<T>* i = leftExt;
    Node<T>* j = rightExt;

    while(i != j) {
        while((i != j) and i->getData()->getCost() <= rightExt->getData()->getCost()) {
            i = i->getNext();
        }
        while((i != j) and j->getData()->getCost() >= rightExt->getData()->getCost()) {
            j = j->getPrev();
        }
        if(i != j) {
            exchange(i, j);
        }
    }
    if(i != rightExt) {
        exchange(i, rightExt);
    }

    quickSortByCost(leftExt, i->getPrev());
    quickSortByCost(i->getNext(), rightExt);

}

template<class T>
void Collection<T>::quickSortByWeight(Node<T>* leftExt, Node<T>* rightExt)
{
    if(isEmpty()) {
        return;
    }

    if(leftExt->getPrev() == rightExt or leftExt == rightExt) {
        return;
    }

    exchange(leftExt, rightExt);

    Node<T>* i = leftExt;
    Node<T>* j = rightExt;

    while(i != j) {
        while((i != j) and i->getData().getWeight() <= rightExt->getData().getWeight()) {
            i = i->getNext();
        }
        while((i != j) and j->getData().getWeight() >= rightExt->getData().getWeight()) {
            j = j->getPrev();
        }
        if(i != j) {
            exchange(i, j);
        }
    }
    if(i != rightExt) {
        exchange(i, rightExt);
    }

    quickSortByWeight(leftExt, i->getPrev());
    quickSortByWeight(i->getNext(), rightExt);

}


template<class T>
void Collection<T>::exchange(Node<T>* a, Node<T>* b)
{
    T aux = a->getData();
    a->setData(b->getData());
    b->setData(aux);
}


template<class T>
void Collection<T>::deleteAll() {
    if(isEmpty()) {
        return;
    }

    Node<T>* aux;
    while(header->getNext() != header) {
        aux = header->getNext();
        header->setNext(aux->getNext());

        delete aux;
    }
    header->setPrevious(header);
    counter = 0;
}


template<class T>
T Collection<T>::operator[](int index) {
    Node<T>* aux = firstPos();

    if(index < counter) {
        for(int i = 0; i < index; i++) {
            aux = aux->getNext();

        }
        return aux->getData();
    }
    else {
        throw CollectionException("Posicion invalida al recuperar con operador []");
    }
}

//Metodos de Pila

template<class T>
void Collection<T>::push(T& e)
{
    insertData(nullptr, e);
}

template<class T>
T Collection<T>::pop()
{
    T aux = top();
    deleteData(firstPos());

    return aux;
}

template<class T>
T& Collection<T>::top()
{
    if(isEmpty()) {
        throw CollectionException("Insuficiencia de datos al intentar obtener el tope!");
    }
    return firstPos()->getData();
}


//Queue's methods

template<class T>
void Collection<T>::enqueue(T& e)
{
    insertData(lastPos(), e);
}

template<class T>
T Collection<T>::dequeue()
{
    T aux = firstPos()->getData();
    deleteData(firstPos());
    return aux;
}

template<class T>
T Collection<T>::getFront()
{
    if(isEmpty()) {
        throw CollectionException("Insuficiencia de datos al intentar obtener el frente!");
    }

    return firstPos()->getData();
}


#endif // COLLECTION_H_INCLUDED
