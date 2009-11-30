#
# Makefile för Panzer,  GNU GCC (g++)
#
# Filkataloger där olika delar av programvaran finns.
PANZER2K     = src
BUILD          = build

# Kompilator och flaggor som påverkar kompilering, inkludering, etc. 
# Lägg till '-g' i CCFLAGS om kompilering för avlusning ska göras.
CCC       = g++
CCFLAGS  +=	-std=c++98 -pedantic -Wall -Wextra

# Objektkodsmoduler som ingår i Panzer 2K

OBJECTS_LIST = Panzer2k.o Element.o GameEngine.o GameWorld.o State.o \
				GraphicsEngine.o
OBJECTS      = $(OBJECTS_LIST:%=$(BUILD)/%)

all: panzer2k


# Huvudmål - skapas med kommandot 'make' eller 'make panzer2k'
panzer2k: $(OBJECTS) Makefile
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -o $(BUILD)/Panzer2k $(OBJECTS)
	
# Delmal
$(BUILD)/Panzer2k.o: $(PANZER2K)/Panzer2k.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/Panzer2k.cc -o $(BUILD)/Panzer2k.o
	
$(BUILD)/Element.o: $(PANZER2K)/Element.h $(PANZER2K)/Element.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/Element.cc -o $(BUILD)/Element.o

$(BUILD)/GameEngine.o: $(PANZER2K)/GameEngine.h $(PANZER2K)/GameEngine.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/GameEngine.cc -o $(BUILD)/GameEngine.o

$(BUILD)/GameWorld.o: $(PANZER2K)/GameWorld.h $(PANZER2K)/GameWorld.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/GameWorld.cc -o $(BUILD)/GameWorld.o

$(BUILD)/GraphicsEngine.o: $(PANZER2K)/GraphicsEngine.h $(PANZER2K)/GraphicsEngine.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/GraphicsEngine.cc -o $(BUILD)/GraphicsEngine.o

$(BUILD)/State.o: $(PANZER2K)/State.h $(PANZER2K)/State.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/State.cc -o $(BUILD)/State.o



# make Element

Element: $(BUILD)/Element.o

# 'make clean' tar bort objektkodsfiler och 'core'
clean:
	@ \rm -rf $(BUILD)/*.o core

# 'make zap' tar också bort det körbara programmet och reservkopior (filer
# som slutar med tecknet '~')
zap: clean
	@ \rm -rf $(BUILD)/* *~
