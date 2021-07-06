project = timber

STD = c++20

library = lib$(project)

targets = $(library)
install = $(library)

$(library).type = shared

include mkbuild/base.mk
