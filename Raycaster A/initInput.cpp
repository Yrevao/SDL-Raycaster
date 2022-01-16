#include "Input.h"

Input::Input() {
	mainLoop();
	quit();
}
void Input::quit() {
	runData.quit();
}