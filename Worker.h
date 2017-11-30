#ifndef PROJETSEMESTRE_WORKER_H
#define PROJETSEMESTRE_WORKER_H

#include <vector>
#include <array>

using namespace std;

class Worker{
    public:
        int idNode;
        double time;
        bool work;
        // handleHistory[0] = idNode
        // handleHistory[1] = timeToExecute
        // handleHistory[2] = currentTime
        vector<array<double, 3>> handleHistory;

        Worker();

};

#endif //PROJETSEMESTRE_WORKER_H
