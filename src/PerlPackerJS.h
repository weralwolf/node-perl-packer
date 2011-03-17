/* 
 * File:   PerlPackJS.h
 * Author: weralwolf
 *
 * Created on March 5, 2011, 12:43 AM
 */

#ifndef __PERLPACKJS_H__
#define	__PERLPACKJS_H__

#include<v8.h>
#include<node.h>
#include<node_object_wrap.h>
#include<node_events.h>
#include<string>
#include"PerlPacker.h"

using namespace v8;
using namespace node;

static Persistent<String> ppj_pack_symbol;
static Persistent<String> ppj_unpack_symbol;

class PerlPackerJS : public ObjectWrap {
private:
    static PerlPacker * __packer;
    static Persistent<FunctionTemplate> __constructorTemplate;
    PerlPackerJS * operator = (PerlPackerJS const &);
    PerlPackerJS(PerlPackerJS const &);
    /**
     * Preparing string to using it in other functions
     * @param string instance
     * @return string what contains prepared string
     */
    static std::string PrepareString(String::Utf8Value const &);
public:
    PerlPackerJS();
    virtual ~PerlPackerJS();
    static void Init(Handle<Object>);
    static Handle<Value> New(Arguments const &);
    static Handle<Value> Pack(Arguments const &);
    static Handle<Value> Unpack(Arguments const &);
};

#endif	/* __PERLPACKJS_H__ */
