#include "Graph.h"

Graph::Graph()
{
    //ctor
}

Graph::~Graph()
{
    //dtor
}

void Graph::readGraph(string fileName)
{
	oriented = false;
	weighted = false;
	ifstream infile(fileName);
	string line;
	string weightString, orientedString;
	int lineNumber = 0;

	while (getline(infile, line))
	{
		istringstream iss(line);
		if (lineNumber == 0)
		{
			iss >> type;
			iss >> nodeCount;
		}
		switch (type)
		{
			case 'C':
				if (lineNumber == 0)
				{
					iss >> weightString;
					if (weightString == "1") weighted = true;
					else weighted = false;
					adjMatrix = vector<vector<int>>(0);
				}
				else
				{
					vector<int> temp = vector<int>(0);
					for (unsigned i = 0; i < nodeCount; i++)
					{
						string str = "";
						iss >> str;
						int node = stoi(str);
						if (!weighted && node > 1) node = 1;
						temp.push_back(node);
					}
					adjMatrix.push_back(temp);
				}
				break;
			case 'L':
				if (lineNumber == 1)
				{
					iss >> orientedString;
					iss >> weightString;
					if (weightString == "1") weighted = true;
					else weighted = false;
					if (orientedString == "1") oriented = true;
					else oriented = false;
					if (!weighted) edgeList = vector<pair<int,int>>(0);
					else weightedEdgeList = vector<tuple<int,int,int>>(0);
				}
				else if (lineNumber > 1 && lineNumber < ((int)nodeCount + 2))
				{
					if (weighted)
					{
						vector<tuple<int,int,int>> tempVector = vector<tuple<int,int,int>>();
						string str = "";
						int node = 0, edgeWeight = 0;
						while(iss)
						{
							iss >> str;
							node = stoi(str);
							if (node == edgeWeight) break;
							iss >> str;
							edgeWeight = stoi(str);
							tuple<int,int,int> tempTuple = tuple<int,int,int>(lineNumber-1, node, edgeWeight);
							tempVector.push_back(tempTuple);
						}
						weightedAdjList.push_back(tempVector);
					}
					else
					{
						vector<pair<int,int>> tempVector = vector<pair<int,int>>();
						string str = "";
						int node = 0;
						while(iss)
						{
							iss >> str;
							if (node == stoi(str)) break;
							node = stoi(str);
							pair<int,int> tempPair = pair<int,int>(lineNumber-1, node);
							tempVector.push_back(tempPair);
						}
						adjList.push_back(tempVector);
					}
				}
				break;
			case 'E':
				if (lineNumber == 1)
				{
					iss >> orientedString;
					iss >> weightString;
					if (weightString == "1") weighted = true;
					else weighted = false;
					if (orientedString == "1") oriented = true;
					else oriented = false;
					if (!weighted) adjList = vector<vector<pair<int,int>>>(0);
					else weightedAdjList = vector<vector<tuple<int,int,int>>>(0);
				}
				else if (lineNumber > 1)
				{
					if (weighted)
					{
						string str = "";
						int from = 0, to = 0, edgeWeight = 0;
						iss >> str;
						if (str == "") break;
						from = stoi(str);
						iss >> str;
						to = stoi(str);
						iss >> str;
						edgeWeight = stoi(str);
						tuple<int,int,int> tempTuple = tuple<int,int,int>(from, to, edgeWeight);
						weightedEdgeList.push_back(tempTuple);
					}
					else
					{
						string str = "";
						int from = 0, to = 0;
						iss >> str;
						if (str == "") break;;
						from = stoi(str);
						iss >> str;
						to = stoi(str);
						pair<int,int> tempPair = pair<int,int>(from, to);
						edgeList.push_back(tempPair);
					}
				}
				break;
		}
		lineNumber++;
	}
}

void Graph::addEdge(int from, int to, int weight)
{
	switch (type)
	{
		case 'C':
			if (!weighted) weight = 1;
			adjMatrix.at(from-1).at(to-1) = weight;
			if (!oriented)
				adjMatrix.at(to-1).at(from-1) = weight;
			break;
		case 'L':
			if (weighted)
			{
				weightedAdjList.at(from-1).push_back(tuple<int,int,int>(from, to, weight));
				if (!oriented)
					weightedAdjList.at(to-1).push_back(tuple<int,int,int>(to, from, weight));
			}
			else
			{
				adjList.at(from-1).push_back(pair<int,int>(from, to));
				if (!oriented)
					adjList.at(to-1).push_back(pair<int,int>(to, from));
			}
			break;
		case 'E':
			if (weighted)
			{
				weightedEdgeList.push_back(tuple<int,int,int>(from, to, weight));
				if (!oriented)
					weightedEdgeList.push_back(tuple<int,int,int>(to, from, weight));
			}
			else
			{
				edgeList.push_back(pair<int,int>(from, to));
				if (!oriented)
					edgeList.push_back(pair<int,int>(to, from));
			}
			break;
	}
}

void Graph::removeEdge(int from, int to)
{
	switch (type)
	{
		case 'C':
			adjMatrix.at(from-1).at(to-1) = 0;
			if (!oriented)
				adjMatrix.at(to-1).at(from-1) = 0;
			break;
		case 'L':
			if (weighted)
			{
				for (unsigned i = 0; i < weightedAdjList[from-1].size(); i++)
				{
					if (get<1>(weightedAdjList.at(from-1).at(i)) == to)
					{
						weightedAdjList.at(from-1).erase(weightedAdjList.at(from-1).begin()+i);
						break;
					}
				}
				if (!oriented)
				{
					for (unsigned i = 0; i < weightedAdjList[to-1].size(); i++)
					{
						if (get<1>(weightedAdjList.at(to-1).at(i)) == from)
						{
							weightedAdjList.at(to-1).erase(weightedAdjList.at(from-1).begin()+i);
							break;
						}
					}
				}
			}
			else
			{
				for (unsigned i = 0; i < adjList[from-1].size(); i++)
				{
					if (get<1>(adjList.at(from-1).at(i)) == to)
					{
						adjList.at(from-1).erase(adjList.at(from-1).begin()+i);
						break;
					}
				}
				if (!oriented)
				{
					for (unsigned i = 0; i < adjList[to-1].size(); i++)
					{
						if (get<1>(adjList.at(to-1).at(i)) == from)
						{
							adjList.at(to-1).erase(adjList.at(to-1).begin()+i);
							break;
						}
					}
				}
			}
			break;
		case 'E':
			if (weighted)
			{
				for (unsigned i = 0; i < weightedEdgeList.size(); i++)
				{
					if (get<0>(weightedEdgeList.at(i)) == from && get<1>(weightedEdgeList.at(i)) == to)
					{
						weightedEdgeList.erase(weightedEdgeList.begin()+i);
						break;
					}
				}
				if (!oriented)
				{
					for (unsigned i = 0; i < weightedEdgeList.size(); i++)
					{
						if (get<1>(weightedEdgeList.at(i)) == from && get<0>(weightedEdgeList.at(i)) == to)
						{
							weightedEdgeList.erase(weightedEdgeList.begin()+i);
							break;
						}
					}
				}
			}
			else
			{
				for (unsigned i = 0; i < edgeList.size(); i++)
				{
					if (get<0>(edgeList.at(i)) == from && get<1>(edgeList.at(i)) == to)
					{
						edgeList.erase(edgeList.begin()+i);
						break;
					}
				}
				if (!oriented)
				{
					for (unsigned i = 0; i < edgeList.size(); i++)
					{
						if (get<1>(edgeList.at(i)) == from && get<0>(edgeList.at(i)) == to)
						{
							edgeList.erase(edgeList.begin()+i);
							break;
						}
					}
				}
			}
			break;
	}
}

int Graph::changeEdge(int from, int to, int newWeight)
{
	if (weighted)
	{
		cout << "Fat chance." << endl;
		return 0;
	}
	int oldWeight = 0;
	switch (type)
	{
		case 'C':
			oldWeight = adjMatrix.at(from-1).at(to-1);
			adjMatrix.at(from-1).at(to-1) = newWeight;
			if (!oriented)
				adjMatrix.at(to-1).at(from-1) = newWeight;
			break;
		case 'L':
			for (unsigned i = 0; i < weightedAdjList[from-1].size(); i++)
			{
				if (get<1>(weightedAdjList.at(from-1).at(i)) == to)
				{
					oldWeight = get<2>(weightedAdjList.at(from-1).at(i));
					get<2>(weightedAdjList.at(from-1).at(i)) = newWeight;
					break;
				}
			}
			if (!oriented)
			{
				for (unsigned i = 0; i < weightedAdjList[to-1].size(); i++)
				{
					if (get<1>(weightedAdjList.at(to-1).at(i)) == from)
					{
						get<2>(weightedAdjList.at(to-1).at(i)) = newWeight;
						break;
					}
				}
			}
			break;
		case 'E':
			for (unsigned i = 0; i < weightedEdgeList.size(); i++)
			{
				if (get<0>(weightedEdgeList.at(i)) == from && get<1>(weightedEdgeList.at(i)) == to)
				{
					oldWeight = get<2>(weightedEdgeList.at(i));
					get<2>(weightedEdgeList.at(i)) = newWeight;
					break;
				}
			}
			if (!oriented)
			{
				for (unsigned i = 0; i < weightedEdgeList.size(); i++)
				{
					if (get<1>(weightedEdgeList.at(i)) == from && get<0>(weightedEdgeList.at(i)) == to)
					{
						get<2>(weightedEdgeList.at(i)) = newWeight;
						break;
					}
				}
			}
			break;
	}
	return oldWeight;
}

void Graph::transformToAdjList()
{
	switch (type)
	{
		case 'C':
			if (weighted)
			{
				weightedAdjList = vector<vector<tuple<int,int,int>>>();
				for (unsigned i = 0; i < nodeCount; i++)
				{
					vector<tuple<int,int,int>> tempVector = vector<tuple<int,int,int>>();
					for (unsigned j = 0; j < nodeCount; j++)
					{
						if (adjMatrix.at(i).at(j) != 0)
							tempVector.push_back(tuple<int,int,int>(i+1, j+1, adjMatrix.at(i).at(j)));
					}
					weightedAdjList.push_back(tempVector);
				}
			}
			else
			{
				adjList = vector<vector<pair<int,int>>>();
				for (unsigned i = 0; i < nodeCount; i++)
				{
					vector<pair<int,int>> tempVector = vector<pair<int,int>>();
					for (unsigned j = 0; j < nodeCount; j++)
					{
						if (adjMatrix.at(i).at(j) != 0)
							tempVector.push_back(pair<int,int>(i+1, j+1));
					}
					adjList.push_back(tempVector);
				}
			}
			break;
		case 'E':
			if (weighted)
			{
				weightedAdjList = vector<vector<tuple<int,int,int>>>(nodeCount);
				for (unsigned i = 0; i < weightedEdgeList.size(); i++)
				{
					int from = get<0>(weightedEdgeList.at(i));
					int to = get<1>(weightedEdgeList.at(i));
					int weight = get<2>(weightedEdgeList.at(i));
					weightedAdjList.at(from-1).push_back(tuple<int,int,int>(from, to, weight));
				}
			}
			else
			{
				adjList = vector<vector<pair<int,int>>>(nodeCount);
				for (unsigned i = 0; i < edgeList.size(); i++)
				{
					int from = get<0>(edgeList.at(i));
					int to = get<1>(edgeList.at(i));
					adjList.at(from-1).push_back(pair<int,int>(from, to));
				}
			}
			break;
	}
	type = 'L';
}

void Graph::transformToAdjMatrix()
{
	adjMatrix = vector<vector<int>>();
	for (int i = 0; i < nodeCount; i++)
		adjMatrix.push_back(vector<int>(nodeCount));

	switch (type)
	{
		case 'L':
			if (weighted)
			{
				for (unsigned int i = 0; i < nodeCount; i++)
				{
					for (unsigned int j = 0; j < weightedAdjList.at(i).size(); j++)
					{
						tuple<int,int,int> tempTuple = weightedAdjList.at(i).at(j);
						int from = get<0>(tempTuple);
						int to = get<1>(tempTuple);
						int weight = get<2>(tempTuple);
						adjMatrix.at(i).at(j) = weight;
					}
				}
			}
			else
			{
				for (unsigned int i = 0; i < nodeCount; i++)
				{
					for (unsigned int j = 0; j < adjList[i].size(); j++)
					{
						int from = adjList.at(i).at(j).first;
						int to = adjList.at(i).at(j).second;
						adjMatrix.at(from-1).at(to-1) = 1;
					}
				}
			}
			break;
		case 'E':
			if (weighted)
			{
				for (unsigned i = 0; i < weightedEdgeList.size(); i++)
				{
					int from = get<0>(weightedEdgeList.at(i));
					int to = get<1>(weightedEdgeList[i]);
					int weight = get<2>(weightedEdgeList[i]);
					adjMatrix.at(from-1).at(to-1) = weight;
				}
			}
			else
			{
				for (unsigned i = 0; i < edgeList.size(); i++)
				{
					int from = edgeList.at(i).first;
					int to = edgeList.at(i).second;
					adjMatrix.at(from-1).at(to-1) = 1;
				}
			}
			break;
	}
	type = 'C';
}

void Graph::transformToListOfEdges()
{
	if (weighted)
		weightedEdgeList = vector<tuple<int,int,int>>();
	else
		edgeList = vector<pair<int,int>>();
	switch (type)
	{
		case 'C':
			if (weighted)
			{
				for (unsigned i = 0; i < nodeCount; i++)
				{
					for (unsigned j = 0; j < nodeCount; j++)
					{
						if (adjMatrix.at(i).at(j) != 0)
							weightedEdgeList.push_back(tuple<int,int,int>(i+1, j+1, adjMatrix.at(i).at(j)));
					}
				}
			}
			else
				for (unsigned i = 0; i < nodeCount; i++)
				{
					for (unsigned j = 0; j < nodeCount; j++)
					{
						if (adjMatrix.at(i).at(j) != 0)
							edgeList.push_back(pair<int,int>(i+1, j+1));
					}
				}
			break;
		case 'L':
			if (weighted)
			{
				for (unsigned i = 0; i < nodeCount; i++)
				{
					for (unsigned j = 0; j < weightedAdjList.at(i).size(); j++)
					{
						int from = get<0>(weightedAdjList.at(i).at(j));
						int to = get<1>(weightedAdjList.at(i).at(j));
						int weight = get<2>(weightedAdjList.at(i).at(j));
						weightedEdgeList.push_back(tuple<int,int,int>(from, to, weight));
					}
				}
			}
			else
			{
				for (unsigned i = 0; i < nodeCount; i++)
				{
					for (unsigned j = 0; j < adjList.at(i).size(); j++)
					{
						int from = get<0>(adjList.at(i).at(j));
						int to = get<1>(adjList.at(i).at(j));
						edgeList.push_back(pair<int,int>(from, to));
					}
				}
			}
			break;
	}
	type = 'E';
}

void Graph::writeGraph(string fileName)
{
	ofstream file;
	file.open (fileName);

	switch (type)
	{
		case 'C':
			file << type << " " << nodeCount << " " << weighted << endl;
			for (unsigned int i = 0; i < nodeCount; i++)
			{
				for (unsigned int j = 0; j < nodeCount; j++)
				{
					if (j != (nodeCount-1))
						file << adjMatrix.at(i).at(j) << " ";
					else
						file << adjMatrix.at(i).at(j) << endl;
				}
			}
			break;
		case 'L':
			file << type << " " << nodeCount << endl;
			file << oriented << " " << weighted << endl;
			if (weighted)
			{
				for (unsigned int i = 0; i < nodeCount; i++)
				{
					for (unsigned int j = 0; j < weightedAdjList.at(i).size(); j++)
					{
						int from = get<1>(weightedAdjList.at(i).at(j));
						int weight = get<2>(weightedAdjList.at(i).at(j));
						file <<  from << " " << weight;
						if (j != (weightedAdjList.at(i).size() - 1))
							file << " ";
						else
							file << endl;
					}
				}
			}
			else
			{
				for (unsigned int i = 0; i < nodeCount; i++)
				{
					for (unsigned int j = 0; j < adjList.at(i).size(); j++)
					{
						file << adjList.at(i).at(j).second;
						if (j != (adjList.at(i).size() - 1))
							file << " ";
						else
							file << endl;
					}
				}
			}
			break;
		case 'E':
			if (weighted)
				file << type << " " << nodeCount<< weightedEdgeList.size() << endl;
			else
				file << type << " " << nodeCount<< edgeList.size() << endl;
			file << oriented << " " << weighted << endl;
			if (weighted)
			{
				for (unsigned int i = 0; i < weightedEdgeList.size(); i++)
				{
					int from = get<0>(weightedEdgeList.at(i));
					int to = get<0>(weightedEdgeList.at(i));
					int weight = get<0>(weightedEdgeList.at(i));
					file << from << " " << to << weight << endl;
				}
			}
			else
			{
				for (unsigned int i = 0; i < edgeList.size(); i++)
				{
					file << edgeList.at(i).first << " " << edgeList.at(i).second << endl;
				}
			}
			break;
	}
	file.close();
}
