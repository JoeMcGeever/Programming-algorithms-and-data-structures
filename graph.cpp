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
    
    
    
    
    bool doesNodesExist(int valueOne, int valueTwo)
    {
        for(auto counter = 0; counter<graph.size(); counter++)
        {
            if(graph[counter].number==valueOne) //find the value in the vector of nodes in this object of class
            {
                oneSet = true;
            }
            if(graph[counter].number==valueTwo) //find the value
            {
                twoSet = true;
            }
        }
        if(oneSet == true && twoSet == true)
        {
            return true;
        }
        return false;
    }
    
    
    
    
    void addEdge(int valueOne, int valueTwo)
    {
        if(doesNodesExist(valueOne, valueTwo)!= true)
        {
            cout << "One or more nodes does not exist" << endl;
            return;
        }
        for(auto counter = 0; counter<graph.size(); counter++)
        {
            if(graph[counter].number==valueOne) //find the value in the vector of nodes in this object of class
            {
                posOfOne = counter; //store the node position within the graph
            }
            if(graph[counter].number==valueTwo) //find the value
            {
                posOfTwo = counter; //and for the second
            }
        }
        graph[posOfOne].adjacenyList.push_back(graph[posOfTwo]); //ADD THE SECOND VALUE TO THE ADJACENCY LIST OF THE FIRST
        graph[posOfTwo].adjacenyList.push_back(graph[posOfOne]); //SAME AS ABOVE BUT 1 IS GOIN IN 2
    }
    
    
    
    
    bool isPath(int v,int w) //v = source, w = destination
    {
        for(auto counter = 0; counter<graph.size(); counter++)
        {
            if(graph[counter].number==v) //find the value in the vector of nodes in this object of class
            {
                posOfOne = counter; //store the node position within the graph
                graph[posOfOne].visited = true; //set to true as it has been visited
            }
        }
        
        for(auto counter = 0; counter < graph[posOfOne].adjacenyList.size(); counter ++)
        {
            if(graph[posOfOne].adjacenyList[counter].number == w) //if the destination is in the adjacenyList
            {
                cout << "FOUND YA" << endl;
                return true;
            }
        }
        
              
        
        
        for(auto counter = 0; counter < graph[posOfOne].adjacenyList.size(); counter ++)
        {
            
           if(graph[posOfOne].adjacenyList[counter].visited==false)
           {
               cout << graph[posOfOne].adjacenyList[counter].number << "     " << w << endl;
               isPath(graph[posOfOne].adjacenyList[counter].number, w);
           }
        }
    
    return false;
    }
    
};






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
    myGraph.addEdge(5, 2);
    myGraph.addEdge(2, 1);
    
    
    cout << myGraph.isPath(3,1) << endl; //DOESNT WORK
   
}