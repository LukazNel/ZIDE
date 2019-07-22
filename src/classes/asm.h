#ifndef _ZASM_H_
#define _ZASM_H_

#include "zutils.h"

namespace zutils {
class assembler {
public:
    void preparse(std::ifstream& Input, std::ofstream& Output);
private:
    std::vector<std::string> LabelStack;
};
}

#endif
