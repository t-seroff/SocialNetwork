#include "BPlusTree.h"

#include <string>
#include <iostream>

using namespace std;

BPlusTree::BPlusTree(){
	// Constructor
	root = new treeNode;
	initNode(root);
	root->leaf = true;
}

string BPlusTree::getStrVal(treeNode* node){
	// Returns "index string" of a node of arbitrary height - traverses down to the leaves

	// Get to level of the leaves
	while (node->leaf != true){
		node = node->ptrOne;
	}
	return node->entryOne->name;
}

void BPlusTree::insert(string name, int index){
	// Make new entry for inserted person
	leafEntry* newEntry = new leafEntry;
	newEntry->name = name;
	newEntry->index = index;

	// Figure out where to put it!
	treeNode* node = root;

	
	// Get to level of the leaves
	while (node->leaf != true){
		// Look backwards to eliminate going into null pointers
		if (name.compare(node->strFour) > 0){
			if (node->strFour.compare("") != 0){
				node = node->ptrFive;
				continue;
			}
		}
		if (name.compare(node->strThree) > 0){
			if (node->strThree.compare("") != 0){
				node = node->ptrFour;
				continue;
			}
		}
		if (name.compare(node->strTwo) > 0){
			if (node->strTwo.compare("") != 0){
				node = node->ptrThree;
				continue;
			}
		}
		if (name.compare(node->strOne) > 0){
			node = node->ptrTwo;
		}
		else{
			node = node->ptrOne;
		}
	}	
	
	
	// Add to the leaf found, if there is an empty space in it
	if (node->entryThree == 0){
		// There is at least one empty space in the leaf, we can insert here!
		
		if (node->entryTwo == 0){
			// There are two empty spaces in the leaf
			if (node->entryOne == 0){
				node->entryOne = newEntry;
			}
			else{
				if (name.compare(node->entryOne->name) < 0){
					// New entry is less than existing element
					node->entryTwo = node->entryOne;
					node->entryOne = newEntry;
				
					// Need to update the parent's index string
					if (node->parent != 0){
						if (node->parent->ptrTwo == node){
							node->parent->strOne = node->entryOne->name;
						}
						else if (node->parent->ptrThree == node){
							node->parent->strTwo = node->entryOne->name;
						}
						else if (node->parent->ptrFour == node){
							node->parent->strThree = node->entryOne->name;
						}
						else if (node->parent->ptrFive == node){
							node->parent->strFour = node->entryOne->name;
						}
					}

				}
				else{
					// New entry greater than existing element
					node->entryTwo = newEntry;
				}
			}
		}
		else{

			// Only one open space in the leaf
			if (name.compare(node->entryOne->name) < 0){
				// New entry is less than both existing elements
				node->entryThree = node->entryTwo;
				node->entryTwo = node->entryOne;
				node->entryOne = newEntry;
	
				// Need to update the parent's index string
				if (node->parent != 0){
					if (node->parent->ptrTwo == node){
						node->parent->strOne = node->entryOne->name;
					}
					else if (node->parent->ptrThree == node){
						node->parent->strTwo = node->entryOne->name;
					}
					else if (node->parent->ptrFour == node){
						node->parent->strThree = node->entryOne->name;
					}
					else if (node->parent->ptrFive == node){
						node->parent->strFour = node->entryOne->name;
					}
				}

			}
			else if (name.compare(node->entryTwo->name) < 0){
				// New entry has value between both existing elements
				node->entryThree = node->entryTwo;
				node->entryTwo = newEntry;
				// entryOne not modified
			}
			else{
				// New entry greater than both existing elements
				node->entryThree = newEntry;
			}
		}

		// Make sure to update parent index string!

	}
	else{
		// Split leaf into two, add new leaf to parent

		treeNode* newLeaf = new treeNode;
		initNode(newLeaf);
		newLeaf->leaf = true;

		newLeaf->nextLeaf = node->nextLeaf;
		node->nextLeaf = newLeaf;
		newLeaf->prevLeaf = node;

		// First figure out how to split the two
		if (name.compare(node->entryOne->name) < 0){
			newLeaf->entryTwo = node->entryThree;
			newLeaf->entryOne = node->entryTwo;

			node->entryTwo = node->entryOne;
			node->entryOne = newEntry;
			node->entryThree = 0;

		}
		else if (name.compare(node->entryTwo->name) < 0){
			newLeaf->entryTwo = node->entryThree;
			newLeaf->entryOne = node->entryTwo;

			node->entryTwo = newEntry;
			node->entryThree = 0;
		}
		else if (name.compare(node->entryThree->name) < 0){
			newLeaf->entryTwo = node->entryThree;
			newLeaf->entryOne = newEntry;

			node->entryThree = 0;
		}
		else{
			newLeaf->entryTwo = newEntry;
			newLeaf->entryOne = node->entryThree;

			node->entryThree = 0;
		}

		if(node->parent == 0){
			// Leaf has no parent (is root!), need to make a new branch and add both leaves
			treeNode* newParent = new treeNode;
			initNode(newParent);

			node->parent = newParent;
			newLeaf->parent = newParent;
			root = newParent;

			newParent->ptrOne = node;
			newParent->strOne = newLeaf->entryOne->name;
			newParent->ptrTwo = newLeaf;
			
		}

		else{	
			// Leaf has a parent, add new leaf to it
			insertIntoBranch(node, newLeaf);
		}
	}
}


treeNode* BPlusTree::splitParent(treeNode* parent, treeNode* newNode){
	// Input: A newly-created node that needs to be inserted into the tree, and a parent that needs to be split
	
	treeNode* newBranch = new treeNode;
	initNode(newBranch);
	
	// Figure out how to split the parent branch
	if (getStrVal(newNode).compare(getStrVal(parent->ptrOne)) < 0){
		// new Node should go into position 1
		newBranch->ptrThree = parent->ptrFive;
		newBranch->strTwo = parent->strFour;
		newBranch->ptrTwo = parent->ptrFour;
		newBranch->strOne = parent->strThree;
		newBranch->ptrOne = parent->ptrThree;

		parent->ptrFive = 0;
		parent->strFour = "";
		parent->ptrFour = 0;
		parent->strThree = "";
		parent->ptrThree = parent->ptrTwo;
		parent->strTwo = parent->strOne;
		parent->ptrTwo = parent->ptrOne;
		parent->strOne = getStrVal(parent->ptrTwo);
		parent->ptrOne = newNode;
	}
	else if (getStrVal(newNode).compare(getStrVal(parent->ptrTwo)) < 0){
		// new Node should go into position 2
		newBranch->ptrThree = parent->ptrFive;
		newBranch->strTwo = parent->strFour;
		newBranch->ptrTwo = parent->ptrFour;
		newBranch->strOne = parent->strThree;
		newBranch->ptrOne = parent->ptrThree;

		parent->ptrFive = 0;
		parent->strFour = "";
		parent->ptrFour = 0;
		parent->strThree = "";
		parent->ptrThree = parent->ptrTwo;
		parent->strTwo = parent->strOne;
		parent->ptrTwo = newNode;
		parent->strOne = getStrVal(newNode);

	}
	else if (getStrVal(newNode).compare(getStrVal(parent->ptrThree)) < 0){
		// new Node should go into position 3
		newBranch->ptrThree = parent->ptrFive;
		newBranch->strTwo = parent->strFour;
		newBranch->ptrTwo = parent->ptrFour;
		newBranch->strOne = parent->strThree;
		newBranch->ptrOne = parent->ptrThree;

		parent->ptrFive = 0;
		parent->strFour = "";
		parent->ptrFour = 0;
		parent->strThree = "";
		parent->ptrThree = newNode;
		parent->strTwo = getStrVal(newNode);

	}
	else if (getStrVal(newNode).compare(getStrVal(parent->ptrFour)) < 0){
		// new Node should go into position 1 of new branch
		newBranch->ptrThree = parent->ptrFive;
		newBranch->strTwo = parent->strFour;
		newBranch->ptrTwo = parent->ptrFour;
		newBranch->strOne = parent->strThree;
		newBranch->ptrOne = newNode;

		parent->ptrFive = 0;
		parent->strFour = "";
		parent->ptrFour = 0;
		parent->strThree = "";
	}
	else if (getStrVal(newNode).compare(getStrVal(parent->ptrFive)) < 0){
		// new Node should go into position 2 of new branch
		newBranch->ptrThree = parent->ptrFive;
		newBranch->strTwo = parent->strFour;
		newBranch->ptrTwo = newNode;
		newBranch->strOne = getStrVal(newNode);
		newBranch->ptrOne = parent->ptrFour;

		parent->ptrFive = 0;
		parent->strFour = "";
		parent->ptrFour = 0;
		parent->strThree = "";
	}
	else{
		// new Node should go into position 3 of new branch
		newBranch->ptrThree = newNode;
		newBranch->strTwo = getStrVal(newNode);
		newBranch->ptrTwo = parent->ptrFive;
		newBranch->strOne = parent->strFour;
		newBranch->ptrOne = parent->ptrFour;

		parent->ptrFive = 0;
		parent->strFour = "";
		parent->ptrFour = 0;
		parent->strThree = "";
	}

	// Fix parent pointers of the nodes that got moved to a new parent
	newBranch->ptrOne->parent = newBranch;
	newBranch->ptrTwo->parent = newBranch;
	newBranch->ptrThree->parent = newBranch;

	return newBranch;	
}


void BPlusTree::insertIntoBranch(treeNode* peerNode, treeNode* newNode){
	treeNode* branch = peerNode->parent;
	newNode->parent = branch;

	// Figure out how to arrange the nodes
	if (branch->ptrThree == 0){
	
		// Only two leaves were already in branch
		if (branch->ptrOne == peerNode){
			// New leaf going into position 2
			branch->ptrThree= branch->ptrTwo;
			branch->strTwo = branch->strOne;
			branch->ptrTwo = newNode;
			branch->strOne = getStrVal(newNode);
		}
		else{
			// New leaf going into position 3
			branch->ptrThree = newNode;
			branch->strTwo = getStrVal(newNode);
		}
	}
	else if (branch->ptrFour == 0){
		// Only three leaves were already in branch
		if (branch->ptrOne == peerNode){
			// New leaf going into position 2
			branch->ptrFour = branch->ptrThree;
			branch->strThree = branch->strTwo;
			branch->ptrThree= branch->ptrTwo;
			branch->strTwo = branch->strOne;
			branch->ptrTwo = newNode;
			branch->strOne = getStrVal(newNode);
		}
		else if (branch->ptrTwo == peerNode){
			// New leaf going into position 3
			branch->ptrFour = branch->ptrThree;
			branch->strThree = branch->strTwo;
			branch->ptrThree = newNode;
			branch->strTwo = getStrVal(newNode);
		}
		else{
			// New leaf going into position 4
			branch->ptrFour = newNode;
			branch->strThree = getStrVal(newNode);

		}
	}
	else if (branch->ptrFive == 0){
		// Only four leaves were already in branch
		if (branch->ptrOne == peerNode){
			// New leaf going into position 2
			branch->ptrFive = branch->ptrFour;
			branch->strFour = branch->strThree;
			branch->ptrFour = branch->ptrThree;
			branch->strThree = branch->strTwo;
			branch->ptrThree= branch->ptrTwo;
			branch->strTwo = branch->strOne;
			branch->ptrTwo = newNode;
			branch->strOne = getStrVal(newNode);
		}
		else if (branch->ptrTwo == peerNode){
			// New leaf going into position 3
			branch->ptrFive = branch->ptrFour;
			branch->strFour = branch->strThree;	
			branch->ptrFour = branch->ptrThree;
			branch->strThree = branch->strTwo;
			branch->ptrThree = newNode;
			branch->strTwo = getStrVal(newNode);

		}
		else if (branch->ptrThree == peerNode){
			// New leaf going into position 4
			branch->ptrFive = branch->ptrFour;
			branch->strFour = branch->strThree;
			branch->ptrFour = newNode;
			branch->strThree = getStrVal(newNode);

		}
		else{
			// New leaf going into position 5
			branch->ptrFive = newNode;
			branch->strFour = getStrVal(newNode);
		}
	}
	else{
		// Branch is full and needs to be split
		treeNode* newBranch = splitParent(branch, newNode);
		if (branch->parent == 0){
			// Base case - branch is root, so create a new root, add both branches to it, grow upwards
			treeNode* newRoot = new treeNode;
			initNode(newRoot);
			root = newRoot;
			root->ptrOne = branch;
			branch->parent = root;
			root->strOne = getStrVal(newBranch);
			root->ptrTwo = newBranch;
			newBranch->parent = root;
		}
		else{
			// Recursive case - propagate upwards!
			insertIntoBranch(branch, newBranch);
		}
	}
}

int BPlusTree::getDataIndex(string name){
	// Find entry by name and return the profileData file index for that person
	treeNode* node = root;

	// Get to the right leaf
	while (node->leaf != true){
		// Have to look backwards when searching for existing record because index string may be less than (or equal to!) desired name
		if (name.compare(node->strFour) >= 0){
			if (node->strFour.compare("") != 0){
				node = node->ptrFive;
				continue;
			}
		}
		if (name.compare(node->strThree) >= 0){
			if (node->strThree.compare("") != 0){
				node = node->ptrFour;
				continue;
			}
		}
		if (name.compare(node->strTwo) >= 0){
			if (node->strTwo.compare("") != 0){
				node = node->ptrThree;
				continue;
			}
		}
		if (name.compare(node->strOne) >= 0){
			node = node->ptrTwo;
		}
		else{
			node = node->ptrOne;
		}
	}

	// Search the leaf for the entry for the specified person
	if (node->entryOne != 0){
		if (node->entryOne->name.compare(name) == 0){
			return node->entryOne->index;
		}
	}
	if (node->entryTwo != 0){
		if (node->entryTwo->name.compare(name) == 0){
			return node->entryTwo->index;
		}
	}
	if (node->entryThree != 0){
		if (node->entryThree->name.compare(name) == 0){
			return node->entryThree->index;
		}
	}

	// Name not found in the leaf!
	cout << "NOT FOUND: " << name << endl;
	return -1;
}

void BPlusTree::printTree(){
	// Prints B+ Tree
	printNode(root);
}

void BPlusTree::printNode(treeNode* node){
	// Recursively print B+ Tree from given node
	if (node != 0){
		if (node->leaf){
			cout << "leaf" << endl;
			if (node->entryOne != 0){
				cout << node->entryOne->name << endl;
			}
			if (node->entryTwo != 0){
				cout << node->entryTwo->name << endl;
			}
			if (node->entryThree != 0){
				cout << node->entryThree->name << endl;
			}
			cout << "end of leaf" << endl << endl;
		}
		else{
			cout << "branch" << endl;
			printNode(node->ptrOne);
			cout << "stringOne is " << node->strOne << endl;
			printNode(node->ptrTwo);
			cout << "stringTwo is " << node->strTwo << endl;
			printNode(node->ptrThree);
			cout << "stringThree is " << node->strThree << endl;
			printNode(node->ptrFour);
			cout << "stringFour is " << node->strFour << endl;
			printNode(node->ptrFive);
			cout << "end of branch" << endl;
		}
	}

	// Otherwise null pointer, nothing to print
}

void BPlusTree::initNode(treeNode* node){
	// Node constructor - set all values and pointers to 0
	node->leaf = false;
	node->parent = 0;

	node->ptrOne = 0;
	node->ptrTwo = 0;
	node->ptrThree = 0;
	node->ptrFour = 0;
	node->ptrFive = 0;
	node->strOne = "\0";
	node->strTwo = "\0";
	node->strThree = "\0";
	node->strFour = "\0";
	
	node->entryOne = 0;
	node->entryTwo = 0;
	node->entryThree = 0;
	node->prevLeaf = 0;
	node->nextLeaf = 0;
}

vector<string> BPlusTree::returnAllNames(){
	// Return ASCII-sorted list of all names in the tree
	treeNode* node = root;
	while (node->leaf != true){
		node = node->ptrOne;
	}
	
	vector<string> friends;
	
	while (node != 0){
		if (node->entryOne != 0){
			friends.push_back(node->entryOne->name);
		}
		if (node->entryTwo != 0){
			friends.push_back(node->entryTwo->name);
		}
		if (node->entryThree != 0){
			friends.push_back(node->entryThree->name);
		}

		node = node->nextLeaf;
	}

	return friends;
}

vector<string> BPlusTree::returnNameRange(string name1, string name2){
	// Return all names in specified range
	treeNode* node = root;
	
	vector<string> people;

	while (node->leaf != true){
		// Have to look backwards when searching, index string may be less than or equal to desired name
		if (name1.compare(node->strFour) >= 0){
			if (node->strFour.compare("") != 0){
				node = node->ptrFive;
				continue;
			}
		}
		if (name1.compare(node->strThree) >= 0){
			if (node->strThree.compare("") != 0){
				node = node->ptrFour;
				continue;
			}
		}
		if (name1.compare(node->strTwo) >= 0){
			if (node->strTwo.compare("") != 0){
				node = node->ptrThree;
				continue;
			}
		}
		if (name1.compare(node->strOne) >= 0){
			node = node->ptrTwo;
		}
		else{
			node = node->ptrOne;
		}
	}

	while (node != 0){
		if (node->entryOne != 0){
			if ((node->entryOne->name.compare(name1) >= 0) && (node->entryOne->name.compare(name2) <= 0)){
				people.push_back(node->entryOne->name);
			}
		}
		if (node->entryTwo != 0){
			if ((node->entryTwo->name.compare(name1) >= 0) && (node->entryTwo->name.compare(name2) <= 0)){
				people.push_back(node->entryTwo->name);
			}
		}
		if (node->entryThree != 0){
			if ((node->entryThree->name.compare(name1) >= 0) && (node->entryThree->name.compare(name2) <= 0)){
				people.push_back(node->entryThree->name);
			}
		}

		node = node->nextLeaf;
	}

	return people;
}
