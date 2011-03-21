/* 
 * File:   Macroses.h
 * Author: weralwolf
 *
 * Created on February 26, 2011, 5:08 PM
 */

#ifndef __MACROSES_H__
#define	__MACROSES_H__

#define ADD_PROTOTYPE_METHOD(class, name, method) \
class ## _ ## name ## _symbol = NODE_PSYMBOL(#name); \
NODE_SET_PROTOTYPE_METHOD(__constructorTemplate, #name, method);

#define THREXC(str) ThrowException(Exception::Error(String::New(str)))
#define OBJUNWRAP ObjectWrap::Unwrap
#define V8STR2(str, len) String::New(str, len)

#define REQ_STR_ARG(I, VAR) \
if (args.Length() <= (I) || !args[I]->IsString()) \
return ThrowException(Exception::TypeError( \
String::New("Argument " #I " must be a string"))); \
String::Utf8Value VAR(args[I]->ToString());

#endif	/* __MACROSES_H__ */

