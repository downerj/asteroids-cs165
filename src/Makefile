.PHONY: clean

EXECUTABLE = asteroids
BINDIR = ../bin
OBJDIR = ../obj
CFLAGS = -Wall -Wextra -Werror -Wpedantic -pedantic-errors -std=c++20
LFLAGS = -lglut -lGLU -lGL

$(BINDIR)/$(EXECUTABLE): $(OBJDIR)/driver.o $(OBJDIR)/game.o $(OBJDIR)/uiInteract.o $(OBJDIR)/uiDraw.o $(OBJDIR)/point.o $(OBJDIR)/velocity.o $(OBJDIR)/moveable.o $(OBJDIR)/ship.o $(OBJDIR)/bullet.o $(OBJDIR)/stars.o $(OBJDIR)/color.o
	mkdir -p $(BINDIR)
	$(CXX) -o $@ $^ $(LFLAGS)

$(OBJDIR)/driver.o: driver.cpp game.hpp
	mkdir -p $(OBJDIR)
	$(CXX) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/game.o: game.cpp game.hpp uiDraw.hpp uiInteract.hpp point.hpp velocity.hpp moveable.hpp bullet.hpp stars.hpp ship.hpp color.hpp
	$(CXX) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/uiDraw.o: uiDraw.cpp uiDraw.hpp color.hpp
	$(CXX) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/uiInteract.o: uiInteract.cpp uiInteract.hpp
	$(CXX) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/point.o: point.cpp point.hpp
	$(CXX) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/velocity.o: velocity.cpp velocity.hpp point.hpp
	$(CXX) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/moveable.o: moveable.cpp moveable.hpp point.hpp velocity.hpp uiDraw.hpp
	$(CXX) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/ship.o: ship.cpp ship.hpp moveable.hpp point.hpp velocity.hpp uiDraw.hpp color.hpp
	$(CXX) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/bullet.o: bullet.cpp bullet.hpp moveable.hpp point.hpp velocity.hpp uiDraw.hpp color.hpp
	$(CXX) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/stars.o: stars.cpp stars.hpp moveable.hpp point.hpp velocity.hpp uiDraw.hpp color.hpp
	$(CXX) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/color.o: color.cpp color.hpp
	$(CXX) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(BINDIR)/$(EXECUTABLE) $(OBJDIR)/*.o
