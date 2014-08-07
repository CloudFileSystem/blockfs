/* -main.cpp----------------------------------------------------------------- */
#include <iostream>

#define FUSE_USE_VERSION 30
#include <fuse.h>
#include "sun.hpp"

/* -struct------------------------------------------------------------------- */
static struct fuse_operations fuse_operation = {
};

/* -main--------------------------------------------------------------------- */
int main(int argc, char **argv) {
	return fuse_main(argc, argv, &fuse_operation, NULL);
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

