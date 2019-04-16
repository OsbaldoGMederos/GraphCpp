#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "vertex.h"

class GraphException : public std::exception {
protected:
    std::string msg;

public:
    explicit GraphException(const char* message) : msg(message) {}

    explicit GraphException(const std::string& message) : msg(message) {}

    virtual ~GraphException() throw () {}

};

template<class T>
class Graph : public Collection<Vertex<T>> {
private:
    bool isDirected;
    bool isWeighted;

public:
    Graph();
    ~Graph();
    Graph(bool, bool);

    void setIsDirected(bool);
    void setIsWeighted(bool);

    bool getIsDirected();
    bool getIsWeighted();

    void insertVertex(Vertex<T>&);
    void insertEdge(Edge<T>&, Node<Vertex<T>>*);

    void depthParse(T);
    void widthParse(T);

    void depthRoute(T,T);
    void widthRoute(T,T);
    void firstInRoute(T,T);

};


template<class T>
Graph<T>::Graph() : Collection<Vertex<T>>()
{
    isDirected = false;
    isWeighted = false;
}

template<class T>
Graph<T>::Graph(bool directed, bool weighted) : Collection<Vertex<T>>()
{
    isDirected = directed;
    isWeighted = weighted;
}

template<class T>
Graph<T>::~Graph(){
    this->deleteAll();
}

template<class T>
void Graph<T>::setIsDirected(bool directed)
{
    isDirected = directed;
}

template<class T>
void Graph<T>::setIsWeighted(bool weighted)
{
    isWeighted = weighted;
}

template<class T>
bool Graph<T>::getIsDirected()
{
    return isDirected;
}

template<class T>
bool Graph<T>::getIsWeighted()
{
    return isWeighted;
}

template<class T>
void Graph<T>::insertVertex(Vertex<T>& v)
{
    this->insertData(this->lastPos(), v);
}

template<class T>
void Graph<T>::insertEdge(Edge<T>& e, Node<Vertex<T>>* p)
{
    if(e.getDestiny() == nullptr) {
        cout << "\nNo se puede insertar un arista sin destino!" << endl;
        return;
    }
    if(p->getData().findData(e) != nullptr) {
        return;
    }
    p->getData().enqueue(e);
    if(!isDirected) {
        Node<Vertex<T>>* aux = p;
        Edge<T> myEdge;
        myEdge.setDestiny(aux);
        e.getDestiny()->getData().enqueue(myEdge);
    }
}


template<class T>
void Graph<T>::depthParse(T e)
{
    Vertex<T> myV(e);
    Node<Vertex<T>>* origin = this->findData(myV);
    if(origin == nullptr) {
        throw GraphException("El vertice de origen no existe, al hacer recorrido en Profundidad!");
    }

    Collection<Node<Vertex<T>>*> vertexStack;
    Collection<Node<Vertex<T>>*> visitedList;
    Node<Vertex<T>>* currentPos;
    Node<Vertex<T>>* currentDest;

    vertexStack.push(origin);
    while(!vertexStack.isEmpty()) {
        currentPos = vertexStack.pop();
        if(visitedList.findData(currentPos) == nullptr) {
            std::cout << currentPos->getData().getTag() << " ";
            visitedList.enqueue(currentPos);

            Vertex<T> destList(currentPos->getData());
            while(!destList.isEmpty()) {
                currentDest = destList.dequeue().getDestiny();

                if(visitedList.findData(currentDest) == nullptr) {
                    vertexStack.push(currentDest);
                }
            }
        }
    }
}

template<class T>
void Graph<T>::widthParse(T e) {
    Vertex<T> myV(e);
    Node<Vertex<T>>* origin = this->findData(myV);
    if(origin == nullptr) {
        throw GraphException("El vertice de origen no existe, al hacer recorrido en Profundidad!");
    }

    Collection<Node<Vertex<T>>*> vertexQueue;
    Collection<Node<Vertex<T>>*> visitedList;
    Node<Vertex<T>>* currentPos;
    Node<Vertex<T>>* currentDest;

    vertexQueue.enqueue(origin);
    while(!vertexQueue.isEmpty()) {
        currentPos = vertexQueue.dequeue();
        if(visitedList.findData(currentPos) == nullptr) {
            std::cout << currentPos->getData().getTag()  << " ";
            visitedList.enqueue(currentPos);

            Vertex<T> destList(currentPos->getData());
            while(!destList.isEmpty()) {
                currentDest = destList.dequeue().getDestiny();

                if(visitedList.findData(currentDest) == nullptr) {
                    vertexQueue.enqueue(currentDest);
                }
            }
        }
    }
}

template<class T>
void Graph<T>::depthRoute(T origin, T dest) {
    Vertex<T> vertexOrigin(origin);
    Vertex<T> vertexDest(dest);
    Node<Vertex<T>>* originPtr = this->findData(vertexOrigin);
    Node<Vertex<T>>* destPtr = this->findData(vertexDest);
    if(originPtr == nullptr or destPtr == nullptr) {
        throw GraphException("El vertice de origen o Destino no existe, al hacer ruta en Profundidad!");
    }

    Collection<Node<Vertex<T>>*> vertexStack;
    Collection<Node<Vertex<T>>*> originStack;
    Collection<Node<Vertex<T>>*> destStack;
    Collection<Node<Vertex<T>>*> visitedList;
    Node<Vertex<T>>* current;
    Node<Vertex<T>>* currentDest;

    vertexStack.push(originPtr);
    while(!vertexStack.isEmpty()) {

        current = vertexStack.pop();

        if(visitedList.findData(current) == nullptr) {
            if(current->getData().getTag() == destPtr->getData().getTag()) {
                cout << endl << destPtr->getData().getTag();//Mostrar ruta
                Node<Vertex<T>>* aux = destPtr;
                while(!originStack.isEmpty()) {
                    if(destStack.pop() == aux) {
                        cout << "<-";
                        cout << originStack.top()->getData().getTag();
                        aux = originStack.pop();
                    } else {
                        originStack.pop();
                    }
                }
                return;
            }
            visitedList.enqueue(current);

            Vertex<T> destList(current->getData());
            while(!destList.isEmpty()) {
                currentDest = destList.dequeue().getDestiny();

                if(visitedList.findData(currentDest) == nullptr) {

                    vertexStack.push(currentDest);
                    originStack.push(current);
                    destStack.push(currentDest);
                }
            }
        }
    }
    cout << "\nNo hay ruta entre estos V\202rtices\n";
}

template<class T>
void Graph<T>::widthRoute(T origin, T dest) {
    Vertex<T> vertexOrigin(origin);
    Vertex<T> vertexDest(dest);
    Node<Vertex<T>>* originPtr = this->findData(vertexOrigin);
    Node<Vertex<T>>* destPtr = this->findData(vertexDest);
    if(originPtr == nullptr or destPtr == nullptr) {
        throw GraphException("El vertice de origen o Destino no existe, al hacer ruta en Profundidad!");
    }

    Collection<Node<Vertex<T>>*> vertexQueue;
    Collection<Node<Vertex<T>>*> originStack;
    Collection<Node<Vertex<T>>*> destStack;
    Collection<Node<Vertex<T>>*> visitedList;
    Node<Vertex<T>>* current;
    Node<Vertex<T>>* currentDest;

    vertexQueue.enqueue(originPtr);
    while(!vertexQueue.isEmpty()) {

        current = vertexQueue.dequeue();

        if(visitedList.findData(current) == nullptr) {
            if(current->getData().getTag() == destPtr->getData().getTag()) {
                cout << endl << destPtr->getData().getTag();//Mostrar ruta
                Node<Vertex<T>>* aux = destPtr;
                while(!originStack.isEmpty()) {
                    if(destStack.pop() == aux) {
                        cout << "<-";
                        cout << originStack.top()->getData().getTag();
                        aux = originStack.pop();
                    } else {
                        originStack.pop();
                    }
                }
                return;
            }
            visitedList.enqueue(current);

            Vertex<T> destList(current->getData());
            while(!destList.isEmpty()) {
                currentDest = destList.dequeue().getDestiny();

                if(visitedList.findData(currentDest) == nullptr) {

                    vertexQueue.enqueue(currentDest);
                    originStack.push(current);
                    destStack.push(currentDest);
                }
            }
        }
    }
    cout << "\nNo hay ruta entre estos V\202rtices\n";
}

template<class T>
void Graph<T>::firstInRoute(T origin, T dest) {

    Vertex<T> vertexOrigin(origin);
    Vertex<T> vertexDest(dest);
    Node<Vertex<T>>* originPtr = this->findData(vertexOrigin);
    Node<Vertex<T>>* destPtr = this->findData(vertexDest);
    if(originPtr == nullptr or destPtr == nullptr) {
        throw GraphException("El vertice de origen o Destino no existe, al hacer ruta en Profundidad!");
    }

    Collection<Node<Vertex<T>>*> costList;
    Collection<Node<Vertex<T>>*> orderedList;
    Collection<Node<Vertex<T>>*> originStack;
    Collection<Node<Vertex<T>>*> destStack;
    Node<Vertex<T>>* currentVertex;
    Node<Vertex<T>>* currentDest;

    float currentCost;
    float destCost;
    Edge<T> e;

    originPtr->setCost(0.0);
    costList.enqueue(originPtr);
    orderedList.enqueue(originPtr);
    orderedList.quickSortByCost(orderedList.firstPos(), orderedList.lastPos());

    while(!orderedList.isEmpty()) {
        currentVertex = orderedList.dequeue();
        currentCost = currentVertex->getCost();

        if(currentVertex->getData().getTag() == destPtr->getData().getTag()) {
            currentDest = destPtr;
            while(!originStack.isEmpty()){
                cout << currentDest->getData().getTag() << "<-";
                while(!originStack.isEmpty() and destStack.top() != currentDest){
                    originStack.pop();
                    destStack.pop();
                }
                if(!originStack.isEmpty()){
                    currentDest = originStack.top();
                }
            }
            return;
        }
        Vertex<T> destList(currentVertex->getData());
        while(!destList.isEmpty()) {
            float weightAux = destList.getFront().getWeight();
            currentDest = destList.dequeue().getDestiny();
            destCost = weightAux + currentCost;
            if(costList.findData(currentDest) == nullptr) {
                currentDest->setCost(destCost);
                costList.enqueue(currentDest);
                orderedList.enqueue(currentDest);
                orderedList.quickSortByCost(orderedList.firstPos(), orderedList.lastPos());

                originStack.push(currentVertex);
                destStack.push(currentDest);
            }
            else if(destCost < costList.findData(currentDest)->getCost()) {
                costList.findData(currentDest)->setCost(destCost);
                orderedList.findData(currentDest)->setCost(destCost);

                originStack.push(currentVertex);
                destStack.push(currentDest);
            }
        }
    }
    cout << "\nNo existe ruta entre esos vertices\n";

/*
    Vertex<T> costList;
    Vertex<T> orderedList;

    Collection<Node<Vertex<T>>*> originStack;
    Collection<Node<Vertex<T>>*> destStack;
    Node<Vertex<T>>* currentVertex;
    Node<Vertex<T>>* currentDest;
    float currentCost;
    float destCost;

    Edge<T> e;

    e.setDestiny(originPtr);
    e.setWeight(0.0);

    costList.enqueue(e);
    orderedList.enqueue(e);
    orderedList.quickSortByWeight(orderedList.firstPos(), orderedList.lastPos());

    while(!orderedList.isEmpty()){
        currentCost = orderedList.getFront().getWeight();
        currentVertex = orderedList.dequeue().getDestiny();

        if(currentVertex->getData().getTag() == destPtr->getData().getTag()){
            currentDest = destPtr;
            while(!originStack.isEmpty()){
                cout << currentDest->getData().getTag() << "<-";
                while(!originStack.isEmpty() and destStack.top() != currentDest){
                    originStack.pop();
                    destStack.pop();
                }
                if(!originStack.isEmpty()){
                    currentDest = originStack.top();
                }
            }
            return;
        }

        Vertex<T> destList(currentVertex->getData());
        while(!destList.isEmpty()){
            destCost = destList.getFront().getWeight() + currentCost;
            currentDest = destList.getFront().getDestiny();
            Edge<T> tmp(currentDest);
            if(costList.findData(tmp) == nullptr){
                tmp.setWeight(destCost);
                costList.enqueue(tmp);
                orderedList.enqueue(tmp);
                orderedList.quickSortByWeight(orderedList.firstPos(), orderedList.lastPos());

                originStack.push(currentVertex);
                destStack.push(currentDest);
            }
            else if(destCost < costList.findData(tmp)->getData().getWeight()){
                costList.findData(tmp)->getData().setWeight(destCost);
                orderedList.findData(tmp)->getData().setWeight(destCost);
                orderedList.quickSortByWeight(orderedList.firstPos(), orderedList.lastPos());

                originStack.push(currentVertex);
                destStack.push(currentDest);
            }
        }
    }
     cout << "\nNo existe ruta entre esos vertices\n";
     */

}

#endif // GRAPH_H_INCLUDED
