#include <string>
#include <iostream>
#include <vector>
using namespace std;

struct Node
{
public:
    int number;
    vector<Node*> edge;
	Node(int number)
    {
		this->number = number;
	}
    void addEdge(Node* node)
    {
        this->edge.push_back(node);
    }
};




bool isPath(int v,int w)
{
    vector<int> nodeVisited;
    
    
}

int main()
{
    vector<Node*> graph;
    Node sourceNode(2);
    Node nodeOne(5);
    cout << sourceNode.number << endl;
    cout << nodeOne.number << endl;
    
    
}