/* -meta.cpp----------------------------------------------------------------- */
#include <iostream>
#include <map>
#include <cstring>
#include <openssl/md5.h>

/* -boost-------------------------------------------------------------------- */
#include <boost/filesystem/path.hpp>

/* -------------------------------------------------------------------------- */
#include "stat.hpp"

using namespace std;

/* -Meta--------------------------------------------------------------------- */
class Metadata {
private:
	multimap<string, string> path_map;
	map<string, Stat> file_map;

public:
	Metadata() {
		// Make root directory
		make_directory("/");
	}

	/*----------------------------------------------------------------------
	 * File System Operation
	 *------------------------------------------------------------------- */
	bool make_directory(string path) {
		// Set Context Infomation of Stat
		Stat new_directory;
		new_directory.setDefaultContext().setDirectory();

		// Parse path
		boost::filesystem::path parser(path);
		string full_path = parser.string();
		string file_path = parser.parent_path().string();
		string file_name = parser.filename().string();

		// File path Mapping
		path_map.insert(pair<string, string>(file_path, file_name));
		file_map.insert(pair<string, Stat>(full_path, new_directory));
		return true;
	}

	bool remove_directory(string path) {
		// Parse path
		boost::filesystem::path parser(path);
		string full_path = parser.string();
		string file_path = parser.parent_path().string();
		string file_name = parser.filename().string();

		// Remove File Map & Path Map
		pair<multimap<string, string>::iterator, multimap<string, string>::iterator> range;
		range = path_map.equal_range(file_path);
		for(multimap<string, string>::iterator it=range.first; it!=range.second; ++it) {
			if (strcmp(it->second.c_str(), file_name.c_str()) == 0) {
				cout << it->first << "\t" << it->second << endl;
				path_map.erase(it);
			}
		}
		//path_map.erase(full_path);
		file_map.erase(full_path);

		return true;
	}

	vector<string> list_directory(string path) {
		// File list
		vector<string> directories;

		// Get Directory Path Range File
		pair<multimap<string, string>::iterator, multimap<string, string>::iterator> range;
		range = path_map.equal_range(path);
		for(multimap<string, string>::iterator it=range.first; it!=range.second; ++it) {
			cout << it->first << "\t" << it->second << endl;
			directories.push_back(it->second);
		}

		return directories;
	}

	/*----------------------------------------------------------------------
	 * File Operation
	 *------------------------------------------------------------------- */
	bool make_file(string path) {
		// Set Context Infomation of Stat
		Stat new_file;
		new_file.setDefaultContext().setFile();

		// Parse path
		boost::filesystem::path parser(path);
		string full_path = parser.string();
		string file_path = parser.parent_path().string();
		string file_name = parser.filename().string();

		// File path Mapping
		path_map.insert(pair<string, string>(file_path, file_name));
		file_map.insert(pair<string, Stat>(full_path, new_file));
		return true;
	}

	Stat stat(string path) {
		Stat st;
		map<string, Stat>::iterator file_map_iter = file_map.find(path);
                if (file_map_iter != file_map.end()) st = file_map_iter->second;
                return st;
	}

	bool isExist(string path) {
		map<string, Stat>::iterator file_map_iter = file_map.find(path);
                if (file_map_iter != file_map.end()) return true;
		return false;
	}
};

