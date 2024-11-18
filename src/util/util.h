#pragma once
#include <cstddef>
#include <stdio.h>


namespace pk {
	
	std::size_t hash_str(const char* s);

	void readstr(char* buffer, FILE* file);

}