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
        // handle[0] = idNode
        // handle[1] = timeToExecute
        // handle[2] = currentTime
        vector<array<double, 3>> handle;

        Worker();

};

#endif //PROJETSEMESTRE_WORKER_H
