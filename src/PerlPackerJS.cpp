/* 
 * File:   PerlPackJS.cpp
 * Author: weralwolf
 * 
 * Created on March 5, 2011, 12:43 AM
 */

#include"PerlPackerJS.h"
#include"Macroses.h"

Persistent<FunctionTemplate> PerlPackerJS::__constructorTemplate;
PerlPacker * PerlPackerJS::__packer = PerlPacker::Instance();

PerlPackerJS * PerlPackerJS::operator = (PerlPackerJS const & copy) {};

PerlPackerJS::PerlPackerJS(PerlPackerJS const & copy) {};

PerlPackerJS::PerlPackerJS() {};

PerlPackerJS::~PerlPackerJS() {
    delete __packer;
};

void PerlPackerJS::Init(Handle<Object> target) {
    HandleScope scope;

    Local<FunctionTemplate> t = FunctionTemplate::New(New);

    // Constructor
    __constructorTemplate = Persistent<FunctionTemplate>::New(t);
    __constructorTemplate->Inherit(EventEmitter::constructor_template);
    __constructorTemplate->InstanceTemplate()->SetInternalFieldCount(1);
    __constructorTemplate->SetClassName(String::NewSymbol("PerlPacker"));

    Local<ObjectTemplate> instance_template =
        __constructorTemplate->InstanceTemplate();

    // Methods
    ADD_PROTOTYPE_METHOD(ppj, pack, Pack);
    ADD_PROTOTYPE_METHOD(ppj, unpack, Unpack);

    // Make it visible in JavaScript
    target->Set(String::NewSymbol("PerlPacker"),
                __constructorTemplate->GetFunction());
};

Handle<Value> PerlPackerJS::New(Arguments const & args) {
    HandleScope scope;
    PerlPackerJS * ppjs = new PerlPackerJS();
    ppjs->Wrap(args.This());
    return args.This();
};

Handle<Value> PerlPackerJS::Pack(Arguments const & args) {
    HandleScope scope;
    REQ_STR_ARG(0, format);
    REQ_STR_ARG(1, arguments);
    std::string formatValue = PrepareString(format);
    std::string argumentsValue = PrepareString(arguments);
    if (formatValue.size() == 0 || argumentsValue.size() == 0) {
        return Undefined();
    };
    std::string result =  PerlPackerJS::__packer->Pack(formatValue.c_str(), argumentsValue.c_str());
    if (PerlPackerJS::__packer->CountOfErrors() != 0) {
        result = PerlPackerJS::__packer->FlushErrors();
    };
    return scope.Close(V8STR2(result.c_str(), result.size()));
};

Handle<Value> PerlPackerJS::Unpack(Arguments const & args) {
    HandleScope scope;
    REQ_STR_ARG(0, specification);
    REQ_STR_ARG(1, source);
    std::string specificationValue = PrepareString(specification);
    std::string sourceValue = PrepareString(source);
    if (specificationValue.size() == 0 || sourceValue.size() == 0) {
        return Undefined();
    };
    std::list<std::string> dataList =  PerlPackerJS::__packer->Unpack(specificationValue.c_str(), sourceValue.c_str());
    if (PerlPackerJS::__packer->CountOfErrors() != 0) {
        std::string errors = PerlPackerJS::__packer->FlushErrors();
        return scope.Close(V8STR2(errors.c_str(), errors.size()));
    };
    v8::Local<v8::Array> JSDataList = Array::New(dataList.size());
    unsigned int i = 0;
    for(std::list<std::string>::iterator str=dataList.begin(); str != dataList.end(); ++str, ++i) {
        JSDataList->Set(i, V8STR2(str->c_str(), str->size()));
    };
    return scope.Close(JSDataList);
};

std::string PerlPackerJS::PrepareString(String::Utf8Value const & string) {
    unsigned int stringLen = static_cast<unsigned int>(string.length());
    char * stringNew = reinterpret_cast<char *>(calloc(stringLen + 1, sizeof(char))); // NOLINT (have no char var)

    int status = snprintf(stringNew, stringLen + 1, "%s", *string);
    if(status != static_cast<int>(stringLen)) {
        printf("Checking status: %i, %i\n", status, static_cast<int>(stringLen)+2);
        free(stringNew);
        THREXC("Snprintf() error");
        return std::string("");
    };
    std::string result(stringNew);
    free(stringNew);
    return result;
};