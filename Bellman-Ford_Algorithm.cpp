#include<iostream>
#include<vector>
#include<limits>
#include<stdexcept>

const int int_max = std::numeric_limits<int>::max();

struct Edge
{
	int source_;
	int destination_;
	int weight_;
};

std::vector<int> bellmanFord(std::vector<Edge>& graph, int vertices, int source) {
	std::vector<int> distance(vertices, int_max);
	distance[source] = 0;

	for (int i = 0; i < vertices - 1; ++i) {
		for (const Edge& e : graph) {
			if (distance[e.source_] != int_max && distance[e.source_] + e.weight_ < distance[e.destination_]) {
				distance[e.destination_] = distance[e.source_] + e.weight_;
			}
		}
	}

	for (const Edge& e : graph) {
		if (distance[e.source_] != int_max && distance[e.source_] + e.weight_ < distance[e.destination_]) {
			throw std::runtime_error("Graph contins negative weight cycle");
		}
	}

	return distance;
}

int main() {
	int vertices = 6;

	std::vector<Edge> graph
		= { { 0, 1, 5 }, { 0, 2, 7 }, { 1, 2, 3 },
				{ 1, 3, 4 }, { 1, 4, 6 }, { 3, 4, -1 },
				{ 3, 5, 2 }, { 4, 5, -3 } };

	std::vector<int> output;
	
	output = bellmanFord(graph, vertices, 0);
	std::cout << "Vertex  Distance from source\n";
	for (int i = 0; i < vertices; ++i) {
		std::cout << i << "\t" << output[i] << "\n";
	}

	std::cout << "Shortest path to vertice 4: " << output[4] << std::endl;

	return 0;
}