#ifndef PROJETSEMESTRE_NODES_H
#define PROJETSEMESTRE_NODES_H

#include <vector>
using namespace std;

class Node{
    public :
        int id;
        double cost;
        vector<int> children;
        vector<int> fathers;
        bool stat;

        Node(int idNode);
        void displayNode();

};

#endif //PROJETSEMESTRE_NODES_H
