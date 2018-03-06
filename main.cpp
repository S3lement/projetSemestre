#include <iostream>
#include <zconf.h>
#include "Dag.h"
#include "WorkPool.h"
#include "SA.h"

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
    int nbWorkers = 20;
    int mode = MODE_RANDOM;
    /*for(int i=0; i < 10; i++) {
        cout << "MODE_NODE_WITH_MOST_FATHER" << endl;
        workPool.playWorkPool(dag, tabBegin, nbBegin, nbWorkers, mode);
        dag.resetDag();
    }*/

    SA sa;
    for (int i = 0; i < 10; ++i) {
        sa.solveSA(dag, 40, 1);
        usleep(1000000);
    }
    return 0;
}