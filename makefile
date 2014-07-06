.PHONY: all prep build clean
all: prep build

prep:
	./deps/firebreath/prepmake.sh src build

build:
	cd ./build ./ && $(MAKE)

clean:
	rm -rf ./build
