#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class ProfileManager{
	public:
		ProfileManager();
		int addEntry(string, int, string);
		string returnInfo(int);

	private:
		FILE* profileData;
		int profileDataEntries;
};

#endif