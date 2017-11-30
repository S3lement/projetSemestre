#ifndef PROJETSEMESTRE_DAG_H
#define PROJETSEMESTRE_DAG_H

#include <vector>
#include "node.h"

using namespace std;

class Dag{
    public:
        vector<Node> nodes;

        Dag();
        void createDag(string filename);
        void addCost(string filename);
        int searchNodeIntoDag(int id);
        vector<int> nodeHandle(int id);
        bool nodeReady(int id);
        void resetDag();
        void displayDag();
};

#endif //PROJETSEMESTRE_DAG_H
