#include <iostream>
#include <fstream>
#include <map>
#include <bitset>
#include <cstdlib>
#include <string>

class Shanon {
public:
	void decode(char in[], char out[]);
	void encode(char in[], char out[]);

private:
	using Byte = unsigned char;
	using Code = std::string;
	Code next(Code);
};
