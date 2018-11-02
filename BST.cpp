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


void addNewNode(Node* node, string word)
{
    if(node == NULL) //creates the node if there are no node present at this point
    {
        node = new Node(word);
        return;
    }
    
    char asciiFinder, asciiCompare;
    int letterCounter = 0;
    
    for(letterCounter; letterCounter < word.size(); letterCounter++)
    {
        asciiFinder = word[letterCounter]; //get the first letter of the word in question
        tolower(asciiFinder); //convert to lower case (I consider "the" and The" to be the same word)
    
        asciiCompare = node->word[letterCounter]; //get the 1st letter of the parent node
        tolower(asciiCompare);
    
        if(int(asciiCompare) > int(asciiFinder)) //the further down the alphabet, the higher the ascii char
        { 
            if(node->leftChild->parentNode==NULL) //If the next node is empty, then set this node as the next nodes parent
            {
                node->leftChild->parentNode = node;
            }
            addNewNode(node->leftChild, word); //re-call function adding to next node, the word and 1 (represents first time this word is used)
        }
        
        
        else if(int(asciiCompare) < int(asciiFinder))
        {
            if(node->rightChild->parentNode=NULL) //If the next node is empty, then set this node as the next nodes parent
            {
                node->rightChild->parentNode = node;
            }
            addNewNode(node->rightChild, word); // same as before but to the right
        }
        
        
        else if(int(asciiCompare) == int(asciiFinder) && word.size() == node->word.size() == letterCounter-1) //if the letter is the same and its the last letter of both, add one to frequency at this node
        {
            node->frequency++; //add 1 to frequency as this word was already present
        }
    }
    
    
}

void constructTree()
{
    ifstream textFile;
    vector<string> binaryTree;
    textFile.open("textFile.txt");
    string word;
//    bool firstWord = true;
    
    
    
    while(getline(textFile, word)) //word would equal the line in the file - change to word
    {
//        if(firstWord)
//        {
//            Node* binaryTree = addNewNode(0, word); //as from moodle link
//        }
        if(word!="")
        {
            //remove punctuation here!!
            addNewNode(0, word); //first parameter should be the first parent node, not sure how to tho ;( buut example just passes 0 so :ascii shrug:
        }
//        firstWord = false;
    }
    textFile.close();
    
}

void findWord()
{
    
}

void preOrder()
{

}

int main()
{
    constructTree();
}