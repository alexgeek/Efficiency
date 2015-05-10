#ifndef FRUSTRUM_H
#define FRUSTRUM_H

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

class Game
{
    public:
      Game();
      ~Game();
      int Init();
      int Start();

      /* accessors & mutators */
      Camera* camera() const { return camera_; }
      void set_camera(Camera* camera) { camera_ = camera; }
    protected:
    private:
      WindowContext* window_context_;
      ScriptEngine script_engine_;
      Input* input_;
      Camera* camera_;

      map<int, Dimension*> dimensions_;

      Script* action_script_;
      Script* update_script_;
      Script* render_script_;
      RenderRect* rect_;

      int init_context();
      int init_input();
      int init_scripting();
      int init_rendering();

      int load_dimensions();
      void update_dimensions();

      int main_loop();

};

#endif
