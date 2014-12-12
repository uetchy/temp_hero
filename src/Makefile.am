bin_PROGRAMS = main.out
main_out_SOURCES = main.cpp battle.cpp renderer.cpp screenplay.cpp map.cpp player.cpp

AM_LDFLAGS = -L/usr/local/opt/ncurses/lib -lncursesw
AM_CPPFLAGS = -I/usr/local/opt/ncurses/include -std=gnu++11

maintainer-clean-local:
	rm -f Makefile.in
