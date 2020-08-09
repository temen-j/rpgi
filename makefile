CXX = g++
CXXFLAGS = -Wall -Iinclude -m64 -mbmi
LIB = -lraylib -lrmem -lopengl32 -lgdi32 -lwinmm -static -lpthread

DEV_OBJ = console.o
GUI_OBJ = gui.o window.o
MATH_OBJ = tmath.o interp.o
GRAPHICS_OBJ = sprite.o
INVENTORY_OBJ = elemino.o inventory.o moveinventory.o
MOVE_OBJ = move.o allmoves.o moveeffect.o move_impl.o
COMBAT_OBJ = actor.o combat.o combatdata.o execmove.o
GAME_OBJ = game.o element.o player.o

BUILD ?= DEBUG
SYSTEM ?= NONE
EMPTY = 

ifeq ($(BUILD),DEBUG)
	CXXFLAGS += -pg -g
endif
ifeq ($(BUILD),FAST)
	CXXFLAGS += -O3 -pg -g
endif
ifeq ($(BUILD),RELEASE)
	CXXFLAGS += -O3 -s
endif
ifeq ($(SYSTEM),WINDOWS)
	CXXFLAGS += -mwindows
endif


game:
	make game.exe
	move game.exe bin

game.exe: src\main.cpp $(GUI_OBJ) $(MATH_OBJ) $(GAME_OBJ) $(DEV_OBJ) $(INVENTORY_OBJ) $(MOVE_OBJ) $(COMBAT_OBJ) $(GRAPHICS_OBJ)
	$(CXX) $(CXXFLAGS) src\main.cpp $(EMPTY) \
		$(GUI_OBJ) $(MATH_OBJ) $(GAME_OBJ) $(INVENTORY_OBJ) $(MOVE_OBJ) $(COMBAT_OBJ) $(DEV_OBJ) $(GRAPHICS_OBJ)\
		-L. $(LIB) -o $@


gui.o: src\gui.cpp include\gui.h include\player.h include\inventory.h include\console.h include\elemino.h include\gamestate.h
	$(CXX) $(CXXFLAGS) -c src\gui.cpp -L. $(LIB)

raygui_impl.o: src\raygui_impl.cpp
	$(CXX) $(CXXFLAGS) -c src\raygui_impl.cpp -L. $(LIB)

tmath.o: src\tmath.cpp include\tmath.h
	$(CXX) $(CXXFLAGS) -c src\tmath.cpp -L. $(LIB)

interp.o: src\interp.cpp include\tmath.h
	$(CXX) $(CXXFLAGS) -c src\interp.cpp -L. $(LIB)

element.o: src\element.cpp include\element.h
	$(CXX) $(CXXFLAGS) -c src\element.cpp -L. $(LIB)

elemino.o: src\elemino.cpp include\elemino.h include\gui.h
	$(CXX) $(CXXFLAGS) -c src\elemino.cpp -L. $(LIB)

actor.o: src\actor.cpp include\actor.h include\element.h include\moveeffect.h
	$(CXX) $(CXXFLAGS) -c src\actor.cpp -L. $(LIB)

player.o: src\player.cpp include\player.h include\team.h include\elemino.h include\inventory.h include\actor.h
	$(CXX) $(CXXFLAGS) -c src\player.cpp -L. $(LIB)

console.o: src\console.cpp include\console.h include\game.h include\player.h include\elemino.h include\gamestate.h
	$(CXX) $(CXXFLAGS) -c src\console.cpp -L. $(LIB)

game.o: src\game.cpp include\game.h
	$(CXX) $(CXXFLAGS) -c src\game.cpp -L. $(LIB)

inventory.o: src\inventory.cpp include\inventory.h include\game.h include\player.h
	$(CXX) $(CXXFLAGS) -c src\inventory.cpp -L. $(LIB)

move.o: src\move.cpp include\move.h
	$(CXX) $(CXXFLAGS) -c src\move.cpp -L. $(LIB)

allmoves.o: src\allmoves.cpp include\allmoves.h include\move.h
	$(CXX) $(CXXFLAGS) -c src\allmoves.cpp -L. $(LIB)

moveinventory.o: src\moveinventory.cpp include\moveinventory.h include\move.h
	$(CXX) $(CXXFLAGS) -c src\moveinventory.cpp -L. $(LIB)

combat.o: src\combat.cpp include\combat.h include\gui.h include\team.h include\move.h
	$(CXX) $(CXXFLAGS) -c src\combat.cpp -L. $(LIB)

combatdata.o: src\combatdata.cpp include\combat.h
	$(CXX) $(CXXFLAGS) -c src\combatdata.cpp -L. $(LIB)

execmove.o: src\execmove.cpp include\combat.h
	$(CXX) $(CXXFLAGS) -c src\execmove.cpp -L. $(LIB)

moveeffect.o: src\moveeffect.cpp include\moveeffect.h include\moveconst.h include\actor.h
	$(CXX) $(CXXFLAGS) -c src\moveeffect.cpp -L. $(LIB)

move_impl.o: src\move_impl.cpp include\move_impl.h include\actor.h include\combat.h include\move.h
	$(CXX) $(CXXFLAGS) -c src\move_impl.cpp -L. $(LIB)

sprite.o: src\sprite.cpp include\sprite.h
	$(CXX) $(CXXFLAGS) -c src\sprite.cpp -L. $(LIB)

window.o: src\window.cpp include\window.h
	$(CXX) $(CXXFLAGS) -c src\window.cpp -L. $(LIB)

librmem.a: src\rmem.c
	gcc -O3 -c src\rmem.c
	ar rcs rmem.o librmem.a

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


