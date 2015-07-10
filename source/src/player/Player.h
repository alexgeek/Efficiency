#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <string>
#include <glm/gtc/matrix_transform.hpp> // rotate etc
#include <glm/gtc/type_ptr.hpp>

class Player {
public:
    Player(std::string name);
    Player(std::string name, glm::vec3 position);

    std::string GetName() const { return name_; }
    void SetName(std::string name) { name_ = name; }
    glm::vec3 GetPosition() const { return position_; }
    void SetPosition(glm::vec3 position) { position_ = position; }

private:
    glm::vec3 position_;
    std::string name_;
};

#endif //GAME_PLAYER_H