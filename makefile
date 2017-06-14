CXX = g++
DEBUG = -g
RM = rm -f
PTHREAD = -lpthread
CFLAGS = -Wall $(DEBUG)
TARGET = Server Client

all: $(TARGET)
Server: Server.cpp
	$(CXX) -o Server Server.cpp $(CFLAGS) $(PTHREAD)
Client: Client.cpp
	$(CXX) -o Client Client.cpp $(CFLAGS)
clean:
	$(RM) $(TARGET)
