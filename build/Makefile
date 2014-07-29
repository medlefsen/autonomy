CXXFLAGS+= -Wall -DBOOST_SPIRIT_SINGLE_GRAMMAR_INSTANCE -DBOOST_SPIRIT_USE_OLD_NAMESPACE -fpermissive -ftemplate-depth=1024 -ftemplate-backtrace-limit=0
ifdef DEBUG
	CXXFLAGS += -DDEBUG
	GDB = 1
endif
ifdef GDB
	CXXFLAGS += -gstabs+ -fno-inline
endif
ifdef OPTIMIZE
	CXXFLAGS += -O$(OPTIMIZE)
endif
ifdef PROFILE
	CXXFLAGS += -pg
endif
ifdef NOGUI
	CXXFLAGS += -DDUI
endif
ifdef DUI
	CXXFLAGS += -DDUI
endif
INCLUDES+=-I$(BASE)
LDFLAGS+=-L/usr/local/acl/lib
LDLIBS+=-lSDL -lSDL_mixer -lSDL_image -lSDL_gfx -lSDL_ttf -lboost_thread -lboost_serialization -lboost_system -lpthread

default: autonomy

tags:
	ctags -R $(ROOT)
include Makefile.gen
