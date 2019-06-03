CC := g++
CPPFLAGS := -Wall -Werror -pedantic -std=c++17 -g -O3
TARGET := markov-chain

SRCS := $(wildcard ./src/*.cc)
OBJS := $(patsubst %.cc,%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CPPFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $<

clean:
	rm -rf $(TARGET) ./src/*.o
	
.PHONY: all clean
