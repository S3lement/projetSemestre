#ifndef PROJETSEMESTRE_WORKPOOL_H
#define PROJETSEMESTRE_WORKPOOL_H

#include <queue>
#include "node.h"
#include "Dag.h"
#include "Worker.h"

using namespace std;

class WorkPool{
    public:
        queue<Node> workpool;
        vector<Worker> workers;

        WorkPool();
        void createWorkPool(Dag dag, int id);
        void playWorkPool(Dag dag, int nbWorker);
        int threadAvailable();
        int smallerWorkerTime();
        bool nodeAlreadyInProgress(int id);
        void Wait(int idWorker);
};

#endif //PROJETSEMESTRE_WORKPOOL_H
