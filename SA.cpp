#include <iostream>
#include <tgmath.h>
#include "SA.h"

SA::SA() {
}

void SA::solveSA(Dag dag, int T_init, int S_init){
    vector<int> orderNode;
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
        nbRand = (int)(rand() % nodeReady.size());
        idNode = nodeReady[nbRand];
        //cout << idNode << endl;
        probE2 = ProbaSol(dag.nodes[dag.searchNodeIntoDag(idNode)]);
        if(isinf(probE2)) break;
        //cout << "probE " << probE << endl;
        //cout << "porbE2 " << probE2 << endl;
        deltaE =  probE2 - probE;
        //cout << "deltaE " << deltaE << endl;
        probE = probE2;
        if(deltaE <= 0){
            //cout << "fin de " << idNode << endl;
            timeToExecute += dag.nodes[dag.searchNodeIntoDag(idNode)].cost;
            vector<int> newNodeReady = dag.nodeHandle(idNode);
            nodeReady.insert(nodeReady.end(), newNodeReady.begin(), newNodeReady.end());
            nodeReady.erase(nodeReady.begin()+nbRand);
            orderNode.push_back(idNode);
        }else{
            //cout << "deltaE " << deltaE << endl;
            metropolis = exp(-deltaE/T);
            //cout << "metropolis " << metropolis << endl;
            if(metropolis > 0.8){
                //cout << "fin de " << idNode << endl;
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
    cout << "Time for execute the dag : " << timeToExecute << " nb ite " << cpt << endl;
    for (int i = 0; i < orderNode.size(); ++i) {
        cout << orderNode[i] << " ";
    }
    cout << endl;
}

double SA::ProbaSol(Node node){
    return (node.cost*10000000)/node.children.size();
}

Node SA::newSol(vector<int> nodeReady){
    /* initialize random seed: */
    srand (time(NULL));
    int nbRand = rand() % (int)nodeReady.size() + 1;

}