#include "Graph.h"
#include<time.h>

Edge::Edge()
{
	this->edge_id = 0;
	this->end1 = 0;
	this->end2 = 0;
}

Node::Node()
{
	this->node_id = 0;
	this->incidence_node.clear();
}

Graph::Graph()
{
	this->edge_list.clear();
	this->node_list.clear();
}

int Graph::contraction()
{
	while(this->node_list.size()>2)
	{
		int id1, id2;
		this->randomSelectEdge(&id1, &id2);
		this->copyIncidenceInfo(id1, id2);
		this->deleteNodebyId(id2);
	}

	printf("Minimum Cut is %d!\n", this->node_list.at(0)->number_of_edges.at(this->node_list.at(1)->node_id));
	return this->node_list.at(0)->number_of_edges.at(this->node_list.at(1)->node_id);
}

int Graph::randomSelect()
{
	return random(this->edge_list.size())+1;
}

void Graph::computeEdgeList()
{

}

bool Graph::isEdgeExist(int end1, int end2)
{
	vector<Edge*>::iterator edge;
	for(edge = this->edge_list.begin();edge!=this->edge_list.end();edge++)
	{
		int temp_end1 = (*edge)->end1;
		int temp_end2 = (*edge)->end2;
		if((temp_end1==end1 && temp_end2==end2)||
			(temp_end1==end2 && temp_end2==end1))
		{
			return true;
		}
	}
	return false;
}

void Graph::deleteNodebyId(unsigned int node_id)
{
	vector<Node*>::iterator node;
	for(node = this->node_list.begin();node != this->node_list.end();node++)
	{
		if((*node)->node_id == node_id)
		{
			this->node_list.erase(node);
			return;
		}
	}
}

void Graph::randomSelectEdge(int *id1, int *id2)
{
	srand((int)time(0));
	int end1 = random(this->node_list.size());
	Node *node1 = this->node_list.at(end1);
	int end2 = random(node1->incidence_node.size());
	*id1 = this->node_list.at(end1)->node_id;
	*id2 = this->node_list.at(end1)->incidence_node.at(end2);
}


Node* Graph::getNodebyId(int id)
{
	vector<Node*>::iterator node;
	for(node = this->node_list.begin();node != this->node_list.end();node++)
	{
		if((*node)->node_id == id)
		{
			return (*node);
		}
	}
	return NULL;
}

void Graph::copyIncidenceInfo(int dst, int src)
{
	Node *node_src = this->getNodebyId(src);
	Node *node_dst = this->getNodebyId(dst);
	vector<int>::iterator inc;

	for(inc=node_src->incidence_node.begin();inc!=node_src->incidence_node.end();inc++)
	{
		Node *node_inc = this->getNodebyId(*inc);
		//printf("dst, src, inc: %d, %d, %d\n",dst, src, *inc);
		if((*inc) != dst)
		{
			if(node_dst->hasIncidence((*inc)))
			{
				node_dst->number_of_edges.at((*inc)) = node_dst->number_of_edges.at((*inc))+node_src->number_of_edges.at((*inc));
				node_inc->number_of_edges.at(dst) = node_dst->number_of_edges.at((*inc));
				node_inc->deleteIncidenceById(src);
			}
			else
			{
				node_dst->incidence_node.push_back((*inc));
				node_dst->number_of_edges.insert(std::pair<int,int>((*inc), node_src->number_of_edges.at((*inc))));
				node_inc->incidence_node.push_back(dst);
				node_inc->number_of_edges.insert(std::pair<int,int>(dst, node_dst->number_of_edges.at((*inc))));
				node_inc->deleteIncidenceById(src);
			}
		}
	}
	node_dst->deleteIncidenceById(src);
}

bool Node::hasIncidence(int id)
{
	vector<int>::iterator inc_id;
	for(inc_id=this->incidence_node.begin();inc_id!=this->incidence_node.end();inc_id++)
	{
		if((*inc_id)==id)
		{
			return true;
		}
	}
	return false;
}

void Node::deleteIncidenceById(int id)
{
	vector<int>::iterator inc_id;
	for(inc_id=this->incidence_node.begin();inc_id!=this->incidence_node.end();inc_id++)
	{
		if((*inc_id)==id)
		{
			this->incidence_node.erase(inc_id);
			this->number_of_edges.erase(id);
			return;
		}
	}
}

/***************
  update the information of the incidence of src
****************/
void updateIncidenceNode(int dst, int src)
{

}

void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}