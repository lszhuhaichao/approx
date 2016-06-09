#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <map>

using namespace std;

#define random(x) (rand()%x)

class Edge
{
public:
	Edge();
	unsigned int edge_id;
	unsigned int end1, end2;
	unsigned int numberof_edges;
};

class Node
{
public:
	~Node()
	{

	}
	Node();
	bool hasIncidence(int id);
	void deleteIncidenceById(int id);
	unsigned int node_id;
	vector<int> incidence_node;
	map<int, int> number_of_edges;;
};

class Graph
{
private:
	bool isEdgeExist(int end1, int end2);
	int randomSelect();
public:
	Graph();
	vector<Node*> node_list;
	vector<Edge*> edge_list;
	int contraction();
	void copyIncidenceInfo(int dst, int src);
	void updateIncidenceNode(int dst, int src);

	Node* getNodebyId(int id);
	void deleteNodebyId(unsigned int node_id);
	void randomSelectEdge(int *end1, int *end2);

	void computeEdgeList();
};

void swap(int *a, int *b);

#endif