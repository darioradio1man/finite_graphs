#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <utility>
#include <tuple>
#include <climits>
#include <algorithm>
#include "DSU.h"

using namespace std;

class Graph
{
    public:
        Graph(int);
        void readGraph(string);
        void addEdge(int, int, int);
        void removeEdge(int, int);
        int changeEdge(int, int, int);
        void transformToAdjList();
        void transformToAdjMatrix();
        void transformToListOfEdges();
        void writeGraph(string);
        
        Graph getSpaingTreePrima();
        Graph getSpaingTreeKruskal();
        Graph getSpaingTreeBoruvka();
        
        //labs 3,4
        int checkEuler(bool &circleExist);
	    vector<int> getEuleranTourFleri();
	    vector<int> getEuleranTourEffective();
	    bool empty();
    	bool fleury(vector<int>);

	    int checkBipart(vector<char> &marks); // Проверка графа на двудольность.
    	vector<pair<int,int> > getMaximumMatchingBipart(); // Алгоритм Куна.
    	bool kuhn(int v); // Вспомогательная функция для алгоритма Куна.

    private:
        char type; // текущий тип отображения
        unsigned int nodeCount; // количество вершин графа
        bool weighted, oriented; // взвешенный/невзвешенный, ориентированный/неориентированный

        vector<vector<int>> adjMatrix; // матрица смежности
        vector<vector<pair<int,int>>> adjList; // невзвешенный список смежности
        vector<vector<tuple<int,int,int>>> weightedAdjList; // взвешенный список смежности
        vector<pair<int,int>> edgeList; // список ребер
        vector<tuple<int,int,int>> weightedEdgeList; // взвшенный список ребер
};

#endif // GRAPH_H
