#ifndef GRAPH_H
#define GRAPH_H

#include<vector>

class Edge{
    int u, v;           //u is the initial, v is the terminal
    int weight;         //the weight of the edge - cost in shortest path problems and capacity in max flow problems
    int flow;           //the flow of the edge - used in max flow problems
    
    friend class Graph; //class Graph can access all private variables
public:
    Edge(int u, int v, int weight, int flow = 0){
        this->u = u;
        this->v = v;
        this->weight = weight;
        this->flow = flow;
    }
};

class Vertex{
    //variables for the Push-Relabel algorithm
    int h;              //the height of the vertex
    int excess;         //the excess flow of the vertex
    
    friend class Graph; //class Graph can access all private variables
public:
    Vertex(){
        this->h = 0;
        this->excess = 0;
    }
    Vertex(int h, int excess){
        this->h = h;
        this->excess = excess;
    }
};

class Graph{
    int V;                              //number of vertices
    std::vector<Vertex> vertList;       //list of vertices in the graph
    std::vector<Edge> edgeList;         //list of edges in the graph
public:
    Graph(int V);
    bool addEdge(int u, int v, int weight);
    std::vector<std::vector<int>> toMatrix();
};

Graph::Graph(int V){
    this->V = V;

    //initialize vertices
    for(int i = 0; i < V; i++){
        vertList.push_back(Vertex());
    }
}

bool Graph::addEdge(int u, int v, int weight){
    //Add an edge to the graph
    //If the intial or terminal vertex is invalid, return false
    if (u < 0 || v < 0 || u >= this->V || v >= this->V) return false;
    else {
    edgeList.push_back(Edge(u, v, weight));
    return true;
    }
}

std::vector<std::vector<int>> Graph::toMatrix(){
    //convert the graph into matrix form and return it
    //initialize matrix
    std::vector<std::vector<int>> ret(this->V, std::vector<int>(this->V, 0));
    //if there are more than 1 edge in the same direction between 2 vertices, the total weight of such edges is recorded in the matrix
    for(auto edge : this->edgeList){
        ret[edge.u][edge.v] += edge.weight;
    }
    return ret;
}

#endif