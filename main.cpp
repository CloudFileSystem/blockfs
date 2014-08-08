/* -main.cpp----------------------------------------------------------------- */
#include <iostream>
#include <fstream>
#include <cstring>

#define FUSE_USE_VERSION 30
#include <fuse.h>

#include "sun.hpp"
#include "fuse.hpp"

using namespace std;

/* -Fuse Operation Function-------------------------------------------------- */
//static int fuse_getattr(const char *path, struct stat *stbuf) {
//	int res = 0;
//
//	std::cout << "FUSE GETATTR" << std::endl;
//
//	memset(stbuf, 0, sizeof(struct stat));
//
//	if (strcmp(path, "/") == 0) {
//		stbuf->st_mode = S_IFDIR | 0755;
//		stbuf->st_nlink = 2;
//	}
//	//} else if (strcmp(path, hello_path) == 0) {
//	//	stbuf->st_mode = S_IFREG | 0444;
//	//	stbuf->st_nlink = 1;
//	//	stbuf->st_size = strlen(hello_str);
//	//} else {
//	//	res = -ENOENT;
//	//}
//
//	return res;
//}

/* -main--------------------------------------------------------------------- */
int main(int argc, char **argv) {
	return fuse_main(argc, argv, new Fuse(), NULL);
	/*
	char buff[1024];
	std::string *message = new std::string("Hello world!!");
	SunFile *file = new SunFile((char *)"/tuntunkun.conf");
	file->write((char *)message->c_str(), message->length() + 1);
	file->read(buff, 14);
	std::cout << *message << std::endl;
	std::cout << buff << std::endl;
	*/
}

