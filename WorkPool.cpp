#include <iostream>
#include "WorkPool.h"
#include <math.h>
#include <unistd.h>


WorkPool::WorkPool() {
}

void WorkPool::createWorkPool(Dag dag, int id) {
    int pos = dag.searchNodeIntoDag(id);
    if (pos != -1) {
        workPool.push(id);
        //cout << dag.nodes[pos].id << endl;
        if (dag.nodes[pos].children.begin() != dag.nodes[pos].children.end()) {
            for (int i = 0; i < dag.nodes[pos].children.size(); i++) {
                createWorkPool(dag, dag.nodes[pos].children[i]);
            }
        }
    }
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
        addNodeInTheWorker(dag,i,begin[i]);
        cout << "worker " << i << " work with node id " << begin[i] << endl;

    }

    while(workersWork()) {
        cout << "-----------------------------------" << endl;
        int idSmallerTime = smallerWorkerTime();
        double timeToSub = workers[idSmallerTime].time;
        workers[idSmallerTime].work = false;
        cout << "worker " << idSmallerTime << " finish node " << workers[idSmallerTime].idNode << endl;

        vector<int> nodeReady = dag.nodeTreaded(workers[idSmallerTime].idNode);
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
                    addNodeInTheWorker(dag, i, idNode);
                    workPool.pop();
                    cout << "worker " << i << " work with node id " << idNode << endl;
                }
            }
        }
    }
}

void WorkPool::addNodeInTheWorker(Dag dag, int idWorker, int idNode){
    int posInTheDag = dag.searchNodeIntoDag(idNode);
    workers[idWorker].idNode = dag.nodes[posInTheDag].id;
    workers[idWorker].time = dag.nodes[posInTheDag].cost;
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

int WorkPool::threadAvailable(){
    for(int i = 0; i < workers.size(); i++){
        if(!workers[i].work) return i;
    }
    return -1;
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

bool WorkPool::nodeAlreadyInProgress(int id){
    for (int i = 0; i < workers.size(); i++) {
        if(workers[i].work){
            if(workers[i].idNode == id) return true;
        }
    }
    return false;
}

void WorkPool::Wait(int idWorker){
    //cout << idWorker << endl;
    //cout << workers[idWorker].time << endl;
    usleep(workers[idWorker].time*pow(10.0,5.0));
}