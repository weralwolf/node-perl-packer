/* 
 * File:   PerlPack.cpp
 * Author: weralwolf
 * 
 * Created on March 4, 2011, 6:54 PM
 */

// g++ -Iblib/headers -I/usr/lib/perl/5.10/CORE --std=gnu++0x -lperl++ -ltap++ -Lblib/so -lstdc++ -c -o PerlPack.o PerlPack.cpp

/*
 * C++ Reserved or Non-graphic Characters


Character	ASCII Representation	ASCII Value	Escape Sequence
Newline	NL (LF)	10	\n
Horizontal tab	HT	9	\t
Vertical tab	VT	11	\v
Backspace	BS	8	\b
Carriage return	CR	13	\r
Formfeed	FF	12	\f
Alert	BEL	7	\a
Backslash	\	92	\\
Question mark	?	63	\?
Single quotation mark	'	39	\'
Double quotation mark	"	34	\"
Octal number	ooo	--	\ooo
Hexadecimal number	hhh	--	\xhhh
Null character	NUL	0	\0
 */

#include "PerlPacker.h"

PerlPacker * PerlPacker::_instance = NULL;

PerlPacker::PerlPacker() {};

PerlPacker::PerlPacker(PerlPacker const & copy) {};

PerlPacker::~PerlPacker() {
    delete _instance;
};

std::list<std::string> const & PerlPacker::GetErrorsList() const {
    return errorsList;
};

std::string PerlPacker::GetErrorsAsString() const {
    std::string errors;
    for(std::list<std::string>::const_iterator i = errorsList.begin(); i != errorsList.end(); ++i) {
        if(i != errorsList.begin()) {
            errors += "\n";
        };
        errors += *i;
    };
    return errors;
};

void PerlPacker::ClearErrorList() {
    errorsList.clear();
};

std::string PerlPacker::FlushErrors() {
    std::string errors = GetErrorsAsString();
    ClearErrorList();
    return errors;
};

unsigned int PerlPacker::CountOfErrors() const {
    return errorsList.size();
};

PerlPacker * PerlPacker::Instance() {
    if (_instance == NULL) {
        _instance = new PerlPacker();
    };
    return _instance;
};

PerlPacker * PerlPacker::operator =(PerlPacker const & copy) {};

std::string PerlPacker::Pack(std::string const & format, std::string const & arguments) {
    return EvalCommand(std::string("pack"), format+", "+arguments);
};

std::string PerlPacker::EvalCommand(std::string const & command, std::string const & arguments) {
    std::string query(command+"("+arguments+")");
    try {
        perl::Scalar::Temp queryResult = interpreter.eval(query.c_str());
        perl::Raw_string rawStringResult = queryResult;
        return rawStringResult.to_string();
    } catch(perl::Runtime_exception & e) {
        std::string eMessage(e.what());
        errorsList.push_back(query + ": " + eMessage);
        return eMessage;
    };
};

std::string PerlPacker::Unpack(std::string const & format, std::string const & arguments) {
    return EvalCommand(std::string("unpack"), format+", "+arguments);
};
