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

	struct Data {
		float p = 0.f;
		float b = 0.f;
		short l = 0;
		std::string code = "";
	};
};
