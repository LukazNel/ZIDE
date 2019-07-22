#include "asm.h"

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

static inline void rmcomment(std::string& Line) {
    Line = Line.substr(0, Line.find(';'));
}

/*ushort getParameterType(std::string Parameter_S, ushort* ParameterInfo) {
    if (Parameter_S.size() == 0) {
        return 0;
    }

    unsigned long i = Parameter_S.find_first_of('_');
    while (i != std::string::npos) {
        Parameter_S.erase(i, 1);
        Parameter_S.find_first_of('_');
    }

    if (Parameter_S.find('#') == 0) {
        Parameter_S = zutils::get_hex(Parameter_S.substr(1));
        ParameterInfo[0] = zutils::IM;
    } else if (Parameter_S.find(';') == 0) {
        ParameterInfo[0] = zutils::p_b;
    } else if (Parameter_S.find("@r") == 0) {
        Parameter_S = Parameter_S.substr(2);
        ParameterInfo[0] = zutils::Ir;
    } else if (Parameter_S.find('r') == 0) {
        Parameter_S = Parameter_S.substr(1);
        ParameterInfo[0] = zutils::r;
    } else if (Parameter_S.find('@') == 0) {
        Parameter_S = zutils::get_hex(Parameter_S.substr(1));
        ParameterInfo[0] = zutils::IR;
    } else if (Parameter_S.find("rr") == 0) {
        Parameter_S = Parameter_S.substr(2);
        ParameterInfo[0] = zutils::rr;
    } else if (Parameter_S.find("@rr") == 0) {
        Parameter_S = Parameter_S.substr(3);
        ParameterInfo[0] = zutils::Irr;
    } else if (Parameter_S.size() == 3){
        Parameter_S = zutils::get_hex(Parameter_S);
        ParameterInfo[0] = zutils::R;
    } else if (Parameter_S.size() == 4) {
        Parameter_S = zutils::get_hex(Parameter_S);
        ParameterInfo[0] = zutils::ER;
    } else if (Parameter_S.size() == 5) {
        Parameter_S = zutils::get_hex(Parameter_S);
        ParameterInfo[0] = zutils::DA;
    } else {
        Parameter_S = zutils::get_hex(Parameter_S);
        ParameterInfo[0] = zutils::unknown;
    }

    if (Parameter_S.find_first_of('h') != std::string::npos) {
        ParameterInfo[1] = std::stoi(P)
    }
}*/

void zutils::assembler::preparse(std::ifstream& Input, std::ofstream& Output) {
    std::string CurrentLine;
    int LineNum = 0;

    while (!Input.eof()) {
        LineNum++;
        getline(Input, CurrentLine);
        rmcomment(CurrentLine);
        trim(CurrentLine);

        if (CurrentLine.size() == 0) {
            Output << std::endl;
        } else if (CurrentLine[0] != '.') {
            Output << CurrentLine << std::endl;
        }

        if (CurrentLine.compare(".hex ") == 0) { //Skip .hex directive
            Output << CurrentLine << std::flush;
            continue;
        }

        std::stringstream LineStream;
        std::string Directive;
        LineStream >> Directive;

        if (Directive.compare(".define") == 0) {

        }
    }
}

void zutils::assm(std::istream& Input, zutils::opcodelist Opcodes, std::ostream& Output) {
    int LineNum = 0;
    std::vector<std::string> LabelStack;
    std::string CurrentLabel;

    //Loop until end of file is reached
    while (!Input.eof()) {
        std::string CurrentLine;

        do {
			LineNum++;
            getline(Input, CurrentLine); //Get the current line
            rmcomment(CurrentLine); //Remove any trailing comments
            trim(CurrentLine); //Remove all whitespaces
        } while (CurrentLine.size() == 0); //Repeat if resulting line is blank

        if (CurrentLine.find_first_of(':') != std::string::npos) { //Check for label
            if (CurrentLine.find_first_of(':') != CurrentLine.find_last_of(':')) {
                errout << "Error line " << LineNum << ": Multiple colons found." << std::endl;
				exit(EXIT_FAILURE);
            } else if (CurrentLine.find_first_of(':') != CurrentLine.size() - 1) {
                errout << "Error line " << LineNum << ": Label name must precede colon." << std::endl;
				exit(EXIT_FAILURE);
            } else if (CurrentLine.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_:") != std::string::npos) {
                errout << "Error line " << LineNum << ": Label incorrectly named." << std::endl;
                exit(EXIT_FAILURE);
            }

            CurrentLine.pop_back(); //Remove the colon
            LabelStack.push_back(CurrentLabel); //Add the current label to the stack
            CurrentLabel = CurrentLine; //Begin new label
        errout << "Debug: Added line " << LineNum << " as label." << std::endl;
            continue;
        } else if (CurrentLine.compare(".hex ") == 0) { //Check for directive
            Output << CurrentLine.substr(strlen(".hex ")); //Print hex values as-is
        }

        //If the current line is not a label or directive it should be an assembly statement
        std::stringstream LineStream(CurrentLine);

        std::string Mnemonic, Parameter1_S, Parameter2_S, Parameter3_S;
        ushort Parameter1_H = 0, Parameter2_H = 0, Parameter3_H = 0;
        getline(LineStream, Mnemonic, ' ');
        getline(LineStream, Parameter1_S, ',');

        //Check for special cases
        if (Mnemonic.compare("bit") == 0 || Mnemonic.compare("btj") == 0) {
            if (Parameter1_S.size() != 1) {
                errout << "Error line " << LineNum << ": Syntax should be \'polarity, bit\'" << std::endl;
                exit(EXIT_FAILURE);
            }
            std::string tmp;
            getline(LineStream, tmp, ',');
            trim(tmp);
            Parameter1_S += ';' + tmp;
            Parameter1_H = zutils::p_b;

        }
        getline(LineStream, Parameter2_S, ',');
        ltrim(Parameter2_S);
        LineStream >> Parameter3_S;

        if (Mnemonic.compare("jr") == 0 || Mnemonic.compare("jp") == 0) {
			if (Parameter1_S.find('@') == 0) {
				Parameter1_H = zutils::IRR;
			} else {
				auto ConditionIndex = std::find_if(conditionCodes.begin(), conditionCodes.end(),
					[&](const char* currentOperand) {
						return Parameter1_S.compare(currentOperand) == 0;
					});
				if (ConditionIndex != conditionCodes.end()) {
					Parameter1_H = zutils::cc;
					ushort dud = static_cast<ushort>(std::distance(conditionCodes.begin(), ConditionIndex));
					Parameter1_S = zutils::to_hex(dud, 1);
				}
				else {
					errout << "Error line " << LineNum << ": Invalid condition code." << std::endl;
					exit(EXIT_FAILURE);
				}
			}
        } else if (Mnemonic.compare("decw") == 0 || Mnemonic.compare("incw") == 0) {
            Parameter1_H = zutils::RR;
            Parameter2_H = zutils::RR;
		}
		else if (Mnemonic.compare("trap") == 0) {
			Parameter1_H = zutils::V;
		}

        if (Mnemonic.compare("djnz") == 0 || Mnemonic.compare("jr") == 0) {
            Parameter2_H = zutils::X;
        }

        errout << "Parameter 1: _" << Parameter1_S << "_" << std::endl;
        errout << "Parameter 2: _" << Parameter2_S << "_" << std::endl;
        errout << "Parameter 3: _" << Parameter3_S << "_" << std::endl;

        getParameterType(Parameter1_S, Parameter1_H);
        getParameterType(Parameter2_S, Parameter2_H);
        getParameterType(Parameter3_S, Parameter3_H);

        //Add padding to hex values
        if (Parameter1_S.size() == 3 && Parameter2_S.size() != 3)
            Parameter1_S = '0' + Parameter1_S;
        if (Parameter2_S.size() == 3 && Parameter1_S.size() != 3)
            Parameter2_S = '0' + Parameter2_S;

        zutils::opcode* CurrentOpcode;
        CurrentOpcode = Opcodes.find(Mnemonic, Parameter1_H, Parameter2_H, Parameter3_H);

        //If opcode is not found
        if (CurrentOpcode == nullptr) {
            errout << "Error line " << LineNum << ": Mnemonic not found." << std::endl;
            continue;
        }

        Output << CurrentOpcode->hexify(Parameter1_S, Parameter2_S) << std::endl;
    }
}
