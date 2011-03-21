/* 
 * File:   PerlPack.cpp
 * Author: weralwolf
 * 
 * Created on March 4, 2011, 6:54 PM
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
        _instance->InitUArray();
    };
    return _instance;
};

PerlPacker * PerlPacker::operator =(PerlPacker const & copy) {};

void PerlPacker::InitUArray() {
    EvalQuery(std::string("my @uDataArray;"));
};

std::string PerlPacker::EvalQuery(std::string const & query) {
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

std::string PerlPacker::PrepareString(std::string const & in) const {
    std::string out(in);

    for(size_t occurence = out.find_first_of("\n", 0); occurence != std::string::npos; occurence = out.find_first_of("\n", occurence+2)) {
        if (out.find_first_of("\\n", occurence-1)+1 != occurence) {
            out.replace(occurence, 1, "\\n");
        };
    };

    for(size_t occurence = out.find_first_of("\"", 0); occurence != std::string::npos; occurence = out.find_first_of("\"", occurence+2)) {
        if (out.find_first_of("\\\"", occurence-1)+1 != occurence) {
            out.replace(occurence, 1, "\\\"");
        };
    };
    return out;
};

std::string PerlPacker::Pack(std::string const & specification, std::string const & arguments) {
    std::stringstream query;
    query << "pack(" << specification << ", " << arguments << ")";
    return EvalQuery(query.str());
};

std::list<std::string> PerlPacker::Unpack(std::string const & specification, std::string const & source) {
    std::stringstream query;
    query << "@uDataArray =  unpack(" << specification << ", \"" << PrepareString(source) << "\"); scalar(@uDataArray);";
    int uDataArrayLen = atoi(EvalQuery(query.str()).c_str());
    std::list<std::string> data;
    for(int i = 0; i < uDataArrayLen; ++i) {
        query.clear();
        query << "$uDataArray[" << i << "];";
        data.push_back(EvalQuery(query.str()));
    };
    return data;
};
