#include <Graph.h>

int main()
{
    Graph graph;
	graph.readGraph("input.txt");
	graph.transformToAdjList();
	graph.addEdge(1, 6, 1);
	//graph.transformToListOfEdges();
	graph.removeEdge(1, 1);
	//graph.transformToAdjMatrix();
	graph.writeGraph("output.txt");
    return 0;
}
