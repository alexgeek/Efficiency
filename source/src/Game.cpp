#include "Game.h"

const std::string Game::Version = "V0";

Game::Game() :
        script_engine_(new ScriptEngine()),
        input_(&Input::Instance()) {
}

Game::~Game() {
    free(script_engine_);
    free(camera_);
    free(action_script_);
    free(update_script_);
    free(render_script_);
    free(rect_);
    for (std::map<int, Dimension *>::iterator it = dimensions_.begin(); it != dimensions_.end(); it++)
        delete it->second;
    glfwTerminate();
}

int Game::Init() {
    int ret = init_context();
    ret &= init_input();
    ret &= init_scripting();
    ret &= init_blocks();
    ret &= init_rendering();
    return ret;
}

int Game::Start() {
    load_dimensions();
    /* Loop until the user closes the window */
    GLFWwindow *window = window_context_->window();

    script_engine_->Set<Game>("game", this);
    int ret;
    ret = script_engine_->Exec("brender = BatchedRenderCube.new(\"assets/textures/hellstone.png\")");
    ret = script_engine_->Exec("print(Game.Version())");
    ret = script_engine_->Exec("for k,v in pairs(BatchedRenderCube) do print(k,v) end");
    ret = script_engine_->Exec("brender:BufferPosition(1,2,3)");
    ret = script_engine_->Exec("print(\"foo\", brender:BufferSize())");


    while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE))
        main_loop();
}

int Game::init_input() {
    GLFWwindow *window = window_context_->window();
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
    int ret = script_engine_->Init();
    if (ret) {
        //script_engine_->RegisterFunction(lua_set_camera, "ActiveCamera");
        script_engine_->RegisterFunction(lua_drawcube, "drawblock");
        script_engine_->RegisterFunction(lua_load_renderer, "load_renderer");
        script_engine_->RegisterFunction(lua_drawbatch, "drawbatch");
        script_engine_->RegisterFunction(lua_time, "time");
        script_engine_->RegisterFunction(lua_get_block, "getBlock");
        script_engine_->RegisterFunction(lua_get_block_by_name, "getBlockByName");
        script_engine_->RegisterFunction(lua_test, "test");


        script_engine_->Run("class.lua");
        script_engine_->Run("entity.lua");
        script_engine_->Run("world.lua");
        script_engine_->Run("component.lua");
        script_engine_->Run("block.lua");
        script_engine_->Run("physics.lua");
        script_engine_->Run("load.lua");

        action_script_ = script_engine_->MakeScript("action.lua");
        update_script_ = script_engine_->MakeScript("update.lua");
        render_script_ = script_engine_->MakeScript("render.lua");
    }
    return ret;
}

int Game::init_blocks() {
    BlockRegistry::Instance().RegisterBlock(new Block("stone"));
    BlockRegistry::Instance().RegisterBlock(new Block("dirt"));
    BlockRegistry::Instance().RegisterBlock(new Block("grass"));
    return 1;
}

int Game::init_rendering() {
    // ActiveCamera
    // renderers
    camera_ = new CameraArcBall(glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(4.9f, 4.9f, 4.9f));
    rect_ = new RenderRect("assets/textures/tex16.png", "inversion2");
    return 1;
}

int Game::main_loop() {
    GLFWwindow *window = window_context_->window();
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);

    //glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT /*| GL_STENCIL_BUFFER_BIT*/);

    // update input and actions
    Input::Instance().update(window);

    // update view and projection
    camera_->update(window);

    if (glfwGetKey(window, 'U'))
        script_engine_->Run(action_script_);

    script_engine_->Run(update_script_);
    script_engine_->Run(render_script_);

    render_world_.Render(ActiveCamera());

    if (glfwGetKey(window, 'F'))
        std::cout << "FPS: " << calcFPS(glfwGetTime()) << std::endl;
    if (glfwGetKey(window, 'Q'))
        screenshot();

    if (glfwGetKey(window, GLFW_KEY_ENTER))
        rect_->draw(camera_, glm::vec2(width, height));

    printOpenGLError();

    /* Swap front and back buffers */
    glfwSwapBuffers(window);
    /* Poll for and process events */
    glfwPollEvents();

    return 1;
}

int Game::load_dimensions() {
    dimensions_[0] = new Dimension();
    glm::vec2 spawn_region_size = glm::vec2(3, 3);
    for (int x = -spawn_region_size.x / 2; x < spawn_region_size.x / 2; x++)
        for (int z = -spawn_region_size.y / 2; z < spawn_region_size.y / 2; z++)
            dimensions_[0]->LoadRegion(x, z);
    return 1;
}

void Game::update_dimensions() {
    for (std::map<int, Dimension *>::iterator it = dimensions_.begin(); it != dimensions_.end(); it++)
        it->second->Update();
}
