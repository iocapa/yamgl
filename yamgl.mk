MODULES = src/y_device.o src/y_font.o src/y_painter.o src/y_widget.o

CXX ?= g++
AR ?= ar
CXXFLAGS += -I./inc

.PHONY : all

all: $(MODULES)
	@$(AR) cr yamgl.a $(MODULES)

%.o: %.cxx
	@$(CXX) $(CXXFLAGS) -c $(input) -o $(output)
	
clean:
	@rm -f $(MODULES)
	@rm -f *.a