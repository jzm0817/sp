# build all programs with names like `membug[0-9]`
DSPROGRAMS = $(patsubst %.cc,%,$(wildcard vector[0-9].cc list[0-9].cc map[0-9].cc set[0-9].cc uomap[0-9].cc uoset[0-9].cc))
PROGRAMS = $(DSPROGRAMS)
all: $(PROGRAMS)

ALLPROGRAMS = $(PROGRAMS) inv testinsert0 greet vectorq listq mapq setq uomapq uosetq

include ../common/rules.mk

LIBS = -lm


# Rules for making object files (i.e., parts of executables)
# from source files

%.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<


# Rules for making executables (runnable programs) from object files

vector%: vector%.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^ $(LIBS)

list%: list%.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^ $(LIBS)

map%: map%.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^ $(LIBS)

uomap%: uomap%.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^ $(LIBS)

uoset%: uoset%.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^ $(LIBS)


clean:
	rm -rf $(ALLPROGRAMS) *.o $(DEPSDIR)

.PHONY: all clean
