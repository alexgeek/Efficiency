#include "Game.h"

Game::Game() :
  script_engine_(ScriptEngine()),
  input_(&Input::instance())
{
}

Game::~Game() {
  free(camera_);
  free(action_script_);
  free(update_script_);
  free(render_script_);
  free(rect_);
  glfwTerminate();
}

int Game::Init() {
  int ret = init_context();
  ret &= init_input();
  ret &= init_rendering();
  ret &= init_scripting();
  return ret;
}

int Game::Start() {
  /* Loop until the user closes the window */
  GLFWwindow* window = window_context_->window();
  while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE))
    main_loop();
}

int Game::init_input() {
  GLFWwindow* window = window_context_->window();
  glfwSetCharCallback(window, &Input::glfw_character_callback);
  glfwSetKeyCallback(window, &Input::glfw_key_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  return 1;
}

int Game::init_context() {
  window_context_ = new WindowContext(1024, 768, "Efficiency");
  return window_context_->Init();
}

int Game::init_scripting() {
  int ret = script_engine_.Init();
  if (ret) {
    script_engine_.RegisterFunction(lua_set_camera, "camera");
    script_engine_.RegisterFunction(lua_drawcube, "drawblock");
    script_engine_.RegisterFunction(lua_load_renderer, "load_renderer");
    script_engine_.RegisterFunction(lua_drawbatch, "drawbatch");
    script_engine_.RegisterFunction(lua_time, "time");

    script_engine_.Run("class.lua");
    script_engine_.Run("entity.lua");
    script_engine_.Run("world.lua");
    script_engine_.Run("component.lua");
    script_engine_.Run("block.lua");
    script_engine_.Run("physics.lua");
    script_engine_.Run("load.lua");

    action_script_ = script_engine_.MakeScript("action.lua");
    update_script_ = script_engine_.MakeScript("update.lua");
    render_script_ = script_engine_.MakeScript("render.lua");
  }
  return ret;
}

int Game::init_rendering() {
  // camera
  // renderers
  camera_ = new CameraArcBall(glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(4.9f, 4.9f, 4.9f));
  rect_ = new RenderRect("assets/textures/tex16.png", "inversion2");
}

int Game::main_loop() {
  GLFWwindow* window = window_context_->window();
  int width, height;
  glfwGetWindowSize(window, &width, &height);
  glViewport(0, 0, width, height);

  //glClearStencil(0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT /*| GL_STENCIL_BUFFER_BIT*/);

  // update input and actions
  Input::instance().update(window);

  // update view and projection
  camera_->update(window);

  if(glfwGetKey(window, 'U'))
      script_engine_.Run(action_script_);

  script_engine_.Run(update_script_);
  script_engine_.Run(render_script_);

  if(glfwGetKey(window, 'F'))
      std::cout << "FPS: " << calcFPS(glfwGetTime()) << std::endl;
  if(glfwGetKey(window, 'Q'))
      screenshot();

  if(glfwGetKey(window, GLFW_KEY_ENTER))
      rect_->draw(camera_, glm::vec2(width, height));

  printOpenGLError();

  /* Swap front and back buffers */
  glfwSwapBuffers(window);
  /* Poll for and process events */
  glfwPollEvents();

  return 1;
}
