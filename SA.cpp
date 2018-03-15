#include <iostream>
#include <tgmath.h>
#include "SA.h"

SA::SA() {
}

/**
 * Solve a dag with the simulated annealing
 * @param dag
 * @param T_init Temperature initial
 * @param S_init Solution initial
 * @param limit of metropolis
 */
void SA::solveSA(Dag dag, int T_init, int S_init, double limit){
    orderNode.clear();

    double timeToExecute = dag.nodes[dag.searchNodeIntoDag(S_init)].cost;

    double probE = ProbaSol(dag.nodes[dag.searchNodeIntoDag(S_init)]);

    int T = T_init;

    vector<int> nodeReady = dag.nodeHandle(S_init);
    orderNode.push_back(S_init);

    srand (time(NULL));
    int nbRand;
    int idNode;
    double deltaE;
    double probE2;
    double metropolis;
    int cpt = 0;

    while(nodeReady.size() != 0){
        //new sol
        nbRand = (int)(rand() % nodeReady.size());
        idNode = nodeReady[nbRand];
        //Proba with the new sol
        probE2 = ProbaSol(dag.nodes[dag.searchNodeIntoDag(idNode)]);
        //calculate the deltaE
        deltaE =  probE2 - probE;
        probE = probE2;
        if(deltaE <= 0){//accept the node
            timeToExecute += dag.nodes[dag.searchNodeIntoDag(idNode)].cost;
            vector<int> newNodeReady = dag.nodeHandle(idNode);
            nodeReady.insert(nodeReady.end(), newNodeReady.begin(), newNodeReady.end());
            nodeReady.erase(nodeReady.begin()+nbRand);
            orderNode.push_back(idNode);
        }else{
            metropolis = exp(-deltaE/T);//calculate metropolis
            if(metropolis > limit){//if metropolis is better than limit we accept the node
                timeToExecute += dag.nodes[dag.searchNodeIntoDag(idNode)].cost;
                vector<int> newNodeReady = dag.nodeHandle(idNode);
                nodeReady.insert(nodeReady.end(), newNodeReady.begin(), newNodeReady.end());
                nodeReady.erase(nodeReady.begin()+nbRand);
                orderNode.push_back(idNode);
            }
        }
        T -= deltaE;
        cpt++;
    }
    orderNode.push_back(idNode);
    timeToExecute += dag.nodes[dag.searchNodeIntoDag(idNode)].cost;
    cout << "Time for execute the dag : " << timeToExecute << " nb ite " << cpt << endl;
}

/**
 * Calculate de new proba for a new solution
 * @param node
 * @return double proba
 */
double SA::ProbaSol(Node node){
    return (node.cost*10000000)/node.children.size();
}

/**
 * Display a node
 */
void SA::displaySA(){
    for (int i = 0; i < orderNode.size(); ++i) {
        cout << orderNode[i] << " ";
    }
    cout << endl;
}