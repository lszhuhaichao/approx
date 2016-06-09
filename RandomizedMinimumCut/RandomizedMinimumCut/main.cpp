#include "Graph.h"
#include <stdio.h>
#include <string>

using namespace std;

#define MAX_LINE 256  
#define SOMEDATA 500000  

int main()
{
	char buf[MAX_LINE];
	int num = 100000;
	for(int i=0; i<100;i++)
	{
		FILE *fp = fopen("kargerMinCut.txt","r");
		Graph *graph = new Graph();
		while(fgets(buf, MAX_LINE, fp) != NULL)  
		{  
			char *p = strtok(buf, " \t");
			Node *node = new Node();
			node->node_id = atoi(p);
			while(p)
			{
				p=strtok(NULL, "\t");
				if(p)
				{
					if(strcmp(p,"")!=0)
					{
						int temp = atoi(p);
						node->incidence_node.push_back(temp);
						node->number_of_edges.insert(std::pair<int, int>(temp, 1));
					}
				}
			}
			graph->node_list.push_back(node);
		}
		//graph->computeEdgeList();
		int temp = graph->contraction();
		if(temp<num)
		{
			num = temp;
		}
	}
	printf("Totally, minimum Cut is %d!\n", num);
	return 0;
}