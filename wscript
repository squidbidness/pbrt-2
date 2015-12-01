#! /usr/bin/env python
from os import path

# the following two variables are used by the target "waf dist"
VERSION="0.0.1"
APPNAME="pbrt-arh"

# these variables are mandatory ("/" are converted automatically)
top = "."
out = "build"
bin_dir = "bin"

lib_roots = [
		"src/geo",
		"src/lib",
		"external/gtest",
		"tests/unit"
		]

bins = [
		]

test_bins = [
		"tests/test_unit"
		]

system_include_paths = [
		"external"
		]

include_paths = [
		".",
		"src"
		]

def options(opt):
	opt.load("compiler_cxx")

def configure(conf):
	conf.load("compiler_cxx")
	conf.env.append_value("CXXFLAGS", ["-O2", "-g", "--std=c++14"])
	conf.env.INCLUDES = system_include_paths

def build(bld):
	srcs = []
	for root in lib_roots:
		srcs = srcs + bld.path.ant_glob( "**/{path}/*.cpp".format(path=root) )
		srcs = srcs + bld.path.ant_glob( "**/{path}/*.cc".format(path=root) )

	for test in test_bins:
		bld.program(
				source=["{t}.cpp".format(t=test)] + srcs, 
				target="{bin}/{bin_name}".format(
                        bin=bin_dir, bin_name=path.basename(test)),
				includes=include_paths
				)
