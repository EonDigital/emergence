.PHONY: all release clean run_emergence coverage
.DEFAULT_GOAL:=all
.EXTRA_PREREQS=Makefile

CXXFLAGS_STD:=-std=c++14
CXXFLAGS_OPT:=-Os -g --coverage
CXXFLAGS_WARN:=-Wall -Werror -Wextra -Wno-error=extra -Wunused -Wno-error=unused -Wunused-value -Wno-error=unused-value
CPPFLAGS_DEPS:=-MMD -MP

DIR_BUILD:=build

DIR_OBJS:=$(DIR_BUILD)/objs
DIR_SRC:=src

EXEC_emergence:=$(DIR_BUILD)/emergence.out
EXECS+=$(EXEC_emergence)
# Library support
LDLIBS_emergence:=$(addprefix -l,SDL2 SDL2main SDL2_image SDL2_mixer gcov stdc++)
# Standard
CXXFLAGS_emergence:=$(CXXFLAGS_STD) $(CXXFLAGS_OPT)
# Make sure we handle dependencies.
# MMD gets .d files, MP adds header handling
# To move the file to a uniform place, add -MF
CPPFLAGS_emergence:=$(CPPFLAGS_DEPS)

print=$(info $(1) $($(1)))

SRC_emergence:=$(foreach d,$(DIR_SRC),$(wildcard $(d)/*.cpp))
DIR_OBJS_emergence:=$(DIR_OBJS)/emergence
OBJS_emergence:=$(patsubst $(DIR_SRC)/%,$(DIR_OBJS_emergence)/%.o,$(SRC_emergence))
DIR_OBJS:=$(dir $(OBJS_emergence))

MKDIR:=mkdir -p

all: $(EXECS)
	echo "Build $@ completed"

$(EXEC_emergence) : $(OBJS_emergence)
$(EXEC_emergence) : LDLIBS:=$(LDLIBS_emergence)
$(EXEC_emergence) $(OBJS_emergence) : CPPFLAGS:=$(CPPFLAGS_emergence)
$(EXEC_emergence) $(OBJS_emergence) : CXXFLAGS:=$(CXXFLAGS_emergence)

$(OBJS_emergence) : $(DIR_OBJS_emergence)/%.cpp.o : $(DIR_SRC)/%.cpp
	echo Making $@
	$(MKDIR) $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $^
	-rm $(patsubst %.o,%.gcda,$@) $(patsubst %.o,%.gcno,$@)
	echo Made   $@

$(EXECS) :
	echo Making $@
	$(MKDIR) $(@D)
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@
	echo Made $@

run_emergence : $(EXEC_emergence)
	./$(EXEC_emergence)
	
clean :
	rm -r $(DIR_BUILD)

coverage : build/coverage/index.htm

build/coverage/index.htm : build/coverage.info
	genhtml build/coverage.info -o build/coverage

build/coverage.info : $(OBJS:%.o=%.gcda)
	lcov -d build -b . -c -o build/coverage.info
	