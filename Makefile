project = timber
version = 0.1.0

library = lib$(project)

targets = $(library)
install = $(library)

$(library).type = shared

include mkbuild/base.mk
