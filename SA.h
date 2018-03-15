#ifndef PROJETSEMESTRE_SA_H
#define PROJETSEMESTRE_SA_H


#include "node.h"
#include "Dag.h"

class SA{
    public:
        vector<int> orderNode;

        SA();
        void solveSA(Dag dag, int T_init, int S_init, double limit);
        double ProbaSol(Node node);
        void displaySA();
};



#endif //PROJETSEMESTRE_SA_H
