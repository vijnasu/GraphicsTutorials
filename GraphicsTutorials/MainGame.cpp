#include "MainGame.h"

#include <iostream>
#include <string>
#include "Errors.h"
#include "ImageLoader.h"

MainGame::MainGame() : 
	_window(nullptr), 
	_screenWidth(512), 
	_screenHeight(512), 
	_time(0.0f), 
	_gameState(GameState::PLAY)
{
}

MainGame::~MainGame()
{
}

void MainGame::run() {
	initSystems();

	_sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);
	_playerTexture = ImageLoader::loadPNG("Textures/grass5_0.png");
	gameLoop();
}

void MainGame::initSystems() {
	// Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// Open an SDL window
	_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);

	if (_window == nullptr) {
		fatalError("SDL Window could not be created.");
	}

	// Set up our OpenGL Context
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	
	if (glContext == nullptr) {
		fatalError("SDL_GL Context could not be created.");
	}

	// Set up glew (optional but recommended
	// might help with compatabilty issues for some people
	// glewExperimental = true;

	GLenum error = glewInit();

	if (error != GLEW_OK) {
		fatalError("Could not initalize GLEW.");
	}

	//Tell SDL that we want a double buffered windo so we don't get any flickering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0, 0.0, 1.0, 1.0);

	// initialize the shaders
	initShaders();
}

void MainGame::initShaders() {
	_colorProgram.compileShaders("./shaders/colorShading.vert", "./shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV"); 
	_colorProgram.linkShaders();
}

void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {
		processInput();
		_time += 0.01;
		drawGame();
	}
}

void MainGame::processInput() {
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;
		}
	}
}

void MainGame::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _playerTexture.id);

	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLuint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);

	_sprite.draw();

	glBindTexture(GL_TEXTURE_2D, 0);

	_colorProgram.unuse();

	SDL_GL_SwapWindow(_window);
}

