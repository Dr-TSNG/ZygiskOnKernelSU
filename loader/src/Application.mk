APP_CFLAGS     := -Wall -Wextra
APP_CFLAGS     += -fno-stack-protector -fomit-frame-pointer
APP_CFLAGS     += -Wno-builtin-macro-redefined -D__FILE__=__FILE_NAME__
APP_CPPFLAGS   := -std=c++20
APP_CONLYFLAGS := -std=c18
APP_STL        := none

ifneq ($(NDK_DEBUG),1)
APP_CFLAGS     += -Oz -flto
APP_CFLAGS     += -Wno-unused -Wno-unused-parameter
APP_CFLAGS     += -fvisibility=hidden -fvisibility-inlines-hidden
APP_CFLAGS     += -fno-unwind-tables -fno-asynchronous-unwind-tables
APP_LDFLAGS    += -Wl,--exclude-libs,ALL -flto -Wl,--gc-sections -Wl,--strip-all
endif
