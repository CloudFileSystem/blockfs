#
# Makefile
#
CC=g++
TARGET = main
#CFLAGS = -g -Wall
LIBS = -lcrypto

all: $(TARGET)

$(TARGET): $(TARGET).cpp sun.hpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp $(LIBS)

clean:
	$(RM) $(TARGET)

