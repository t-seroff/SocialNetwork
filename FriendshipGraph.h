#ifndef FRIENDSHIPGRAPH_H
#define FRIENDSHIPGRAPH_H

#include <vector>
#include <string>

using namespace std;

#define TABLE_SIZE 211

struct graphNode{
	string name;
	int profileDataIndex;
	graphNode* nextFriend;
};


class FriendshipGraph{
	public:
		FriendshipGraph();
		void addPerson(string, int, vector<string>);
		bool addFriendship(string, string);
		void print();
		int search(string);
		vector<string> listFriends(string);

	private:
		int hashName(string, int);
		graphNode** graph;

};

#endif