CXX = g++
DEBUG = -g
RM = rm -f
LIBS = -lpthread -lncurses
CFLAGS = -Wall $(DEBUG)
TARGET = Server Client

all: $(TARGET)
Server: Server.cpp
	$(CXX) -o Server Server.cpp $(CFLAGS) $(LIBS)
Client: Client.cpp
	$(CXX) -o Client Client.cpp $(CFLAGS) $(LIBS)
clean:
	$(RM) $(TARGET)
