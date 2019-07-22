#include "zutils.h"

zutils::opcode::opcode(const ushort hex_value, const std::string Mem, const ushort num_fetches, const ushort op_count, const bool is_reversed, std::string* operands)
    : hex_value(hex_value), num_fetches(num_fetches), opcount(op_count), reversed(is_reversed), is_special(false) {
    Mem.copy(mnemonic, Mem.size()+1);
    mnemonic[Mem.size()] = '\0';

    if ((hex_value & 0xF) >= 0xA && (hex_value & 0xF) <= 0xE)
        is_special = true;

    for (int i = 0; i < 3; i++) {
        ops[i] = getoperandtype(operands[i]);
    }
    (hex_value>>8) == 0x1F ? is_extra = true : is_extra = false;
}

std::string zutils::opcode::parse(std::string Hexline) {
    if (opcount == 0)
        return std::string(mnemonic);

    std::string opout[3];
    for (int i = 0; i < opcount; i++) {
        opout[i] = notate(ops[i], Hexline);
    }

    std::stringstream Output;
    if (opcount == 1) {
        Output << mnemonic << ' ' << opout[0];
    } else if (opcount == 3) {
        if (ops[2] != RA)
            Output << mnemonic << ' ' << opout[0] << ", " << opout[1] << ", " << opout[2];
        else if (reversed == true)
            Output << mnemonic << ' ' << opout[2] << '(' << opout[1] << "), " << opout[0];
        else if (hex_value == 0x89)
            Output << mnemonic << ' ' << opout[2] << '(' << opout[0] << "), " << opout[1];
        else Output << mnemonic << ' ' << opout[0] << ", " << opout[2] << '(' << opout[1] << ')';
    } else if (hex_value == 0x87) {
        Output << mnemonic << ' ' << opout[1] << ", @.ER(" << opout[0] << ')';
    } else if (hex_value == 0x97) {
        Output << mnemonic << " @.ER(" << opout[0] << "), " << opout[1];
    }  else if (reversed == true) {
        Output << mnemonic << ' ' << opout[1] << ", " << opout[0];
    } else {
        Output << mnemonic << ' ' << opout[0] << ", " << opout[1];
    }
    return Output.str();
}

std::string zutils::opcode::notate(ushort Operand, std::string& Hexline) {
    std::stringstream s_out;

    ushort Offset = 0;
    switch (Operand) {
    case IM : s_out << '#' << Hexline.substr(0, Offset = 2) << 'h';
        break;
    case Ir : s_out << "@r" << std::stoi(Hexline.substr(0, Offset = 1), nullptr, 16);
        break;
    case IR : s_out << '@' << Hexline.substr(0, Offset = 2) << 'h';
        break;
    case Irr : s_out << "@rr" << std::stoi(Hexline.substr(0, Offset = 1), nullptr, 16);
        break;
    case IRR : s_out << '@' <<  Hexline.substr(0, Offset = 2) << 'h';
        break;
    case r : {if ((hex_value & 0xF) >= 0xA && (hex_value & 0xF) <= 0xE) {
            s_out << 'r' << (hex_value>>4);
        } else {
            s_out << 'r' << std::stoi(Hexline.substr(0, Offset = 1), nullptr, 16);
        }
        break;}
    case R : s_out << Hexline.substr(0, Offset = 2) << 'h';
        break;
    case rr : s_out << "rr" << std::stoi(Hexline.substr(0, Offset = 1), nullptr, 16);
        break;
    case RR : s_out << Hexline.substr(0, Offset = 2) << 'h';
        break;
    case ER : s_out << Hexline.substr(Hexline.size() == 4 ? 1 : 0, Offset = 3) << 'h';
        break;
    case DA : s_out << Hexline.substr(0, Offset = 4) << 'h';
        break;
    case RA : {short value = static_cast<short>(std::stoi(Hexline.substr(0, Offset = 2), nullptr, 16));
        value >> 7 == 1 ? value |= 0xFF00 : value; //zutils::to_hex(static_cast<short>(std::stoi(Hexline.substr(0, Offset = 2), nullptr, 16)), 2) << 'h';
        s_out << value;
        break;}
    case X : {short value = static_cast<short>(std::stoi(Hexline.substr(0, Offset = 2), nullptr, 16));
        value >> 7 == 1 ? value |= 0xFF00 : value; //zutils::to_hex(static_cast<short>(std::stoi(Hexline.substr(0, Offset = 2), nullptr, 16)), 2) << 'h';
        s_out << value;
        break;}
    case V : s_out << "V";
        break;
    case p_b : {const int value = std::stoi(Hexline.substr(0, Offset = 1), nullptr, 16);
        s_out << (value>>7) << ", " << ((value>>4) & 7);
        break;}
    case cc : s_out << conditionCodes[hex_value>>4];
        break;
    default : s_out << "Whoops! Forgot one!";
    }
    Hexline = Hexline.substr(Offset);
    return s_out.str();
}

std::string zutils::opcode::hexify(std::string Param1, std::string Param2) {
    std::stringstream Out;
    if ((hex_value&0xF) >= 0xA && (hex_value&0xF) <= 0xE) {
        Out << Param1 << to_hex(static_cast<ushort>(hex_value&0xF), 1) << Param2;
    } else if (reversed == true) {
        Out << to_hex(hex_value, 2) << std::dec << Param2 << Param1;
    } else {
        Out << to_hex(hex_value, 2) << std::dec << Param1 << Param2;
    }
    return Out.str();
}

ushort zutils::opcode::fetches() const {
    return num_fetches - is_extra;
}

ushort zutils::opcode::hex() const {
    return hex_value;
}

std::string zutils::opcode::mem() const {
    return mnemonic;
}

ushort zutils::opcode::operand(int Index) const {
    return ops[Index-1];
}

ushort zutils::opcode::operand() const {
    return opcount;
}

bool zutils::opcode::is_reversed() const {
    return reversed;
}

zutils::opcodelist::opcodelist() {}

zutils::opcodelist::opcodelist(std::string FileName) {
    getOpcodes(FileName);
}

void zutils::opcodelist::getOpcodes(std::string FileName) {
    std::ifstream FileIn(FileName);

    std::string Line;
    getline(FileIn, Line); // Remove header
    while (getline(FileIn, Line)) {
        std::stringstream LineStream(Line);
        std::string In, mem;

        getline(LineStream, In, ',');//Dud

        getline(LineStream, In, ',');//Hex
        ushort hex = static_cast<unsigned short>(stoi(In, nullptr, 16));

        getline(LineStream, mem, ',');//Memnomic

        getline(LineStream, In, ',');//Fetches
        ushort fetches = static_cast<ushort>(stoi(In, nullptr, 10));

        getline(LineStream, In, ',');//Opcount
        ushort opcount = static_cast<ushort>(stoi(In, nullptr, 10));

        std::string ops[3];
        bool is_reversed = false;
        for (ushort i = 0; i < opcount; i++) {
            getline(LineStream, ops[i], ',');
            if (i == 0 && (ops[i].find('y') != std::string::npos || ops[i].find("IM") != std::string::npos))
                is_reversed = true;
            //ops[i] = zutils::getoperandtype(In);
        }
        if (mem.compare("srp") == 0) {
            is_reversed = false;
        }

        opcode currentOpcode(hex, mem, fetches, opcount, is_reversed, ops);
        Opcodes.push_back(currentOpcode);
    }
    FileIn.close();
}

zutils::opcode* zutils::opcodelist::find(ushort hex_value) {
    std::vector<opcode>::iterator OpIndex;
    OpIndex = std::find_if(Opcodes.begin(), Opcodes.end(),
                [&] (const zutils::opcode& Opcode) {
                    return hex_value == Opcode.hex();});
    if (OpIndex != Opcodes.end())
        return &(*OpIndex);
    else return nullptr;
}

zutils::opcode* zutils::opcodelist::find(std::string mem, ushort Parameter1_H, ushort Parameter2_H, ushort Parameter3_H) {
    std::vector<opcode>::iterator OpIndex;
    OpIndex = std::find_if(Opcodes.begin(), Opcodes.end(),
                           [&] (const zutils::opcode& Opcode) {
        if (Opcode.is_reversed() == true)
            return (mem.compare(Opcode.mem()) == 0) && (Parameter1_H == Opcode.operand(2)) && (Parameter2_H == Opcode.operand(1)) && (Parameter3_H == Opcode.operand(3));
        else
            return (mem.compare(Opcode.mem()) == 0) && (Parameter1_H == Opcode.operand(1)) && (Parameter2_H == Opcode.operand(2)) && (Parameter3_H == Opcode.operand(3));
    });
    if (OpIndex != Opcodes.end())
        return &(*OpIndex);
    else return nullptr;
}

zutils::opcodelist::~opcodelist() {}

std::string zutils::to_hex(ushort value, ushort precision) {
    std::string hex;
    for (ushort i = precision * 4; i > 0; i -= 4) {
        char digit = static_cast<char>((value>>(i-4))&0xF);
        digit > 9 ? digit = digit - 10 + 'A' : digit += '0';
        hex += digit;
    }
    return hex;
}

std::string zutils::to_hex(short value, ushort precision) {
    //value >> 7 == 1 ? value |= 0xFF00 : value;
    char dud = value >> 7 == 1 ? '-' : '+';
    return dud + to_hex(static_cast<ushort>((~value)&0x7), precision);
}

void zutils::dism(std::string Hexline, zutils::opcodelist Opcodes, std::ostream& Output) {
    while (Hexline != "") {
        //Read opcode hex value
        ushort HexValue = static_cast<ushort>(stoi(Hexline.substr(0, 2), nullptr, 16));
        if (HexValue == 0x1f) { //If opcode is extra
            HexValue = static_cast<ushort>((HexValue<<8) | stoi(Hexline.substr(2, 2), nullptr, 16));
            Hexline = Hexline.substr(2);
        }

        //Find mnemonic of opcode
        zutils::opcode* CurrentOpcode;
        CurrentOpcode = Opcodes.find(HexValue);

        //If opcode is not found
        if (CurrentOpcode == nullptr) {
            //!!
            Hexline = Hexline.substr(2);
            continue;
        }

        //Get operands of opcode from HexLine
        std::string Operands = Hexline.substr(2, 2*(CurrentOpcode->fetches()-1));
        Hexline = Hexline.substr(2*CurrentOpcode->fetches());

        Output << CurrentOpcode->parse(Operands) << "\t;" << zutils::to_hex(HexValue, 2) << Operands << std::endl;
    }
}

ushort zutils::getoperandtype(std::string Operand) {
    if (Operand.compare("-") == 0) {
        return 0;
    }

    if (Operand.find_first_of("0123456789") != std::string::npos) {
        //return s;
        Operand.pop_back();
    }

    if (Operand.find_first_of("xy") != std::string::npos)
        Operand.pop_back();

    auto index = std::find_if(operandtype_C.begin(), operandtype_C.end(),
                 [&] (const char* currentOperand) {
        return Operand.compare(currentOperand) == 0;
    });

    if (index == operandtype_C.end())
        return 0;
    else return static_cast<ushort>(std::distance(operandtype_C.begin(), index));
}

void zutils::getParameterType(std::string& Parameter_S, ushort& ParameterType) {
    //If parameter is blank, do nothing
    if (Parameter_S.size() == 0) {
        return;
    }

    if (ParameterType == 0) {
        auto OperandIndex = std::find_if(OperandShorthand.begin(), OperandShorthand.end(),
                     [&] (const char* currentOperand) {
            return Parameter_S.find(currentOperand) == 0;
        });

        if (OperandIndex != OperandShorthand.end()) {
            Parameter_S = Parameter_S.substr(strlen(*OperandIndex));
            ParameterType = static_cast<ushort>(std::distance(OperandShorthand.begin(), OperandIndex));
        } else {
            ParameterType = zutils::R;
        }
    }

    verifyParameter(Parameter_S, ParameterType);
    if (Parameter_S.find('h') != std::string::npos)
        Parameter_S.pop_back();
}

void zutils::verifyParameter(std::string& Parameter_S, ushort& ParameterType) {
    std::string Result;
    switch (ParameterType) {
    case IM : Parameter_S = get_hex(Parameter_S);
        break;
    case p_b : {
        break;
    }
    case cc : return; //Shouldnt be necessary
        //break;
    case R : {
        Parameter_S = zutils::get_hex(Parameter_S);
        switch (Parameter_S.size()) {
        case 2 : ParameterType = R;
            break;
        case 3 : ParameterType = ER;
            break;
        case 4 : ParameterType = DA;
            break;
        default : ParameterType = unknown;
        }
        break;
    }
	case X: Parameter_S = get_hex(Parameter_S);
    }
}

std::string zutils::get_hex(std::string In) {
    if (In[0] == '%') {
        In = In.substr(1);
    } else if (In[In.size()-1] == 'h') {
        In.pop_back();
    } else {
        //return std::string("Forgot hex sign.");
		std::stringstream convert;
		convert << std::hex << std::stoi(In) << std::dec;
		return convert.str();
    }

    if (In.find_first_not_of("0123456789ABCDEFabcdef") != std::string::npos) {
        return std::string("Invalid value.");
    } else {
        return In;
    }
}
