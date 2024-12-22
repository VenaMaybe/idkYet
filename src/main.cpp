#include <iostream>
#include "main_render.h"
#include "random.h"
#include "obj/obj_manager.h"

int main() {
	ObjMan manager;

	std::cout << "Hello World" << std::endl;

	beginRaylibEnv([&manager](){
		manager.render();
		manager.update();
	});

	// Meows back to the computer
	return 0;
}