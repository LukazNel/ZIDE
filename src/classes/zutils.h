#ifndef _ZUTILS_H_
#define _ZUTILS_H_

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>
#include <ostream>
#include <cstring>
#include <Windows.h>

class dbgout : public std::stringbuf {
protected:
	virtual int sync() {
		OutputDebugString(this->str().c_str());
		this->str("");
		
		return 0;
	}
};

using ushort = unsigned short;
static dbgout DBGOut;
static std::ostream errout(&DBGOut);

namespace zutils {
enum operandtype {IM = 1, p_b, cc, Ir, Irr, r, rr, IR, IRR, R, RR, ER, DA, RA, X, V, unknown, num_types};

class opcode {
public:
    opcode(const ushort hex_value, const std::string mnemonic, const ushort num_fetches, const ushort op_count, const bool is_reversed, std::string* ops);
    std::string parse(std::string Hexline);
    std::string hexify(std::string Param1, std::string Param2);
    ushort fetches() const;
    ushort hex() const;
    std::string mem() const;
    ushort operand(int Index) const;
    ushort operand() const;
    bool is_reversed() const;

private:
    const ushort hex_value;
    char mnemonic[6];
    const ushort num_fetches;
    const ushort opcount;
    const bool reversed;
    bool is_extra;
    bool is_special;
    ushort ops[3];

    std::string notate(ushort Operand, std::string& Hexline);
    std::string get_hex(std::string Parameter);
    ushort getparametertype(std::string Parameter);
};

class opcodelist {
public:
    opcodelist();
    opcodelist(std::string FileName);
    void getOpcodes(std::string FileName);
    opcode* find(ushort hex_value);
    opcode* find(std::string mem, ushort Parameter1_H, ushort Parameter2_H, ushort Parameter3_H);
    ~opcodelist();
private:
    std::vector<opcode> Opcodes;
    
};

std::string to_hex(ushort value, ushort precision = 4);
std::string to_hex(short value, ushort precision = 4);
std::string get_hex(const std::string In);
void dism(std::string Hexline, opcodelist Opcodes, std::ostream& Output);
void assm(std::istream& Input, opcodelist Opcodes, std::ostream& Output);

const std::vector<const char*> conditionCodes {"F", "LT", "LE", "ULE", "OV", "MI", "Z", "C", "T", "GE", "GT", "UGT", "NOV", "PL", "NE", "NC"};
const std::vector<const char*> operandtype_C {"-", "IM", "p_b", "cc", "Ir", "Irr", "r", "rr", "IR", "IRR", "R", "RR", "ER", "DA", "RA", "X", "V"};
const std::vector<const char*> OperandShorthand {"-", "#", ";", "cc", "@r", "@rr", "r", "rr", "@"};
ushort getoperandtype(std::string Operand);
void getParameterType(std::string& Parameter_S, ushort& ParameterType);
void verifyParameter(std::string& Parameter_S, ushort& ParameterType);
}

#endif
