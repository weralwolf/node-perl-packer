/*!
 * Copyright by Anatolii Koval and node-perl-packer contributors
 * See contributors list in README
 *
 */

#include"./PerlPackerJS.h"

/**
 * Init V8 structures
 *
 * Classes to populate in JavaScript:
 *
 * * PerlPacker JS
 */
extern "C" void init(Handle<Object> target) {
    PerlPackerJS::Init(target);
};
