# Compilers
CP = g++
CC = gcc

# Compiler flags
CFLAGS = -std=c++11 -g

# Includes (/usr/include is already included)
INCLUDES = -Iinclude

# Static libraries included in project
LIBA = libs/libglfw3.a libs/libdrawtext.a libs/libSOIL.a

# Link libraries
LIBS = -lGLEW -lGL -lGLU -lX11 -lXxf86vm -lXrandr -lpthread -lXi -llua -ldl

# Source files for project
SRCS = main.cpp Game.cpp Input.cpp WindowContext.cpp ScriptEngine.cpp Script.cpp Triangle.cpp Camera.cpp CameraArcBall.cpp Shader.cpp RenderCube.cpp RenderQuad.cpp RenderRect.cpp BatchedRenderCube.cpp Debug.cpp Dimension.cpp Region.cpp
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
#	./$(MAIN)

$(MAIN): $(OBJS)	$(COBJS)
	$(CP) $(CFLAGS) $(INCLUDES) $(COBJS) $(OBJS) $(LIBA) $(LIBS) -o $(MAIN)

# compile (CSRC) c sources with c compiler
.c.o:
	$(CC) $(INCLUDES) -c $<  -o $@

# compile (SRCS) c++ source with c++ compiler
.cpp.o:
	$(CP) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN) gl.log
