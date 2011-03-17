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
#define V8STR(str) String::New(str)
#define V8STR2(str, len) String::New(str, len)

#define REQ_INT_ARG(I, VAR) \
if (args.Length() <= (I) || !args[I]->IsInt32()) \
return ThrowException(Exception::TypeError( \
String::New("Argument " #I " must be an integer"))); \
int32_t VAR = args[I]->Int32Value();

#define REQ_UINT_ARG(I, VAR) \
if (args.Length() <= (I) || !args[I]->IsUint32()) \
return ThrowException(Exception::TypeError( \
String::New("Argument " #I " must be an integer"))); \
uint32_t VAR = args[I]->Uint32Value();

#define REQ_STR_ARG(I, VAR) \
if (args.Length() <= (I) || !args[I]->IsString()) \
return ThrowException(Exception::TypeError( \
String::New("Argument " #I " must be a string"))); \
String::Utf8Value VAR(args[I]->ToString());

#define REQ_BOOL_ARG(I, VAR) \
if (args.Length() <= (I) || !args[I]->IsBoolean()) \
return ThrowException(Exception::TypeError( \
String::New("Argument " #I " must be a boolean"))); \
bool VAR = args[I]->BooleanValue();

#define REQ_EXT_ARG(I, VAR) \
if (args.Length() <= (I) || !args[I]->IsExternal()) \
return ThrowException(Exception::TypeError( \
String::New("Argument " #I " invalid"))); \
Local<External> VAR = Local<External>::Cast(args[I]);

#define REQ_FUN_ARG(I, VAR) \
if (args.Length() <= (I) || !args[I]->IsFunction()) \
return ThrowException(Exception::TypeError( \
String::New("Argument " #I " must be a function"))); \
Local<Function> VAR = Local<Function>::Cast(args[I]);

#endif	/* __MACROSES_H__ */

