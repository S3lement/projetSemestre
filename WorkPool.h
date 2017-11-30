#ifndef PROJETSEMESTRE_WORKPOOL_H
#define PROJETSEMESTRE_WORKPOOL_H

#include <queue>
#include "node.h"
#include "Dag.h"
#include "Worker.h"

using namespace std;

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
        void display(int timeExecute, int base);
};

#endif //PROJETSEMESTRE_WORKPOOL_H
