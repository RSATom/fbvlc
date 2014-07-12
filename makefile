.PHONY: all prep build install clean

INSTALLDIR = $(DESTDIR)/usr/lib/mozilla/plugins

all: prep build

prep:
	./deps/firebreath/prepmake.sh src build

build:
	cd ./build ./ && $(MAKE)

install:
	test -d $(INSTALLDIR) || mkdir -p $(INSTALLDIR)
	install  ./build/bin/FBVLC/npFBVLC.so $(INSTALLDIR)

clean:
	rm -rf ./build
