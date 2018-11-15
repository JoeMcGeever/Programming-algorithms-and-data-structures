#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


//CURRENTLY, IT SEEMS AS IF THE NODES ADJACENCY LIST NODES DONT HAVE AN UPDATED ADJACENCY LIST
//SO JUST FIND THE NUMBER, AND SEARCH FOR IT WITHIN THE GRAPH AGAIN -_- 

struct Node
{
public:
    int number;
    bool visited = false;
    vector<Node*> adjacenyList;
	Node(int number)
    {
		this->number = number;
	}
};

class Graph
{
    public:
    vector<Node> graph;
    void addNode(int value)
    {
        Node node = Node(value);
        graph.push_back(node);
        return;
    }
    int findPosOfNode(int value)
    {
        for(auto counter = 0; counter<graph.size(); counter++)
        {
            if(graph[counter].number==value)
            {
                return counter;
            }
        }
        return 100;
    }
    void addEdge(int value1, int value2)
    {
        int pos1 = findPosOfNode(value1);
        int pos2 = findPosOfNode(value2);
        Node* node = &graph[pos1]; //sets node to be a pointer to the node in the graph
        graph[pos2].adjacenyList.push_back(node); //adds the pointer to the adjacent node
        node = &graph[pos2]; //same for the next
        graph[pos1].adjacenyList.push_back(node);
    }
    
    
};

int main()
{
    Graph myGraph;
    myGraph.addNode(3);
    myGraph.addNode(5);
    myGraph.addEdge(3, 5);
    cout << myGraph.graph[0].adjacenyList[0]->number << endl;
}