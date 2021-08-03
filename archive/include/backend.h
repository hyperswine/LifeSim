// Included by Vizr frontend. Declares all functions to be used
#pragma once
#include <string>

// avoids a lot of boilerplate code
#define c_for(j, n) for(int j=0; j<n; j++)

// custom stdout logging function
void c_log(std::string);
// custom stderr logging function
void e_log(const char*);
