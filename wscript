#import Options, Utils

srcdir = '.'
blddir = 'build'
VERSION = '0.0.1'

#print Utils.cmd_output(Options.options.mysql_config)
#conf.env.append_unique('LINKFLAGS', Utils.cmd_output(Options.options.mysql_config + ' --libs_r').split())

def set_options(opt):
  opt.tool_options('compiler_cxx');

def configure(conf):
  conf.env.append_unique('CXXFLAGS', '-Iblib/headers -I/usr/lib/perl/5.10/CORE --std=gnu++0x'.split())
  conf.env.append_unique('LINKFLAGS', '-lperl++ -ltap++ -Lblib/so -lstdc++'.split())
  conf.check_tool('compiler_cxx')
  conf.check_tool('node_addon')

def build(bld):
  obj = bld.new_task_gen('cxx', 'shlib', 'node_addon')
  obj.target = 'ppjs'
  obj.source = './src/PerlPackerBindings.cpp ./src/PerlPacker.cpp ./src/PerlPackerJS.cpp'
