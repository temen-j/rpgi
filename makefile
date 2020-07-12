CXX = g++
CXXFLAGS = -Wall -Iinclude -m64
LIB = -lraylib -lopengl32 -lgdi32 -lwinmm -static -lpthread

DEV_OBJ = console.o tmem.o
GUI_OBJ = gui.o
MATH_OBJ = tmath.o interp.o
GRAPHICS_OBJ = sprite.o
INVENTORY_OBJ = elemino.o inventory.o moveinventory.o
MOVE_OBJ = move.o allmoves.o moveeffect.o move_impl.o
COMBAT_OBJ = actor.o combat.o
GAME_OBJ = game.o element.o player.o

BUILD ?= DEBUG
EMPTY = 

ifeq ($(BUILD),DEBUG)
	CXXFLAGS += -pg -g
endif
ifeq ($(BUILD),RELEASE)
	CXXFLAGS += -s -O3
endif


game:
	make game.exe
	move game.exe bin

game.exe: main.cpp $(GUI_OBJ) $(MATH_OBJ) $(GAME_OBJ) $(DEV_OBJ) $(INVENTORY_OBJ) $(MOVE_OBJ) $(COMBAT_OBJ)
	$(CXX) $(CXXFLAGS) main.cpp $(EMPTY) \
		$(GUI_OBJ) $(MATH_OBJ) $(GAME_OBJ) $(INVENTORY_OBJ) $(MOVE_OBJ) $(COMBAT_OBJ) $(DEV_OBJ) \
		-L. $(LIB) -o $@


gui.o: gui.cpp include\gui.h include\player.h include\inventory.h include\console.h include\elemino.h include\gamestate.h
	$(CXX) $(CXXFLAGS) -c gui.cpp -L. $(LIB)

raygui_impl.o: raygui_impl.cpp
	$(CXX) $(CXXFLAGS) -c raygui_impl.cpp -L. $(LIB)

tmath.o: tmath.cpp include\tmath.h
	$(CXX) $(CXXFLAGS) -c tmath.cpp -L. $(LIB)

interp.o: interp.cpp include\tmath.h
	$(CXX) $(CXXFLAGS) -c interp.cpp -L. $(LIB)

element.o: element.cpp include\element.h
	$(CXX) $(CXXFLAGS) -c element.cpp -L. $(LIB)

elemino.o: elemino.cpp include\elemino.h include\gui.h
	$(CXX) $(CXXFLAGS) -c elemino.cpp -L. $(LIB)

actor.o: actor.cpp include\actor.h include\element.h
	$(CXX) $(CXXFLAGS) -c actor.cpp -L. $(LIB)

player.o: player.cpp include\player.h include\team.h include\elemino.h include\inventory.h include\actor.h
	$(CXX) $(CXXFLAGS) -c player.cpp -L. $(LIB)

console.o: console.cpp include\console.h include\game.h include\player.h include\elemino.h include\gamestate.h
	$(CXX) $(CXXFLAGS) -c console.cpp -L. $(LIB)

game.o: game.cpp include\game.h
	$(CXX) $(CXXFLAGS) -c game.cpp -L. $(LIB)

inventory.o: inventory.cpp include\inventory.h include\game.h include\player.h
	$(CXX) $(CXXFLAGS) -c inventory.cpp -L. $(LIB)

move.o: move.cpp include\move.h
	$(CXX) $(CXXFLAGS) -c move.cpp -L. $(LIB)

allmoves.o: allmoves.cpp include\allmoves.h include\move.h
	$(CXX) $(CXXFLAGS) -c allmoves.cpp -L. $(LIB)

moveinventory.o: moveinventory.cpp include\moveinventory.h include\move.h
	$(CXX) $(CXXFLAGS) -c moveinventory.cpp -L. $(LIB)

combat.o: combat.cpp include\combat.h include\gui.h include\team.h include\move.h
	$(CXX) $(CXXFLAGS) -c combat.cpp -L. $(LIB)

moveeffect.o: moveeffect.cpp include\moveeffect.h include\moveconst.h include\actor.h
	$(CXX) $(CXXFLAGS) -c moveeffect.cpp -L. $(LIB)

move_impl.o: move_impl.cpp include\move_impl.h include\actor.h include\combat.h include\move.h
	$(CXX) $(CXXFLAGS) -c move_impl.cpp -L. $(LIB)

tmem.o: tmem.c
	gcc -O3 -c tmem.c

cwl.exe: core_window_letterbox.c
	$(CXX) $(CXXFLAGS) core_window_letterbox.c -L. $(LIB) -o $@

sprite.o: sprite.cpp include\sprite.h
	$(CXX) $(CXXFLAGS) -c sprite.cpp -L. $(LIB)

run:
	$(MAKE) -C bin run

debug:
	$(MAKE) -C bin debug

prof:
	$(MAKE) -C bin prof

clean:
	del *.o

ctags:
	ctags -R -B -F


