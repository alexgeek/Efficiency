# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++11

# Includes (/usr/include is already included)
INCLUDES = -Iinclude

LIBA = libs/libglfw3.a libs/libdrawtext.a

# Link libraries
LIBS = -lGLEW -lGL -lGLU -lfreetype -lX11 -lXxf86vm -lXrandr -lpthread -lXi -llua -ldl

# Source files for project
SRCS = main.cpp Input.cpp Window.cpp Triangle.cpp Camera.cpp CameraArcBall.cpp

# Get object names from source names
# $(target:find=replace)
OBJS = $(SRCS:.cpp=.o)

# executable filename
MAIN = game

.PHONY: clean

all:    $(MAIN)
	@echo  Project Compiled

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBA) $(LIBS) -o $(MAIN)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN) gl.log

