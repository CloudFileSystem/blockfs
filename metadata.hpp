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

	bool make_directory(string path) {
		// Set Context Infomation of Stat
		Stat new_directory;
		new_directory.setDefaultContext().setDirectory();
		boost::filesystem::path parser(path);

		// Parse path
		string full_path = parser.string();
		string file_path = parser.parent_path().string();
		string file_name = parser.filename().string();

		// File path Mapping
		path_map.insert(pair<string, string>(file_path, file_name));
		file_map.insert(pair<string, Stat>(full_path, new_directory));
		return true;
	}



	bool remove_directory(string path) {
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

