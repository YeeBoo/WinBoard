#
# Makefile for WinBoard, using Microsoft Visual C++ and nmake
# Command line:   nmake /f msvc.mak
#
ENV=WIN32
CPU=i386
INC_PATH   = /Iextends\infboard

!include <WIN32.MAK>

!ifndef OUTDIR
!ifndef NODEBUG
OUTDIR=Debug
!else
OUTDIR=Release
!endif
!endif

# Use up to date help compiler
#hc="c:\program files\microsoft visual studio\common\tools\hcrtf.exe" -xn
hc="c:\program files\help workshop\hcrtf.exe" -xn

# Comment out both to turn on debugging symbols #######
#!!cdebug=
#!!linkdebug=
#######################################################

proj = winboard
allobj = $(OUTDIR)\winboard.obj $(OUTDIR)\backend.obj $(OUTDIR)\parser.obj $(OUTDIR)\moves.obj $(OUTDIR)\lists.obj \
	 $(OUTDIR)\gamelist.obj $(OUTDIR)\pgntags.obj $(OUTDIR)\wedittags.obj $(OUTDIR)\wgamelist.obj $(OUTDIR)\zippy.obj \
         $(OUTDIR)\wsockerr.obj $(OUTDIR)\wclipbrd.obj $(OUTDIR)\woptions.obj $(OUTDIR)\infboard.obj

cvars = $(cvars) -I. -I.. -DWINVER=0x0400
#cflags = $(cflags) /FR
cflags = $(cflags) $(INC_PATH)

all: $(OUTDIR) $(OUTDIR)\$(proj).exe

clean:
	$(CLEANUP)

# If OUTDIR does not exist, then create directory
$(OUTDIR):
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Update the help file if necessary
$(proj).hlp : $(proj).rtf
    $(hc) $(proj).hpj
    type $(proj).err

# Update the resource if necessary
$(OUTDIR)\$(proj).rbj: $(proj).rc $(proj).h $(OUTDIR)\$(proj).res resource.h
    cvtres -$(CPU) /OUT:$(OUTDIR)\$(proj).rbj $(OUTDIR)\$(proj).res

$(OUTDIR)\$(proj).res: $(proj).rc $(proj).h resource.h
    $(rc) $(rcvars) -r -fo $(OUTDIR)\$(proj).res $(proj).rc

# Update the object files if necessary
$(OUTDIR)\winboard.obj: winboard.c config.h winboard.h ../common.h ../frontend.h \
        ../backend.h ../moves.h wgamelist.h defaults.h resource.h wclipbrd.h \
        wedittags.h wsockerr.h ../lists.h
    $(cc) $(cflags) $(cvars) $(cdebug) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" winboard.c

$(OUTDIR)\backend.obj: ../backend.c config.h ../common.h ../frontend.h ../backend.h \
        ../parser.h ../moves.h ../zippy.h ../backendz.h ../lists.h
    $(cc) $(cflags) $(cvars) $(cdebug) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" ../backend.c

$(OUTDIR)\parser.obj: parser.c config.h ../common.h ../backend.h ../parser.h \
        ../frontend.h ../moves.h ../lists.h
    $(cc) $(cflags) $(cvars) $(cdebug) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" parser.c

parser.c: ../parser.l
    flex -oparser.c -L ../parser.l

$(OUTDIR)\moves.obj: ../moves.c config.h ../backend.h ../common.h ../parser.h \
        ../moves.h ../lists.h ../frontend.h
    $(cc) $(cflags) $(cvars) $(cdebug) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" ../moves.c

$(OUTDIR)\lists.obj: ../lists.c config.h ../lists.h ../common.h
    $(cc) $(cflags) $(cvars) $(cdebug) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" ../lists.c

$(OUTDIR)\gamelist.obj: ../gamelist.c config.h ../lists.h ../common.h ../frontend.h \
        ../backend.h ../parser.h ../lists.h
    $(cc) $(cflags) $(cvars) $(cdebug) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" ../gamelist.c

$(OUTDIR)\pgntags.obj: ../pgntags.c config.h ../common.h ../frontend.h ../backend.h \
    ../parser.h ../lists.h
    $(cc) $(cflags) $(cvars) $(cdebug) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" ../pgntags.c

$(OUTDIR)\wclipbrd.obj: wclipbrd.c config.h ../common.h ../frontend.h ../backend.h \
              winboard.h wclipbrd.h ../lists.h resource.h
    $(cc) $(cflags) $(cvars) $(cdebug) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" wclipbrd.c

$(OUTDIR)\wedittags.obj: wedittags.c config.h ../common.h winboard.h ../frontend.h \
        ../backend.h ../lists.h resource.h
    $(cc) $(cflags) $(cvars) $(cdebug) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" wedittags.c

$(OUTDIR)\wgamelist.obj: wgamelist.c config.h. ../common.h winboard.h ../frontend.h \
        ../backend.h wgamelist.h ../lists.h resource.h
    $(cc) $(cflags) $(cvars) $(cdebug) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" wgamelist.c

$(OUTDIR)\woptions.obj: woptions.c config.h ../common.h ../frontend.h ../backend.h \
	../lists.h defaults.h
    $(cc) $(cflags) $(cvars) $(cdebug) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" woptions.c

$(OUTDIR)\wsockerr.obj: wsockerr.c wsockerr.h
    $(cc) $(cflags) $(cvars) $(cdebug) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" wsockerr.c

$(OUTDIR)\zippy.obj: ../zippy.c config.h ../common.h ../zippy.h ../frontend.h \
	../backend.h ../backendz.h ../lists.h
    $(cc) $(cflags) $(cvars) $(cdebug) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" ../zippy.c

$(OUTDIR)\infboard.obj: extends\infboard\infboard.c
    $(cc) $(cdebug) $(cflags) $(INC_PATH) $(cvars) \
    /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" extends\infboard\infboard.c

$(OUTDIR)\$(proj).exe: $(allobj) $(OUTDIR)\$(proj).rbj $(proj).hlp $(proj).rc
    $(link) $(linkdebug) $(guiflags) $(allobj) \
	wsock32.lib comctl32.lib winmm.lib oldnames.lib kernel32.lib \
	advapi32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib \
	ws2_32.lib $(libc) \
	$(OUTDIR)\$(proj).rbj -out:$(OUTDIR)\$(proj).exe
# I don't use the .sbr, but it can be reenabled.  Also turn /FR back on above.
#	bscmake *.sbr

test.exe: test.c
	$(cc) $(cflags) $(cvars) $(cdebug) test.c
	$(link) $(linkdebug) $(conflags) test.obj $(conlibs) -out:test.exe

