#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Class to represent an Edge
class Edge {
public:
    int src, dest, weight;
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

// Class to represent the Graph
class Graph {
private:
    int vertices; // Number of vertices
    vector<Edge> edges; // List of edges

public:
    // Constructor to initialize the graph
    Graph(int v) : vertices(v) {}

    // Method to add an edge to the graph
    void addEdge(int src, int dest, int weight) {
        edges.emplace_back(src, dest, weight);
    }

    // Bellman-Ford algorithm implementation
    bool bellmanFord(int source) {
        vector<int> distance(vertices, INT_MAX); // Distance array
        distance[source] = 0; // Distance to source is 0

        // Relax all edges (vertices - 1) times
        for (int i = 0; i < vertices - 1; i++) {
            for (const Edge& edge : edges) {
                int u = edge.src;
                int v = edge.dest;
                int weight = edge.weight;
                if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                }
            }
        }

        // Check for negative-weight cycles
        for (const Edge& edge : edges) {
            int u = edge.src;
            int v = edge.dest;
            int weight = edge.weight;
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                cout << "Graph contains a negative-weight cycle.\n";
                return false;
            }
        }

        // Print results
        cout << "Vertex\tDistance from Source\n";
        for (int i = 0; i < vertices; i++) {
            cout << i << "\t\t" << (distance[i] == INT_MAX ? "INF" : to_string(distance[i])) << endl;
        }

        return true;
    }
};

int main() {
    int vertices, edgesCount, source;

    cout << "Enter the number of vertices: ";
    cin >> vertices;
    cout << "Enter the number of edges: ";
    cin >> edgesCount;

    // Create the graph
    Graph graph(vertices);

    // Add edges to the graph
    cout << "Enter each edge as: source destination weight\n";
    for (int i = 0; i < edgesCount; i++) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph.addEdge(src, dest, weight);
    }

    // Input the source vertex
    cout << "Enter the source vertex: ";
    cin >> source;

    // Run Bellman-Ford algorithm
    if (!graph.bellmanFord(source)) {
        cout << "The algorithm could not complete due to a negative-weight cycle.\n";
    }

    return 0;
}
