# Compiler
CP = g++
CC = gcc

# Compiler flags
CFLAGS = -std=c++11

# Includes (/usr/include is already included)
INCLUDES = -Iinclude

LIBA = libs/libglfw3.a libs/libdrawtext.a

# Link libraries
LIBS = -lGLEW -lGL -lGLU -lfreetype -lX11 -lXxf86vm -lXrandr -lpthread -lXi -llua -ldl

# Source files for project
SRCS = main.cpp Input.cpp Window.cpp Triangle.cpp Camera.cpp CameraArcBall.cpp
CSRC = util.c

# Get object names from source names
# $(target:find=replace)
OBJS = $(SRCS:.cpp=.o)
COBJS = $(CSRC:.c=.o)

# executable filename
MAIN = game

.PHONY: clean

all:    $(MAIN)
	@echo  Project Compiled

$(MAIN): $(OBJS)	$(COBJS)
	$(CP) $(CFLAGS) $(INCLUDES) $(COBJS) $(OBJS) $(LIBA) $(LIBS) -o $(MAIN)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@
    
.cpp.o:
	$(CP) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN) gl.log

