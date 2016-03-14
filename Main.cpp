/*
 * Main.cpp
 *
 *  Created on: Feb 11, 2016
 *      Author: omid (Modified by Tristan Seroff for use in my project)
 */

#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include "Network.h"
using namespace std;

vector<string> split(string str, char delimiter)
{
	vector<string> internal;
	stringstream ss(str);       // turn the string into a stream
	string tok;

	while(getline(ss, tok, delimiter))
	{
		internal.push_back(tok);
	}

	return internal;
}

int main()
{
	Network net;

	// Print possible command inputs
	cout << "Social network ---------------------" << endl;
	cout << "'import' to import a network from file" << endl;
	cout << "'insert' to insert a new person to the network" << endl;
	cout << "'addFriendship' to add a new friendship" << endl;
	cout << "'printAll' to print the network" << endl;
	cout << "'listFriendsInfo' to list info of someone's friends" << endl;
	cout << "'listRangeInfo' to list info of a range of people" << endl;
	cout << "'list' to list commands" << endl;
	cout << "'quit' to quit" << endl;

	// Receive and process commands
	while (true){

		cout << endl;
		cout << "Enter a command:" << endl;

		string command;
		cin >> command;

		if (command.compare("import") == 0){
			// Create a new network
			Network newNet;
			net = newNet;

			string fileName;
			cout << "Enter file path" << endl;
			cin >> fileName;

			ifstream f;
			f.open(fileName, ios::in);
			if (!f){
				cerr << "File not found" << endl;
			}
			else
			{
				string line;
				while(std::getline(f, line))
				{
					vector<string> words = split(line, ',');
					net.addPerson(words);
				}
			}
		}

		else if (command.compare("insert") == 0){
			vector<string> words;
			cout << "Enter name: " << endl;
			string name;
			cin >> name;
			if (name.length() > 20){
				name = name.substr(0,19);
			}
			
			cout << "Enter age: " << endl;
			string age;
			cin.ignore(); // Get rid of leading newline character
			getline(cin, age, '\n');
			if (age.length() > 3){
				age = age.substr(0,2);
			}		

			cout << "Enter occupation: " << endl;
			string occupation;
			cin.ignore(); // Get rid of leading newline character
			getline(cin, occupation, '\n');
			if (occupation.length() > 30){
				occupation = occupation.substr(0,29);
			}

			words.push_back(name);
			words.push_back(age);
			words.push_back(occupation);
			
			net.addPerson(words);
		}

		else if ((command.compare("addFriendship") == 0) || (command.compare("addfriendship") == 0)){
			cout << "Enter name of first friend: " << endl;
			string name1;
			cin >> name1;

			cout << "Entry name of second friend: " << endl;
			string name2;
			cin >> name2;

			bool result = net.addFriendship(name1, name2);
			if (!result){
				cout << "Unable to create friendship. Both friends need to be in the network!" << endl;
			}
		}
		
		else if ((command.compare("listFriendsInfo") == 0) || (command.compare("listfriendsinfo") == 0)){
			cout << "Enter name of person whose friends should be listed:" << endl;
			string name;
			cin >> name;
			net.listFriendsInfo(name);
		}

		else if ((command.compare("listRangeInfo") == 0) || (command.compare("listrangeinfo") == 0)){
			cout << "Enter lower name bound to list:" << endl;
			string lower = "";
			cin >> lower;
			
			cout << "Enter upper name bound to list:" << endl;
			string upper = "";
			cin >> upper;

			net.listRangeInfo(lower, upper);
		}

		else if ((command.compare("printAll") == 0) || (command.compare("printall") == 0)){
			net.printAll();
		}

		else if (command.compare("list") == 0){
			// Print possible command inputs
			cout << "Social network ---------------------" << endl;
			cout << "'import' to import a network from file" << endl;
			cout << "'insert' to insert a new person to the network" << endl;
			cout << "'addFriendship' to add a new friendship" << endl;
			cout << "'printAll' to print the network" << endl;
			cout << "'listFriendsInfo' to list info of someone's friends" << endl;
			cout << "'listRangeInfo' to list info of a range of people" << endl;
			cout << "'list' to list commands" << endl;
			cout << "'quit' to quit" << endl;
		}

		else if (command.compare("quit") == 0){
			break;
		}
	}

	return 0;
}
