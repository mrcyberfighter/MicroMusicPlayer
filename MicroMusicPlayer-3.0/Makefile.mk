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
# $% Target meber name if the target is an archive member.
# $<  First dependencies in first rule.
# $?  List of all dependencies newer than the target.
# $^  List of all dependencies without repetition.
# $+  List of all dependencies with repetition.
# $*  The steam which match implicit rules.



####### Assigments #######
# define var     value  # Value definition (used for multiline).
# define var =   value  # indirect. (the value change at the next assignment for the final variable value.)
# define var :=  value  # direct.   (the value doesn't change at the next assignment for the final variable value.)
# define var ::= value  # retro and inter compatibility with other make tools.
# define var +=  value  # incr   assigment operator.
# define var ?=  value  # ifndef assigment operator.

# endif # End of a definition.

# target : dependencies    # target can be a target name or a file...
# \t RULE                  # dependencies can be files to update.
#                          # starting with a tab or whatever define in the .RECIPEPREFIX built-in variables.



# CC        is defined per default as the system c-compiler.
# CXX       is defined per default as the system c++-compiler.
#
# COMPILER_FLAGS    isn't defined per default.  # By distributing think about that the user can overwrite it.
# CXXFLAGS  isn't defined per default.  # By distributing think about that the user can overwrite it.
# CPPFLAGS  isn't defined per default.  # By distributing think about that the user can overwrite it.
#
# LDFLAGS   ins't defined per default.  # By distributing think about that the user can overwrite it,
# LDLIBS    isn't defined per default   # but should if he desn't fork the project with additional.

# .PHONY: targets are run everytime you call it with:
# $ make phony_target

# --no-print-directory -> I dislike directory printing behaviour of make: it look's like an error message cause of formatting --print-directory...
# -j       -> This enable the job option the compilation will be faster because it start a job for command simultaneous.
# -j [int] -> You can add an integer to limit the number of jobs you want. 4 jobs is good.
# -O [target|line|recurse|none] -> Type of output synchronizing by using jobs
MAKE_OPTS = --no-print-directory -j 4

MAKEFLAGS += $(MAKE_OPTS)

SHELL = /bin/bash

################################################################################

########## [START] directory variables [START] #################################

prefix = /usr/local

exec_prefix = $(prefix)

bindir  = $(prefix)/bin

sbindir = $(prefix)/sbin

libexecdir = $(exec_prefix)/libexec

datarootdir = $(prefix)/share

datadir     = $(datarootdir)

sysconfdir = $(prefix)/etc

sharedstatedir = $(prefix)/com

localstatedir = $(prefix)/var

includedir   = $(prefix)/include

oldincludedir = /usr/include

docdir = $(datarootdir)/doc

infodir = $(datarootdir)/info

htmldir = $(docdir)

dvidir = $(docdir)

pdfdir = $(docdir)

psdir = $(docdir)

libdir  = $(exec_prefix)/lib

lispdir =$(datarootdir)/emacs/site-lisp

localedir = $(datarootdir)/locale

mandir  = $(datarootdir)/man

man1dir = $(mandir)/man1

man2dir = $(mandir)/man2

man3dir = $(mandir)/man3

man4dir = $(mandir)/man4

man5dir = $(mandir)/man5

man6dir = $(mandir)/man6

man7dir = $(mandir)/man7

man7dir = $(mandir)/man8

man9dir = $(mandir)/man9


################################################################################

pkgdatadir      = $(datarootdir)/$(PRGNAME)

pkgincludedir   = $(includedir)/$(PRGNAME)

pkglibdir       = $(libdir)/$(PRGNAME)

pkglibexecdir   = $(libexecdir)/$(PRGNAME)

################################################################################

srcdir  = .

################################################################################

#################### [Start] functions [Start] #################################

# Define a function to check the presence of an executable through his binary path.
BINARY_CHECK = $(shell which $1)

BINARY_EXIST = $(if $(call BINARY_CHECK, $1 ), $(call BINARY_CHECK, $1 ))

# Define a function to check if a file exist.
FILE_EXIST   = $(shell if `test -f $1` ; then echo T ; else echo F ; fi)

################################################################################


############### [START] Check GNU make tool purpose [START] ####################

# NOTE: Use the defined $(MAKE) variable for calling the make tool in recipes.

MAKE    = $(call BINARY_EXIST, make)

############### [END] Check GNU make tool purpose [END] ########################

############### [START] Check coreutils tools [START] ##########################

MKDIR   = $(call BINARY_EXIST, mkdir)

MKDIR_P = $(MKDIR) -p

BASENAME = $(call BINARY_EXIST, basename)

LS = $(call BINARY_EXIST, ls)

LS_SIZE = $(LS) -s -h

CP = $(call BINARY_EXIST, cp)

CP_R = $(CP) -R

RM = $(call BINARY_EXIST, rm)

RM_R = $(RM) -R

MV  =  $(call BINARY_EXIST, mv)

CHMOD = $(call BINARY_EXIST, chmod)

TOUCH = $(call BINARY_EXIST, touch)

CD = $(call BINARY_EXIST, cd)

LN = $(call BINARY_EXIST, ln)

LN_S = $(LN) -s -T

############### [END] Check coreutils tools [END] ##############################


########## [START] installation variables [START] ##############################

INSTALL  = $(call BINARY_EXIST, install)

INSTALL_PROGRAM = ${INSTALL} -c
INSTALL_DATA    = ${INSTALL} -c -m 644
INSTALL_DATA_RW = ${INSTALL} -c -m 666

DESTDIR =

################################################################################

#################### [Start] Other needed binaries [Start] #####################

# Install the findutils package if missing.
FIND = $(call BINARY_EXIST, find)

# Install the file package if missing.
FILE = $(call BINARY_EXIST, file)

# Package ???
SIZE = $(call BINARY_EXIST, size)

# Package ???
STRIP = $(call BINARY_EXIST, strip)

# Package ???
GREP  = $(call BINARY_EXIST, grep)

# Package ???
SED = $(call BINARY_EXIST, sed)

# Package ???
HEXDUMP = $(call BINARY_EXIST, hexdump)

# Install the install-info package if missing.
INSTALL_INFO = $(call BINARY_EXIST, install-info)

#################### [End] Other needed binaries [End] #########################

#################### [START] Check debugging and profiling tools [START] #######
# DEBUGGING AND PROFILING programs and settings

# gprof binary check.
GPROF  = $(call BINARY_EXIST, gprof)

# nm binary check.
# nm: display symbols of an object file or a program (named a.out) per default.
NM      = $(call BINARY_EXIST, nm)


# readelf binary check.
# readelf: display informations about a program (a ELF (Executable Linkable Format) binary).
READELF = $(call BINARY_EXIST, readelf)

# strace binary check.
# strace: Intercepts  and  records  the  system  calls  which are called by a
#         process and the signals which are received by a process.
STRACE  = $(call BINARY_EXIST, strace)


# ltrace binary check.
# ltrace: Trace library calls of a given program.
LTRACE  = $(call BINARY_EXIST, ltrace)


# objdump binary check.
# objdump: Display the informations about the object file(s).
OBJDUMP = $(call BINARY_EXIST, objdump)

# ldd: ldd  print the  shared  libraries  required by each program or shared
#      library specified on the command line.
#
# NOTE: A  safer alternative when dealing with untrusted executables is:
# $ objdump -p /path/to/program | grep NEEDED
LDD = $(call BINARY_EXIST, ldd)


# diff: diff print difference between 2 or more files
#
#
# NOTE: diff can work recursively on a folder.
# SUGGEST: the kompare diff-gui program.
DIFF = $(call BINARY_EXIST, diff)

#################################################################################


#################### [START] archiving and compressing utilities [START] #######

ZIP     = $(call BINARY_EXIST, zip)

TAR     = $(call BINARY_EXIST, tar)

GZ      = $(call BINARY_EXIST, gzip)

BZ2     = $(call BINARY_EXIST, bzip2)

#################### [END] archiving and compressing utilities [END] ###########

############### Compiler settings ##################

# Programming language choosen by the user.

# IMPORTANT: Do not comment this variables and remove trailing spaces.
PRG_LANG = C++

# IMPORTANT: Do not comment this variables and remove trailing spaces.
EXT_SRC = .cpp

# IMPORTANT: Do not comment this variables and remove trailing spaces.
EXT_HDR = .h

# Compiler according user choice or automatique to language.





################### Variables for future use ! ################################
# Better compare host as the $(OS) variable.


# OS = UNIX or WIN32.
OS = UNIX

# if $OS == UNIX ; then TAGRGET = LINUX or MACOSX ; else WIN32.
TARGET = LINUX


ARCH = $(ARCH) # to set in binary_checks.mk

############################################################
# this attemp to try to guess the default compiler.
#
# COMPILER = $(ARCH)-w64-$(HOST)-$(CXX)
#
#   for windows x86_64-w65-mingw32-g++ compiler per example.
#   In case of MSYS2 compilation.
#
###########################################################

ifeq ($(OS), UNIX)
COMPILER = $(CXX)
else ifeq ($(OS), WIN32)
COMPILER = x86_64-w64-mingw32-g++
endif

DIST_NAME = MicroMusicPlayer

###############################################################################

WALL =  -Wall

WEXTRA = -Wextra

# Define the warning the user want.
WARNS = -Wall -pedantic -Wno-deprecated -Wno-deprecated-declarations # By releasing: -w

# Use the increment operator so that the user can define the flags he want.

ifeq ($(OS),UNIX)

COMPILER_FLAGS = -g -O2 -std=c++11  # -Wl,--export-dynamic

ifeq ($(TARGET), MACOSX)

CPPFLAGS = -DMACOSX

LDFLAGS = `pkg-config --cflags gtk+-3.0` `pkg-config --cflags libvlc` `pkg-config --cflags gtk-mac-integration-gtk3` `pkg-config --cflags gdk-quartz-3.0`

LDLIBS = `pkg-config --libs gtk+-3.0` `pkg-config --libs libvlc` `pkg-config --libs gtk-mac-integration-gtk3` `pkg-config --libs gdk-quartz-3.0`

else

CPPFLAGS =

LDFLAGS = `pkg-config --cflags gtk+-3.0` `pkg-config --cflags libvlc`

LDLIBS = `pkg-config --libs gtk+-3.0` `pkg-config --libs libvlc`

endif

endif


ifeq ($(OS),WIN32)

COMPILER_FLAGS = -mwindows -std=c++11 -g -O2 -Wl,--export-all-symbols  -static-libgcc -static-libstdc++

CPPFLAGS =

LDFLAGS = `x86_64-w64-mingw32-pkg-config --cflags gtk+-3.0` `x86_64-w64-mingw32-pkg-config --cflags libvlc`

LDLIBS = `x86_64-w64-mingw32-pkg-config --libs gtk+-3.0` `x86_64-w64-mingw32-pkg-config --libs libvlc`

endif



ANIM_COMPILER_FLAGS = -g -O2 -std=c11

ANIM_CPPFLAGS =

ANIM_LDFLAGS = `pkg-config --cflags gtk+-3.0`

ANIM_LDLIBS = `pkg-config --libs gtk+-3.0`

ANIM_SRC_FILES = ./source/animations/gtk_image_pixbuf.c

all: build

.PHONY: anim anim-exec

anim:
	$(CC) -Wall -pedantic $(ANIM_COMPILER_FLAGS) $(ANIM_SRC_FILES) -o ./source/animations/anim $(ANIM_LDFLAGS) $(ANIM_LDLIBS)

anim-exec:
	cd ./source/animations ; ./anim "$(argv)"



# IMPORTANT: Do not comment this variables and remove trailing spaces.
USE_PRG_LIB = F

######## Program informations. #########################

BIN_DIR = ./bin

ifeq ($(OS),UNIX)
PRGNAME = MicroMusicPlayer
endif

ifeq ($(OS),WIN32)
PRGNAME = mmp.exe
endif

PRGPATH = $(BIN_DIR)/$(PRGNAME)

VERSION = 3.0.0

########################################################

SRC_DIR   = ./source

SRC_FILES =   $(SRC_DIR)/main.cpp \
              $(SRC_DIR)/global_vars.cpp \
              $(SRC_DIR)/dialogs.cpp \
              $(SRC_DIR)/folder_parsing.cpp \
              $(SRC_DIR)/generate_menu.cpp \
              $(SRC_DIR)/gui_configuration.cpp \
              $(SRC_DIR)/music_hooks.cpp \
              $(SRC_DIR)/playing_controls_callback.cpp \
              $(SRC_DIR)/shuffle.cpp \
              $(SRC_DIR)/view_playlist.cpp \
              $(SRC_DIR)/other_callbacks.cpp \
              $(SRC_DIR)/Resizer.cpp

OBJECTS = $(SRC_FILES:$(EXT_SRC)=.o)


S_FILES  = $(SRC_FILES:$(EXT_SRC)=.s)

CPP_FILES = $(SRC_FILES:$(EXT_SRC)=.i)

HDR_DIR   = $(SRC_DIR)/headers

HDR_FILES =   $(HDR_DIR)/includes.h \
              $(HDR_DIR)/defines.h  \
              $(SRC_DIR)/global_vars.h \
              $(SRC_DIR)/dialogs.h \
              $(SRC_DIR)/folder_parsing.h \
              $(SRC_DIR)/generate_menu.h \
              $(SRC_DIR)/gui_configuration.h \
              $(SRC_DIR)/music_hooks.h \
              $(SRC_DIR)/playing_controls_callback.h \
              $(SRC_DIR)/shuffle.h \
              $(SRC_DIR)/view_playlist.h \
              $(SRC_DIR)/other_callbacks.h \
              $(SRC_DIR)/Resizer.h


#######################################################

#NOTE: not GNU make tools have less capabilitites than the original tool.
ifneq ($(notdir $(MAKE)),make)
$(warning You don't use the GNU make tool: this can go into incompatiblities with this Makefile)
endif

# The default or all target is the default target (wenn you only enter $ make) or the first target encounter in the Makefile.
all: build

build: $(PRGPATH)


#################### [START] Program library target [START] #####################

ifeq ($(USE_PRG_LIB),T)

LIB_NAME = lib$(PRGNAME)

LIB_SRC_PATH = $(SRC_DIR)/$(LIB_NAME)

LIB_PATH = $(LIB_SRC_PATH)/$(LIB_NAME)

$(LIB_NAME):
	cd $(LIB_SRC_PATH) ; $(MAKE)

$(LIB_PATH):
	cd $(LIB_SRC_PATH) ; $(MAKE)

else

LIB_PATH =

endif

################################################################################


# First target appearing is the implicte variable: .DEFAULT: target.
$(PRGPATH):  $(BIN_DIR) $(LIB_PATH) $(OBJECTS)
	$(COMPILER)  $(WARNS) $(DEBUG_FLAG) $(CPPFLAGS) $(LDFLAGS) $(COMPILER_FLAGS)  $(DEBUG_OPTION)  $(PG_OPTION) -o $(PRGPATH) $(OBJECTS) $(LIB_PATH) $(LDLIBS)


.PHONY: $(BIN_DIR)
$(BIN_DIR):
	- @if `test ! -d $(BIN_DIR)` ; then  $(MKDIR_P) $(BIN_DIR) ; fi


%.o: %$(EXT_SRC)
	$(COMPILER)  $(WARNS) $(DEBUG_FLAG) $(CPPFLAGS) $(LDFLAGS) $(COMPILER_FLAGS)  $(DEBUG_OPTION)  $(PG_OPTION)  -c $< -o $@ $(LDLIBS)


assembly: $(S_FILES)

%.s : %$(EXT_SRC)
	$(COMPILER) $(CPPFLAGS) $(LDFLAGS) $(COMPILER_FLAGS) -S $(AS_OPTS) $< -o $@ $(LDLIBS)

.PHONY: assembly-att assembly-intel

assembly-att:
	$(MAKE) -B assembly AS_OPTS=-masm=att


assembly-intel:
	$(MAKE) -B assembly AS_OPTS=-masm=intel


.PHONY: preproc

preproc: $(CPP_FILES)

%.i: %$(EXT_SRC)
	$(COMPILER) $(CPPFLAGS) $(LDFLAGS) $(COMPILER_FLAGS) -E $< -o $@ $(LDLIBS)


################################################################################

ifeq ($(OS),WIN32)
BROWSER = "C:\Program Files (x86)\Mozilla Firefox\firefox.exe"
endif

sphinx-singlehtml:
	cd ./sphinx ; $(MAKE) singlehtml

sphinx-html:
	cd ./sphinx ; $(MAKE) html

sphinx-info:
	cd ./sphinx ; $(MAKE) info

sphinx-man:
	cd ./sphinx_man ; $(MAKE) man

sphinx-text:
	cd ./sphinx ; $(MAKE) text

sphinx-show-singlehtml:
	cd ./sphinx/build/singlehtml ; $(BROWSER) *.html


sphinx-show-html:
	cd ./sphinx/build/html ; $(BROWSER) *.html

sphinx-show-info:
	cd ./sphinx/build/texinfo ; $(INFO) *.info

sphinx-show-man:
	cd ./sphinx_man/build/man ; $(MAN) -l *.1

sphinx-show-text:
	cd ./sphinx/build/text/README ; *.txt

#################### [START] gettext support [START] ###########################


ifneq ($(XGETTEXT), )
XGETTEXT_OPTS = -L C --keyword=_ --keyword=N_ --from-code=UTF-8
.PHONY: xgettext
xgettext:
	$(XGETTEXT) $(XGETTEXT_OPTS) $(SRC_FILES)
	$(MV) messages.po $(PRGNAME).pot
endif

lang=


ifneq ($(MSGFMT), )
MSGFMT_OPTS = -v -f
.PHONY: msgfmt
msgfmt:
ifneq ($(lang), )
	$(MSGFMT) $(MSGFMT_OPTS) $(PRGNAME).pot -o $(PRGNAME).mo
	if `test ! -d $(LOCALE_DIR)/$(lang)/LC_MESSAGES` ; then $(MKDIR_P) $(LOCALE_DIR)/$(lang)/LC_MESSAGES ; fi
	if `test ! -d $(LOCALE_DIR)/$(lang)/LC_MESSAGES` ; then $(MKDIR_P) $(LOCALE_DIR)/$(lang)/LC_MESSAGES ; fi
	if `test ! -d $(GETTEXT_BKUP_DIR)/$(lang)` ;       then $(MKDIR_P) $(GETTEXT_BKUP_DIR)/$(lang)       ; fi
	$(CP) $(PRGNAME).pot $(GETTEXT_BKUP_DIR)/$(lang)/
	$(MV) $(PRGNAME).mo $(LOCALE_DIR)/$(lang)/LC_MESSAGES
	@echo
	@echo "Now you can try your translation"
	@echo "by setting the value of the \$$LANGUAGE variable:"
	@echo "$$ export LANGUAGE=fr:en      # Language on French with English fallback."
	@echo "$$ export set LANGUAGE=fr:en  # Language on French with English fallback."
	@echo "$$ declare LANGUAGE=fr:en     # Language on French with English fallback."
else
	@echo  "You must define the lang variable on the commandline."
	@echo  "Per example \"make msgfmt lang=fr\" for french."
endif

endif


ifneq ($(MSGUNIQ), )
.PHONY: msguniq
MSGUNIQ_OPTS=
msguniq:
	if `test -f $(PRGNAME).pot` ; then $(MSGUNIQ) $(MSGUNIQ_OPTS) $(PRGNAME).pot -o $(PRGNAME).pot ; fi
endif

################################################################################

#################### [START] Debugging targets [START] #########################

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
gdb: $(PRGPATH)
	cd $(BIN_DIR) ; gdb ./$(PRGNAME)

#################### [END] Debugging targets [END] #############################


#################### [START] program analyze tools targets [START] #############

# Default -pg option filename.
PG_FILE = $(BIN_DIR)/gmon.out

ifeq ($(MAKECMDGOALS),gprof)
test_gmon = $(call FILE_EXIST, $(PG_FILE))
ifneq ($(test_gmon),T)
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


.PHONY: pg gprof
pg:
	$(MAKE) -B clean_pg
	$(MAKE) clean
	$(MAKE) PG_OPTION=-pg

ifneq ($(GPROF), )
# You must execute your program to generate the gmon.out file.
# Edit the wanted options to give to gprof program.
GPROF_OPTS =
gprof: $(PG_FILE)
	$(GPROF) $(GPROF_OPTS) $(PRGPATH) $(PG_FILE)
endif

ifneq ($(STRACE), )
# Edit the wanted options to give to strace program.
STRACE_OPTS =
strace: $(PRGPATH)
	$(STRACE) $(STRACE_OPTS) $(PRGPATH)
endif

ifneq ($(LTRACE), )
# Edit the wanted options to give to strace program.
LTRACE_OPTS =
ltrace: $(PRGPATH)
	$(LTRACE) $(STRACE_OPTS) $(PRGPATH)
endif

ifneq ($(NM), )
# Edit the wanted options to give to nm program.
NM_OPTS =
nm: $(PRGPATH)
	$(NM) $(NM_OPTS) $(PRGPATH)
endif

ifneq ($(READELF), )
# Edit the wanted options to give to readelf program.
READELF_OPTS =
readelf: $(PRGPATH)
	$(READELF) $(READELF_OPTS) $(PRGPATH)
endif

ifneq ($(OBJDUMP), )
# Edit the wanted options to give to objdump program. # One is required from the program.
OBJDUMP_OPTS =
# objdump require an option.
objdump: $(PRGPATH)
	$(OBJDUMP) $(OBJDUMP_OPTS) $(PRGPATH)
endif

ifneq ($(LDD), )
# Edit the wanted options to give to ldd program.
LDD_OPTS =
ldd:$(PRGPATH)
	$(LDD) $(LDD_OPTS) $(PRGPATH)
endif

ifneq ($(HEXDUMP), )
# Edit the wanted options to give to hexdump program.
HEXDUMP_OPTS =
.PHONY: hexdump
hexdump: $(PRGPATH)
	$(HEXDUMP) $(HEXDUMP_OPTS) $(PRGPATH)
endif

ifneq ($(DIFF), )
# Edit the wanted options to give to diff program.
# -q -y  -t --suppress-blank-empty --suppress-common-lines --show-c-function
DIFF_OPTS =
.PHONY: diff
diff:
ifneq ($(argv), )
	$(DIFF) $(DIFF_OPTS) "$(argv)"
else
	@echo "You must provide 2 filepath given on the cmdline:"
	@echo "$ make diff argv=\"filepath1 filepath2\""
endif
endif

#################### [END] program analyze tools targets [END] #################



#################### [START] cleaning targets [START] ##########################

.PHONY: clean_all clean_o clean_lib clean_save clean_prg clean_pg clean clean_doc clean_s clean_cpp

clean_prg:
	- $(RM) -f $(PRGPATH)

ifneq ($(FIND), )
.PHONY: clean_save
clean_save:
	$(FIND) . -iregex .*~$$ -exec rm -f {} \;
endif

clean_pg:
	- $(RM) -f $(PG_FILE)

clean_o:
	- $(RM) -f $(OBJECTS)

clean_lib:
	- $(RM) -f $(LIB_PATH)

clean_cpp:
	- $(RM) -f $(CPP_FILES)

clean_s:
	- $(RM) -f $(S_FILES)

.PHONY: clean_doc
clean_doc:
	- $(RM) -f $(INFO_FILE) $(TEXT_FILE) $(PDF_FILE) $(HTML_FILE) $(HTML5_FILE) $(TEXI_FILE) $(ODT_FILE) $(XML_FILE) $(LATEX_FILE) $(ASCIIDOC_FILE) $(EPUB_FILE)

.PHONY: clean_doc_gen
clean_doc_gen:
	- $(RM) -f $(TEXI_FILE) $(TEXI_MAN_FILE) $(TEXI_INFO_FILE) $(TEXI_PDF_FILE) $(TEXI_HTML_FILE) $(TEXI_HTML5_FILE) $(TEXI_ODT_FILE) $(TEXI_XML_FILE) $(TEXI_LATEX_FILE) $(TEXI_ASCIIDOC_FILE) $(TEXI_EPUB_FILE) $(TEXI_PLAIN_FILE) \
	                        $(RST_MAN_FILE)  $(RST_INFO_FILE)  $(RST_PDF_FILE)  $(RST_HTML_FILE)  $(RST_HTML5_FILE)  $(RST_ODT_FILE)  $(RST_XML_FILE)  $(RST_LATEX_FILE)  $(RST_ASCIIDOC_FILE)  $(RST_EPUB_FILE)  $(RST_PLAIN_FILE) \
	                        $(MD_MAN_FILE)   $(MD_INFO_FILE)   $(MD_PDF_FILE)   $(MD_HTML_FILE)   $(MD_HTML5_FILE)   $(MD_ODT_FILE)   $(MD_XML_FILE)   $(MD_LATEX_FILE)   $(MD_ASCIIDOC_FILE)   $(MD_EPUB_FILE)   $(MD_PLAIN_FILE)



clean_all: clean_o clean_prg clean_save clean_pg clean_s clean_lib clean_cpp

clean: clean_o clean_prg

#################### [END] cleaning targets [END] ##############################


#################### [START] utilities targets [START] #########################

.PHONY: strip info exec

ifneq ($(FIND), )
.PHONY: list-project
list-project:
	$(FIND) * -exec file {} \;
endif



ifneq ($(STRIP), )
strip:
	strip $(PRGPATH)
endif

# Put the informations you need in this target.
info:
	@echo
	@ls -l $(PRGPATH) ; # Must make a personnal tool displaying file size in K but with the comma rest.
	@echo
ifneq ($(FILE), )
	@file $(PRGPATH)  ;
	@echo
endif
ifneq ($(SIZE), )
	@size $(PRGPATH)  ;
	@echo
endif
	@ls -s -h $(PRGPATH) ;
	@echo



.PHONY: set_x
set_x:
	@ if `test ! -x $(PRGPATH)` ; then $(CHMOD) u+x $(PRGPATH) ; fi


# Overwrite on the cmdline or set it in Makefile if your program need some args.
# or call make by defining this variable:
# $ make argv="foo bar" exec
exec:
# The execute bit removed can append by sharing executable on different device or file system.
	@ $(MAKE) set_x
	cd $(BIN_DIR) ; ./$(PRGNAME) $(argv)


ifneq ($(GREP), )
GREP_OPTS = -n --color
.PHONY: search-pattern
search-pattern:
	cd $(SRC_DIR) ; $(GREP) $(GREP_OPTS) -r "$(argv)"
endif

ifneq ($(FIND), )
ifneq ($(SED), )
.PHONY: rm-trailing-spaces
rm-trailing-spaces:
	$(FIND) $(SRC_DIR) -iregex .*\$(EXT_SRC) -exec $(SED) --in-place "s/[[:space:]]$$//" {} \;
	$(FIND) $(SRC_DIR) -iregex .*\$(EXT_HDR) -exec $(SED) --in-place "s/[[:space:]]$$//" {} \;
endif
endif


ifneq ($(SED), )
.PHONY: replace-in-file
replace-in-file:
ifneq ($(pattern), )
	@if `test -f $(filepath)` ; \
	then $(SED) --in-place "s/$(pattern)/$(replace)/" $(filepath) ; \
	else echo "$(filepath) is not a valid filepath" ; fi
else
	@echo "You must provide a pattern to replace !"
	@echo "$ make replace-in-file pattern=\"\" replace=\"\" filepath=\"\""
endif
endif

ifneq ($(FIND), )
ifneq ($(SED), )
.PHONY: replace-all
replace-all:
ifneq ($(pattern), )
	$(FIND) $(SRC_DIR) -iregex .*\$(EXT_SRC) -exec $(SED) --in-place "s/$(pattern)/$(replace)/" {} \;
	$(FIND) $(SRC_DIR) -iregex .*\$(EXT_HDR) -exec $(SED) --in-place "s/$(pattern)/$(replace)/" {} \;
else
	@echo "You must provide a pattern to replace !"
	@echo "$ make replace-all pattern=\"\" replace=\"\""
endif
endif
endif

.PHONY: prepend-license
prepend-license:
ifneq ($(BOILERPLATE_PATH), )
ifneq ($(PRG_LANG), )
ifneq ($(PYTHON), )
ifneq ($(CHMOD), )
	$(CHMOD) a+rx $(PREPEND_LICENSE_SCRIPT)
	$(PYTHON) $(PREPEND_LICENSE_SCRIPT) -d $(SRC_DIR) -f $(BOILERPLATE_PATH) -l $(PRG_LANG)
	$(PYTHON) $(PREPEND_LICENSE_SCRIPT) -d $(HDR_DIR) -f $(BOILERPLATE_PATH) -l $(PRG_LANG)
endif
endif
endif
endif

#########################
# Script ldd_to_dest.sh :
#########################
###############################################################################

# #! /bin/bash

#function usage {
#
#  echo "a script to copy all required dll files from a binary to a destdir."
#  echo "usage: $0 pathtobin destdir"
#
#  exit 1
#
#}

#if [[ ! -f $1 ]] || [[ ! -d $2 ]] ; then

#    usage ;

#else
 
   # Case mingw64 else adapt it to your case.
   # ldd $1 | grep /mingw64/bin/ | cp $(gawk '{print $3}' ) $2
   # ldd $1 | grep /mingw64/bin/ | echo "$(gawk '{print $3}' )"
   #echo "copy to $2"
   #cp $1 $2
   #echo "copy $1 to $2"
   #exit 0 ;
#fi

###############################################################################

ifeq ($(OS),WIN32)
cp-dll:
	if `test ! -x ./ldd_to_dest.sh` ; then $(CHMOD) +x ldd_to_dest.sh ; fi
	if `test -d $(destdir)` ; then ./ldd_to_dest.sh $(PRGPATH) $(destdir) \
	else \
	@echo "$(destdir) isn't a valid directory !" ; \
	@echo "make cp-dll destidr=\"\""
endif

#################### [END] utilities targets [END] #############################


#################### Test (un)install: to customize (experimental). ############

.PHONY: desktop test-install test-uninstall

desktopdir  = $(DESTDIR)$(prefix)/share/applications

desktop_file_name_base_on_id = mmp.mrcyberfighter.desktop

# it were good to use a tool like xdg-desktop-icon or desktop-file-install for installing the *.desktop file.
desktop:
	- @echo "[Desktop Entry]" > "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "Version=1.0" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "Name=Micro Music Player" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "GenericName=Micro Music Player" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "Comment=Micro Music Player a very simple play a folder content or files music player." >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "Exec=MicroMusicPlayer %F" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "Icon=$(DESTDIR)$(pkgdatadir)/images/images/Micro_Music_Player.png" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "Terminal=false" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "X-MultipleArgs=false" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "StartupNotify=true" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "Type=Application" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "MimeType=audio/mpeg;audio/ogg;audio/flac;audio/x-wav;audio/x-flac;" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "Keywords=Audio;Player;Song;mmp;mp3;wav;ogg;wav;flac;" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "Categories=AudioVideo;Audio;Player;GNOME;GTK;" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "#DBusActivatable=true" >> "$(desktopdir)/$(desktop_file_name_base_on_id)"
	- @echo "desktop file generated at: "$(desktopdir)/$(desktop_file_name_base_on_id)""
#	xdg-desktop-icon install $(DESTDIR)$(DESKTOP_DIR)/$(PRGNAME).desktop
#	desktop-file-install --rebuild-mime-info-cache $(DESTDIR)$(DESKTOP_DIR)/$(PRGNAME).desktop

ifeq ($(OS),UNIX)
install:
ifeq ($(TARGET), MACOSX)
	$(MAKE) -B CPPFLAGS="-D'PREFIX=\"$(prefix)\"' -D'MACOSX'"
else
	$(MAKE) -B CPPFLAGS="-D'PREFIX=\"$(prefix)\"'"
endif
	@if `test ! -d $(prefix)/share/$(PRGNAME)` ; then sudo mkdir $(prefix)/share/$(PRGNAME) ; fi
	sudo cp -R ./share/$(PRGNAME)/images $(prefix)/share/$(PRGNAME);
	sudo cp -R  ./share/$(PRGNAME)/Configuration $(prefix)/share/$(PRGNAME) ;
	sudo cp -R  ./share/$(PRGNAME)/README $(prefix)/share/$(PRGNAME) ;
	sudo cp -R  ./share/$(PRGNAME)/License $(prefix)/share/$(PRGNAME) ;
	sudo chmod -R a+rx $(prefix)/share/$(PRGNAME) ;
	sudo chmod -R o+rwx $(prefix)/share/$(PRGNAME)/Configuration ;
	$(MAKE) desktop
	sudo install $(PRGPATH) $(prefix)/bin
	if `test ! -L $(prefix)/bin/mmp` ; then sudo ln -s $(prefix)/bin/$(PRGNAME) $(prefix)/bin/mmp  ; fi
else
ifeq ($(OS),WIN32)
	$(MAKE) cp-dll
endif
endif


test-uninstall:
# To execute as root.
# Remove all dependencies files:
	- if `test -d $(DESTDIR)$(prefix)/share/$(PRGNAME)` ; then $(RM_R) -f $(DESTDIR)$(prefix)/share/$(PRGNAME) ; fi
# Remove the binary
	- if `test -f $(DESTDIR)$(bindir)/$(PRGNAME)` ; then $(RM) $(DESTDIR)$(bindir)/$(PRGNAME) ; fi
# Remove translation files
#	- $(RM) -f $(prefix)/share/locale/(fr)/LC_MESSAGES/$(PRGNAME).mo
#	- $(RM) -f $(DESKTOP_DIR)/$(PRGNAME).desktop


################################################################################




#################### [START] print available targets [START] ###################

.PHONY: help

help:
	@echo "make build      # Build the binary."
	@echo "make exec       # Execute the binary."
	@echo
	@echo "make ddebug     # Build the binary with DEBUG flag defined."
	@echo "make gdebug     # Build the binary with the debugging -g option."
	@echo "make gdb        # Launch gdb with the binary given as argument."
	@echo "make fdebug     # Build the binary and generate a debug.txt file from the build."
	@echo "make pg         # Build the binary with the profiling -pg option."
	@echo "make gprof      # Launch the gprof tool."
	@echo
	@echo "make assembly-att    # Generate assembly files (AT&T syntax) from src files."
	@echo "make assembly-intel  # Generate assembly files (Intel syntax) from src files."
	@echo
	@echo "make preproc    # Generate preprocessor file (*.i) from source files."
	@echo
ifneq ($(HEXDUMP), )
	@echo "make hexdump    # Process a hexdump on the program."
	@echo
endif
	@echo "make info       # Print binary file informations."
	@echo
ifneq ($(STRIP), )
	@echo "make strip      # strip the binary."
	@echo
endif
	@echo "make clean_o    # Remove all object files."
	@echo "make clean_prg  # Remove the binary file."
	@echo "make clean      # Remove all object files and the binary."
	@echo "make clean_lib  # Remove the static library (ar) file if any."
	@echo "make clean_s    # Remove all assembly generated files."
	@echo "make clean_cpp  # Remove all preprocessor files."
	@echo "make clean_pg   # Remove gmon.out file."
	@echo "make clean_all  # Remove all generated files."
	@echo "make clean_doc  # Remove all documentation files."
	@echo
ifneq ($(FIND), )
	@echo "make clean_save # Remove backup files."
	@echo
endif
ifneq ($(GREP), )
	@echo "make search-pattern argv=pattern # Search for pattern in files."
	@echo
endif
ifneq ($(SED), )
	@echo "make replace-in-file pattern=\"\" replace=\"\" filepath=\"\"" # Replace pattern only in the given file.
	@echo
endif
ifneq ($(FIND), )
ifneq ($(SED), )
	@echo "make replace-all pattern=\"\" replace=\"\"" # Replace all occurences from $pattern in all source files.
	@echo
endif
endif
ifneq ($(SED), )
	@echo "make rm-trailing-spaces # Remove trailing spaces from source and headers."
	@echo
endif
	@echo "make prepend-license    # Prepend license to all source and headers files."
	@echo
ifneq ($(DIFF), )
	@echo "make diff argv=file1 file2 # Make a diff between the given files."
	@echo
endif
ifneq ($(XGETTEXT), )
	@echo "make xgettext           # Generate a *.pot file from source files."
endif
ifneq ($(MSGFMT), )
	@echo "make msgfmt lang=[LANG] # Generate a *.mo file and set it into locale directory"
endif
ifneq ($(MSGUNIQ), )
	@echo "make msguniq            # Remove duplicate in a translation file (*.po, *.pot)"
	@echo
endif

	@echo
ifneq ($(STRACE), )
	@echo "make strace      # trace the binary."
endif
ifneq ($(LTRACE), )
	@echo "make ltrace      # ltrace the binary."
endif
ifneq ($(NM), )
	@echo "make nm          # process the binary the nm tool."
endif
ifneq ($(READELF), )
	@echo "make readelf     # display informations about the ELF binary."
endif
ifneq ($(OBJDUMP), )
	@echo "make objdump     # Process the binary the objdump tool."
endif
ifneq ($(LDD), )
	@echo "make ldd         # Process the binary with the ldd tool."
endif
	@echo
ifeq ($(USE_INDENT),T)
ifneq ($(INDENT), )
	@echo "make indent-kr    # Format all source files in the kr style."
	@echo "make indent-gnu   # Format all source files in the gnu style."
	@echo "make indent-linux # Format all source files in the linux style."
	@echo "make indent-orig  # Format all source files in the original style."
	@echo "make indent-user  # Format all source files in the user defined style."
	@echo
	@echo "make indent-clean # Remove all formatted files with suffix."
	@echo
endif
endif # USE_INDENT
ifeq ($(USE_ASTYLE),T)
ifneq ($(ASTYLE), )
	@echo "make astyle-ansi          # Format all source files in the ansi style."
	@echo "make astyle-java          # Format all source files in the java style."
	@echo "make astyle-kr            # Format all source files in the kr style."
	@echo "make astyle-stroustrup    # Format all source files in the stroustrup style."
	@echo "make astyle-whitesmith    # Format all source files in the whitesmith style."
	@echo "make astyle-banner        # Format all source files in the banner style."
	@echo "make astyle-gnu           # Format all source files in the gnu style."
	@echo "make astyle-linux         # Format all source files in the linux style."
	@echo "make astyle-horstmann     # Format all source files in the horstmann style."
	@echo "make astyle-lisp          # Format all source files in the lisp style."
	@echo "make astyle-pico          # Format all source files in the pico style."
	@echo "make astyle-python        # Format all source files in the python style."
	@echo "make astyle-user          # Format all source files in the user defined style."
	@echo
	@echo "make astyle-clean         # Remove all formatted files with suffix."
	@echo
endif
endif # USE_ASTYLE
ifeq ($(USE_BCPP),T)
ifneq ($(BCPP), )
	@echo "make bcpp-kr      # Format all source files in the bcpp-kr style."
	@echo "make bcpp-pascal  # Format all source files in the bcpp-pascal style."
	@echo
	@echo "make bcpp-clean   # Remove all formatted files with suffix."
	@echo
endif
endif # USE_BCPP
	@echo
ifneq ($(TAR), )
	@echo "make dist-tar     # Generate a tar archive from the project."
ifneq ($(GZ), )
	@echo "make dist-tar-gz  # Generate a tar.gz archive from the project."
endif
ifneq ($(BZ2), )
	@echo "make dist-tar-bz2 # Generate a tar.bz2 archive from the project."
endif
endif
ifneq ($(ZIP), )
	@echo "make dist-zip     # Generate a zip archive from the project."
endif
	@echo
	@echo "make help         # Display all available targets."

#################### [END] print available targets [END] #######################