#include <string>
#include <iostream>
#include <vector>
using namespace std;

//ADD A NODE MEANS ADDING IT TO THE LIST OF NODES IN THE GRAPH CLASS, ADDING AN EDGE MEANS UPDATING THE ADJACENCY LIST OF BOTH NODES

struct Node
{
public:
    int number;
    vector<Node> adjacenyList;
	Node(int number)
    {
		this->number = number;
	}
};

class graph
{
    public:
    vector<Node> graph;
    int posOfOne, posOfTwo;
    bool oneSet = false, twoSet = false; //used to see if the nodes are present
    void addNode(int value)
    {
        graph.push_back(value);
        return;
    }
    void addEdge(int valueOne, int valueTwo)
    {
        for(auto counter = 0; counter<graph.size(); counter++)
        {
            if(graph[counter].number==valueOne) //find the value in the vector of nodes in this object of class
            {
                posOfOne = counter; //store the node position within the graph
                oneSet = true;
            }
            if(graph[counter].number==valueTwo) //find the value
            {
                posOfTwo = counter; //and for the second
                twoSet = true;
            }
        }
        if(oneSet==true && twoSet==true) //if they exist on the graph
        {
            graph[posOfOne].adjacenyList.push_back(graph[posOfTwo]); //ADD THE SECOND VALUE TO THE ADJACENCY LIST OF THE FIRST
            graph[posOfTwo].adjacenyList.push_back(graph[posOfOne]); //SAME AS ABOVE BUT 1 IS GOIN IN 2
            
            
            return;
        }
        else
        {
            cout << "One or more nodes not present" << endl;
            return;
        }
    }
};


bool isPath(int v,int w)
{
    vector<int> nodeVisited;
    
    
}



int main()
{
    graph myGraph;
    
    myGraph.addNode(1); //0
    myGraph.addNode(2); //1
    myGraph.addNode(3); //etc
    myGraph.addNode(4);
    myGraph.addNode(5);
    myGraph.addNode(6);
    myGraph.addNode(7);
    myGraph.addNode(8);
    
    myGraph.addEdge(3, 5);
    myGraph.addEdge(2, 1);
    
    cout << myGraph.graph[4].adjacenyList[0].number << endl;
   
}