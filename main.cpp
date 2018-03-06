#include <iostream>
#include "Dag.h"
#include "WorkPool.h"

using namespace std;

int main() {
    Dag dag;
    dag.createDag("data/DAG512T_edges.dot");
    dag.addCost("data/DAG512T_nodes.dot");
    //dag.createDag("data/edges.dot");
    //dag.addCost("data/nodes.dot");


    //dag.displayDag();
    //cout << "End create Dag" << endl;
    WorkPool workPool;
    int nbBegin = 1;
    int tabBegin[nbBegin] = {1};
    int nbWorkers = 4;
    int mode = MODE_RANDOM;
    for(int i=0; i < 10; i++) {
        cout << "MODE_NODE_WITH_MOST_FATHER" << endl;
        workPool.playWorkPool(dag, tabBegin, nbBegin, nbWorkers, mode);
        dag.resetDag();
    }
    return 0;
}