#include <string>
#include <fstream>
#include <cctype>
#include <iostream>
#include <vector>
using namespace std;

//alphabetically store using ascii values to determine position(capital letters should not affect)

struct Node
{
    string word;
    int frequency;
    Node* leftChild;
    Node* rightChild;
};

void addNewNode(Node* node, string word, int frequency)
{
    if(node == NULL) //creates the node if there are no node present at this point
    {
        node = new Node(word, 1);  //DOESNT WORK, EXPECTS 0 ARGMENTS FOR SOME REASON
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
            addNewNode(node->leftChild, word, 1); //re-call function adding to next node, the word and 1 (represents first time this word is used)
        }
        else if(int(asciiCompare) < int(asciiFinder))
        {
            addNewNode(node->rightChild, word, 1); // same as before but to the right
        }
        else if(int(asciiCompare) == int(asciiFinder) && word.size() == node->word.size() == letterCounter-1) //if the letter is the same and its the last letter of both, add one to frequency at this node
        {
            node->frequency++; //add 1 to frequency as this word was already present
        }
    }
    
    
}

vector<int> constructTree()
{
    ifstream textFile;
    vector<string> binaryTree;
    textFile.open("textFile.txt");
    string word;
    
    while(getline(textFile, word)) //word would equal the line in the file - change to word
    {
        
    }
    textFile.close();
    
}

int main()
{
    
}