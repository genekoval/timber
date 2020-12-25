project = timber

STD = c++17

library = lib$(project)

targets = $(library)
install = $(library)

$(library).type = shared

include mkbuild/base.mk
