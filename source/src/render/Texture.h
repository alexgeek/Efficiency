#ifndef GAME_TEXTURE_H
#define GAME_TEXTURE_H

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
