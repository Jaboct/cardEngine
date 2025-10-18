
#CompType=win

CC = gcc
ifeq ($(CompType), win)
CFLAGS = -Wall -g -I$(IDIR)
else
CFLAGS = -Wall -g -I$(IDIR) -Dreg -DubuComp -I/usr/include/freetype2/
endif
# these make it a .so (Shared Object library) with (Position Independent Code)
CFLAGS2 = -fPIC -shared
# -Wl,--no-undefined

IDIR = include/
ODIR = obj/
LDIR = lib/
SDIR = src/

ifeq ($(CompType), win)
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSOIL -lfreetype \
 -ljalbDraw -ljalb_xml -ljalb \
 -lGLEW32 -lopengl32 -lglu32 -lm \
 -lSDL2main -lSDL2 \
 -lSOIL -lGLEW32 -lopengl32
Dep = dep\\
else
LIBS = \
 -ljalb_xml -ljalbDraw -ljalb_xml -ljalb \
 -lGLEW -lGL -lSOIL \
 -lSDL2 -lfreetype \
 -lm
Dep = dep/
endif
# -ldl // for dlsym stuff.


# libGenerics expects the .so to contain 1 class, which is the same name as the .so.
# libSpecifics will have their own list of class files, declared in "cardEngineFiles = ..."

all: libGeneric libSpecific

# Lib Loop for generic so's#

_libGenericData = # mods with a single file that match the mod name go here.
libGenericData = $(patsubst %,$(LDIR)%.so,$(_libGenericData))
libGeneric: $(libGenericData)

$(libGenericData): $(LDIR)%.so: $(SDIR)%.c $(IDIR)%.h
	$(CC) $(CFLAGS) $(CFLAGS2) -o $@ $< $(LIBS)


# Lib Shit for specific so's#

cardEngine: $(LDIR)cardEngine.so

SPECIFIC = cardEngine # mods with specific file lists (below) go here.
SPECIFICSO = $(patsubst %,$(LDIR)%.so,$(SPECIFIC))

libSpecific: $(SPECIFICSO)

# cardEngine
cardEngineFiles = \
 mod \
 card_util \
 solitaire solitaire_hand \
 oasis oasis_hand oasis_render oasis_event

# can i make these 2 generic, so i dont need to copy paste it for each mod.
# backbone_cardEngine xmlFunctGrouper_cardEngine
cardEngineOs = $(patsubst %,$(ODIR)%.o,$(cardEngineFiles))
cardEngineDeps = $(patsubst %,$(Dep)%.d,$(cardEngineFiles))

# can i make this generic, so i dont need to copy paste it for each mod?
$(LDIR)cardEngine.so: $(cardEngineOs)
	$(CC) $(CFLAGS) $(CFLAGS2) -o $@ $^ $(LIBS)


# this is generic.
$(ODIR)%.o:
	$(CC) $(CFLAGS) $(CFLAGS2) -c -o $@ $< $(LIBS)


#in this, convert obj to $(ODIR)
ifeq ($(CompType), win)
$(Dep)%.d: $(SDIR)%.c
	del $@;
	$(CC) -MM $(CFLAGS) $< >$@.$$$$
	sed "s,\($*\)\.o[ :]*,obj/\1.o $(Dep)\1.d : ,g" < $@.$$$$ > $@
	del $@.$$$$

else
$(Dep)%.d: $(SDIR)%.c
	rm -f $@; \
	$(CC) -MM $(CFLAGS) $< >$@.$$$$; \
	sed "s,\($*\)\.o[ :]*,obj/\1.o dep/\1.d : ,g" < $@.$$$$ > $@; \
	rm $@.$$$$;

endif

ifneq ($(MAKECMDGOALS),clean)
# paste each modDeps here so they are generated when building.
include $(cardEngineDeps)
endif

.PHONY: clean

clean:
ifeq ($(CompType), win)
	del obj\*.o *~ modCore.exe dep\*.d lib\*.so
else
	rm -f $(ODIR)*.o $(Dep)*.d $(libGenericData) $(SPECIFICSO) *~ $(LDIR)*.so
endif




