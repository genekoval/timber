project = logger++
version = 0.1.0

library = lib$(project)

install = $(library)
targets := $(install)

$(library).type = shared
define $(library).libs
 ext++
endef

define test.libs
 $(project)
 gtest
 gtest_main
endef
test.deps = $(library)

include $(DEVROOT)/include/mkbuild/base.mk
