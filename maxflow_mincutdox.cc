/**

@file ford_fulkerson.cpp
@brief Implementation of the Ford-Fulkerson algorithm for finding maximum flow and minimum cut in a network flow graph.
@author [Insert Your Name Here]
*/
#include <iostream>
#include <bits/stdc++.h>
#include <chrono>
#include <fstream>

using namespace std::chrono;
using namespace std;

const int INF = 1e9;

int n, s, t; // n number of nodes ,source and sink
vector<vector<int>> graph, residual_graph;

/**

@brief Adds an edge with given weight between nodes u and v in the graph.
@param u The starting node of the edge.
@param v The ending node of the edge.
@param w The weight of the edge.
*/
void add_edge(int u, int v, int w) {
graph[u][v] = w;
}
/**

@brief Performs Breadth First Search (BFS) to find the shortest augmenting path from source to sink in the residual graph.
@param parent A vector containing the parent of each node in the shortest augmenting path.
@return true if there exists an augmenting path, false otherwise.
*/
bool bfs(vector<int>& parent) {
fill(parent.begin(), parent.end(), -1);
queue<int> q;
q.push(s);
parent[s] = -2;
while (!q.empty()) {
int u = q.front();
q.pop();
for (int v = 0; v < n; v++) {
if (parent[v] == -1 && residual_graph[u][v] > 0) {
parent[v] = u;
q.push(v);
}
}
}
return parent[t] != -1;
}
/**

@brief Implements the Ford-Fulkerson algorithm for finding the maximum flow in the network flow graph.
@return The maximum flow in the network flow graph.
*/
int ford_fulkerson() {
int max_flow = 0;
vector<int> parent(n);
while (bfs(parent)) {
int flow = INF;
for (int v = t; v != s; v = parent[v]) {
int u = parent[v];
flow = min(flow, residual_graph[u][v]);
}
for (int v = t; v != s; v = parent[v]) {
int u = parent[v];
residual_graph[u][v] -= flow;
residual_graph[v][u] += flow;
}
max_flow += flow;
}
return max_flow;
}
/**

@brief Performs Depth First Search (DFS) to find all nodes reachable from the source in the residual graph.
@param u The node to start DFS from.
@param visited A vector containing whether a node has been visited or not.
*/
void dfs(int u, vector<bool>& visited) {
visited[u] = true;
for (int v = 0; v < n; v++) {
if (residual_graph[u][v] > 0 && !visited[v]) {
dfs(v, visited);
}
}
}

/**

@brief Find the minimum cut of a graph using Ford-Fulkerson algorithm
@param void
@return void
*/
void find_minimum_cut() {
vector<bool> visited(n);
dfs(s, visited);
cout << "Minimum cut: ";
for (int u = 0; u < n; u++) {
if (visited[u]) {
for (int v = 0; v < n; v++) {
if (!visited[v] && graph[u][v] > 0) {
cout << "(" << u << ", " << v << ") ";
}
}
}
}
cout << endl;
}
/**

@brief Main function that reads input from a file, runs the Ford-Fulkerson algorithm to find the maximum flow

and the minimum s-t cut, and prints the results along with the time taken by the algorithm.

@return 0 if program executes successfully.
*/
int main() {

     std::string line;
    std::ifstream myfile("input1.txt"); // replace example.txt with your file name
   


    /*cin >> n;
    graph.assign(n, vector<int>(n, 0));
    residual_graph.assign(n, vector<int>(n, 0));
    int m, u, v, w;//m number of edges , edge between u to v with cost w
    cin >> m >> s >> t;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        add_edge(u, v, w);
        residual_graph[u][v] = w;
    }*/

       if (myfile.is_open()) { // check if file is open
    std::getline(myfile,line);

    int fi=line.find(' ');
           string sl1=line.substr(0,fi);string sl2=line.substr(fi+1);
            int fi1=sl2.find(' ');
           string sl22=sl2.substr(0,fi1);
           string sl33=sl2.substr(fi1+1);
           n=stoi(sl1);s=stoi(sl22);t=stoi(sl33);
             //  initialize the graph and residual graph
            graph.assign(n, vector<int>(n, 0));
    residual_graph.assign(n, vector<int>(n, 0));

        while (std::getline(myfile, line)) { // read each line using getline
           // std::cout << line << std::endl; // print the line
            int u, v,w;
           int fi=line.find(' ');
           string sl1=line.substr(0,fi);string sl2=line.substr(fi+1);
           int fi1=sl2.find(' ');
           string sl22=sl2.substr(0,fi1);
           string sl33=sl2.substr(fi1+1);
           //x.push_back(stoi(sl1));y.push_back(stod(sl2));
           u=stoi(sl1);v=stoi(sl22);w=stoi(sl33);
          
             add_edge(u, v, w);
        residual_graph[u][v] = w;
           
        }
        myfile.close(); // close the file
    }
    else {
        std::cout << "Unable to open file";
    }


   

    

    //starting timer
auto start = high_resolution_clock::now();

    // run the Ford-Fulkerson algorithm
    int max_flow = ford_fulkerson();
    cout << "Maximum flow: " << max_flow << endl;

    auto stop = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(stop - start);
 
    cout << "Time taken by algorithm: "
         << duration.count() << " microseconds" << endl;
//ending timer and printing it
//printing the decomposition just for our reference

    // find the minimum st cut
    find_minimum_cut();

    return 0;
}
