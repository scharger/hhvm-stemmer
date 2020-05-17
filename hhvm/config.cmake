project(php_stemmer)

HHVM_EXTENSION(php_stemmer ext_php_stemmer.cpp)
HHVM_SYSTEMLIB(php_stemmer ext_php_stemmer.php)

target_link_libraries(php_stemmer ${CMAKE_SOURCE_DIR}/libstemmer.o)