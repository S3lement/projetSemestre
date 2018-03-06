#ifndef PROJETSEMESTRE_SA_H
#define PROJETSEMESTRE_SA_H


#include "node.h"
#include "Dag.h"

class SA{
    public:

        SA();
        void solveSA(Dag dag, int T_init, int S_init);
        double ProbaSol(Node node);
        Node newSol(vector<int> nodeReady);
};



#endif //PROJETSEMESTRE_SA_H
