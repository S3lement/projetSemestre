#ifndef PROJETSEMESTRE_WORKPOOL_H
#define PROJETSEMESTRE_WORKPOOL_H

#include <queue>
#include "node.h"
#include "Dag.h"
#include "Worker.h"

using namespace std;
const int MODE_QUEUE = 1;
const int MODE_RANDOM = 2;
const int MODE_NODE_WITH_MOST_FATHER = 3;

const int DISPLAY_TEXT = 0;
const int DISPLAY_GRAPH = 1;

class WorkPool{
    public:
        queue<int> workPool;
        vector<Worker> workers;
        vector<int> workPoolVector;

        WorkPool();
        void playWorkPool(Dag dag, int* begin , int nbBegin,int nbWorker, int mode);
        void addNodeInTheWorker(Dag dag, int idWorker, int idNode, double currentTime);
        bool workersWork();
        int smallerWorkerTime();
        void display(int timeExecute, int base, int mode);
};

#endif //PROJETSEMESTRE_WORKPOOL_H
