#include <iostream>

#include "engine.h"

int main(int argc, char** argv)
{
	// Start an engine and run it then cleanup after


	// Create the engine
	Engine* engine = new Engine("Marlo Ongkingco PA3", 800, 600);

	// Engine initialization

	if (!engine->Initialize()) {
		// Engine did not initialize properly,
		// destroy it and return early
		printf("The engine failed to start.\n");
		delete engine;
		engine = NULL;
		return 1;
	}

	// Run the engine
	engine->Run();

	// Destroy the engine
	delete engine;
	engine = NULL;

	return 0;
}
