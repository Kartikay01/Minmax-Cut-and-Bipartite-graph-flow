/**

@file maxflow.cpp
@brief This file contains the implementation of the Ford-Fulkerson algorithm for finding the maximum flow in a flow network
@author [Insert Your Name Here]
@date [Insert Date Here]
*/
#include <iostream>
#include <bits/stdc++.h>
#include <chrono>
#include <fstream>
#include <cstring>

using namespace std::chrono;

using namespace std;

const int INF = 1e9;

int N, M; // N = number of vertices in left set, M = number of vertices in right set
vector<int> adj[100]; // adjacency list for graph
int capacity[100][100]; // capacity matrix for graph

/**

@brief Find the bottleneck flow in an augmenting path using BFS

@param source The source vertex

@param sink The sink vertex

@param parent A vector to store the BFS tree

@return The bottleneck flow in the augmenting path (or 0 if no augmenting path exists)
*/
int bfs(int source, int sink, vector<int>& parent) {
fill(parent.begin(), parent.end(), -1); // initialize parent vector to -1
parent[source] = -2; // mark source as visited

queue<pair<int, int>> q; // store (vertex, flow) pairs in the queue
q.push({source, INF}); // push the source vertex with infinite flow

while (!q.empty()) {
int u = q.front().first;
int flow = q.front().second;
q.pop();
 for (int v : adj[u]) {
     if (parent[v] == -1 && capacity[u][v] > 0) { // if v is not visited and there is residual capacity from u to v
         parent[v] = u; // set u as the parent of v in the BFS tree
         int new_flow = min(flow, capacity[u][v]); // update flow to be the minimum of the current flow and the residual capacity
         if (v == sink) {
             return new_flow; // if sink is reached, return the bottleneck flow
         }
         q.push({v, new_flow}); // add the (vertex, flow) pair to the queue
     }
 }
}
return 0; // if sink is not reached, return 0
}

/**

@brief Find the maximum flow in a flow network using the Ford-Fulkerson algorithm

@param source The source vertex

@param sink The sink vertex

@return The maximum flow in the flow network
*/
int maxflow(int source, int sink) {
int flow = 0;
vector<int> parent(N+M+2); // vector to store the BFS tree

while (true) {
int bottleneck = bfs(source, sink, parent); // find the bottleneck flow in the current augmenting path
if (bottleneck == 0) {
break; // if sink is not reachable from source, terminate the algorithm
}
flow += bottleneck; // add bottleneck flow to total flow
 // update residual capacities along the augmenting path
 for (int v = sink; v != source; v = parent[v]) {
     int u = parent[v];
     capacity[u][v] -= bottleneck;
     capacity[v][u] += bottleneck;
 }
}
return flow;
}

/**

@brief Computes the maximum bipartite matching for a given graph using the Ford-Fulkerson algorithm

@return the size of the maximum matching
*/
int max_bipartite_matching() {
int source = 0, sink = N + M + 1;

// connect left vertices to source with capacity 1
for (int i = 1; i <= N; i++) {
adj[source].push_back(i);
adj[i].push_back(source);
capacity[source][i] = 1;
}

// connect right vertices to sink with capacity 1
for (int i = N+1; i <= N+M; i++) {
adj[i].push_back(sink);
adj[sink].push_back(i);
capacity[i][sink] = 1;
}

// run maxflow algorithm
return maxflow(source, sink);
}

/**

@brief Reads the input graph from a file and computes its maximum bipartite matching using Ford-Fulkerson algorithm.
*/
int main() {

std::string line;
std::ifstream myfile("input2.txt"); // replace example.txt with your file name

// initialize capacity matrix to 0
memset(capacity, 0, sizeof(capacity));

if (myfile.is_open()) { // check if file is open
std::getline(myfile,line);

int fi=line.find(' ');
string sl1=line.substr(0,fi);string sl2=line.substr(fi+1);
N=stoi(sl1);M=stoi(sl2);
 while (std::getline(myfile, line)) { // read each line using getline
    // std::cout << line << std::endl; // print the line
     int u, v;
    int fi=line.find(' ');
    string sl1=line.substr(0,fi);string sl2=line.substr(fi+1);
    //x.push_back(stoi(sl1));y.push_back(stod(sl2));
    u=stoi(sl1);v=stoi(sl2);
    adj[u].push_back(N+v); // add edge from u in left set to v in right set
 adj[N+v].push_back(u); // add reverse edge from v to u
 capacity[u][N+v] = 1; // set capacity of edge to 1

    
 }
 myfile.close(); // close the file
}
else {
std::cout << "Unable to open file";
}

//starting timer
auto start = high_resolution_clock::now();
// find maximum bipartite matching using Ford-Fulkerson algorithm

int max_matching = max_bipartite_matching();

auto stop = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(stop - start);

cout << "Time taken by algorithm: "
<< duration.count() << " microseconds" << endl;
//ending timer and printing it
//printing the decomposition just for our reference

    cout << "Maximum Bipartite Matching: " << max_matching << endl;

    return 0;
}















