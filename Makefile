.PHONY: php

php: libstemmer.o
	cd php; ( make clean && phpize --clean && phpize && ./configure && make )

libstemmer.o:
	make -Csnowball clean
	make CFLAGS=-fPIC -Csnowball libstemmer.o

test:
	cd php && NO_INTERACTION=1 TEST_PHP_ARGS=--show-diff make test

memtest:
	cp run-tests.php php
	cd php && echo 's' | TEST_PHP_ARGS=-m make test

