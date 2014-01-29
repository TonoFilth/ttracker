# COMPILER
CC:=g++
CFLAGS:=-Wall -ggdb -std=c++11

# APP
APPNAME:=ttracker

# APP DIRECTORIES
BUILDDIR:=bin
INCLUDEDIR:=include
LIBDIR:=lib
SRCDIR:=src
TMPDIR:=.obj

# SOURCES
MAINFILE=$(SRCDIR)/main.cpp
SOURCES:=$(shell find $(SRCDIR) -name '*.cpp')
_SOURCESFOLDERS:=$(shell find $(SRCDIR) -type d)
SOURCESFOLDERS:=$(subst ./,,$(_SOURCESFOLDERS))

# OBJECTS
_OBJECTS:=$(addprefix $(TMPDIR)/,$(SOURCES:%.cpp=%.o))
_OBJECTS:=$(subst ./,,$(_OBJECTS))
OBJECTS:=$(subst $(TMPDIR)/$(SRCDIR)/main.o,,$(_OBJECTS))

# EXTERNAL DEPENDENCIES
#SHAREDIR:=../shared
#SHAREDLIB:=$(SHAREDIR)/lib
#SHAREDHEADERS:=$(SHAREDIR)/include
_EXTLIBS:=cppunit sfml-system
EXTLIBS:=$(addprefix -l,$(_EXTLIBS))

# TESTS
TESTDIR:=tests
TMPTESTDIR:=.obj_tests
TESTMAINFILE:=$(TESTDIR)/main.cpp
TESTOUTPUTFILE:=test-runner

TESTSOURCES:=$(shell find $(TESTDIR) -name '*.cpp')
TESTSOURCES:=$(subst $(TESTMAINFILE),,$(TESTSOURCES))
_TESTSOURCESFOLDERS:=$(shell find $(TESTDIR) -type d)
TESTSOURCESFOLDERS:=$(subst ./,,$(_TESTSOURCESFOLDERS))

_TESTOBJECTS:=$(addprefix $(TMPTESTDIR)/,$(TESTSOURCES:%.cpp=%.o))
TESTOBJECTS:=$(subst ./,,$(_TESTOBJECTS))

_TESTEXTLIBS:=cppunit
TESTEXTLIBS:=$(addprefix -l,$(_TESTEXTLIBS))

# INSTALLATION VARS
INSTALLDIR:=/usr/local/bin

# ================================== COMPILE ===================================
all: check $(OBJECTS) $(MAINFILE)
	@echo "========================="
	@echo " Building $(APPNAME) ..."
	@echo "========================="
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) $(MAINFILE) $(OBJECTS) $(EXTLIBS) -o $(BUILDDIR)/$(APPNAME)

$(TMPDIR)/%.o: %.cpp
	@echo "------------------------"
	@echo "> COMPILING $< ..."
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) $< -c -o $@

check:
	@test -d $(BUILDDIR) || mkdir $(BUILDDIR)
	@$(shell find $(SRCDIR) -depth -type d -print | cpio -pd $(TMPDIR))

# =================================== TEST =====================================
check-test:
	@echo "Checking test dirs ..."
	@test -d $(TESTDIR) || { echo "The directory '$(TESTDIR)' doesn't exists. No tests to run."; exit 1; }
	@test -d $(TMPTESTDIR) || mkdir $(TMPTESTDIR)
	@$(shell find $(TESTSRCDIR) -depth -type d -print | cpio -pd $(TMPTESTDIR))

$(TMPTESTDIR)/%.o: %.cpp
	@echo "------------------------"
	@echo "> COMPILING $< ..."
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) -I$(TESTDIR) $< -c -o $@

test: all check-test $(TESTOBJECTS)
	@echo "==============================="
	@echo "> Building $(APPNAME) tests ..."
	@echo "==============================="
	@echo "$(TESTOBJECTS)"
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) -I$(TESTDIR) $(TESTMAINFILE) $(OBJECTS) $(TESTOBJECTS) $(TESTEXTLIBS) -o $(BUILDDIR)/$(TESTOUTPUTFILE)

# ================================== INSTALL ===================================
install:
	@echo "==============================="
	@echo "> INSTALLING $(APPNAME) ..."
	@echo "==============================="
	@echo "InstallDir is $(INSTALLDIR)"
	@sudo test $(INSTALLDIR)/$(APPNAME) || rm $(INSTALLDIR)/$(APPNAME)
	@sudo cp $(BUILDDIR)/$(APPNAME) $(INSTALLDIR)
	@echo "DONE!"

# =================================== OTHER ====================================
clean:
	-rm -Rf $(TMPDIR)
	-rm -Rf $(TMPTESTDIR)

.PHONY: clean all
