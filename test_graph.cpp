#include "graph.h"
#include <iostream>

using namespace std;

int main() {
	Graph<int> graph(5);
	graph.add_edge(0,1,1); // from, to, weight
	graph.add_edge(0,2,3);
	graph.add_edge(0,3,2);
	graph.add_edge(1,2,1);
	graph.add_edge(1,3,4);
	graph.add_edge(2,3,1);
	graph.add_edge(3,0,1);
	auto p = graph.get_shortest_paths(0);
	Graph<int>::print_paths(p);
	//for (auto& x : d) {
		//cout << x << ' ';
	//}
}
