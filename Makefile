.PHONY: hhvm

hhvm:
	cd hhvm/libstemmer_c/ && make && mv libstemmer.o ../libstemmer.o && cd .. && ${hphpizepatch}hphpize && cmake . && make && cp hhvm_stemmer.so /opt/hhvm/4.56.6/lib/hhvm/extensions/hhvm_stemmer.so && service hhvm restart && hhvm tests/001.php
