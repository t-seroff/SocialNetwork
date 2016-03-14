#include "FriendshipGraph.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

FriendshipGraph::FriendshipGraph(){
	// Constructor
	graph = new graphNode*[211];
	
	for (int i = 0; i < TABLE_SIZE; i++){
		graph[i] = 0;
	}
}

void FriendshipGraph::addPerson(string name, int pdFileIndex, vector<string> friends){
	// Add new person to the graph with specified parameters	

	// Check to make sure entry doesn't already exist?
	graphNode* mainPerson = new graphNode;
	mainPerson->name = name;
	mainPerson->profileDataIndex = pdFileIndex;
	mainPerson->nextFriend = 0;

	// Find an empty bucket and insert the node into the graph
	int hashVal = hashName(name, 0);
	int index = hashVal;
	while (graph[index] != 0){
		// Stops when an empty bucket is found
		index = (index + 1) % TABLE_SIZE;
	}
	graph[index] = mainPerson;

	// For each listed friend, see if they're in the network, add references if they are
	for (int i = 0; i < int(friends.size()); i++){
		addFriendship(name, friends[i]);
	}

}

bool FriendshipGraph::addFriendship(string friend1, string friend2){
	// Add a new friendship between two people

	// Search for both people in the friendship
	int friendOneIndex = search(friend1);
	int friendTwoIndex = search(friend2);
	if ((friendOneIndex != -1) && (friendTwoIndex != -1)){
		// Both people in the friendship were found

		// Check to make sure friendship doesn't already exist?

		// Make a node representing second friend and add to first friend's linked list
		graphNode* secondFriend = new graphNode;
		secondFriend->name = graph[friendTwoIndex]->name; // Just to be sure
		secondFriend->profileDataIndex = graph[friendTwoIndex]->profileDataIndex;
		secondFriend->nextFriend = 0;
		
		// Get to end of existing linked list
		graphNode* listPtr = graph[friendOneIndex];
		while (listPtr->nextFriend != 0){
			listPtr = listPtr->nextFriend;
		}
		// Append to the list
		listPtr->nextFriend = secondFriend;

		// Make a node representing the newly added person as the existing friend's friend
		graphNode* firstFriend = new graphNode;
		firstFriend->name = graph[friendOneIndex]->name; // Again, just to be sure
		firstFriend->profileDataIndex = graph[friendOneIndex]->profileDataIndex;
		firstFriend->nextFriend = 0;

		// Get to end of their existing friend list
		graphNode* newListPtr = graph[friendTwoIndex];
		while (newListPtr->nextFriend != 0){
			newListPtr = newListPtr->nextFriend;
		}
		// Append to the list
		newListPtr->nextFriend = firstFriend;		

		return true;	
	}
	else{
		return false;
	}
}

int FriendshipGraph::hashName(string str, int seed = 0){
	// Calculate hash value for a person's name
	int hash = seed;	for(int i = 0; i < int(str.length()); i++)	{		hash = (hash*101 + str[i]) % TABLE_SIZE;	}	return hash;
}

int FriendshipGraph::search(string name){
	// Return index of entry with provided name, if found
	// If not found, returns -1;

	int hashVal = hashName(name, 0);
	for (int i = hashVal; graph[i] != 0; i++){
		// Linear probing - search until empty space
		if (graph[i]->name.compare(name) == 0){
			// If name is a match, return index
			return i;
		}
	}

	return -1;
}

void FriendshipGraph::print(){
	// Print friendship graph contents

	for (int i = 0; i < TABLE_SIZE; i++){
		cout << i << ": ";
		if (graph[i] == 0){
			cout << "--empty--" << endl;
		}
		else{
			cout << graph[i]->name << ", " << graph[i]->profileDataIndex << ", " << graph[i]->nextFriend << endl;
			graphNode* friendListPtr = graph[i]->nextFriend;
			while (friendListPtr != 0){
				cout << '\t' << friendListPtr->name << endl;
				friendListPtr = friendListPtr->nextFriend;
			}
		}
	}
}

vector<string> FriendshipGraph::listFriends(string name){
	// Return list of friends of specified user

	vector<string> friends;
	int personIndex = search(name);
	if (personIndex == -1){
		return friends;
	}
	
	graphNode* friendPtr = graph[personIndex]->nextFriend;
	while (friendPtr != 0){
		friends.push_back(friendPtr->name);
		friendPtr = friendPtr->nextFriend;
	}
	
	return friends;
}