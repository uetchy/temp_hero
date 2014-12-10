bin_PROGRAMS = main
main_SOURCES = main.cpp battle.cpp renderer.cpp screenplay.cpp map.cpp player.cpp

AM_LDFLAGS = -L/usr/local/opt/ncurses/lib -lncursesw
AM_CPPFLAGS = -I/usr/local/opt/ncurses/include

maintainer-clean-local:
	rm -f Makefile.in
