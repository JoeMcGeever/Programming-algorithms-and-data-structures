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
    
    bool isPathNodeFinder(int value1, int value2)
    {
        ofstream textFile;
        int pos1 = findPosOfNode(value1);
        int pos2 = findPosOfNode(value2);
        bool pathResult = isPath(graph[pos2], graph[pos1]);
        for(auto counter = 0; counter < graph.size(); counter ++) //resets the visited values
        {
            graph[counter].visited = false;
        }
        if(pathResult==true)
        {
            textFile.open("graphText.txt", std::ios_base::app);
            string fileAdd = to_string(value2); //add the last value to the text file as it skips in my program once its found
            textFile << fileAdd << " ";
            textFile.close();
        }
        return pathResult;
    }
    
    bool isPath(Node v, Node w)
    {
        ofstream textFile;
        string fileAdd;
        for(auto counter = 0; counter < v.adjacenyList.size(); counter++) //loop through v's adjacenyList
        {
            if(w.number == v.adjacenyList[counter]->number) //if the node is foudn within this v's adjacency list
            {
                cout << w.number << endl;
                textFile.open("graphText.txt", std::ios_base::app); //APPENDS TO THE END OF THE FILE
                fileAdd = to_string(w.number); //ADD TO THE TEXT FILE
                textFile << fileAdd << "-";
                textFile.close();
                return true;
            }
        }
        
        for(auto counter = 0; counter < v.adjacenyList.size(); counter++)
        {
            int posOfNode = findPosOfNode(v.adjacenyList[counter]->number); //fidn the position of hte node in the graph vector from the adjacenyList
            if(graph[posOfNode].visited==false) //only does this when the node in question hasnt already been observed
            {
                graph[posOfNode].visited=true; // sets visited to be true so its not visited again
                int posOfNode = findPosOfNode(v.adjacenyList[counter]->number); //find the position of the node in the graph vector
                if(isPath(graph[posOfNode], w)==true) //returns true only when the deeper level of recursion returns true for values in v's adjacency list
                {
                    textFile.open("graphText.txt", std::ios_base::app);
                    fileAdd = to_string(graph[posOfNode].number); //ADD TO THE TEXT FILE
                    textFile << fileAdd << "-";
                    textFile.close();
                    return true;
                }
            }
        }
        
        return false;

    }
    
};

int main()
{
    Graph myGraph;
    myGraph.addNode(3);
    myGraph.addNode(5);
    myGraph.addNode(1);
    myGraph.addNode(10);
    myGraph.addNode(4);
    myGraph.addEdge(3, 5);
    myGraph.addEdge(10, 5);
    myGraph.addEdge(10, 1);
    myGraph.addEdge(1, 4);
//    cout << myGraph.graph[0].adjacenyList[0]->number << endl;
    
    cout << myGraph.isPathNodeFinder(4, 3) << endl;
    
}