#
# Makefile för Panzer,  GNU GCC (g++)
#
# Filkataloger där olika delar av programvaran finns.
PANZER2K     = src
BUILD          = build
SDL	=	-lSDL -lSDL_image -lSDL_ttf

# Kompilator och flaggor som påverkar kompilering, inkludering, etc. 
# Lägg till '-g' i CCFLAGS om kompilering för avlusning ska göras.
CCC       = g++
CCFLAGS  +=	-std=c++98 -pedantic -Wall -Wextra -g

# Objektkodsmoduler som ingår i Panzer 2K

OBJECTS_LIST = Element.o Ground.o Cannon.o Concrete.o MovableElement.o PhysicsEngine.o State.o GameEngine.o GameWorld.o Panzer2k.o \
				SDL_rotozoom.o GraphicsEngine.o
OBJECTS      = $(OBJECTS_LIST:%=$(BUILD)/%)

all: panzer2k


# Huvudmål - skapas med kommandot 'make' eller 'make panzer2k'
panzer2k: $(OBJECTS) Makefile
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -o $(BUILD)/Panzer2k $(SDL) $(OBJECTS)
	
# Delmal
$(BUILD)/Panzer2k.o: $(PANZER2K)/Panzer2k.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/Panzer2k.cc -o $(BUILD)/Panzer2k.o
	
$(BUILD)/Element.o: $(PANZER2K)/Element.h $(PANZER2K)/Element.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/Element.cc -o $(BUILD)/Element.o
	
$(BUILD)/Cannon.o: $(PANZER2K)/Cannon.h $(PANZER2K)/Cannon.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/Cannon.cc -o $(BUILD)/Cannon.o
	
$(BUILD)/Ground.o: $(PANZER2K)/Ground.h $(PANZER2K)/Ground.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/Ground.cc -o $(BUILD)/Ground.o

$(BUILD)/Concrete.o: $(PANZER2K)/Concrete.h $(PANZER2K)/Concrete.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/Concrete.cc -o $(BUILD)/Concrete.o

$(BUILD)/GameEngine.o: $(PANZER2K)/GameEngine.h $(PANZER2K)/GameEngine.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) $(SDL) -c $(PANZER2K)/GameEngine.cc -o $(BUILD)/GameEngine.o

$(BUILD)/GameWorld.o: $(PANZER2K)/GameWorld.h $(PANZER2K)/GameWorld.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/GameWorld.cc -o $(BUILD)/GameWorld.o

$(BUILD)/GraphicsEngine.o: $(PANZER2K)/GraphicsEngine.h $(PANZER2K)/GraphicsEngine.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) $(SDL) -c $(PANZER2K)/GraphicsEngine.cc -o $(BUILD)/GraphicsEngine.o
	
$(BUILD)/MovableElement.o: $(PANZER2K)/MovableElement.h $(PANZER2K)/MovableElement.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/MovableElement.cc -o $(BUILD)/MovableElement.o	
	
$(BUILD)/PhysicsEngine.o: $(PANZER2K)/PhysicsEngine.h $(PANZER2K)/PhysicsEngine.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/PhysicsEngine.cc -o $(BUILD)/PhysicsEngine.o
	
$(BUILD)/SDL_rotozoom.o: $(PANZER2K)/SDL_rotozoom.h $(PANZER2K)/SDL_rotozoom.c
	gcc -c $(PANZER2K)/SDL_rotozoom.c -o $(BUILD)/SDL_rotozoom.o

$(BUILD)/State.o: $(PANZER2K)/State.h $(PANZER2K)/State.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) $(SDL) -c $(PANZER2K)/State.cc -o $(BUILD)/State.o



# make Element

Element: $(BUILD)/Element.o

# make Cannon

Cannon: $(BUILD)/Cannon.o

# make GameWorld

GameWorld: $(BUILD)/GameWorld.o

# 'make clean' tar bort objektkodsfiler och 'core'
clean:
	@ \rm -rf $(BUILD)/*.o core

# 'make zap' tar också bort det körbara programmet och reservkopior (filer
# som slutar med tecknet '~')
zap: clean
	@ \rm -rf $(BUILD)/* *~
