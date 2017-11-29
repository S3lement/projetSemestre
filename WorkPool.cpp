#include <iostream>
#include "WorkPool.h"


WorkPool::WorkPool() {
}

void WorkPool::playWorkPool(Dag dag, int* begin, int nbBegin, int nbWorker){
    //Create thread(simulation)
    for(int i = 0; i < nbWorker; i++){
        Worker newWorker;
        workers.push_back(newWorker);
    }

    //Push in the queue if the nbBegin > nbWorker
    int diff = nbBegin-nbWorker;
    if(nbBegin > nbWorker){
        for(int i = nbBegin-diff; i < nbBegin; i++){
            workPool.push(begin[i]);
            cout << "add node id " << begin[i] << " in the queue" << endl;
        }
    }

    //Put in the worker the node for be handled
    for(int i = 0; i < nbBegin; i++){
        addNodeInTheWorker(dag,i,begin[i], 0.0);
        cout << "worker " << i << " work with node id " << begin[i] << endl;

    }
    double timeExecute = 0;
    while(workersWork()) {
        cout << "-----------------------------------" << endl;
        int idSmallerTime = smallerWorkerTime();
        double timeToSub = workers[idSmallerTime].time;
        workers[idSmallerTime].work = false;
        timeExecute += workers[idSmallerTime].time;
        cout << "worker " << idSmallerTime << " finish node " << workers[idSmallerTime].idNode << endl;

        vector<int> nodeReady = dag.nodeHandle(workers[idSmallerTime].idNode);
        for (int i = 0; i < nodeReady.size(); i++) {
            workPool.push(nodeReady[i]);
            cout << "add node id " << nodeReady[i] << " in the queue" << endl;
        }

        for (int i = 0; i < nbWorker; i++) {
            if (workers[i].work) {
                workers[i].time -= timeToSub;
            } else {
                if (!workPool.empty()) {
                    int idNode = workPool.front();
                    addNodeInTheWorker(dag, i, idNode, timeExecute);
                    workPool.pop();
                    cout << "worker " << i << " work with node id " << idNode << endl;
                }
            }
        }
    }

    cout << "Time to execute all the program " << timeExecute << endl;

    display((int)timeExecute, 1);
}

void WorkPool::addNodeInTheWorker(Dag dag, int idWorker, int idNode, double currentTime){
    int posInTheDag = dag.searchNodeIntoDag(idNode);
    array<double, 3> infoNode = {(double)dag.nodes[posInTheDag].id, dag.nodes[posInTheDag].cost, currentTime};
    workers[idWorker].idNode = dag.nodes[posInTheDag].id;
    workers[idWorker].time = dag.nodes[posInTheDag].cost;
    workers[idWorker].handle.push_back(infoNode);
    workers[idWorker].work = true;
}

bool WorkPool::workersWork(){
    for(int i = 0; i < workers.size(); i++){
        if(workers[i].work){
            return true;
        }
    }
    return false;
}

int WorkPool::smallerWorkerTime(){
    int smaller;
    double time;
    bool init = false;
    for(int i = 0; i < workers.size(); i++){
        if(workers[i].work) {
            if(!init){
                smaller = i;
                time = workers[i].time;
                init = true;
            }else {
                if (workers[i].time < time) {
                    smaller = i;
                    time = workers[i].time;
                }
            }
        }
    }
    return smaller;
}

void WorkPool::display(int timeExecute, int base) {
    int cptTimeBegin = 0;
    bool work = false;
    cout << "Workers in the time" << endl;
    for(int i = 0; i < workers.size(); i++){
        cout << "------worker " << i << "------" << endl;
        for(int j = 0; j < workers[i].handle.size(); j++){
            cout << "node id " << workers[i].handle[j][0] << " time begin " << workers[i].handle[j][2]
                << " time end " << workers[i].handle[j][2]+workers[i].handle[j][1] << endl;

        }
        /*for(int k = 0; k < timeExecute*base; k++){
            if(cptTimeBegin < workers[i].handle.size() && workers[i].handle[cptTimeBegin][2] <= k/base){
                work = true;
            }

            if(work){
                cout << "*";
            }else{
                cout << "-";
            }

            if(work && workers[i].handle[cptTimeBegin][2]+workers[i].handle[cptTimeBegin][1] == k/base){
                work = false;
                cptTimeBegin++;
            }

        }
        work = false;
        cptTimeBegin = 0;
        cout << endl;*/
    }
}