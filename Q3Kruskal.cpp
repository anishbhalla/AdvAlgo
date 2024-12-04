#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Class to represent an edge
class Edge {
public:
    int src, dest, weight;

    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

// Class to represent a graph
class Graph {
private:
    int vertices; // Number of vertices
    vector<Edge> edges; // List of all edges in the graph

    // Function to find the root (or representative) of a node
    int findRoot(vector<int>& parent, int node) {
        // If the node is not its own parent, follow the parent chain
        if (parent[node] != node) {
            parent[node] = findRoot(parent, parent[node]); // Path compression
        }
        return parent[node];
    }

    // Function to join (union) two sets by rank
    void unionSets(vector<int>& parent, vector<int>& rank, int root1, int root2) {
        // Attach the smaller tree under the larger tree
        if (rank[root1] < rank[root2]) {
            parent[root1] = root2;
        } else if (rank[root1] > rank[root2]) {
            parent[root2] = root1;
        } else {
            parent[root2] = root1;
            rank[root1]++;
        }
    }

public:
    // Constructor to initialize the graph with a given number of vertices
    Graph(int v) : vertices(v) {}

    // Function to add an edge to the graph
    void addEdge(int src, int dest, int weight) {
        edges.push_back(Edge(src, dest, weight));
    }

    // Function to find the Minimum Spanning Tree (MST) using Kruskal's algorithm
    vector<Edge> kruskalMST() {
        // Sort all edges by weight (smallest to largest)
        sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
            return a.weight < b.weight;
        });

        vector<int> parent(vertices); // Parent array for Union-Find
        vector<int> rank(vertices, 0); // Rank array for Union-Find

        // Initialize each vertex to be its own parent (single-node set)
        for (int i = 0; i < vertices; i++) {
            parent[i] = i;
        }

        vector<Edge> mst; // To store the edges in the MST

        // Iterate through all edges
        for (const Edge& edge : edges) {
            int rootSrc = findRoot(parent, edge.src); // Find root of the source
            int rootDest = findRoot(parent, edge.dest); // Find root of the destination

            // If they belong to different sets, include this edge in MST
            if (rootSrc != rootDest) {
                mst.push_back(edge);
                unionSets(parent, rank, rootSrc, rootDest); // Join the sets
            }

            // If we've found enough edges for the MST, stop early
            if (mst.size() == vertices - 1) {
                break;
            }
        }

        return mst;
    }
};

int main() {
    int vertices, edgesCount;
    cout << "Enter the number of vertices: ";
    cin >> vertices;
    cout << "Enter the number of edges: ";
    cin >> edgesCount;

    Graph graph(vertices);

    cout << "Enter the edges (source destination weight):\n";
    for (int i = 0; i < edgesCount; i++) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph.addEdge(src, dest, weight);
    }

    // Find the MST
    vector<Edge> mst = graph.kruskalMST();

    // Display the MST
    cout << "\nMinimum Spanning Tree edges (source - destination : weight):\n";
    int totalWeight = 0;
    for (const Edge& edge : mst) {
        cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl;
        totalWeight += edge.weight;
    }
    cout << "Total weight of MST: " << totalWeight << endl;

    return 0;
}
