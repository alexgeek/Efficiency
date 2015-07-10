#ifndef GAME_TEXTURE_H
#define GAME_TEXTURE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Texture
{
public:
    Texture(std::string file);
    unsigned int SizeX();
    unsigned int SizeY();
private:
    std::string file_;
};

#endif //GAME_TEXTURE_H
