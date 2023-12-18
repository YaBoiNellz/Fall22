#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include "binary_heap.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

// This file is for your graph implementation.
// Add everything you need in between the "ifndef and "endif" statements.
// Do not put anything outside those statements

class graph{
public:

    // constructor which reads graph from path
    graph(const std::string path){
        ifstream st;
        // open file
        st.open(path);

        std::string line;
        // get the number of vertices
        std::getline(st, line);
        auto tmp = split(line, ' ');
        int num = std::stoi(tmp[0]);

        for (int i = 0; i < num; i++){
            // creating empty adjacency list
            g.push_back({});
        }

        // writing the adjacency list
        for (int i = 0; i < num; i++){
            std::getline(st, line);
            std::vector<std::string> components = split(line, ' ');
            int v = std::stoi(components[0]);
            for (int j = 1; j < components.size(); j += 2){
                // reading vertex info
                int to = std::stoi(components[j]);
                long double w = std::stof(components[j + 1]);
                // adding edge
                add_edge(v, to, w);
            }
        }
    }

    // destructor
    ~graph() = default;

    // adding directed edge between 'from' and 'to' vertexes
    // with weight 'w'
    void add_edge(int from, int to, long double w){
        g[from - 1].push_back({w, to - 1});
    }

    // checking if 'from' and 'to' vertexes are connected
    bool is_connected(int from, int to, long double &w){
        // finding the `to` vertex in a `from` vertex neighbors
        for (int i = 0; i < g[from - 1].size(); i++){
            if (g[from - 1][i].second == to - 1) {
                w = g[from - 1][i].first;
                return true;
            }
        }
        return false;
    }

    // run dijkstra algorithm from vertex 'v'
    void dijkstra(int v){
        --v;
        // defining the binary heap
        BinaryHeap<std::pair<long double, int>> q(g.size() + 10);
        // inserting starting vertex
        q.insert({0, v});
        // create a parent array, which stores the parent vertex for each vertex in a order
        vector<int> used(g.size() + 10, -1);
        // creating the distance array and set all distances to infinity
        vector<long double> weight(g.size() + 10, 10000000);
        weight[v] = 0;
        used[v] = v;
        long double answ = 0.;
        while (!q.isEmpty()){
            // get the smallest element from the heap
            std::pair<long double, int> tmp = q.findMin();
            // delete it from the heap
            q.deleteMin();
            answ += tmp.second;
            for (int i = 0; i < g[tmp.second].size(); i++){
                // find if we can achieve a more optimal result in a distance
                std::pair <long double, int> to = g[tmp.second][i];
                // check if the new distance will be smaller
                if (weight[to.second] > weight[tmp.second] + to.first){
                    // if smaller than insert it to a binary heap
                    q.insert(to);
                    // save the vertex from which we have a minimal distance
                    used[to.second] = tmp.second;
                    // save the distance
                    weight[to.second] = weight[tmp.second] + to.first;
                }
            }
        }
        // finding the path and distance of vertexes
        for (int i = 0; i < g.size(); i++){
            std::cout << i + 1 << ": ";
            // if not inserted in a heap then we can't acheve the vertex
            if (used[i] == -1){
                std::cout << "not_possible\n";
                continue;
            }
            // reconstructing the path using used[] array which stores the parent of each vertex
            std::vector<int> path;
            int tt = i;
            while (true){
                if (tt == used[tt]) break;
                tt = used[tt];
                path.push_back(tt);
            }
            // printing the path
            for (int ii = path.size() - 1; ii >= 0; --ii){
                std::cout << path[ii] + 1 << ' ';
            }
            std::cout << i + 1 << ' ';
            // printing the distance
            std::cout << "cost: " << weight[i] << '\n';
        }
    }

    // splitting line with 'symbol'
    static std::vector<std::string> split(const std::string& line, char symbol){
        std::string res = "";
        std::vector<std::string> answ;
        for (int i = 0; i < line.size(); i++){
            // check if we need to split here
            if (line[i] == symbol) {
                answ.push_back(res);
                res = "";
            }else{
                // otherwise add the new character to our string
                res += line[i];
            }
        }
        if (res != "")
            answ.push_back(res);
        return answ;
    }

    // The adjacency list
    std::vector<std::vector<std::pair<long double, int>>> g;
};



#endif
