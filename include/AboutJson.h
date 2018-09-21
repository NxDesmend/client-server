#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
using namespace std;
using json = nlohmann::json;


class AboutJson{
	private:
	    json jMessage;
	public:
	    bool readFile(const string& filename);
		json getjMessage();	
};