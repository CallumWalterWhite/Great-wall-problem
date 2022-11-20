/*
Reasons for why hash map would not work with the great wall problem -

You can't print from opposite directions for the hash map, as the key being south or north repersents the direction of sequences
This means, you can't have the correct.

Time complexity = O(N)

Example (North is hash key)

[5,2] -> [2,9] -> [9,1] -> [1,!]

[5,2] </- [2,9] </- [9,1] </- [1,!]

You can't search back from end of sequence because 1 does not have a hash key within the hash table.

*/



#include <iostream>
#include <unordered_map>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

using chrono::steady_clock;
using chrono::nanoseconds;
using chrono::duration_cast;

struct brick {
	int index;
	string north;
	string south;
};

list<string> load_results(string file_path) {
	string line;
	ifstream t(file_path);
	list<string> results;
	try{
		while (getline(t, line))
		{
			results.push_back(line.c_str());
		}
	}
	catch (const exception ex) {
		cout << ex.what() << endl;
		
	}
	return results;
}

unordered_map<string, string> load_bricks_hash_map(string file_path, bool northSouth) {
	string line;
	ifstream t(file_path);
	unordered_map<string, string> bricks;
	vector<string> segment_list;
	string segment;
	try{
		while (getline(t, line))
		{
			segment_list = {};
			stringstream linestream(line.c_str());
			while (getline(linestream, segment, ','))
			{
				segment_list.push_back(segment);
			}
			if (northSouth) {
				bricks.insert({ segment_list.front(),segment_list.back() }); // NORTH->SOUTH
			}
			else {
				bricks.insert({ segment_list.back(),segment_list.front() }); // SOUTH->NORTH
			}
		}
	}
	catch (const exception ex) {
		cout << ex.what() << endl;
		
	}
	return bricks;
}

map<string, string> load_bricks_bst(string file_path, bool northSouth) {
	string line;
	ifstream t(file_path);
	map<string, string> bricks;
	vector<string> segment_list;
	string segment;
	try{
		while (getline(t, line))
		{
			segment_list = {};
			stringstream linestream(line.c_str());
			while (getline(linestream, segment, ','))
			{
				segment_list.push_back(segment);
			}
			if (northSouth) {
				bricks.insert({ segment_list.front(),segment_list.back() }); // NORTH->SOUTH
			}
			else {
				bricks.insert({ segment_list.back(),segment_list.front() }); // SOUTH->NORTH
			}
		}
	}
	catch (const exception ex) {
		cout << ex.what() << endl;
		
	}
	return bricks;
}


list<string> add_sequence_hash_map(unordered_map<string, string> bricks, string start_symbol, list<string> sequence, bool front) {
	auto search = bricks.find(start_symbol);
	while (search != bricks.end()) {
		if (front){
			sequence.push_front(search->second);
		}
		else {
			sequence.push_back(search->second);
		}
		search = bricks.find(search->second);
	}
	
	return sequence;
}

list<string> add_sequence_bst(map<string, string> bricks, string start_symbol, list<string> sequence, bool front) {
	auto search = bricks.find(start_symbol);
	while (search != bricks.end()) {
		if (front){
			sequence.push_front(search->second);
		}
		else {
			sequence.push_back(search->second);
		}
		search = bricks.find(search->second);
	}
	
	return sequence;
}

vector<string> get_arugments(int argc, char *argv[]) { 
	vector<string> arugments;
	if (argc > 1) {
		arugments.assign(argv + 1, argv + argc);
	}
	return arugments;
}

bool check_order(list<string> sequence, string result_file_location) 
{
	list<string> results = load_results(result_file_location);
	return equal(sequence.begin(), sequence.end(), results.begin(), results.end());
}

list<string> hash_map_list(string file_location) {
	list<string> sequence = list<string>();
	unordered_map<string, string> northSouth = load_bricks_hash_map(file_location, true);
	unordered_map<string, string> southNorth = load_bricks_hash_map(file_location, false);
	sequence = add_sequence_hash_map(northSouth, northSouth.begin()->first, sequence, false);
	sequence = add_sequence_hash_map(southNorth, northSouth.begin()->second, sequence, true);
	return sequence;
}

list<string> bst_list(string file_location) {
	list<string> sequence = list<string>();
	map<string, string> northSouth = load_bricks_bst(file_location, true);
	map<string, string> southNorth = load_bricks_bst(file_location, false);
	sequence = add_sequence_bst(northSouth, northSouth.begin()->first, sequence, false);
	sequence = add_sequence_bst(southNorth, northSouth.begin()->second, sequence, true);
	return sequence;
}

int main(int argc, char *argv[])
{
	vector<string> arugments = get_arugments(argc, argv);
	string file_location = arugments[0];
	string result_file_location = arugments[1];
	int implementation = stoi(arugments[2]);
	list<string> sequence;
   	steady_clock::time_point startTime = steady_clock::now();
	string data_strcuture;
	switch(implementation){
		case 0:
			data_strcuture = "std::unordered_map (HashMap)";
			sequence = hash_map_list(file_location);
			break;
		case 1:
			data_strcuture = "std::map (red-black tree)";
			sequence = bst_list(file_location);
			break;
		default:
			throw exception("Wrong input");
			break;
	}
	steady_clock::time_point finishTime = steady_clock::now();
	nanoseconds timeTaken = duration_cast<nanoseconds>(finishTime - startTime);
    std::cout << "Data structure: " + data_strcuture << std::endl;
    std::cout << "Time taken: " << timeTaken.count() << " nanoseconds." << std::endl;
	bool order_correct = check_order(sequence, result_file_location);
    std::cout << "Is order correct: " << order_correct << std::endl;
}