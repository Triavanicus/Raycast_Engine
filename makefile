#START PROJECT SPECIFIC MAKE CODE
CC=g++

baseDir=./

objDir=$(baseDir)obj/
srcDir=$(baseDir)src/
includeDir=$(baseDir)include/

objEnd=.obj
output=bin/Game.exe
osflags=-lmingw32

flags= \
	-lSDL2main \
	-lSDL2 \
	-std=c++11 \
	-Wall \
	-O2 \
	-g3

sdlDir=C:/Dev/SDL2_64/

flagsI=-I$(includeDir) -I$(sdlDir)include
flagsL=-L$(sdlDir)lib
flagsD=
#END   PROJECT SPECIFIC MAKE CODE

CXXFLAGS=$(flagsI) $(flagsL) $(flagsD) $(osflags) $(flags)

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

aCpp:=$(call rwildcard,$(srcDir),*.cpp)
aObjs=$(aCpp:.cpp=$(objEnd))
aObj=$(aObjs:$(srcDir)%=$(objDir)%)

AUTODEPS:= $(aObj:=.d)

default: run

run: clear $(output)
ifdef debug
	@gdb -ex run $(output)
else
ifndef shared
	@$(output)
endif
endif

build: clear $(output)

$(output): $(aObj)
ifdef linux
	@mkdir -p $(@D)
else
	@if not exist $(subst /,\,$(@D)) mkdir $(subst /,\,$(@D)) > nul
endif
ifndef shared
	@$(CC) $(aObj) -o $(output) $(CXXFLAGS)
	@echo "Binary created!"
else
	@$(CC) $(aObj) -o $(output) -shared $(CXXFLAGS)
	@echo "Shared object created!"
endif

-include $(AUTODEPS)
$(objDir)%$(objEnd): $(srcDir)%.cpp
ifdef linux
	@mkdir -p $(@D)
else
	@if not exist $(subst /,\,$(@D)) mkdir $(subst /,\,$(@D)) > nul
endif
	@$(CC) -MM -MT $@ $(CXXFLAGS) $< > $@.d
	@$(CC) -c $< $(CXXFLAGS) -o $@
	@echo "$@"

clear:
ifdef linux
	@clear
else
	@cls
endif
