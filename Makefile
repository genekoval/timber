project = timber

STD = c++20

library = lib$(project)
$(library).type = shared
$(library).libs = fmt

console = console
$(console).type = executable
$(console).deps = $(library)
$(console).libs = $(project) fmt

install := $(library)
targets := $(install) $(console)

files = $(include) $(src) Makefile VERSION

include mkbuild/base.mk
