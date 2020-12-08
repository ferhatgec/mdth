/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <iostream>
#include <string>
#include <fstream>

#include <Mdth.hpp>
#include <StringTools.hpp>

static bool is_list = false;

void HelpFunction(char* argument) {
	std::cout << argument << " file\n";
}

std::string
Mdth::is_token(std::string &data) {
	unsigned i = 0;
	
	if(stringtools::Find(data, "#")) {
		data = stringtools::ltrim(data);

		if(data[0] == '#') {
			i = stringtools::Count(data, '#');
		
			// #### test
			if(data[i] == ' ') {
				data.erase(0, i + 1);
			
				if(i > 6) {
					i = 6;
				}
			
				data = "<h" + std::to_string(i) + "> " + data+ " </h" + std::to_string(i) + ">";   
			}
		}
	} else if(stringtools::Find(data, "*")) {
		data = stringtools::ltrim(data);
		
		if(data[0] == '*' && data[1] == ' ') {
			data.erase(0, 2);
				
			if(is_list == false) {
				data = "<ul>\n<li><p>" + data + "</p></li>";
				is_list = true;
			} else {
				data = "<li><p>" + data + "</p></li>";
			}
		} else if(data[0] == '*' && data[1] == '*') {
			data = stringtools::Between(data, "**", "**");
		
			data = "<p><strong>" + data + "</strong></p>";
		} else if(is_list == true) {
			data = "</ul>";
			is_list = false;
		} else {
			data = "<p>" + data + "</p>";	
		}
	} else if(stringtools::Find(data, "~~")) {
		data = stringtools::ltrim(data);
		
		if(data[0] == '~' && data[1] == '~') {
			data = stringtools::Between(data, "~~", "~~");
			data = "<p><del>" + data + "</del></p>";
		}
	} else if(stringtools::Find(data, "!")) {
		data = stringtools::ltrim(data);
		
		if(data[0] == '!') {
			data = "<p><img src=\"" + stringtools::Between(data, "(", ")") + "\" alt=\"" + stringtools::Between(data, "![", "]") + "\"></p>";
		}
	} else if(is_list == true) {
			data = "</ul>";
			is_list = false;
	}
	
	return data;
}


void
Mdth::read(std::string file) {
	std::ifstream read(file.c_str());
	std::string data = "";
	
	if(read.is_open()) {
		while(std::getline(read, data)) {
			std::cout << is_token(data) << "\n";
		}		
	} else {
		std::cout << "[ERROR]: File is not open!\n";
	}	
}

int main(int argc, char** argv) {
	if(argc <= 1) {
		HelpFunction(argv[0]);
		return 0;
	}	
	
	Mdth converter;
			
	std::string file(argv[1]);	
		
	converter.read(file);	
	
	return 0;
}
