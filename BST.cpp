#include <string>
#include <fstream>
#include <cctype>
#include <iostream>
#include <vector>
using namespace std;

//alphabetically store using ascii values to determine position(capital letters should not affect)

class Node
{
public:
	Node(string word)
    {
		this->word = word;
        this->frequency = 1;
        this-> parentNode = NULL;
		this->leftChild = NULL;
		this->rightChild = NULL;
	}
	string word;
    int frequency;
    Node* parentNode; 
	Node* leftChild;
	Node* rightChild;

};


Node* addNewNode(Node* node, string word)
{
    
    if(node==NULL) //creates the node if there are no node present at this point
    {
        node = new Node(word);
        return node;
    }
    char asciiFinder, asciiCompare;
    int letterCounter = 0;
    for(letterCounter; letterCounter < word.size(); letterCounter++)
    {
        
        
        asciiFinder = word[letterCounter]; //get the first letter of the word in question
        asciiFinder = tolower(asciiFinder); //convert to lower case (I consider "the" and The" to be the same word)
    
        
        asciiCompare = node->word[letterCounter]; //get the 1st letter of the parent node
        asciiCompare = tolower(asciiCompare);
        
        
        
        
        if(int(asciiCompare) > int(asciiFinder)) //the further down the alphabet, the higher the ascii char
        { 
            if(node->leftChild==NULL) //if there isnt a left child
            {
                node->leftChild = new Node(word); //then this word becomes the left child
                node->leftChild->parentNode = node; //pointer to its parent
                break;
            }
            else
            {
                addNewNode(node->leftChild, word);
                break;
            }
        }
        
        
        else if(int(asciiCompare) < int(asciiFinder))
        {
            if(node->rightChild==NULL)
            {
                node->rightChild = new Node(word);
                node->rightChild->parentNode = node;
                break;
            }
            else
            {
                addNewNode(node->rightChild, word);
                break;
            }
        }
        
        
        else if(int(asciiCompare) == int(asciiFinder) && word.size() == node->word.size() == letterCounter-1) //if the letter is the same and its the last letter of both, add one to frequency at this node
        {
            node->frequency++; //add 1 to frequency as this word was already present
            break;
        }
    }
    
    return node;
}

Node* constructTree()
{
    ifstream textFile;
    textFile.open("textFile.txt");
    string word;
    bool firstWord = true;
    Node* binaryTree;
    
    
    while(textFile >> word) //word would equal the line in the file - change to word!! HERE
    {   
        if(firstWord)
        {
            binaryTree = addNewNode(0, word); //as from moodle link
        }
        else if(word!="")
        {
            addNewNode(binaryTree, word); //first parameter should be the first parent node, not sure how to tho ;( buut example just passes 0 so :ascii shrug:
        }
        firstWord = false;
    }
    textFile.close();
    
    return binaryTree;
    
}


bool findWord(Node* node, string word)
{
    char asciiFinder, asciiCompare;
    int letterCounter = 0;
    cout << "Node observed: " << node->word << " VS " << word << " target Node" << endl;
    if(node->word==word)
    {
        return true;
    }
    for(letterCounter; letterCounter < word.size(); letterCounter++)
    {
        asciiFinder = word[letterCounter]; //get the first letter of the word in question
        asciiFinder = tolower(asciiFinder); //convert to lower case (I consider "the" and The" to be the same word)   
        asciiCompare = node->word[letterCounter]; //get the 1st letter of the parent node
        asciiCompare = tolower(asciiCompare);

        if(int(asciiCompare) > int(asciiFinder)) //the further down the alphabet, the higher the ascii char
        { 
            if(node->leftChild==NULL) //if there isnt a left child
            {
                return false;
            }
            else
            {
                cout << "Going left" << endl;
                return findWord(node->leftChild, word);
            }
        }  
        else if(int(asciiCompare) < int(asciiFinder))
        {
            if(node->rightChild==NULL)
            {
                return false;
            }
            else
            {
                cout << "Going right" << endl;
                return findWord(node->rightChild, word);
            }
        }     
    }
}

void preOrder(Node* binaryTree)
{

   
    
    if(binaryTree->word.empty()==false) //if there is a word present
    {
        cout << binaryTree->word << " : frequency : " << binaryTree->frequency << endl;
    }
    if(binaryTree->leftChild!=NULL) //if left child is present, do search again
    {
        preOrder(binaryTree->leftChild); //go left down the tree
    }
    if(binaryTree->rightChild!=NULL)
    {
        preOrder(binaryTree->rightChild); //go right down the tree
    }
}

int main()
{
    string target;
    Node* binaryTree;
    binaryTree = constructTree();
    preOrder(binaryTree);
    cout << "Enter the word you want to find" << endl;
    cin >> target;
    if(findWord(binaryTree, target) == true)
    {
        cout << "Word found" << endl;
    }
    else
    {
        cout << "Word not found" << endl;
    }
}