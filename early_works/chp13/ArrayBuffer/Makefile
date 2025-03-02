CXX = g++
CXXFLAGS = -std=c++11

SRCS = ArrayBuffer.cpp SimpleTextEditor.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = a.out

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<


# make clean ,rm all generated file from this folder
clean:
	rm -f $(OBJS) $(TARGET)


# evetually it has same affect as excuting each following commands
#g++ -std=c++11 -c 1202.cpp -o 1202.o
#g++ -std=c++11 -c intarray.cpp -o intarray.o

#g++ 1202.o intarray.o -o a.out
