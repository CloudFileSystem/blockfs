#
# Makefile
#
CC=g++
TARGET = main
CFLAGS = -g -Wall
LIBS = -lcrypto `pkg-config fuse --cflags --libs`
BOOST_LIBS = -lboost_system -lboost_filesystem

all: $(TARGET)

$(TARGET): $(TARGET).cpp sun.hpp fuse.hpp metadata.hpp stat.hpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp $(LIBS) $(BOOST_LIBS)

install:
	sudo apt-get install libboost-all-dev

debug:
	./main -d ./mnt

mount:
	./main ./mnt

umount:
	fusermount -u ./mnt

clean:
	$(RM) $(TARGET)

