#include "Danger.h"

Danger::Danger(string path):AddOn(path) {

}

string Danger::getType() {
	return "Danger";
}