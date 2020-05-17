.PHONY: hhvm

hhvm:
	cd hhvm/libstemmer_c/ && make && mv libstemmer.o ../libstemmer.o && cd .. && hphpize && cmake . && make && cp hhvm_stemmer.so /etc/hhvm/hhvm_stemmer.so && service hhvm restart && hhvm tests/001.php
