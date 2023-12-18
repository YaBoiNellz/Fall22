//Darnell Chambers Gordon
#include <iostream>
#include <vector>
#include <string>

#include "graph.h"

using namespace std;

int pathfindDriver(int argc, char **argv) {

    // creating the graph
    graph g(argv[1]);
    // running dijkstra algorithm from given vertex
    g.dijkstra(std::stoi(argv[2]));

    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
		return 0;
    }

    pathfindDriver(argc, argv);

    return 0;
}

