#include "PowerUp.h"

PowerUp::PowerUp(string path) :AddOn(path) {

}

string PowerUp::getType() {
	return "PowerUp";
}