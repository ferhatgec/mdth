/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef MDTH_HPP
#define MDTH_HPP

#include <iostream>
#include <string>

class Mdth {
public:
	std::string is_token(std::string &data);

	void read(std::string file);
};

#endif // MDTH_HPP
