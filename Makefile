project = timber

STD = c++20

library = lib$(project)

install := $(library)
targets := $(install)

$(library).type = shared

files = $(include) $(src) Makefile VERSION

include mkbuild/base.mk
