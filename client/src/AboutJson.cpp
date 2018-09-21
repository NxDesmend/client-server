#include "AboutJson.h"

bool AboutJson::readFile(const string& filename){
	ifstream i(filename);
    i >> jMessage;
	return true;
}
json AboutJson::getjMessage(){
	return jMessage;
}