#include <iostream>
#include "WorkPool.h"
#include <math.h>
#include <unistd.h>


WorkPool::WorkPool() {
}

void WorkPool::createWorkPool(Dag dag, int id) {
    int pos = dag.searchNodeIntoDag(id);
    if (pos != -1) {
        workpool.push(dag.nodes[pos]);
        //cout << dag.nodes[pos].id << endl;
        if (dag.nodes[pos].children.begin() != dag.nodes[pos].children.end()) {
            for (int i = 0; i < dag.nodes[pos].children.size(); i++) {
                createWorkPool(dag, dag.nodes[pos].children[i]);
            }
        }
    }
}

void WorkPool::playWorkPool(Dag dag, int nbWorker){
    //Create thread(simulation)
    for(int i = 0; i < nbWorker; i++){
        Worker newWorker;
        workers.push_back(newWorker);
    }

    //Action thread
    int idActiveThread;
    int pos;
    while(!workpool.empty()){
        Node node = workpool.front();
        pos = dag.searchNodeIntoDag(node.id);
        if(!dag.nodes[pos].stat){
            idActiveThread = threadAvailable();
            if(idActiveThread != -1) {
                if(!nodeAlreadyInProgress(node.id)) {
                    if (dag.allFathersAreExecuted(node.id)) {
                        workers[idActiveThread].idNode = node.id;
                        workers[idActiveThread].time = node.cost * pow(10.0, 5.0);
                        workers[idActiveThread].work = true;
                    } else {
                        workpool.push(node);
                        cout << "wait all father ar executed" << endl;
                        int idWorker = smallerWorkerTime();
                        Wait(idWorker);
                        for(int i = 0; i < workers.size(); i++){
                            if(i == idWorker){
                                cout << "Finish with thread " << i << " id node " << node.id << " time " << node.cost << endl;
                                pos = dag.searchNodeIntoDag(workers[i].idNode);
                                dag.nodes[pos].stat = true;
                                workers[i].work = false;
                            }else {
                                if(workers[i].work) {
                                    if (workers[i].time > workers[idWorker].time) {
                                        workers[i].time -= workers[idWorker].time;
                                    } else {
                                        workers[i].time = 0;
                                    }
                                }
                            }
                        }
                    }
                }
                workpool.pop();
            }else{
                cout << "All threads work" << endl;
                int idWorker = smallerWorkerTime();
                Wait(idWorker);
                for(int i = 0; i < workers.size(); i++){
                    if(i == idWorker){
                        cout << "Finish with thread " << i << " id node " << node.id << " time " << node.cost << endl;
                        pos = dag.searchNodeIntoDag(workers[i].idNode);
                        dag.nodes[pos].stat = true;
                        workers[i].work = false;
                    }else {
                        if(workers[i].time > workers[idWorker].time) {
                            workers[i].time -= workers[idWorker].time;
                        }else{
                            workers[i].time = 0;
                        }
                    }
                }
            }
        }else{
            workpool.pop();
        }
    }
}

int WorkPool::threadAvailable(){
    for(int i = 0; i < workers.size(); i++){
        if(!workers[i].work) return i;
    }
    return -1;
}

int WorkPool::smallerWorkerTime(){
    int smaller = 0;
    int time = workers[0].time;
    for(int i = 1; i < workers.size(); i++){
        if(workers[i].work) {
            if (workers[i].time < time) {
                smaller = i;
                time = workers[i].time;
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