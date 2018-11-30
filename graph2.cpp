#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <map>
#include <algorithm>
using namespace std;


struct Node
{
public:
    int number;
    bool visited = false;
    vector<pair <Node*, int> > adjacenyList; //pair - one holding a pointer for the node, the other being an integer for the weight
	Node(int number)
    {
		this->number = number;
	}
};

class Graph
{
    public:
    vector<Node> graph;
    void addNode(int value) //adds a node to the graph vector
    {
        Node node = Node(value);
        graph.push_back(node);
        return;
    }
    int findPosOfNode(int value) //returns the position of the node in the vector from an input of the nodes value
    {
        for(auto counter = 0; counter<graph.size(); counter++)
        {
            if(graph[counter].number==value)
            {
                return counter;
            }
        }
        return numeric_limits<int>::max();
    }
    void addEdge(int value1, int value2, int weight) //adds an edge between 2 given values (nodes value) and adds its weight
    {
        int pos1 = findPosOfNode(value1);
        int pos2 = findPosOfNode(value2);
        Node* node = &graph[pos1]; //sets node to be a pointer to the node in the graph
        graph[pos2].adjacenyList.push_back(make_pair(node, weight)); //adds the pointer to the adjacent node
        node = &graph[pos2]; //same for the next
        graph[pos1].adjacenyList.push_back(make_pair(node, weight));
    }
    
    bool isPathNodeFinder(int value1, int value2) //returns true if there is a path
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
    
    bool isPath(Node v, Node w) //returns true if there is a path between 2 node values -- same as above but allows for recu rsion (one above resets visitedvalues)
    {
        ofstream textFile;
        string fileAdd;
        for(auto counter = 0; counter < v.adjacenyList.size(); counter++) //loop through v's adjacenyList
        {
            if(w.number == v.adjacenyList[counter].first->number) //if the node is foudn within this v's adjacency list
            {
                textFile.open("graphText.txt", std::ios_base::app); //APPENDS TO THE END OF THE FILE
                fileAdd = to_string(w.number); //ADD TO THE TEXT FILE
                textFile << fileAdd << "-";
                textFile.close();
                return true;
            }
        }
        
        for(auto counter = 0; counter < v.adjacenyList.size(); counter++)
        {
            int posOfNode = findPosOfNode(v.adjacenyList[counter].first->number); //fidn the position of hte node in the graph vector from the adjacenyList
            if(graph[posOfNode].visited==false) //only does this when the node in question hasnt already been observed
            {
                graph[posOfNode].visited=true; // sets visited to be true so its not visited again
                int posOfNode = findPosOfNode(v.adjacenyList[counter].first->number); //find the position of the node in the graph vector
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


void shortestPath(Graph g, int node, int destination) //functin prints the shortest distance number between 2 node values from a graph
{
    
    map<int, int> distance; //First integer holds the nodes number , second holds tentative weight from source
    vector<int> queue;
    int counter, neighbourNode, weight, buffer; //holds the min value in main while loop to decide minimum value
    
    distance[node] = 0;
    
    for(counter = 0; counter < g.graph.size(); counter ++) //resets the visited values
    {
         g.graph[counter].visited = false;
    }
    
    
    
    for(counter = 0; counter < g.graph.size(); counter++) 
    {
        if(g.graph[counter].number != node)
        {
            distance[g.graph[counter].number] =  (numeric_limits<int>::max())-15000; //set to equal infinity (-15000 to allow infinity + something to still be a large number)
        }
        queue.push_back(counter); //HERE COUNTER HOLDS 0,1,2,3,4... this is to mirror the g.graph vector node position in the vector
    }

    while(!queue.empty())
    {
        buffer = numeric_limits<int>::max();
        for(counter = 0; counter<queue.size(); counter++) //loops through
        {
            if(distance.find(g.graph[queue[counter]].number)->second < buffer) //to find
            {
                buffer = distance.find(g.graph[queue[counter]].number)->second; //the smallest value
                node = queue[counter]; //and sets the node in question to be that
            }
        }
        
        queue.erase(remove(queue.begin(), queue.end(), node), queue.end()); //deletes this node from the queue (uses std::algorithm)
        g.graph[node].visited = true; //USED TO REFERENCE IF IT IS NO LONGER IN THE QUEUE
        for(counter = 0; counter < g.graph[node].adjacenyList.size(); counter++)
        {
            
            neighbourNode = g.graph[node].adjacenyList[counter].first->number;
            
            if(g.graph[g.findPosOfNode(neighbourNode)].visited==true) //if already removed from the queue
            {
                continue;
            }
            
            weight = g.graph[node].adjacenyList[counter].second; //.second holds the weight of the edge
            buffer = distance.find(g.graph[node].number)->second + weight; //holds the new tentative value for weight
            if(buffer < distance.find(neighbourNode)->second) //if a smaller path is found
            {
                distance[neighbourNode] = buffer; //this becomes the new path
            }
        }
    }
    
    
    cout << "The shortest distance to the source node is :" << distance.find(destination)->second << endl;

     
}

void BFS(Graph g, int node) //Does a bredth first search on a graph from a starting node
{
    ofstream textFile;
    vector<int> queueBFS;
    int posOfNode, posOfNode2, counter;
    textFile.open("pathBFS.txt", std::ios_base::app); //open file
    
    for(auto counter = 0; counter < g.graph.size(); counter ++) //resets the visited values
    {
         g.graph[counter].visited = false;
    }
    
    posOfNode = g.findPosOfNode(node); 
    queueBFS.push_back(posOfNode); //add to the queue the node
    g.graph[posOfNode].visited = true; //set as true
    textFile << g.graph[posOfNode].number << " ";
    while(!queueBFS.empty()) //keep looping until queue is empty
    {
        posOfNode = queueBFS[0]; //get first item from queue
        queueBFS.erase(queueBFS.begin()); //and delete it from the queue
        for(counter = 0; counter<g.graph[posOfNode].adjacenyList.size(); counter ++) //loop through the nodes adjacency list
        {
            posOfNode2 = g.findPosOfNode(g.graph[posOfNode].adjacenyList[counter].first->number); //get the pos in vector of the node (from the adjacency list of last node)
            if(g.graph[posOfNode2].visited==false) //if it hasnt been visited
            {
                queueBFS.push_back(posOfNode2); //add to queue
                textFile << g.graph[posOfNode2].number << " ";
                g.graph[posOfNode2].visited = true; //set as true
            }
        }
    }
    textFile.close();
    
    
}

Graph actionDFS(Graph g, int node, int posOfNode) //allows for recursion in DFS
{
    ofstream textFile;
    g.graph[posOfNode].visited = true; //set current node as visited
    textFile.open("pathDFS.txt", std::ios_base::app); 
    textFile << node << " ";
    textFile.close();
    
    for(auto counter = 0; counter < g.graph[posOfNode].adjacenyList.size(); counter++) //for each node in this nodes adjacency list
    {
        int posOfNode2 = g.findPosOfNode(g.graph[posOfNode].adjacenyList[counter].first->number); // HAS TO BE NEW VARIABLE AS TO NOT MESS WITH THE FOR LOOP BEFORE
        if(g.graph[posOfNode2].visited==false) //if the node in question has not been visited
        {
            g = actionDFS(g, g.graph[posOfNode2].number, posOfNode2); //call this function
        }
    }
    return g;
}

bool DFS(Graph g, int firstNode) //Performs a depth first search on a graph from a starting node (returns true if connected for isConnected function)
{
    int posOfNode = g.findPosOfNode(firstNode);
    for(auto counter = 0; counter < g.graph.size(); counter ++) //resets the visited values
    {
         g.graph[counter].visited = false;
    }
    g = actionDFS(g, firstNode, posOfNode);
    
    for(auto counter2 = 0; counter2<g.graph.size(); counter2++) //if one isnt visited retur false (not connected)
    {
        if(g.graph[counter2].visited==false)
        {
            return false;
        }
    }
    return true;
}

void isConnected(Graph G) //prints whether the graph is connnected or not (uses DFS)
{
    int choice;
    cout << "Choose your starting node" << endl;
    cin >> choice;
    if(DFS(G, choice)==true)
    {
        cout << "Connected tree" << endl;
    }
    else
    {
        cout << "Unconnected tree" << endl;
    }
}

int main()
{
    
    
    Graph myGraph;
    myGraph.addNode(3);
    myGraph.addNode(5);
    myGraph.addNode(1);
    myGraph.addNode(10);
    myGraph.addNode(4);
    myGraph.addNode(7);
    myGraph.addNode(22);
    myGraph.addNode(23);
    myGraph.addEdge(3, 5, 1);
    myGraph.addEdge(10, 5, 5);
    myGraph.addEdge(10, 1, 6);
    myGraph.addEdge(1, 4, 7);
    myGraph.addEdge(3, 1, 1);
    myGraph.addEdge(7, 5, 10);
    myGraph.addEdge(7, 22, 9);
    myGraph.addEdge(7, 23, 8);
    myGraph.addEdge(4, 23, 1);

    if(myGraph.isPathNodeFinder(4, 3)==true)
    {
        cout << "There is a path" << endl;
    }
    
    isConnected(myGraph); //uses DFS anyway
    
    
    int choice;
    cout << "Choose your starting node" << endl;
    cin >> choice;
    for(auto counter = 0; counter < myGraph.graph.size(); counter ++) //resets the visited values
    {
        myGraph.graph[counter].visited = false;
    }
    BFS(myGraph, choice);
    
    
    
    shortestPath(myGraph, 10, 23);
    
}