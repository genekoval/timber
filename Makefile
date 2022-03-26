project = timber

STD = c++20

library = lib$(project)

install := $(library)
targets := $(install)

$(library).type = shared
$(library).libs = fmt

files = $(include) $(src) Makefile VERSION

include mkbuild/base.mk
