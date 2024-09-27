CXX = /opt/homebrew/opt/gcc/bin/g++-14

INC_DIR=/opt/homebrew/opt/freeglut/include
LIB_DIR=/opt/homebrew/opt/freeglut/lib


all:
	$(CXX) paint_app.cpp -o paint_app -I$(INC_DIR) -L$(LIB_DIR) -framework OpenGL -framework GLUT

clean:
	rm -f paint_app