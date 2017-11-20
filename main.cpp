#include <iostream>
#include "Dag.h"
#include "WorkPool.h"

using namespace std;

int main() {
    Dag dag;
    dag.createDag("data/DAG32T_edges.dot");
    dag.addCost("data/DAG32T_nodes.dot");
    dag.displayDag();
    cout << "End create Dag" << endl;
    WorkPool workPool;
    workPool.createWorkPool(dag,1);
    workPool.playWorkPool(dag, 2);

    return 0;
}