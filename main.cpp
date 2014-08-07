/* -main.cpp----------------------------------------------------------------- */
#include <iostream>
#include "sun.hpp"

/* -main--------------------------------------------------------------------- */
int main(int argc, char **argv) {
	std::string *message = new std::string("Hello world!!");
	SunFile *file = new SunFile((char *)"/etc/resolv.conf");
	file->write((char *)message->c_str(), message->length());
	
	return 0;
}

