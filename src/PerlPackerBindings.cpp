/*!
 * Copyright by Anatolii Koval and node-binary-pool contributors
 * See contributors list in README
 *
 * See license text in LICENSE file
 */

/**
 * Include headers
 *
 * @ignore
 */
#include"./PerlPackerJS.h"

// CXXFLAGS="-Iblib/headers -I/usr/lib/perl/5.10/CORE --std=gnu++0x -lperl++ -ltap++ -Lblib/so -lstdc++" node-waf configure build

/**
 * Init V8 structures
 *
 * Classes to populate in JavaScript:
 *
 * * MysqlConnection
 * * MysqlResult
 * * MysqlStatement
 */
extern "C" void init(Handle<Object> target) {
    PerlPackerJS::Init(target);
};
