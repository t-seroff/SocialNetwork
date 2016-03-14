#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <string>
#include <vector>

using namespace std;

struct leafEntry{
	string name;
	int index;
};

struct treeNode{
	bool leaf;
	treeNode* parent;

	// Used for branches
	//  M = 5
	treeNode* ptrOne;
	string strOne;
	treeNode* ptrTwo;
	string strTwo;
	treeNode* ptrThree;
	string strThree;
	treeNode* ptrFour;
	string strFour;
	treeNode* ptrFive;

	// Used for leafs
	//  L = 3
	leafEntry* entryOne;
	leafEntry* entryTwo;
	leafEntry* entryThree;
	treeNode* prevLeaf;
	treeNode* nextLeaf;

};

class BPlusTree{
	public:
		BPlusTree();
		void insert(string, int);
		int getDataIndex(string);
		void printTree();
		vector<string> returnAllNames();
		vector<string> returnNameRange(string, string);

	private:
		treeNode* root;
		void initNode(treeNode*);
		treeNode* splitParent(treeNode*, treeNode*);
		void insertIntoBranch(treeNode*, treeNode*);
		string getStrVal(treeNode*);
		void printNode(treeNode*);
		
};

#endif