#include <iostream>
#include "Dag.h"
#include "WorkPool.h"

using namespace std;

int main() {
    Dag dag;
    dag.createDag("data/DAG32T_edges.dot");
    dag.addCost("data/DAG32T_nodes.dot");
    //dag.createDag("data/edges.dot");
    //dag.addCost("data/nodes.dot");
    //dag.displayDag();
    //cout << "End create Dag" << endl;
    WorkPool workPool;
    int nbBegin = 1;
    int tabBegin[nbBegin] = {1};
    int nbWorkers = 4;
    int mode = MODE_NODE_WITH_MOST_FATHER;
    cout << "MODE_NODE_WITH_MOST_FATHER" << endl;
    workPool.playWorkPool(dag, tabBegin, nbBegin, nbWorkers, mode);
    dag.resetDag();
    mode = MODE_QUEUE;
    cout << "MODE_QUEUE" << endl;
    workPool.playWorkPool(dag, tabBegin, nbBegin, nbWorkers, mode);

    return 0;
}