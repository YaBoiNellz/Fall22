//Darnell Chambers Gordon
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "graph.h"

using namespace std;

int graphTestDriver(int argc, char **argv) {
    
    // Begin your code here. Feel free to add any helper functions or classes you need,
    // as long as we only have to call this function to run the specified assignment.

    std::string graph_file = argv[1];
    std::string adj_list_file = argv[2];

    // creating the graph
    graph g(graph_file);
    std::ifstream adj(adj_list_file);

    std::string line;
    while (std::getline(adj, line)){
        auto tmp = graph::split(line, ' ');
        int a = std::stoi(tmp[0]);
        int b = std::stoi(tmp[1]);
        long double w = 0.;
        // checking ig the 'a' and 'b' vertexes are connected and get the weight of connection
        if (g.is_connected(a, b, w)){
            std::cout << a << ' ' << b << ": connected " << w << '\n';
        }else{
            // otherwise print not_connected
            std::cout << a << ' ' << b << ": not_connected\n";
        }
    }

    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_File>" << "<ADJACENCY_QUERYFILE>" << endl;
		return 0;
    }

    graphTestDriver(argc, argv);

    return 0;
}
