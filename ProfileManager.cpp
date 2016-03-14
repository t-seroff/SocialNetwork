#include "ProfileManager.h"
#include <string>

#define EMPTY_CHAR 0

ProfileManager::ProfileManager(){
	// Constructor - initialize data file
	profileData = fopen("profileData.txt", "w+");
	profileDataEntries = 0;
}

int ProfileManager::addEntry(string name, int age, string occupation){
	// Add new entry into the profile data file

	// Create character arrays of size for profileData file
	char file_name[20];
	char file_age[3];
	char file_occupation[30];
	char newline[1] = {'\n'};
	
	// Copy in the information provided
	strcpy(file_name, name.c_str());
	sprintf(file_age, "%d", age);
	strcpy(file_occupation, occupation.c_str());

	// Pad any extra spaces
	for (int i = int(name.length()); i < 20; i++){
		file_name[i] = EMPTY_CHAR;
	}
	if (age < 10){
		file_age[2] = file_age[1] = EMPTY_CHAR;
	}
	else{
		file_age[2] = EMPTY_CHAR;
	}
	for (int i = int(occupation.length()); i < 30; i++){
		file_occupation[i] = EMPTY_CHAR;
	}
	
	// Write it all to the profileData file
	fwrite(file_name, 20, 1, profileData);
	fwrite(file_age, 3, 1, profileData);
	fwrite(file_occupation, 30, 1, profileData);
	fwrite(newline, 1, 1, profileData);

	// Increment entries count and return index of newly added entry
	profileDataEntries++;
	return(profileDataEntries-1);
}

string ProfileManager::returnInfo(int index){
	// Return info at specified file index

	if ((index < profileDataEntries) && (index >= 0)){
		// Calculate base pointer from index, allocate c strings for data
		int base_pointer = (index*54);
		char file_name[20];
		char file_age[3];
		char file_occupation[30];
		
		// Set file pointer to base pointer and read data from file
		fseek(profileData, base_pointer, SEEK_SET);
		fread(file_name, 20, 1, profileData);
		fread(file_age, 3, 1, profileData);
		fread(file_occupation, 30, 1, profileData);
		
		// Convert to C++ strings, truncating at null char in the process
		string name(file_name);	
		string age(file_age);
		string occupation(file_occupation);

		// Return as comma-separated string of attributes
		return name + "," + age + "," + occupation;
	}
	else{
		// Index requested is past end of file
		return "INDEX INVALID";
	}
}