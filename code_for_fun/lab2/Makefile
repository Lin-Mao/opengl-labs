CXX = /opt/homebrew/opt/gcc/bin/g++-14

INC_DIR=/opt/homebrew/opt/freeglut/include
LIB_DIR=/opt/homebrew/opt/freeglut/lib


all:
	$(CXX) cover_the_spot.cpp -o cover_the_spot -I$(INC_DIR) -L$(LIB_DIR) -framework OpenGL -framework GLUT

clean:
	rm -f cover_the_spot