CXX = /opt/homebrew/opt/gcc/bin/g++-14

INC_DIR=/opt/homebrew/opt/freeglut/include
LIB_DIR=/opt/homebrew/opt/freeglut/lib

# MacOS
LDFLAGS = -framework OpenGL -framework GLUT
# Linux
# LDFLAGS =  -lGL -lglut


all:
	$(CXX) main.cpp -I$(INC_DIR) -I./ -L$(LIB_DIR) -o app $(LDFLAGS)

.PHONY: test
test:
	$(CXX) main.cpp -I$(INC_DIR) -I./ -L$(LIB_DIR) -o app $(LDFLAGS)
	./app

.PHONY: clean
clean:
	rm -rf app