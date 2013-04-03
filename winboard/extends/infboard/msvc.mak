#
# Influence Board Makefile
#

# Nmake macros for building Win32 apps
!include <win32.mak>

PROJ = infboard
all: $(OUTDIR) $(OUTDIR)\$(PROJ).exe

# Define project specific macros
PROJ_OBJS  = $(OUTDIR)\$(PROJ).obj $(OUTDIR)\main.obj $(OUTDIR)\support.obj \
	$(OUTDIR)\moves.obj
BASE_OBJS  =
EXTRA_LIBS = 
GLOBAL_DEP = infboard.h
RC_DEP     =
INC_PATH   = /I..\..\ /I..\..\..
LINK_FLAGS = /SUBSYSTEM:CONSOLE

#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Updating the object files
$(OUTDIR)\$(PROJ).obj: $(PROJ).c
    $(cc) $(cdebug) $(cflags) $(INC_PATH) $(cvars) \
    /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(PROJ).c

$(OUTDIR)\main.obj: main.c
    $(cc) $(cdebug) $(cflags) $(INC_PATH) $(cvars) \
    /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" main.c

$(OUTDIR)\support.obj: support.c
    $(cc) $(cdebug) $(cflags) $(INC_PATH) $(cvars) \
    /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" support.c

$(OUTDIR)\moves.obj: ..\..\..\moves.c
    $(cc) $(cdebug) $(cflags) $(INC_PATH) $(cvars) \
    /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" ..\..\..\moves.c

# Build rule for resource file
#$(OUTDIR)\$(PROJ).res: $(PROJ).rc $(RC_DEP)
#    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\$(PROJ).res $(PROJ).rc

# Build rule for EXE
$(OUTDIR)\$(PROJ).EXE: $(BASE_OBJS) $(PROJ_OBJS)
    $(link) $(linkdebug) $(guilflags) $(LINK_FLAGS) \
    $(BASE_OBJS) $(PROJ_OBJS) $(guilibs) $(EXTRA_LIBS) \
    -out:$(OUTDIR)\$(PROJ).exe $(MAPFILE)

# Build rule for help file
#$(OUTDIR)\$(PROJ).hlp: $(PROJ).rtf $(PROJ).hpj
#    copy $(PROJ).hlp $(OUTDIR)



# Rules for cleaning out those old files
clean:
        $(CLEANUP)
