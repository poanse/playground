#pragma once
#include <queue>
#include <vector>
#include <limits>
#include <iostream>

template<class Weight>
struct Edge {
	size_t from;
	size_t to;
	Weight weight;
	bool operator<(const Edge<Weight>& rhs) const {
		return weight < rhs.weight;
	}
};

template<class Weight>
class Graph {
public:
	Graph(size_t N) : adjacency_list(N) {} // N - number of vertexes
	void add_edge(size_t from, size_t to, Weight w) {
		adjacency_list[from].push_back({from, to, w});
	}
	std::vector<size_t> get_shortest_paths(size_t from); 
	std::vector<size_t> topological_sort();
	static void print_paths(const std::vector<size_t>& parents) {
		for (size_t id = 0; id < parents.size(); id++) {
			std::cout << "Path to vertex " << id << ": ";
			print_path(parents, id);
			std::cout << '\n';
		}
	}
	static void print_path(const std::vector<size_t>& parents, size_t id) {
		if (parents[id] != id) {
			print_path(parents, parents[id]);
			std::cout << "->";
		}
		std::cout << id;
	}
private:
	std::vector<std::vector<Edge<Weight>>> adjacency_list;

};

// Dijkstra's algorithm with lazy deletion from the priority queue
// O(E*logE)
template<class Weight>
std::vector<size_t> Graph<Weight>::get_shortest_paths(size_t from) {
	struct Vertex {
		size_t id;
		size_t pred;
		Weight distance;
	};
	auto comp = [](const Vertex& l, const Vertex& r)->bool { 
		return l.distance > r.distance; 
	};
	std::priority_queue<Vertex, std::vector<Vertex>, decltype(comp)> pq(comp);
	size_t V = adjacency_list.size(); // number of vertexes
	std::vector<size_t> parents(V);
	std::vector<Weight> distances(V, std::numeric_limits<Weight>::max());
	for (size_t id = 0; id < V; id++) {
		parents[id] = id;
		if (id == from) {
			pq.push({id, id, 0});
		} else {
			pq.push({id, id, std::numeric_limits<Weight>::max()});
		}
	};
	while (!pq.empty()) {
		auto vertex = pq.top();
		pq.pop();
		if (parents[vertex.id] == vertex.id) {
			parents[vertex.id] = vertex.pred;
			distances[vertex.id] = vertex.distance;
			for (const auto& edge : adjacency_list[vertex.id]) {
				Weight candidate_distance = vertex.distance + edge.weight;
				if (distances[edge.to] > candidate_distance) {
					pq.push({edge.to, edge.from, candidate_distance});
				}
			}
		}
	}
	return parents; // could also return distances as a struct or pair
}
