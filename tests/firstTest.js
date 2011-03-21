/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

var ppjs = require("./ppjs");
var util = require('util');

//console.log(util.inspect(ppjs, true, null));
//console.log(util.inspect(mb, true, null));
var pp = new ppjs.PerlPacker();
//console.log(util.inspect(pp.unpack, true, null));

//console.log(pp.pack('"a/W2"', 'ord("a") .. ord("z")'));
console.log(pp.pack("'H2' x 10", 'map { "3$_" } ( 0..9 )'));
console.log(pp.unpack('"A10xA27xA7A*"', "01/24/2001 Ahmed's Camel Emporium                  1147.99"));
console.log(pp.unpack('"A10xA27xA7A*"', "01/28/2001 Flea spray                                24.99"));