#include "Network.h"
#include "ProfileManager.h"
#include "BPlusTree.h"
#include "FriendshipGraph.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

Network::Network(){
	// Constructor
	;
}

void Network::addPerson(vector<string> attributes){
	// Add new person into the network
	string name = attributes[0];
	attributes.erase(attributes.begin());
	int age = stoi(attributes[0]);
	attributes.erase(attributes.begin());
	string occupation = attributes[0];
	attributes.erase(attributes.begin());
	// Remaining elements in attributes are friends list

	// Check to make sure person doesn't already exist
	int index = friendsGraph.search(name);
	if (index == -1){
		// Add to profile data file
		int index = profManager.addEntry(name, age, occupation);

		// Add to name tree
		nameTree.insert(name, index);

		// Add to friendship graph
		friendsGraph.addPerson(name, index, attributes);
	}
	else{
		cout << "A person with that name already exists in the network!" << endl;
	}
}

bool Network::addFriendship(string name1, string name2){
	// Add a friendship between two people
	return friendsGraph.addFriendship(name1, name2);
}

void Network::printAll(){
	// Print all users in the network

	// Get each person from B tree
	vector<string> people = nameTree.returnAllNames();

	// For each person, print their info and friends list
	for (int i = 0; i < int(people.size()); i++){
		string name = people[i];	
		cout << "Name: " << name << endl;
		int index = nameTree.getDataIndex(name);

		// Get their info from the profile manager
		string info = profManager.returnInfo(index);
		cout << "Info: " << info << endl;

		// Print their friends list from the friendship graph
		cout << "Friends: " << endl;
		vector<string> friends = friendsGraph.listFriends(name);
		for (int i = 0; i < int(friends.size()); i++){
			cout << '\t' << friends[i] << endl;
		}
	}
}

void Network::listFriendsInfo(string name){
	// Print info of friends of specified user	

	// Get list of friends for person from graph
	vector<string> friends = friendsGraph.listFriends(name);

	// For each friend, look up profile data index from b-tree
	for (int i = 0; i < int(friends.size()); i++){
		int index = nameTree.getDataIndex(friends[i]);
		
		// Read profiledata file, print info for each friend
		cout << profManager.returnInfo(index) << endl;
	}
}

void Network::listRangeInfo(string lower, string upper){
	// Print info of all users with names in specified range

	// Get list of people with names within bounds, from graph
	vector<string> people = nameTree.returnNameRange(lower, upper);

	// For each friend, look up profile data index from b-tree
	for (int i = 0; i < int(people.size()); i++){
		int index = nameTree.getDataIndex(people[i]);
		
		// Read profiledata file, print info for each person
		cout << profManager.returnInfo(index) << endl;
	}
}

