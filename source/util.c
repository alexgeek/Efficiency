#include "util.h"

// http://r3dux.org/2012/07/a-simple-glfw-fps-counter/
double calcFPS(double t)
{
	// Static values which only get initialised the first time the function runs
	static double theTimeInterval = 1.0;
	static double t0Value       = 0; // Set the initial time to now
	static int    fpsFrameCount = 0;             // Set the initial FPS frame count to 0
	static double fps           = 0.0;           // Set the initial FPS value to 0.0
 
	// Get the current time in seconds since the program started (non-static, so executed every time)
	double currentTime = t;
 
	// Ensure the time interval between FPS checks is sane (low cap = 0.1s, high-cap = 10.0s)
	// Negative numbers are invalid, 10 fps checks per second at most, 1 every 10 secs at least.
	if (theTimeInterval < 0.1)
	{
		theTimeInterval = 0.1;
	}
	if (theTimeInterval > 10.0)
	{
		theTimeInterval = 10.0;
	}
 
	// Calculate and display the FPS every specified time interval
	if ((currentTime - t0Value) > theTimeInterval)
	{
		// Calculate the FPS as the number of frames divided by the interval in seconds
		fps = (double)fpsFrameCount / (currentTime - t0Value);

		// Reset the FPS frame counter and set the initial time to be now
		fpsFrameCount = 0;
		t0Value = t;
	}
	else // FPS calculation time interval hasn't elapsed yet? Simply increment the FPS frame counter
	{
		fpsFrameCount++;
	}
 
	// Return the current FPS - doesn't have to be used if you don't want it!
	return fps;
}

void glfw_error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

int load_texture()									// Load Bitmaps And Convert To Textures
{
	/* load an image file directly as a new OpenGL texture */
	GLuint texture = SOIL_load_OGL_texture
		(
		"assets/textures/grass.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	return texture;
}

int screenshot()
{
    int save_result = SOIL_save_screenshot
	(
		"assets/screen.bmp",
		SOIL_SAVE_TYPE_BMP,
		0, 0, 1024, 768
	);
	return save_result;
}