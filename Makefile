#
# Makefile f�r Panzer,  GNU GCC (g++)
#
# Filkataloger d�r olika delar av programvaran finns.
PANZER2K  = src
BUILD     = build
TESTS     = $(PANZER2K)/tests
SDL      += -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer

ifeq ($(NETWORK),yes)
BOOST_LD  = -lboost_system-mt -lboost_thread-mt
CPPFLAGS  += -DWITH_NETWORK
endif

# Kompilator och flaggor som p�verkar kompilering, inkludering, etc. 
# L�gg till '-g' i CCFLAGS om kompilering f�r avlusning ska g�ras.
CCC       = g++
CPPFLAGS += -std=c++98 -pedantic -Wall -Wextra -g

ifeq ($(OS),OSX)
SDL      += -lSDLmain -Wl,-framework,Cocoa
CCFLAGS  += -arch x86_64 -I/opt/local/include -L/opt/local/lib
endif


# Objektkodsmoduler som ing�r i Panzer 2K
OBJECTS_LIST = Element.o Interval.o Ground.o Cannon.o Concrete.o MovableElement.o \
			   	PhysicsEngine.o State.o Player.o GameEngine.o \
				GameWorld.o SDL_rotozoom.o GraphicsEngine.o Network.o Audio.o Panzer2k.o

OBJECTS      = $(OBJECTS_LIST:%=$(BUILD)/%)

all: panzer2k

# Huvudm�l - skapas med kommandot 'make' eller 'make panzer2k'
panzer2k: $(OBJECTS) Makefile
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -o $(BUILD)/Panzer2k $(SDL) $(BOOST_LD) $(OBJECTS)

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
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/GameEngine.cc -o $(BUILD)/GameEngine.o

$(BUILD)/GameWorld.o: $(PANZER2K)/GameWorld.h $(PANZER2K)/GameWorld.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/GameWorld.cc -o $(BUILD)/GameWorld.o

$(BUILD)/Interval.o: $(PANZER2K)/Interval.h $(PANZER2K)/Interval.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/Interval.cc -o $(BUILD)/Interval.o

$(BUILD)/GraphicsEngine.o: $(PANZER2K)/GraphicsEngine.h $(PANZER2K)/GraphicsEngine.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/GraphicsEngine.cc -o $(BUILD)/GraphicsEngine.o

$(BUILD)/MovableElement.o: $(PANZER2K)/MovableElement.h $(PANZER2K)/MovableElement.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/MovableElement.cc -o $(BUILD)/MovableElement.o	

$(BUILD)/PhysicsEngine.o: $(PANZER2K)/PhysicsEngine.h $(PANZER2K)/PhysicsEngine.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/PhysicsEngine.cc -o $(BUILD)/PhysicsEngine.o

$(BUILD)/SDL_rotozoom.o: $(PANZER2K)/SDL_rotozoom.h $(PANZER2K)/SDL_rotozoom.c
	gcc $(CCFLAGS) -c $(PANZER2K)/SDL_rotozoom.c -o $(BUILD)/SDL_rotozoom.o

$(BUILD)/State.o: $(PANZER2K)/State.h $(PANZER2K)/State.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/State.cc -o $(BUILD)/State.o

$(BUILD)/Player.o: $(PANZER2K)/Player.h $(PANZER2K)/Player.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/Player.cc -o $(BUILD)/Player.o

$(BUILD)/Network.o: $(PANZER2K)/Network.h $(PANZER2K)/Network.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/Network.cc -o $(BUILD)/Network.o

$(BUILD)/Audio.o: $(PANZER2K)/Audio.h $(PANZER2K)/Audio.cc
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c $(PANZER2K)/Audio.cc -o $(BUILD)/Audio.o


# make Element
Element: $(BUILD)/Element.o

# make Cannon
Cannon: $(BUILD)/Cannon.o

# make GameWorld
GameWorld: $(BUILD)/GameWorld.o

# make Network
Network: $(BUILD)/Network.o

tests: Network_client Network_server

Network_client: $(BUILD)/Network.o
	$(CCC) $(BOOST_LD) $(CCFLAGS) $(CPPFLAGS) -o $(BUILD)/Network_client $(BUILD)/Network.o $(TESTS)/Network_client.cc

Network_server: $(BUILD)/Network.o
	$(CCC) $(BOOST_LD) $(CCFLAGS) $(CPPFLAGS) -o $(BUILD)/Network_server $(BUILD)/Network.o $(TESTS)/Network_server.cc


# 'make clean' tar bort objektkodsfiler och 'core'
clean:
	@ \rm -rf $(BUILD)/*.o core

# 'make zap' tar ocks� bort det k�rbara programmet och reservkopior (filer
# som slutar med tecknet '~')
zap: clean
	@ \rm -rf $(BUILD)/* *~
