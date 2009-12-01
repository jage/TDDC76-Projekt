#
# Makefile f�r Panzer,  GNU GCC (g++)
#
# Filkataloger d�r olika delar av programvaran finns.
PANZER2K     = src
BUILD          = build
SDL	=	-lSDL -lSDL_image

# Kompilator och flaggor som p�verkar kompilering, inkludering, etc. 
# L�gg till '-g' i CCFLAGS om kompilering f�r avlusning ska g�ras.
CCC       = g++
CCFLAGS  +=	-std=c++98 -pedantic -Wall -Wextra

# Objektkodsmoduler som ing�r i Panzer 2K

OBJECTS_LIST = Panzer2k.o Element.o GameEngine.o GameWorld.o State.o \
				GraphicsEngine.o
OBJECTS      = $(OBJECTS_LIST:%=$(BUILD)/%)

all: panzer2k


# Huvudm�l - skapas med kommandot 'make' eller 'make panzer2k'
panzer2k: $(OBJECTS) Makefile
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -o $(BUILD)/Panzer2k $(SDL) $(OBJECTS)
	
# Delmal
$(BUILD)/Panzer2k.o: $(PANZER2K)/Panzer2k.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/Panzer2k.cc -o $(BUILD)/Panzer2k.o
	
$(BUILD)/Element.o: $(PANZER2K)/Element.h $(PANZER2K)/Element.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/Element.cc -o $(BUILD)/Element.o
	
$(BUILD)/Cannon.o: $(PANZER2K)/Cannon.h $(PANZER2K)/Cannon.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/Cannon.cc -o $(BUILD)/Cannon.o

$(BUILD)/GameEngine.o: $(PANZER2K)/GameEngine.h $(PANZER2K)/GameEngine.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) $(SDL) -c $(PANZER2K)/GameEngine.cc -o $(BUILD)/GameEngine.o

$(BUILD)/GameWorld.o: $(PANZER2K)/GameWorld.h $(PANZER2K)/GameWorld.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/GameWorld.cc -o $(BUILD)/GameWorld.o

$(BUILD)/GraphicsEngine.o: $(PANZER2K)/GraphicsEngine.h $(PANZER2K)/GraphicsEngine.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/GraphicsEngine.cc -o $(BUILD)/GraphicsEngine.o

$(BUILD)/State.o: $(PANZER2K)/State.h $(PANZER2K)/State.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) $(SDL) -c $(PANZER2K)/State.cc -o $(BUILD)/State.o



# make Element

Element: $(BUILD)/Element.o

# make Cannon

Cannon: $(BUILD)/Cannon.o

# 'make clean' tar bort objektkodsfiler och 'core'
clean:
	@ \rm -rf $(BUILD)/*.o core

# 'make zap' tar ocks� bort det k�rbara programmet och reservkopior (filer
# som slutar med tecknet '~')
zap: clean
	@ \rm -rf $(BUILD)/* *~
