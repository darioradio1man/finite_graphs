#include <Graph.h>

int main()
{
    //Graph graph;
	//graph.readGraph("input.txt");
	//graph.transformToAdjList();
	//graph.addEdge(1, 6, 1);
	//graph.transformToListOfEdges();
	//graph.removeEdge(1, 1);
	//graph.transformToAdjMatrix();
	//graph.writeGraph("output.txt");
	
	//Graph graph = Graph(0);
	//graph.readGraph("input.txt");

	//vector<int> circuit1 = graph.getEuleranTourFleri();
	//vector<int> circuit2 = graph.getEuleranTourEffective();

	//lab3
	//cout << "Eulerian tour using Fleury's algorithm:" << endl;
	//for (int i = 0; i <  circuit1.size(); i++)
	//	cout << circuit1[i] + 1 << " ";
	//cout << "\n\n";
	//cout << "Eulerian tour using an effective algorithm:" << endl;
	//for (int i = 0; i < circuit2.size(); i++)
	//	cout << circuit2[i] + 1 << " ";

	//cin.get();
	
	
	//lab4
	Graph graph = Graph(0);
	graph.readGraph("bipart.txt");

	vector<char> marks;
	int i = graph.checkBipart(marks);
	if (i != -1)
		cout << "True, " << i << endl;
	else
		cout << "False" << endl;

	vector<pair<int,int>> x = graph.getMaximumMatchingBipart();
	
	for (int i = 0; i < x.size(); i++)
		cout << "(" << x[i].first << ", " << x[i].second << ")" << endl;

	cin.get();
	return 0;
}
