#include <iostream>
#include <cstring>
#include "zutils.h"

int main() {
    zutils::opcodelist Opcodes;
    Opcodes.getOpcodes("../content/opcodes.csv");

    //std::string Hexline = zutils::importHex("file.hex");
    //zutils::vectorlist Vectors;
    //Vectors.getVectors(Hexline, true);
    std::ifstream FileIn("../content/file.hex");
    std::string Hexline, Line;

    getline(FileIn, Line);
    Line = Line.substr(strlen(":40000000") + 112);
        Line = Line.substr(0, Line.size()-2);
        while(Line != "") {
            Hexline += Line;
            getline(FileIn, Line);
            Line = Line.substr(strlen(":40000000"));
            Line = Line.substr(0, Line.size()-2);
        }
        FileIn.close();

    std::ofstream FileOut("../content/file.asm");
    zutils::dism(Hexline, Opcodes, FileOut);
    FileOut.close();
}
