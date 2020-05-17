project(hhvm_stemmer)

HHVM_EXTENSION(hhvm_stemmer ext_hhvm_stemmer.cpp)
HHVM_SYSTEMLIB(hhvm_stemmer ext_hhvm_stemmer.php)

target_link_libraries(hhvm_stemmer ${CMAKE_SOURCE_DIR}/libstemmer.o)