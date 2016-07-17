#  Make invocation
#
#  Make -f [--file ] filename -q [--question] -n [--just-print] ...
#

# Introduction:
#
# They are 2 sort of Makefile (i Think)
# 1. They for making you the life easier.
# 2. They for distributing stuff (see automake from the autotools or cmake).
#

####### Variables. #######
#
# $@  Target filename with extension
# $%  Target meber name if the target is an archive member.
# $<  First dependencies in first rule.
# $?  List of all dependencies newer than the target.
# $^  List of all dependencies without repetition.
# $+  List of all dependencies with repetition.
# $*  The steam which match implicit rules.



####### Assigments #######
# define var     value  # Value definition (used for multiline).
# define var =   value  # indirect.
# define var :=  value  # direct.
# define var ::= value  #
# define var +=  value  # incr   assigment operator.
# define var ?=  value  # ifndef assigment operator.

# endif # End of a definition.

# target : dependencies    # target can be a target name or a file...
# \t RULE                  # dependencies can be files to update.
#                          # starting with a tab or whatever define in the .RECIPEPREFIX built-in variables.



# CC        is defined per default as the system c-compiler.
# CXX       is defined per default as the system c++-compiler.
#
# CXXFLAGS    isn't defined per default.  # By distributing think about that the user can overwrite it.
# CXXFLAGS  isn't defined per default.  # By distributing think about that the user can overwrite it.
# CPPFLAGS  isn't defined per default.  # By distributing think about that the user can overwrite it.
#
# LDFLAGS   ins't defined per default.  # By distributing think about that the user can overwrite it,
# LDLIBS    isn't defined per default   # but should if he desn't fork the project with additional.



# --no-print-directory -> I dislike directory printing behaviour of make: it look's like an error message cause of formatting --print-directory...
# -j       -> This enable the job option the compilation will be faster because it start a job for command simultaneous.
# -j [int] -> You can add an integer to limit the number of jobs you want. 4 jobs is good.
# -O [target|line|recurse|none] -> Type of output synchronizing by using jobs
MAKEFLAGS += --no-print-directory

SHELL=/bin/bash

########## directory variables ###############

prefix = /usr/local

exec_prefix = $(prefix)

bindir  = $(prefix)/bin
sbindir = $(prefix)/sbin


libexecdir = $(exec_prefix)/libexec

datarootdir = $(prefix)/share
datadir     = $(datarootdir)

pkgdatadir  = $(datarootdir)/MicroMusicPlayer

includedir   = $(prefix)/include
oldincludedir = /usr/include

docdir = $(datarootdir)/doc

infodir = $(datarootdir)/info

libdir  = $(exec_prefix)/lib

mandir  = $(datarootdir)/man

man1dir = $(mandir)/man1

srcdir  = .

##############################################


################################################################################

# Define a function to check the presence of an executable through his binary path.
BINARY_CHECK = $(shell which $1 2> /dev/null)

BINARY_EXIST = $(if $(call BINARY_CHECK, $1 ), $(call BINARY_CHECK, $1 ))

################################################################################

############### [START] Check GNU make tool purpose [START] ####################

# NOTE: Use the defined $(MAKE) variable for calling the make tool in recipes.

MAKE_BINARY    = $(call BINARY_EXIST, make)

############### [END] Check GNU make tool purpose [END] ########################

############### [START] Check coreutils tools [START] ##########################

MKDIR_P        = $(call BINARY_EXIST, mkdir)

MKDIR_p  += -p

BASENAME_BINARY = $(call BINARY_EXIST, basename)

CP_BINARY = $(call BINARY_EXIST, cp)

CP = $(CP_BINARY)

CP_R_BINARY = $(CP) -R

RM_BINARY = $(call BINARY_EXIST, rm)

RM = $(RM_BINARY)

RM_R = $(RM) -R

CHMOD = $(call BINARY_EXIST, chmod)

############### [END] Check coreutils tools [END] ##############################

########## installation variables ############

INSTALL_BINARY  = $(call BINARY_EXIST, install)

INSTALL = $(INSTALL_BINARY) -c

INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA    = ${INSTALL} -m 644
INSTALL_DATA_RW = ${INSTALL} -m 666

DESTDIR =

##############################################

COMPILER = $(CXX)

WALL =  -Wall

WEXTRA = -Wextra

WARNS = $(WALL) -Wno-deprecated -Wno-deprecated-declarations

CXXFLAGS     += -g -O2 -std=c++11 # Use the increment operator so that the user can define the flags he want.

CPPFLAGS   =

LDFLAGS = `pkg-config --cflags gtk+-3.0` `pkg-config --cflags libvlc`
LDLIBS  = `pkg-config --libs gtk+-3.0` `pkg-config --libs libvlc`




BIN_DIR = ./bin

PRGNAME = MicroMusicPlayer

PRGPATH = $(BIN_DIR)/$(PRGNAME)

VERSION = 2.1




SRC_DIR   = ./source

SRC_FILES = $(SRC_DIR)/Resizer.cpp \
            $(SRC_DIR)/main.cpp \
            $(SRC_DIR)/global_vars.cpp \
            $(SRC_DIR)/dialogs.cpp \
            $(SRC_DIR)/folder_parsing.cpp \
            $(SRC_DIR)/generate_menu.cpp \
            $(SRC_DIR)/gui_configuration.cpp \
            $(SRC_DIR)/music_hooks.cpp \
            $(SRC_DIR)/playing_controls_callback.cpp \
            $(SRC_DIR)/shuffle.cpp \
            $(SRC_DIR)/view_playlist.cpp


OBJECTS = $(SRC_FILES:.cpp=.o)



#NOTE: not GNU make tools have less capabilitites than the original tool.
ifneq ($(notdir $(MAKE_BINARY)),make)
$(warning You don't use the GNU make tool: this can go into incompatiblities with this Makefile)
endif

# The default or all target is the default target (wenn you only enter $ make) or the first target encounter in the Makefile.
all: $(PRGPATH)

# First target appearing is the implicte variable: .DEFAULT: target.
$(PRGPATH):  $(BIN_DIR) $(OBJECTS)
	$(COMPILER)  $(WARNS) $(DEBUG_FLAG) $(CPPFLAGS) $(LDFLAGS) $(CXXFLAGS)  $(DEBUG_OPTION)  $(PG_OPTION) -o $(PRGPATH) $(OBJECTS) $(LDLIBS) $(FDEBUG)

%.o: %.cpp
	$(COMPILER)  $(WARNS) $(DEBUG_FLAG) $(CPPFLAGS) $(LDFLAGS) $(CXXFLAGS)  $(DEBUG_OPTION)  $(PG_OPTION)  -c $< -o $@ $(LDLIBS) $(FDEBUG)

#.PHONY: $(BIN_DIR)

.PHONY: $(BIN_DIR)
$(BIN_DIR):
	- @if `test ! -d $(BIN_DIR)` ; then  $(MKDIR_P) $(BIN_DIR) ; fi








# DEBUGGING AND PROFILING programs and settings

# gprof binary check.
PGPROF_BINARY  = $(call BINARY_EXIST, gprof)
# Edit the wanted options to give to gprof program.
PGPROF_OPTIONS =
# Default -pg option filename.
PG_FILE = $(BIN_DIR)/gmon.out

# nm binary check and options:
# nm: display symbols of an object file or a program (named a.out) per default.
NM_BINARY      = $(call BINARY_EXIST, nm)
# Edit the wanted options to give to nm program.
NM_OPTIONS     =

# strace binary check.
# strace: Intercepts  and  records  the  system  calls  which are called by a
#         process and the signals which are received by a process.
STRACE_BINARY  = $(call BINARY_EXIST, strace)
# Edit the wanted options to give to strace program.
STRACE_OPTIONS =

# ltrace binary check.
# ltrace: Trace library calls of a given program.
LTRACE_BINARY  = $(call BINARY_EXIST, ltrace)
# Edit the wanted options to give to strace program.
LTRACE_OPTIONS =

# objdump binary check.
# objdump: Display the informations about the object file(s).
OBJDUMP_BINARY = $(call BINARY_EXIST, objdump)
# Edit the wanted options to give to objdump program. # One is required from the program.
OBJDUMP_OPTIONS = -H # Display Help ; change this option at your convienence.

# ldd: ldd  print the  shared  libraries  required by each program or shared
#      library specified on the command line.
#
# NOTE: A  safer alternative when dealing with untrusted executables is:
# $ objdump -p /path/to/program | grep NEEDED
LDD_BINARY = $(call BINARY_EXIST, ldd)
# Edit the wanted options to give to ldd program.
LDD_OPTIONS =

# diff: diff print difference between 2 or more files
#
#
# NOTE: diff can work recursively on a folder.
# SUGGEST: the kompare diff-gui program.
DIFF_BINARY = $(call BINARY_EXIST, diff)
# Edit the wanted options to give to diff program.
DIFF_OPTIONS = # -q -y  -t --suppress-blank-empty --suppress-common-lines --show-c-function

#######################################################################################


############### [START] archiving and compressing utilities [START] ###################

ZIP_BINARY     = $(call BINARY_EXIST, zip)

TAR_BINARY     = $(call BINARY_EXIST, tar)

GZ_BINARY      = $(call BINARY_EXIST, gzip)

BZ2_BINARY     = $(call BINARY_EXIST, bzip2)

############### [END] archiving and compressing utilities [END] #####################


#### [START] Debugging targets [START] ####

# .PHONY: targets are run everytime you call it with:
# $ make phony_target
.PHONY: fdebug ddebug gdebug gdb

# File debug.
fdebug:
	- $(RM) -f ./debug.txt
	$(MAKE) $(PRGPATH) 2> ./debug.txt

# Define -DDEBUG
ddebug:
	$(MAKE) -B DEBUG_FLAG=-DDEBUG

# Compile with -g debugging option
gdebug:
	$(MAKE) -B $(PRGPATH) DEBUG_OPTION=-g

# Launch interactive gdb (gnu debugger).
gdb:
	cd $(BIN_DIR) ; gdb ./$(PRGNAME)

#### [END] Debugging targets [END] ####


#### [START] program analyze tools targets [START] ####

ifeq ($(MAKECMDGOALS),gprof)
test_gmon = $(if $(realpath $(PG_FILE)),T)
ifneq ($(test_gmon), T)
$(info  )
$(info ***************************************************************)
$(info You must first execute your program so that it can be profiled,)
$(info it generate the profiling file gmon.out by runtime,)
$(info then you can analyse it content with gprof...)
$(info ***************************************************************)
$(info  )
$(error $(PG_FILE) missing)
endif
endif



pg: $(PRGPATH)
	$(MAKE) -B clean_pg
	$(MAKE) -B $(PRGNAME) PG_OPTION=-pg

# You must execute your program to generate the gmon.out file.
gprof: $(PG_FILE)
	$(PGPROF_BINARY) $(PGPROF_OPTIONS) $(PRGPATH) $(PG_FILE)

ifneq ($(STRACE_BINARY), )
strace: $(PRGNAME)
	$(STRACE_BINARY) $(STRACE_OPTIONS) $(PRGPATH)
endif

ifneq ($(LTRACE_BINARY), )
ltrace: $(PRGNAME)
	$(LTRACE_BINARY) $(STRACE_OPTIONS) $(PRGPATH)
endif

ifneq ($(NM_BINARY), )
nm: $(OBJECTS)
	$(NM_BINARY) $(NM_OPTIONS) $(OBJECTS)
endif

ifneq ($(OBJDUMP_BINARY), )
# objdump require an option.
objdump: $(OBJECTS)
	$(OBJDUMP_BINARY) $(OBJDUMP_OPTIONS) $(OBJECTS)
endif

ifneq ($(LDD_BINARY), )
ldd:$(PRGNAME)
	$(LDD_BINARY) $(LDD_OPTIONS) $(PRGPATH)
endif

ifneq ($(DIFF_BINARY), )
diff:
	$(DIFF_BINARY) $(DIFF_OPTIONS) "$(argv)"
endif

#### [END] program analyze tools targets [END] ####




CUR_PATH = .


#### [START] Distributing targets [START] ####

DIST_DIR  = ./dist

DIST_NAME = $(PRGNAME)-$(VERSION)

TMP_DIR   = /tmp

DIST_EXCLUDE_FOLDER = build dist

TAR_EXCLUDE_CMD = $(foreach var, $(DIST_EXCLUDE_FOLDER), --exclude=$(var)/*)

ZIP_EXCLUDE_CMD = $(foreach var, $(DIST_EXCLUDE_FOLDER), -x $(var)/\*)

# .PHONY: targets are run everytime you call it with:
# $ make phony_target

.PHONY: FORCE dist-zip dist-tar dist-tar-gz dist-tar-bz2

$(DIST_DIR):
	- $(MKDIR_P) $(DIST_DIR)

ifneq ($(ZIP_BINARY), )
dist-zip: $(DIST_DIR)
	$(ZIP_BINARY) -r  $(ZIP_EXCLUDE_CMD)  -9 -o -v  $(TMP_DIR)/$(DIST_NAME).zip .
	$(ZIP_BINARY) $(TMP_DIR)/$(DIST_NAME).zip $(DIST_EXCLUDE_FOLDER)
	$(CP) $(TMP_DIR)/$(DIST_NAME).zip $(DIST_DIR)
	$(ZIP_BINARY) -T $(DIST_DIR)/$(DIST_NAME).zip
	- $(RM) -f $(TMP_DIR)/$(DIST_NAME).zip
endif

ifneq ($(TAR_BINARY), )
$(DIST_NAME).tar: $(DIST_DIR)
	$(TAR_BINARY) $(TAR_EXCLUDE_CMD) -W -cvf  $(TMP_DIR)/$(DIST_NAME).tar .


dist-tar: $(DIST_NAME).tar
	$(CP) $(TMP_DIR)/$(DIST_NAME).tar $(DIST_DIR)
	$(TAR_BINARY) --test-label $(DIST_DIR)/$(DIST_NAME).tar
endif

ifneq ($(GZ_BINARY), )
dist-tar-gz: $(DIST_DIR) $(DIST_NAME).tar
	$(GZ_BINARY) -v -9 $(TMP_DIR)/$(DIST_NAME).tar
	$(CP) $(TMP_DIR)/$(DIST_NAME).tar.gz $(DIST_DIR)
	$(GZ_BINARY) -v -t $(DIST_DIR)/$(DIST_NAME).tar.gz
	- $(RM) -f $(TMP_DIR)/$(DIST_NAME).tar $(TMP_DIR)/$(DIST_NAME).tar.gz
endif

ifneq ($(BZ2_BINARY), )
dist-tar-bz2: $(DIST_DIR) $(DIST_NAME).tar
	$(BZ2_BINARY) -v -9 $(TMP_DIR)/$(DIST_NAME).tar
	$(CP) $(TMP_DIR)/$(DIST_NAME).tar.bz2 $(DIST_DIR)
	$(BZ2_BINARY) -v -t $(DIST_DIR)/$(DIST_NAME).tar.bz2
	- $(RM) -f $(TMP_DIR)/$(DIST_NAME).tar $(TMP_DIR)/$(DIST_NAME).tar.bz2
endif
#### [END] Distributing targets [END] ####




#### [START] cleaning targets [START] ####

.PHONY: clean_all clean_o clean_save clean_prg clean_pg clean

clean_prg:
	- $(RM) -f $(PRGPATH)

FIND_BINARY = $(call BINARY_EXIST, find)

ifneq ($(FIND_BINARY), )
.PHONY: clean_save
clean_save:
	$(FIND_BINARY) . -iregex .*~$$ -exec rm -f {} \;
endif

clean_pg:
	- $(RM) -f $(PG_FILE)

clean_o:
	- $(RM) -f $(OBJECTS)

clean_all: clean_o clean_prg clean_save clean_pg

clean: clean_o clean_prg

#### [END] cleaning targets [END] ####


#### [START] utilities targets [START] ####

.PHONY: strip info exec

strip:
	strip $(PRGPATH)

# Put the informatuons you need in this target.
info:
	@echo
	@ls -l $(PRGPATH) ; # Must make a personnal tool displaying file size in K but with the comma rest.
	@echo
	@file $(PRGPATH)  ;
	@echo
	@size $(PRGPATH)  ;
	@echo
	@ls -s -h $(PRGPATH) ;
	@echo

# Overwrite on the cmdline or set it in Makefile if your program need some args.
# or call make by defining this variable:
# $ make argv="foo bar" exec
argv =

exec:
	@chmod u+x $(PRGPATH)
# This can append by sharing executable on different device or file system (maybe security by executable).
	cd $(BIN_DIR) ; ./$(PRGNAME) $(argv)

#### [END] utilities targets [END] ####




#### [START] print available targets [START] #####

.PHONY: help

help:
	@echo "make        # Build the binary."
	@echo "make exec   # Execute the binary."
	@echo
	@echo "make ddebug # Build the binary with DEBUG flag defined."
	@echo "make gdebug # Build the binary with the debugging -g option."
	@echo "make gdb    # Launch gdb with thye binary given as argument."
	@echo "make fdebug # Build the binary and generate a debug.txt file from the build."
	@echo "make pg     # Build the binary with the profiling -pg option."
	@echo "make gprof  # Launch the gprof tool."
	@echo
	@echo "make info       # Print binary file informations."
	@echo
	@echo "make strip      # strip the binary."
	@echo
	@echo "make clean_o    # Remove all object files."
	@echo "make clean_prg  # Remove the binary file."
	@echo "make clean      # Remove all object files and the binary."
	@echo "make clean_pg   # Remove gmon.out file."
	@echo "make clean_all  # Remove all generated files."
ifneq ($(FIND_BINARY), )
	@echo "make clean_save # Remove backup files."
endif
	@echo
ifneq ($(STRACE_BINARY), )
	@echo "make strace     # trace the binary."
endif
ifneq ($(LTRACE_BINARY), )
	@echo "make ltrace     # ltrace the binary."
endif
ifneq ($(NM_BINARY), )
	@echo "make nm         # process all object files with the nm tool."
endif
ifneq ($(OBJDUMP_BINARY), )
	@echo "make objdump    # Process all object files with the objdump tool."
endif
ifneq ($(LDD_BINARY), )
	@echo "make ldd        # Process the binary with the ldd tool."
endif
	@echo
ifneq ($(TAR_BINARY), )
	@echo "make dist-tar     # Generate a tar archive from the project."
ifneq ($(GZ_BINARY), )
	@echo "make dist-tar-gz  # Generate a tar.gz archive from the project."
endif
ifneq ($(BZ2_BINARY), )
	@echo "make dist-tar-bz2 # Generate a tar.bz2 archive from the project."
endif
endif
ifneq ($(ZIP_BINARY), )
	@echo "make dist-zip     # Generate a zip archive from the project."
endif
	@echo
ifneq ($(DIFF_BINARY), )
	@echo "make diff argv=file1 file2 # Make a diff between the given files."
endif
#### [END] print available targets [END] #####