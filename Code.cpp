// C++ program for implementation of Ford Fulkerson
// algorithm
#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;
//Ford - Fulkerson Algorithm
//The following is simple idea of Ford - Fulkerson algorithm :
//1) Start with initial flow as 0(A point) and endpoint is B.
//2) While there is a augmenting path from A to B.
//Add this path - flow to flow.
//3) Return flow.
// Number of vertices in given graph
#define V 4

/* Returns true if there is a path from source 's'(point A) to sink
  't'(point B) in residual graph. Also fills parent[] to store the
  path */
bool bfs(int rGraph[V][V], int s, int t, int parent[])
{
    // Create a visited array and mark all vertices as not
    // visited
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    // Create a queue, enqueue source vertex and mark source
    // vertex as visited
    queue<int> queue;
    queue.push(s);
    visited[s] = true;
    parent[s] = -1;

    // BFS( Breadth Fist Search) Loop (see chapter 11 dstree)
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();

        for (int v = 0; v < V; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                // If we find a connection to B node,
                // then there is no point in BFS anymore We
                // just have to set its parent and can return true
                
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                queue.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    // if we didn't reach B node in BFS starting from source return false
 
    return false;
}

// Returns the maximum flow from s to t in the given graph
int fordFulkerson(int graph[V][V], int s, int t)
{   //s mark the starting point and t mark the end point index of points
    int u, v;

    // Create a residual graph and fill the residual graph
    // with given capacities in the original graph as
    // residual capacities in residual graph
    int rGraph[V]
        [V]; // Residual graph where rGraph[i][j]
             // indicates residual capacity of edge
             // from i to j (if there is an edge. If
             // rGraph[i][j] is 0, then there is not)
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int parent[V]; // This array is filled by BFS and to
                   // store path

    int max_flow = 0; // There is no flow initially

    // Augment the flow while there is path from source to
    // sink
    while (bfs(rGraph, s, t, parent)) {
        // Find minimum residual capacity of the edges along
        // the path filled by BFS. Or we can say find the
        // maximum flow through the path found.
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // update residual capacities of the edges and
        // reverse edges along the path
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        // Add path flow to overall flow
        max_flow += path_flow;
    }

    // Return the overall flow
    return max_flow;
}

// Driver program to test above functions
int main()
{
    //input graph : 
    // create like and two dim array[a][b]
    // where a is the index of the current point and b is index of next point it lead to
    // which mean array[a][b](graph[a][b]) is the flow available from point of index a to point of index b
    //since this case is a report and cannot give you a direct demo so i have created a graph to illustrates
    int graph[V][V]
        = { { 0, 6, 8, 0 }, { 0, 0, 1, 6 },
            { 0, 0, 0, 4 },  { 0, 0, 0, 0 } };

    cout << "The maximum possible flow is "
        << fordFulkerson(graph, 0, 3);// 0 is index of starting point(A) and 3 is index of endpoint(B)

    return 0;
}