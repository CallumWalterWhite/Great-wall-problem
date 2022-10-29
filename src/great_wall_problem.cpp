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
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string path = ".\\Great_Wall_Problem-test_data";

struct brick {
	int index;
	string north;
	string south;
};

unordered_map<string, string> load_bricks(string nSize) {
	string folder_path_pairs = path + "\\" + nSize + "\\input-pairs-" + nSize + ".txt";
	ifstream t(folder_path_pairs);
	std::string line;
	unordered_map<string, string> u;
	vector<string> seglist;
	string segment;
	while (getline(t, line))
	{
		seglist = {};
		stringstream linestream(line.c_str());
		while (getline(linestream, segment, ','))
		{
			seglist.push_back(segment);
		}
		u.insert({ seglist.front(),seglist.back() }); // NORTH->SOUTH
		//u.insert({ seglist.back(),seglist.front() }); // SOUTH->NORTH
	}
	return u;
}

void print_sequence_east(unordered_map<string, string> u, string start_symbol) {
	auto search = u.find(start_symbol);
	while (search != u.end()) {
		cout << search->second << endl;
		search = u.find(search->second);
	}
}

void print_sequence_west(unordered_map<string, string> u, string start_symbol) {
	auto search = u.find(start_symbol);
	while (search != u.end()) {
		cout << search->second << endl;
		search = u.find(search->second);
	}
}

int main(int argc, char *argv[])
{
	unordered_map<string, string> u = load_bricks("1K");
	print_sequence_east(u, u.begin()->first);
}
