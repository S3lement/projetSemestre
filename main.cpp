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
    int nbWorkers = 2;
    for(int i=0; i < 2; i++) {
        cout << "----MODE_QUEUE----" << endl;
        workPool.playWorkPool(dag, tabBegin, nbBegin, nbWorkers, MODE_QUEUE);
        cout << "----MODE_RANDOM----" << endl;
        workPool.playWorkPool(dag, tabBegin, nbBegin, nbWorkers, MODE_RANDOM);
        cout << "----MODE_NODE_WITH_MOST_FATHER----" << endl;
        workPool.playWorkPool(dag, tabBegin, nbBegin, nbWorkers, MODE_NODE_WITH_MOST_FATHER);
        usleep(1000000);
        dag.resetDag();
    }

    SA sa;
    /*for (int i = 0; i < 2; ++i) {
        sa.solveSA(dag, 40, 1, 0.8);
        sa.displaySA();
        usleep(1000000);
    }*/
    return 0;
}