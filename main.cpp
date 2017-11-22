#include <iostream>
#include "Dag.h"
#include "WorkPool.h"

using namespace std;

int main() {
    Dag dag;
    dag.createDag("data/edges.dot");
    dag.addCost("data/nodes.dot");
    //dag.displayDag();
    //cout << "End create Dag" << endl;
    WorkPool workPool;
    //workPool.createWorkPool(dag,1);
    int nbBegin = 1;
    int tabBegin[nbBegin] = {1};
    int nbWorkers = 3;
    workPool.playWorkPool(dag, tabBegin, nbBegin, nbWorkers);

    return 0;
}