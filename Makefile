CC = g++

CFLAGS = -Wall -g

TARGETS := $(wildcard *.cpp)
TARGET_EXECUTABLES := $(TARGETS:.cpp=.app)

all: $(TARGET_EXECUTABLES)

%.app: %.cpp
	@$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGET_EXECUTABLES)
