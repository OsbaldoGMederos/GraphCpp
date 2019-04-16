#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "graph.h"

#ifdef _WIN32

#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define SEE_GRAPH '0'
#define INSERT_VERTEX '1'
#define DELETE_VERTEX '2'
#define INSERT_DIRECTED_EDGE '3'
#define DELETE_DIRECTED_EDGE '4'
#define INSERT_NOT_DIRECTED_EDGE '5'
#define DELETE_NOT_DIRECTED_EDGE '6'
#define PARSES '7'
#define ROUTES_FIRST_IN '8'
#define RANDOM_GRAPH 'A'
#define ALL_PARSES 'R'
#define ALL_ROUTES 'U'
#define CLEAN 'L'
#define EXIT '9'

using namespace std;

template<class T>
class Menu {
private:

    Graph<T>* graphRef;

public:

    Menu(Graph<T>*);

    void showMainMenu();
    void showGraph();
    void insertVertex();
    void deleteVertex();
    void insertDirectedEdge();
    void deleteDirectedEdge();
    void insertNotDirectedEdge();
    void deleteNotDirectedEdge();
    void showParseMenu();
    void depthParse();
    void widthParse();
    void showRoutesMenu();
    void depthRoute();
    void widthRoute();
    void firstIn();
    void randomGraph();
    void allParses();
    void allRoutes();
    void cleanAll();

    float getRandom();

    void pause();


};

template<class T>
Menu<T>::Menu(Graph<T>* g) {
    graphRef = g;
    showMainMenu();
}


template<class T>
void Menu<T>::showMainMenu() {

    char opc;

    do {

        system(CLEAR);
        cout << "MENU DE GRAFO" << endl << endl;
        cout << "0. Ver el contenido del grafo" << endl;
        cout << "1. Insertar Vertice" << endl;
        cout << "2. Eliminar Vertice" << endl;
        cout << "3. Insertar Arista Dirigida" << endl;
        cout << "4. Eliminar Arista Dirigida" << endl;
        cout << "5. Insertar Arista NO Dirigida" << endl;
        cout << "6. Eliminar Arista NO Dirigida" << endl;
        cout << "7. Recorridos..." << endl;
        cout << "8. Rutas Primero en..." << endl;
        //cout << "A. Crear un grafo Aleatorio" << endl;
        cout << "R. Todos los recorridos" << endl;
        cout << "U. Todas las Rutas" << endl;
        cout << "L. Limpiar (anular) el Grafo" << endl;
        cout << "9. Salir" << endl << endl;
        cout << "Seleccione opcion: ";
        cin >> opc;
        cin.ignore();
        while(cin.fail()) {
            cin.clear();
            cin.ignore();
        }
        opc = toupper(opc);

        switch(opc) {
        case SEE_GRAPH:
            showGraph();
            break;
        case INSERT_VERTEX:
            insertVertex();
            break;
        case DELETE_VERTEX:
            deleteVertex();
            break;
        case INSERT_DIRECTED_EDGE:
            insertDirectedEdge();
            break;
        case DELETE_DIRECTED_EDGE:
            deleteDirectedEdge();
            break;
        case INSERT_NOT_DIRECTED_EDGE:
            insertNotDirectedEdge();
            break;
        case DELETE_NOT_DIRECTED_EDGE:
            deleteNotDirectedEdge();
            break;
        case PARSES:
            showParseMenu();
            break;
        case ROUTES_FIRST_IN:
            showRoutesMenu();
            break;
        case RANDOM_GRAPH:
            randomGraph();
            break;
        case ALL_PARSES:
            allParses();
            break;
        case ALL_ROUTES:
            allRoutes();
            break;
        case CLEAN:
            cleanAll();
            break;
        case EXIT:
            ;
            break;
        default:
            cout << "\nOpcion No Valida!...";
            pause();
        }


    } while(opc != EXIT);

}

template<class T>
void Menu<T>::showGraph() {
    system(CLEAR);
    cout << "MOSTRANDO EL CONTENIDO DEL GRAFO" << endl << endl;
    if(graphRef->isEmpty()) {
        cout << "El grafo esta vacio!";
        pause();
        return;
    }

    graphRef->print();
    pause();
}

template<class T>
void Menu<T>::insertVertex() {
    T id;

    system(CLEAR);
    cout << "INSERTANDO VERTICE" << endl << endl;
    cout << "Que numero le dará al vertice?: ";
    cin >> id;
    cin.ignore();
    while(cin.fail()) {
        cin.clear();
        cin.ignore();
    }

    Vertex<T> myVertex(id);
    if(graphRef->findData(myVertex) == nullptr) {
        graphRef->insertVertex(myVertex);

        cout << "\n\n\nEl vertice fue creado con exito!";
        pause();
    }
    else {
        cout << "\nYa existe un vertice con ese identificador!";
        pause();
    }
}

template<class T>
void Menu<T>::deleteVertex() {
    system(CLEAR);
    cout << "ELIMINANDO VERTICE" << endl << endl;
    if(graphRef->isEmpty()) {
        cout << "El grafo esta vacio" << endl;
        cout << "\nNo se puede eliminar..." << endl;
        pause();
        return;
    }
    T id;
    cout << "Este es el contenido del grafo:" << endl;
    graphRef->print();
    cout << "\nQue vertice deseas eliminar: ";
    cin >> id;
    cin.ignore();

    Vertex<T> aux(id);
    if(graphRef->findData(aux) == nullptr) {
        cout << "\nNo se encontro ese vertice... " << endl;
        pause();
        return;
    }
    else {
        graphRef->deleteData(graphRef->findData(aux));
        cout << "\nEl vertice se elimino con exito!";
        pause();
    }
}

template<class T>
void Menu<T>::insertDirectedEdge() {
    system(CLEAR);
    cout << "INSERTANDO ARISTA DIRIGIDO" << endl << endl;
    if(graphRef->isEmpty()) {
        cout << "No hay vertices para insertar aristas" << endl;
        pause();
        return;
    }
    T id;
    cout << "Estos son los vertices en el grafo:" << endl;
    graphRef->print();
    cout << "\nEn cual de ellos deseas insertar el arista: ";
    cin >> id;
    cin.ignore();

    Vertex<T> myV(id);
    Node<Vertex<T>>* origin = graphRef->findData(myV);
    Node<Vertex<T>>* dest;
    if(origin == nullptr) {
        cout << "\nNo se encontro ese vertice...";
        pause();
        return;
    }
    else {
        char answer;
        do {
            cout << "\nHacia que vertice fijara su destino? ";
            cin >> id;
            cin.ignore();

            myV.setTag(id);
            dest = graphRef->findData(myV);
            if(dest == nullptr) {
                cout << "\nNo se encontro ese vertice de destino!";
                pause();
            }
        } while(dest == nullptr);
        graphRef->setIsDirected(true);
        Edge<T> myEdge(dest);
        cout << "\nAgregar peso [S/N]: ";
        cin >> answer;
        cin.ignore();
        answer = toupper(answer);
        float w = 1.0;
        if(answer == 'S') {

            cout << "\nDime el peso que llevara: ";
            cin >> w;
            cin.ignore();

            myEdge.setWeight(w);

        }
        else {
            ;
        }
        graphRef->insertEdge(myEdge, origin);
        graphRef->findData(origin->getData())->getData().findData(myEdge)->setCost(myEdge.getWeight());

        cout << "\nEl arista dirigido fue insertado con exito!";
        pause();

    }
}

template<class T>
void Menu<T>::deleteDirectedEdge() {
    system(CLEAR);
    cout << "ELIMINANDO ARISTA DIRIGIDO" << endl << endl;
    if(!graphRef->getIsDirected()) {
        cout << "El grafo es NO dirigido!" << endl;
        cout << "No se puede eliminar un arista Dirigido";
        pause();
        return;
    }
    else {
        if(graphRef->isEmpty()) {
            cout << "El grafo esta vacio, no se pueden eliminar aristas!" ;
            pause();
        }
        else {
            T id;
            cout << "\nEstos son los vertices que existen en el grafo:" << endl;
            graphRef->print();
            cout << "\nEn cual de ellos se encuentra el arista que deseas eliminar? ";
            cin >> id;
            cin.ignore();
            Vertex<T> myV(id);
            Node<Vertex<T>>* origin = graphRef->findData(myV);

            if(origin == nullptr) {
                cout << "\n\n\nNo se encontro el vertice...";
                pause();
                return;
            }
            else {
                if(origin->getData().isEmpty()) {
                    cout << "\n\n\nEse vertice no tiene aristas\n";
                    pause();
                    return;
                }
                else {
                    cout << "\nSe encontraron aristas con estos destinos en ese vertice:" << endl;
                    origin->getData().print();

                    T id;
                    cout << "\n\nCual destino corresponde el arista que deseas eliminar? ";
                    cin >> id;
                    cin.ignore();

                    Vertex<T> myV(id);
                    Node<Vertex<T>>* dest = graphRef->findData(myV);
                    if(dest == nullptr) {
                        cout << "\n\n\nNo se encontro ese destino!";
                        pause();
                        return;
                    }
                    Edge<T> myE(dest);
                    Node<Edge<T>>* deletePtr = origin->getData().findData(myE);
                    origin->getData().deleteData(deletePtr);

                    cout << "\n\n\n\nEl arista Dirigido se elimino correctamente!";
                    pause();
                }
            }
        }
    }
}

template<class T>
void Menu<T>::insertNotDirectedEdge() {

    system(CLEAR);
    cout << "INSERTANDO ARISTA NO DIRIGIDO" << endl << endl;
    if(graphRef->getIsDirected()) {
        cout << "\n\nEl grafo se establecio previamente como \"Dirigido\"" << endl;
        cout << "No se puede insertar un arista \"NO Dirigido\"" << endl;
        pause();
        return;
    }
    else if(graphRef->isEmpty()) {
        cout << "\nEl grafo esta vacio" << endl;
        cout << "No se pueden insertar aristas\n";
        pause();
        return;
    }
    else {
        T id;
        cout << "Estos son los vertices en el grafo:" << endl;
        graphRef->print();
        cout << "\nEn cual de ellos deseas insertar el arista: ";
        cin >> id;
        cin.ignore();

        Vertex<T> myV(id);
        Node<Vertex<T>>* origin = graphRef->findData(myV);
        Node<Vertex<T>>* dest;
        if(origin == nullptr) {
            cout << "\nNo se encontro ese vertice...";
            pause();
            return;
        }
        else {
            do {
                cout << "\nHacia que vertice fijara su destino? ";
                cin >> id;
                cin.ignore();

                myV.setTag(id);
                dest = graphRef->findData(myV);
                if(dest == nullptr) {
                    cout << "\nNo se encontro ese vertice de destino!";
                    pause();
                }
            } while(dest == nullptr);
            Edge<T> myEdge(dest);
            graphRef->insertEdge(myEdge, origin);

            cout << "\nEl arista  NO dirigido fue insertado con exito!";
            pause();
        }
    }
}

template<class T>
void Menu<T>::deleteNotDirectedEdge() {

    system(CLEAR);
    cout << "ELIMINANDO UN ARISTA NO DIRIGIDO" << endl << endl;

    if(graphRef->getIsDirected()) {
        cout << "\nEl grafo fue definido previamente como \"Dirigido\"" << endl;
        cout << "No se puede eliminar un arista \"NO Dirigido\"";
        pause();
        return;
    }
    else if(graphRef->isEmpty()) {
        cout << "\nEL grafo esta vacio" << endl;
        cout << "No se pueden eliminar aristas";
        pause();
        return;
    }
    else {
        T id;
        cout << "\nEstos son los vertices del Grafo:" << endl;
        graphRef->print();
        cout << "\n\nEn cual se encuentra el arista que deseas eliminar? ";
        cin >> id;
        cin.ignore();

        Vertex<T> myV(id);
        Node<Vertex<T>>* origin = graphRef->findData(myV);

        if(origin == nullptr) {
            cout << "\n\n\nNo se encontri el vertice...";
            pause();
            return;
        }
        else {
            if(origin->getData().isEmpty()) {
                cout << "\n\n\nEse vertice no tiene aristas\n";
                pause();
                return;
            }
            else {
                cout << "\nSe encontraron aristas con estos destinos en ese vertice:" << endl;
                origin->getData().print();

                T id;
                cout << "\n\nCual destino corresponde el arista que deseas eliminar? ";
                cin >> id;
                cin.ignore();

                Vertex<T> myV(id);
                Node<Vertex<T>>* dest = graphRef->findData(myV);
                if(dest == nullptr) {
                    cout << "\n\n\nNo se encontro ese destino!";
                    pause();
                    return;
                }
                Edge<T> e1(dest);
                Edge<T> e2(origin);
                Node<Edge<T>>* e1Ptr = origin->getData().findData(e1);
                Node<Edge<T>>* e2Ptr = dest->getData().findData(e2);

                origin->getData().deleteData(e1Ptr);
                dest->getData().deleteData(e2Ptr);

                cout << "\n\n\n\nEl arista NO Dirigido se elimino correctamente!";
                pause();
            }
        }
    }
}

template<class T>
void Menu<T>::showParseMenu() {

    if(graphRef->isEmpty()) {
        cout << "\n\nEl grafo esta vacio " << endl;
        pause();
        return;
    }

    int opc;

    do {
        system(CLEAR);
        cout << "MENU DE RECORRIDOS" << endl << endl;
        cout << "1. Recorrido en profundidad" << endl;
        cout << "2. Recorrido en anchura" << endl;
        cout << "3. regresar al menu principal" << endl << endl;
        cout << "Elige una opcion ";
        cin >> opc;
        cin.ignore();
        while(cin.fail()) {
            cin.clear();
        }

        switch(opc) {
        case 1:
            depthParse();
            break;
        case 2:
            widthParse();
            break;
        case 3:
            ;
            break;
        default:
            cout << "\n\nOpcion invalida!";
            pause();
            break;

        }
    } while(opc != 3);


}

template<class T>
void Menu<T>::widthParse() {
    T id;
    system(CLEAR);
    cout << "RECORRIDO EN ANCHURA" << endl << endl;
    cout << "Estos son los vertices del grafo:" << endl;
    graphRef->print();
    cout << "\n\nEn que vertice deseas iniciar el recorrido en anchura: ";
    cin >> id;
    cin.ignore();
    Vertex<T> myV(id);
    if(graphRef->findData(myV) == nullptr) {
        cout << "\nNo se encontro ese vertice";
        pause();
        return;
    }
    else {
        graphRef->widthParse(id);
        pause();
    }
}

template<class T>
void Menu<T>::depthParse() {
    T id;
    system(CLEAR);
    cout << "RECORRIDO En Profundidad" << endl << endl;
    cout << "Estos son los vertices del grafo:" << endl;
    graphRef->print();
    cout << "\n\nEn que vertice deseas iniciar el recorrido en profundidad: ";
    cin >> id;
    cin.ignore();
    Vertex<T> myV(id);
    if(graphRef->findData(myV) == nullptr) {
        cout << "\nNo se encontro ese vertice";
        pause();
        return;
    }
    else {
        graphRef->depthParse(id);
        pause();
    }
}

template<class T>
void Menu<T>::showRoutesMenu() {

    if(graphRef->isEmpty()) {
        cout << "\n\nEl grafo esta vacio " << endl;
        pause();
        return;
    }

    int opc;

    do {
        system(CLEAR);
        cout << "MENU DE RUTAS" << endl << endl;
        cout << "1. Primero en Profundidad" << endl;
        cout << "2. Primero en anchura" << endl;
        cout << "3. Primero el mejor" << endl;
        cout << "4. Regresar al menu principal" << endl << endl;
        cout << "Elige una opcion: ";
        cin >> opc;
        cin.ignore();
        while(cin.fail()) {
            cin.clear();
        }

        switch(opc) {
        case 1:
            depthRoute();
            break;
        case 2:
            widthRoute();
            break;
        case 3:
            firstIn();
            break;
        case 4:
            ;
            break;
        default:
            cout << "\n\nOpcion invalida!";
            pause();
            break;

        }
    } while(opc != 4);
}

template<class T>
void Menu<T>::depthRoute() {
    T orig;
    T dest;
    system(CLEAR);
    cout << "RUTA PRIMERO EN PROFUNDIDAD" << endl << endl;
    cout << "Estos son los vertices del grafo:" << endl;
    graphRef->print();
    cout << "\n\nEn que vertice sera el origen de la ruta en profundidad: ";
    cin >> orig;
    cin.ignore();

    cout << "\n\nEn que vertice sera el final de la ruta en profundidad: ";
    cin >> dest;
    cin.ignore();
    Vertex<T> myVerOrig(orig);
    Vertex<T> myVerDest(dest);
    if(graphRef->findData(myVerOrig) == nullptr or graphRef->findData(myVerDest) == nullptr) {
        cout << "\nNo se encontro uno de los dos vertices";
        pause();
        return;
    }
    else {
        graphRef->depthRoute(orig, dest);
        pause();
    }
}

template<class T>
void Menu<T>::widthRoute() {
    T orig;
    T dest;
    system(CLEAR);
    cout << "RUTA PRIMERO EN ANCHURA" << endl << endl;
    cout << "Estos son los vertices del grafo:" << endl;
    graphRef->print();
    cout << "\n\nEn que vertice sera el origen de la ruta en anchura: ";
    cin >> orig;
    cin.ignore();

    cout << "\n\nEn que vertice sera el final de la ruta en anchura: ";
    cin >> dest;
    cin.ignore();
    Vertex<T> myVerOrig(orig);
    Vertex<T> myVerDest(dest);
    if(graphRef->findData(myVerOrig) == nullptr or graphRef->findData(myVerDest) == nullptr) {
        cout << "\nNo se encontro uno de los dos vertices";
        pause();
        return;
    }
    else {
        graphRef->widthRoute(orig, dest);
        pause();
    }
}

template<class T>
void Menu<T>::firstIn() {
    T orig;
    T dest;
    system(CLEAR);
    cout << "RUTA PRIMERO EL MEJOR" << endl << endl;
    cout << "Estos son los vertices del grafo:" << endl;
    graphRef->print();
    cout << "\n\nEn que vertice sera el origen de la ruta: ";
    cin >> orig;
    cin.ignore();

    cout << "\n\nEn que vertice sera el final de la ruta: ";
    cin >> dest;
    cin.ignore();
    Vertex<T> myVerOrig(orig);
    Vertex<T> myVerDest(dest);
    if(graphRef->findData(myVerOrig) == nullptr or graphRef->findData(myVerDest) == nullptr) {
        cout << "\nNo se encontro uno de los dos vertices";
        pause();
        return;
    }
    else {
        graphRef->firstInRoute(orig, dest);
        pause();
    }
}

template<class T>
void Menu<T>::randomGraph() {
    char answer;
    int vNum;
    int eNum;

    system(CLEAR);
    cout << "GRAFO ALEATORIO" << endl << endl;
    cout << "Ponderado [S/N]: ";
    cin >> answer;
    cin.ignore();
    answer = toupper(answer);

    if(answer == 'S') {
        graphRef->setIsWeighted(true);
    }
    else {
        graphRef->setIsWeighted(false);
    }

    cout << "Dirigido [S/N]: ";
    cin >> answer;
    cin.ignore();
    answer = toupper(answer);

    if(answer == 'S') {
        graphRef->setIsDirected(true);
    }
    else {
        graphRef->setIsDirected(false);
    }

    cout << "\nNumero de Vertices (max 25): ";
    cin >> vNum;
    cin.ignore();
    if(vNum > 25) {
        cout << "\nEl numero de vertices supera el limite\n";
        pause();
        return;
    }

    for(int i = 1; i <= vNum; i++) {
        Vertex<T> myV(i);
        graphRef->insertVertex(myV);
    }

    if(graphRef->getIsDirected()) {
        cout << "\nNumero de Aristas (max " << vNum*vNum << "): ";
        cin >> eNum;
        cin.ignore();
        if(eNum > 625) {
            cout << "\nEl numero de aristas supera el limite\n";
            pause();
            graphRef->deleteAll();
            return;
        }
        else {
            int j = 1;
            for(int i = 1; i <= vNum; i++) {
                Vertex<T> v(i);
                Node<Vertex<T>>* origin = graphRef->findData(v);
                Node<Vertex<T>>* dest = graphRef->firstPos();
                Edge<T> e;

                while(j <= eNum and dest != graphRef->lastPos()->getNext()) {
                    if(graphRef->getIsWeighted()) {
                        e.setWeight(getRandom());
                    }
                    e.setDestiny(dest);
                    graphRef->insertEdge(e, origin);
                    dest = dest->getNext();
                    j++;
                }
            }
        }
    }
    else {
        int sum = 0;
        for(int k = vNum; k > 0; k--) {
            sum = sum + k;
        }

        cout << "\nNumero de Aristas (max " << sum << "): ";
        cin >> eNum;
        cin.ignore();
        if(eNum > 325) {
            cout << "\nEl numero de aristas supera el limite\n";
            pause();
            graphRef->deleteAll();
            return;
        }
        else {
            int j = 1;
            for(int i = 1; i <= vNum; i++) {
                Vertex<T> v(i);
                Node<Vertex<T>>* origin = graphRef->findData(v);
                Node<Vertex<T>>* dest = graphRef->firstPos();
                Edge<T> e;

                while(j <= eNum and dest != graphRef->lastPos()->getNext()) {
                    if(graphRef->getIsWeighted()) {
                        e.setWeight(getRandom());
                    }
                    e.setDestiny(dest);
                    graphRef->insertEdge(e, origin);
                    dest = dest->getNext();
                    j++;
                }
            }
        }
    }
}

template<class T>
void Menu<T>::allParses() {
    system(CLEAR);
    cout << "TODOS LOS RECORRIDOS" << endl << endl;

    if(graphRef->isEmpty()) {
        cout << "\n\nEl grafo esta vacio";
        pause();
        return;
    }

    cout << "\n***En Profundidad***" << endl;

    Node<Vertex<T>>* aux = graphRef->firstPos();
    while(aux != graphRef->lastPos()->getNext()) {

        cout << "\nComenzando en " << aux->getData().getTag() << endl;
        graphRef->depthParse(aux->getData().getTag());
        cout << endl;

        aux = aux->getNext();
    }

    cout << "\n\n***En Anchura***" << endl;

    aux = graphRef->firstPos();
    while(aux != graphRef->lastPos()->getNext()) {

        cout << "\nComenzando en " << aux->getData().getTag() << endl;
        graphRef->widthParse(aux->getData().getTag());
        cout << endl;

        aux = aux->getNext();
    }

    pause();

}

template<class T>
void Menu<T>::allRoutes() {
    system(CLEAR);
    cout << "TODAS LAS RUTAS" << endl << endl;

    if(graphRef->isEmpty()) {
        cout << "\n\nEl grafo esta vacio";
        pause();
        return;
    }

    system(CLEAR);
    cout << "TODAS LAS RUTAS" << endl << endl;
    cout << "\n***Primero En Profundidad***" << endl;

    Node<Vertex<T>>* origin = graphRef->firstPos();
    Node<Vertex<T>>* dest;
    while(origin != graphRef->lastPos()->getNext()) {
        dest = graphRef->firstPos();
        cout << "\n*******************" << endl;
        while(dest != graphRef->lastPos()->getNext()) {

            cout << "\nDesde: " << origin->getData().getTag() << " Hasta: " << dest->getData().getTag() << endl;
            graphRef->depthRoute(origin->getData().getTag(), dest->getData().getTag());
            cout << endl;

            dest = dest->getNext();
        }
        origin = origin->getNext();
    }

    pause();
    system(CLEAR);
    cout << "TODAS LAS RUTAS" << endl << endl;

    cout << "\n\n***En Anchura***" << endl;

    origin = graphRef->firstPos();
    while(origin != graphRef->lastPos()->getNext()) {
        dest = graphRef->firstPos();
        cout << "\n*******************" << endl;
        while(dest != graphRef->lastPos()->getNext()) {

            cout << "\nDesde: " << origin->getData().getTag() << " Hasta: " << dest->getData().getTag() << endl;
            graphRef->widthRoute(origin->getData().getTag(), dest->getData().getTag());
            cout << endl;

            dest = dest->getNext();
        }
        origin = origin->getNext();
    }

    pause();
    system(CLEAR);
    cout << "TODAS LAS RUTAS" << endl << endl;

    cout << "\n\n***Primero el mejor***" << endl;

    origin = graphRef->firstPos();
    while(origin != graphRef->lastPos()->getNext()) {
        dest = graphRef->firstPos();
        cout << "\n*******************" << endl;
        while(dest != graphRef->lastPos()->getNext()) {

            cout << "\nDesde: " << origin->getData().getTag() << " Hasta: " << dest->getData().getTag() << endl;
            graphRef->firstInRoute(origin->getData().getTag(), dest->getData().getTag());
            cout << endl;

            dest = dest->getNext();
        }
        origin = origin->getNext();
    }

    pause();
}


template<class T>
float Menu<T>::getRandom() {
    int tmp;
    float value;
    srand(time(NULL));

    tmp = rand() % 3000 + 1;

    value = tmp * 1.25;


    return value;
}

template<class T>
void Menu<T>::cleanAll() {
    graphRef->deleteAll();
}

template<class T>
void Menu<T>::pause() {
    cout << "\n\n\nPresiona enter para continuar...";
    cin.ignore();
}

#endif // MENU_H_INCLUDED
