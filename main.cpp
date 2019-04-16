#include <iostream>

#include "menu.h"

using namespace std;

int main()
{
    Graph<int> g2;
    Menu<int> myMenu(&g2);



    /*Graph<int> g;
    Edge<int> e;
    Vertex<int> v;

    g.enqueue(v);

    e.setDestiny(g.findData(v));
    e.setWeight(13);

    v.enqueue(e);
    v.findData(e)->setCost(e.getWeight());

    cout << v.findData(e)->getCost();*/


    return 0;
}

