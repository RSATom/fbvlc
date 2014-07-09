.PHONY: all prep build install clean

installdir = /usr/lib/mozilla/plugins

all: prep build

prep:
	./deps/firebreath/prepmake.sh src build

build:
	cd ./build ./ && $(MAKE)

install: build
	test -d $(installdir) || mkdir $(installdir)
	install  ./build/bin/FBVLC/npFBVLC.so $(installdir)

clean:
	rm -rf ./build
