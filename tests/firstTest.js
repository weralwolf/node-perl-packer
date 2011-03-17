/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

var ppjs = require("./ppjs");
//var mb = require("./mysql_bindings");
var util = require('util');

//console.log(util.inspect(ppjs, true, null));
//console.log(util.inspect(mb, true, null));
var pp = new ppjs.PerlPacker();
console.log(util.inspect(pp.unpack, true, null));

console.log(pp.pack('"a/W2"', 'ord("a") .. ord("z")'));