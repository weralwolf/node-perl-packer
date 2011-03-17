/* 
 * File:   PerlPack.h
 * Author: weralwolf
 *
 * Created on March 4, 2011, 6:54 PM
 */

#ifndef __PERLPACK_H__
#define	__PERLPACK_H__

#include<perl++/perl++.h>
#include<string.h>
#include<list>

class PerlPacker {
private:
    perl::Interpreter interpreter;
    std::list<std::string> errorsList;
    static PerlPacker * _instance;

    PerlPacker();
public:
    static PerlPacker * Instance();
    std::string Pack(std::string const &, std::string const &);
    std::string Unpack(std::string const &, std::string const &);
    std::list<std::string> const & GetErrorsList() const;
    std::string GetErrorsAsString() const;
    std::string FlushErrors();
    void ClearErrorList();
    unsigned int CountOfErrors() const;
    ~PerlPacker();

private:
    PerlPacker(PerlPacker const &);
    PerlPacker * operator = (PerlPacker const &);
    std::string EvalCommand(std::string const &, std::string const &);
};

#endif	/* __PERLPACK_H__ */

