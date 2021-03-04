#include <SDL.h>
#include <Page.h>
#include <glad/glad.h>
#include <stdio.h>

SDL_Window* window;
SDL_GLContext gl_context;

GLuint vertexShaderID;
const GLchar* vertexShader = R"glsl(
	#version 330 core
	layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

	out vec2 TexCoords; // Output to the fragment shader (the texture coordinates)

	uniform mat4 model; // Transformation matrix

	void main()
	{
		// Set TexCoords output to vec2 of the last 2 elements in vertex
		TexCoords = vertex.zw;

		// Transform xy vertices based on model
		gl_Position = model * vec4(vertex.xy, 0.0, 1.0); 
	}
)glsl";

GLuint fragmentShaderID;
const GLchar* fragmentShader = R"glsl(
	#version 330 core
	in vec2 TexCoords;
	out vec4 color;

	uniform sampler2D image; # sampler2D is a built-in glsl data-type

	void main()
	{    
		# built-in texture function to return color vectors
		color = texture(image, TexCoords);
	}  
)glsl";

// Use sdl_die when an SDL error occurs to print out the error and exit
// argument err_msg can be anything, but try to keep it related to the error
void sdl_die(const char* err_msg)
{
	printf("%s: %s\n", err_msg, SDL_GetError());
	SDL_Quit();
	exit(1);
}

// This takes care of initializing everything SDL needs to begin running
void init() {
	// Initialize video mode of SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		sdl_die("Error initializing SDL video mode :(");
	}

	// This was all from the sample code, I haven't looked into it yet
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	// Create the flags for creating the window
	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	// Create a new centered game window based on window_flags (1280x720 for now)
	window = SDL_CreateWindow("Game Core", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);

	// Create the Game opengl context
	gl_context = SDL_GL_CreateContext(window);


	// Create and compile the vertex shader
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &vertexShader, NULL);
    glCompileShader(vertexShaderID);

    // Create and compile the fragment shader
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &fragmentShader, NULL);
    glCompileShader(fragmentShaderID);

	// Load opengl? I can barely find information/documentation about glad
	gladLoadGL();
}

// Test function for rendering entities
void renderEntity() {

}

int render() {
	// Show the current context
	SDL_GL_MakeCurrent(window, gl_context);

	//////////////////////////////
	// RENDERING CODE GOES HERE //
	//////////////////////////////
	// Everything before the ending ///////'s is just test code and will eventually be deleted


	// Clear the buffer with a red background
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(window); // Show the buffer by bringing it to the front
	SDL_Delay(1000); // Wait 1 sec before continuing

	// Clear the buffer with a dark red background
	glClearColor(0.5, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(window); // Show the buffer by bringing it to the front
	SDL_Delay(1000); // Wait 1 sec before continuing


	//////////////////////////////

	return 0;
}


int main(int argc, char* argv[]) {
	// Initialize OpenGL and necessary SDL objects
	init();

	SDL_Event event;
	int close_window = false;
	///////////////
	// Game loop //
	///////////////
	while (!close_window) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				close_window = true;
			}
		}

		///////////////
		// PAGE TEST
		// This loop will render whatever occurs in render()
		// followed by a new Page and whatever is in its render()
		// This is just a test to make sure page rendering is correctly set up
		render();
		Page page(window);
		page.render();
		///////////////
	}

	// Take care of deleting SDL objects and cleanly exit 
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
