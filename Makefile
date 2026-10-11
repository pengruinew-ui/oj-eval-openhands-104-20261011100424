CXX = g++
CXXFLAGS = -O2 -Wall
TARGET = code
SOURCE = solution.cpp

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)