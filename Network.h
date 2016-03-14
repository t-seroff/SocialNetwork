#ifndef NETWORK_H
#define NETWORK_H

#include "ProfileManager.h"
#include "BPlusTree.h"
#include "FriendshipGraph.h"

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Network{
	public:
		Network();
		void addPerson(vector<string>);
		bool addFriendship(string, string);
		void printAll();
		void listFriendsInfo(string);
		void listRangeInfo(string, string);

	private:
		ProfileManager profManager;
		BPlusTree nameTree;
		FriendshipGraph friendsGraph;
		

};

#endif