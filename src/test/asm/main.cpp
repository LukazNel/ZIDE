#include <Windows.h>
#include <iostream>
#include "zutils.h"



int main() {
	std::ofstream FileOut("file.hex");
    zutils::opcodelist Opcodelist("opcodes.csv");
    std::ifstream FileIn("file.asm");
	if (!FileIn.is_open()) {
		errout << "Error: file not found." << std::endl;
		exit(EXIT_FAILURE);
	}
    zutils::assm(FileIn, Opcodelist, errout);
    FileIn.close();
	FileOut.close();
    return 0;
}