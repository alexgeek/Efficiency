#ifndef FRUSTRUM_H
#define FRUSTRUM_H

#include <unordered_map>
#include <iostream>
#include "WindowContext.h"
#include "ScriptEngine.h"
#include "Input.h"
#include "CameraArcBall.h"
#include "Camera.h"
#include "RenderRect.h"
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

      Script* action_script_;
      Script* update_script_;
      Script* render_script_;
      RenderRect* rect_;

      int init_context();
      int init_input();
      int init_scripting();
      int init_rendering();

      int main_loop();

};

#endif
