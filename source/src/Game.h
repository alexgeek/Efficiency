#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include <iostream>

#include "camera/Camera.h"
#include "camera/CameraArcBall.h"
#include "world/Dimension.h"
#include "Input.h"
#include "render/RenderRect.h"
#include "script/ScriptEngine.h"
#include "WindowContext.h"
#include "util.h"
#include "render/RenderWorld.h"

class Game
{
    public:
      Game();
      ~Game();
      int Init();
      int Start();

      /* accessors & mutators */
      RenderWorld* GetRenderWorld() { return &render_world_; };
      Camera* GetActiveCamera() const { return camera_; }
      void SetActiveCamera(Camera *camera) { camera_ = camera; }
    protected:
    private:
      // core func
      WindowContext* window_context_;
      ScriptEngine script_engine_;
      Input* input_;
      Camera* camera_;

      // containers
      map<int, Dimension*> dimensions_;

      // scripts
      Script* action_script_;
      Script* update_script_;
      Script* render_script_;

      // render
      RenderRect* rect_;
      RenderWorld render_world_;

      // sub-taks of initialisation
      int init_context();
      int init_input();
      int init_scripting();
      int init_rendering();

      int load_dimensions();
      void update_dimensions();

      int main_loop();

};

#endif
