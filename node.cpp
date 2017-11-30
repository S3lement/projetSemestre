#include <iostream>
#include "node.h"

using namespace std;

/**
 * Create a node
 * @param idNode
 */
Node::Node(int idNode){
    id = idNode;
    cost = 0.0;
    cptReady = 0;
    state = false;

}

/**
 * Display node
 */
void Node::displayNode() {
    cout << "id node: " << id << " time: " << cost << endl;
    for (int i = 0; i < children.size(); ++i) {
        cout << "   Children " << children[i] << endl;
    }
    for (int i = 0; i < fathers.size(); ++i) {
        cout << "   fathers " << fathers[i] << endl;
    }
}