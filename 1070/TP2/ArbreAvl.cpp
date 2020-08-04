
#include "math.h"
#include <string.h>
#include <climits>
#include "ArbreAvl.hpp"
#include "Histoire.hpp"
#include "Phrase.hpp"

using namespace std;

TreeNode::TreeNode()
{
    this->count = 0;
    this->item = "";
    this->leftChildPtr = NULL;
    this->rightChildPtr = NULL;
    this->titre = "";
}

TreeNode::TreeNode(string newWord, string nouveauTitre)
{
    this->count = 1;
    this->item = newWord;
    this->leftChildPtr = NULL;
    this->rightChildPtr = NULL;
    this->titre = nouveauTitre;
}

ArbreAvl::ArbreAvl()
{
    root = NULL;
}

ArbreAvl::~ArbreAvl()
{

}

int ArbreAvl::getBalance( TreeNode *node)
{//Return height difference between right and left sub tree
    return getHeight(node->rightChildPtr) - getHeight(node->leftChildPtr);
}

int ArbreAvl::getHeight( TreeNode *node)
{//Return height
    if ( node != NULL)
    {
        return 1 + max(getHeight(node->leftChildPtr),getHeight(node->rightChildPtr));
    }

    return 0;
} 

void ArbreAvl::rotateRight( TreeNode* &node)
{//Rotate AVL tree to right
    TreeNode *temp = node->leftChildPtr;
    node->leftChildPtr = temp->rightChildPtr;
    temp->rightChildPtr = node;

    node = temp;
    temp = NULL;
}

void ArbreAvl::rotateLeft( TreeNode* &node)
{//Rotate AVL tree to left
    TreeNode *temp = node->rightChildPtr;
    node->rightChildPtr = temp->leftChildPtr;
    temp->leftChildPtr = node;

    node = temp;
    temp = NULL;
}

void ArbreAvl::balance(TreeNode* &node)
{//Balance the AVL tree
 //Check balance factors of all nodes from leaf to root
 //and balance the tree accordingly
    if (getBalance(node) > 1)
    {
        if (getBalance(node->rightChildPtr) < 0)
        {
            rotateRight(node->rightChildPtr);
            rotateLeft(node);
        }
        else
        {
            rotateLeft(node);
        }
    }

    else if (getBalance(node) < -1) {

        if (getBalance(node->leftChildPtr) > 0)
        {
            rotateLeft(node->leftChildPtr);
            rotateRight(node);
        }
        else
        {
            rotateRight(node);
        }

    }

}

void ArbreAvl::findWordCount( TreeNode *node, long long &count)
{//Count word with an inorder traversal
    if(node != NULL)
    {
        findWordCount(node->leftChildPtr, count);
        count++;
        findWordCount(node->rightChildPtr, count);
    }
}

/*void ArbreAvl::findMostFrequent( TreeNode* node, string &item, string &nouveauTitre,int &count)
{//While inorder traversaling it compares and finds the most frequent word
    if(node != NULL)
    {
        findMostFrequent(node->leftChildPtr, item, nouveauTitre,count);

        if (node->count > count)
        {
            count = node->count;
            item = node -> item;
            nouveauTitre = node ->titre;
        }

        findMostFrequent(node->rightChildPtr, item, nouveauTitre,count);
    }
}*/

/*void ArbreAvl::findLeastFrequent( TreeNode* node, string &item, int &count)
{//While inorder traversaling it compares and finds the least frequent word
    if(node != NULL)
    {
        findLeastFrequent(node->leftChildPtr, item, count);

        if (node->count < count)
        {
            count = node->count;
            item = node -> item;
        }

        findLeastFrequent(node->rightChildPtr, item, count);
    }
}*/

/*void ArbreAvl::printInorder( TreeNode* node, ofstream &file)
{//While inorder traversaling it prints the words and their frequencies
    if( node != NULL)
    {
        printInorder(node->leftChildPtr, file);
        file << (node->item) << " " << (node->count) << "\n";
        printInorder(node->rightChildPtr, file);
    }

}*/

/*void ArbreAvl::totalFrequence(TreeNode* node, double &total)
{//While inorder traversaling sum all the frequencies of the words
    if( node != NULL)
    {
        totalFrequence(node->leftChildPtr, total);
        total = total + node->count;
        totalFrequence(node->rightChildPtr, total);
    }
}
*/
/*void ArbreAvl::calculateSquareofDifferences(TreeNode* node, double average, double &squareDiff)
{//While inorder traversaling it calculates sum of square of difference between average and each words frequency.
    if( node != NULL)
    {
        calculateSquareofDifferences(node->leftChildPtr, average, squareDiff);
        squareDiff = squareDiff + (average - node->count) * (average - node->count);
        calculateSquareofDifferences(node->rightChildPtr, average, squareDiff);
    }
}*/

void ArbreAvl::addWord(string newWord, string nouveauTitre,TreeNode* &node)
{//Add given word to the AVL
    if( node == NULL)
    {
        node = new TreeNode(newWord,nouveauTitre);
    }

    else
    {
        if ( newWord.compare(node->item) > 0 || nouveauTitre.compare(node->titre) > 0)
        {
            addWord(newWord, nouveauTitre,node->rightChildPtr);
            balance(node);
        }

        else if( newWord.compare(node->item) == 0 && nouveauTitre.compare(node->titre) == 0)
        {
            node->count++;
        }

        else
        {
            addWord(newWord, nouveauTitre,node->leftChildPtr);
            balance(node);
        }

    }


}

void ArbreAvl::generateTree(string mot, string nouveauTitre)
{//Read from file and add to tree one by one

            addWord(mot, nouveauTitre,root);

}

// These functions write the calculated data to the text files
/*void ArbreAvl::printHeight()
{
    ofstream file;
    file.open ("statistics.txt",file.app);
    file << "Tree Height: " << getHeight(root) << "\n";
    file.close();
}
*/
void ArbreAvl::printTotalWordCount()
{
    long long count = 0;
    findWordCount( root, count);

    ofstream file;
    file.open ("statistics.txt");
    file << "Total Word Count: " << count << "\n";
    file.close();
}

/*void ArbreAvl::printWordFrequencies()
{
    ofstream file;
    file.open ("wordfreqs.txt");
    printInorder(root,file);
    file.close();
}
*/
/*void ArbreAvl::printMostFrequent()
{
    int count = 0;
    string item = "";
    string nouveauTitre = "";
    findMostFrequent( root, item, nouveauTitre,count);

    ofstream file;
    file.open ("statistics.txt",file.app);
    file << "Most Frequent: " << " LE MOT : " << item << " "  <<  " LE TITRE : " << nouveauTitre << " NOMBRE OCCURENCE : " << count << "\n";
    file.close();
}*/

/*void ArbreAvl::printLeastFrequent()
{
    int count = INT_MAX;
    string item = "";
    findLeastFrequent( root, item, count);

    ofstream file;
    file.open ("statistics.txt",file.app);
    file << "Least Frequent: " << item << " " << count << "\n";
    file.close();
}
*/
/*void ArbreAvl::printStandartDeviation()
{
    long long count = 0;
    findWordCount( root, count);

    double total = 0;
    totalFrequence(root, total);

    double average = total/count;
    double squareDiff = 0;
    calculateSquareofDifferences(root, average, squareDiff);

    
    cout << (sqrt(squareDiff/count)) << "\n";
    
}*/


