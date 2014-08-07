#
# Makefile
#
CC=g++
TARGET = main
CFLAGS = -g -Wall
LIBS = -lcrypto `pkg-config fuse --cflags --libs`

all: $(TARGET)

$(TARGET): $(TARGET).cpp sun.hpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp $(LIBS)

debug:
	./main -d ./mnt

mount:
	./main ./mnt

umount:
	fusermount -u ./mnt

clean:
	$(RM) $(TARGET)

