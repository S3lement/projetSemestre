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

        WorkPool();
        void createWorkPool(Dag dag, int id);
        void playWorkPool(Dag dag, int* begin , int nbBegin,int nbWorker);
        void addNodeInTheWorker(Dag dag, int idWorker, int idNode);
        int threadAvailable();
        bool workersWork();
        int smallerWorkerTime();
        bool nodeAlreadyInProgress(int id);
        void Wait(int idWorker);
};

#endif //PROJETSEMESTRE_WORKPOOL_H
