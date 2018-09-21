LIB = yamgl-0.0.5.a

CXX ?= g++
AR ?= ar
CXXFLAGS := -O3 -std=c++14

all:
	@echo "building yamgl..."
	@$(CXX) $(CXXFLAGS) -I.\inc -c src\y_device.cpp -o src\y_device.o
	@$(CXX) $(CXXFLAGS) -I.\inc -c src\y_font.cpp -o src\y_font.o
	@$(CXX) $(CXXFLAGS) -I.\inc -c src\y_painter.cpp -o src\y_painter.o
	@$(CXX) $(CXXFLAGS) -I.\inc -c src\y_widget.cpp -o src\y_widget.o
	@$(AR) cr $(LIB) src\y_device.o src\y_font.o src\y_painter.o src\y_widget.o 
	@echo "done"
	
clean:
	@rm -f src\y_device.o
	@rm -f src\y_font.o
	@rm -f src\y_painter.o
	@rm -f src\y_widget.o
	@rm -f $(LIB)