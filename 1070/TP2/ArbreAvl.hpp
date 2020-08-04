
#ifndef ARBREAVL_A_
#define ARBREAVL_A_

#include "Histoire.hpp"
#include "Phrase.hpp"

#include <iostream>
#include <fstream>



using namespace std;

class TreeNode {

public:
    TreeNode();
    TreeNode(string newWord, string nouveauTitre);

    string item;
    int count;
    string titre;
    TreeNode *leftChildPtr, *rightChildPtr;

    friend class ArbreAvl;
};

class ArbreAvl {

private:
    TreeNode *root;

public:
    ArbreAvl();
    ~ArbreAvl();

    int getBalance( TreeNode *node);
    int getHeight( TreeNode *node);
    void rotateRight( TreeNode* &node);
    void rotateLeft( TreeNode* &node);
    void balance( TreeNode* &node);

    void findWordCount( TreeNode *node, long long &count);
    //void findMostFrequent( TreeNode* node, string &item, string &nouveauTitre,int &count);
    //void findLeastFrequent( TreeNode* node, string &item, int &count);
    //void printInorder( TreeNode* node, ofstream &file);
    //void totalFrequence(TreeNode* node, double &total);
    //void calculateSquareofDifferences(TreeNode* node, double average, double &squareDiff);

    void addWord(string newWord, string nouveauTitre,TreeNode* &node);
    void generateTree(string mot, string nouveauTitre);
    //void printHeight();
    void printTotalWordCount();
    //void printWordFrequencies();
    //void printMostFrequent();
    //void printLeastFrequent();
    //void printStandartDeviation();

};

#endif