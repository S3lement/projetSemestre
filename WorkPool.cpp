#include <iostream>
#include "WorkPool.h"



WorkPool::WorkPool() {
}

/**
 *
 * @param dag
 * @param begin node or nodes of begin
 * @param nbBegin number of node
 * @param nbWorker number of worker
 * @param mode 1 = queue
 *             2 = random
 */
void WorkPool::playWorkPool(Dag dag, int* begin, int nbBegin, int nbWorker, int mode){
    //Create thread(simulation)
    if(workers.size() > 0){
        workers.clear();
    }
    for(int i = 0; i < nbWorker; i++){
        Worker newWorker;
        workers.push_back(newWorker);
    }

    //Push in the queue if the nbBegin > nbWorker
    int diff = nbBegin-nbWorker;
    if(nbBegin > nbWorker){
        for(int i = nbBegin-diff; i < nbBegin; i++){
            switch(mode){
                case MODE_QUEUE ://queue
                    workPool.push(begin[i]);
                    break;
                case MODE_RANDOM ://random
                    workPoolVector.push_back(begin[i]);
                    break;
                case MODE_NODE_WITH_MOST_FATHER ://node with the most father
                    workPoolVector.push_back(begin[i]);
                    break;
                default:
                    cout << "error mode " << mode << endl;
            }
            //cout << "add node id " << begin[i] << " in the queue" << endl;
        }
    }

    //Put in the worker the node for be handled
    for(int i = 0; i < nbBegin; i++){
        addNodeInTheWorker(dag,i,begin[i], 0.0);
        //cout << "worker " << i << " work with node id " << begin[i] << endl;

    }

    srand(time(NULL));

    double timeExecute = 0;
    while(workersWork()) {
        //cout << "-----------------------------------" << endl;
        int idSmallerTime = smallerWorkerTime();
        double timeToSub = workers[idSmallerTime].time;
        workers[idSmallerTime].work = false;
        timeExecute += workers[idSmallerTime].time;
        //cout << "worker " << idSmallerTime << " finish node " << workers[idSmallerTime].idNode << endl;

        vector<int> nodeReady = dag.nodeHandle(workers[idSmallerTime].idNode);
        for (int i = 0; i < nodeReady.size(); i++) {
            switch(mode){
                case MODE_QUEUE ://queue
                    workPool.push(nodeReady[i]);
                    break;
                case MODE_RANDOM ://random
                    workPoolVector.push_back(nodeReady[i]);
                    break;
                case MODE_NODE_WITH_MOST_FATHER ://node with the most father
                    workPoolVector.push_back(nodeReady[i]);
                    break;
                default:
                    cout << "error mode " << mode << endl;
            }
            //cout << "add node id " << nodeReady[i] << " in the queue" << endl;
        }

        for (int i = 0; i < nbWorker; i++) {
            if (workers[i].work) {
                workers[i].time -= timeToSub;
            } else {
                switch(mode){
                    case MODE_QUEUE ://queue
                        if (!workPool.empty()) {
                            int idNode = workPool.front();
                            addNodeInTheWorker(dag, i, idNode, timeExecute);
                            workPool.pop();
                            //cout << "worker " << i << " work with node id " << idNode << endl;
                        }
                        break;
                    case MODE_RANDOM ://random
                        if(workPoolVector.size()!=0){
                            int ran = (int)(rand() % workPoolVector.size());
                            int idNode = workPoolVector[ran];
                            workPoolVector.erase(workPoolVector.begin()+ran);
                            addNodeInTheWorker(dag, i, idNode, timeExecute);
                        }
                        break;
                    case MODE_NODE_WITH_MOST_FATHER :
                        if(workPoolVector.size()!=0){
                            int numFather = 0;
                            int nbFather = (int)dag.nodes[dag.searchNodeIntoDag(workPoolVector[0])].fathers.size();
                            for(int i = 1; i < workPoolVector.size(); i++){
                                if(dag.nodes[dag.searchNodeIntoDag(workPoolVector[i])].fathers.size() > nbFather){
                                    nbFather = (int)dag.nodes[dag.searchNodeIntoDag(workPoolVector[i])].fathers.size();
                                    numFather = i;
                                }
                            }
                            int idNode = workPoolVector[numFather];
                            workPoolVector.erase(workPoolVector.begin()+numFather);
                            addNodeInTheWorker(dag, i, idNode, timeExecute);
                        }
                        break;
                    default:
                        cout << "error mode " << mode << endl;
                }
            }
        }
    }

    cout << "Time to execute all the program " << timeExecute << endl;

    display((int)timeExecute, 1, DISPLAY_TEXT);
}

/**
 * Add node in the worker
 * @param dag
 * @param idWorker id of worker
 * @param idNode  id of node
 * @param currentTime time on the current time
 */
void WorkPool::addNodeInTheWorker(Dag dag, int idWorker, int idNode, double currentTime){
    int posInTheDag = dag.searchNodeIntoDag(idNode);
    array<double, 3> infoNode = {(double)dag.nodes[posInTheDag].id, dag.nodes[posInTheDag].cost, currentTime};
    workers[idWorker].idNode = dag.nodes[posInTheDag].id;
    workers[idWorker].time = dag.nodes[posInTheDag].cost;
    workers[idWorker].handleHistory.push_back(infoNode);
    workers[idWorker].work = true;
}

/**
 * Test if a worker work
 * @return bool true if a worker work
 */
bool WorkPool::workersWork(){
    for(int i = 0; i < workers.size(); i++){
        if(workers[i].work){
            return true;
        }
    }
    return false;
}

/**
 * Find the smaller worker time
 * @return int time of worker
 */
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

/**
 * Display all the workers handles
 * @param timeExecute time global of program
 * @param base base of time
 */
void WorkPool::display(int timeExecute, int base, int mode) {
    int cptTimeBegin = 0;
    bool work = false;
    cout << "Workers in the time" << endl;
    for(int i = 0; i < workers.size(); i++){
        if(mode == DISPLAY_TEXT){
            cout << "------worker " << i << "------" << endl;
            for(int j = 0; j < workers[i].handleHistory.size(); j++){
                cout << "node id " << workers[i].handleHistory[j][0] << " time begin " << workers[i].handleHistory[j][2]
                    << " time end " << workers[i].handleHistory[j][2]+workers[i].handleHistory[j][1] << endl;

            }
        }else if(mode == DISPLAY_GRAPH){
            for(int k = 0; k < timeExecute*base; k++){
                if(cptTimeBegin < workers[i].handleHistory.size() && workers[i].handleHistory[cptTimeBegin][2] <= k/base){
                    work = true;
                }

                if(work){
                    cout << "*";
                }else{
                    cout << "-";
                }

                if(work && workers[i].handleHistory[cptTimeBegin][2]+workers[i].handleHistory[cptTimeBegin][1] == k/base){
                    work = false;
                    cptTimeBegin++;
                }

            }
            work = false;
            cptTimeBegin = 0;
            cout << endl;
        }

    }
}