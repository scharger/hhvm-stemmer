# HHVM Snowball Stemmer extension

(Forked from https://github.com/shabbyrobe/php-stemmer)

## Version for PHP
https://github.com/scharger/php-stemmer-short

This HHVM extension wraps the C-language version of the stemmers provided by the
snowball project. http://snowballstem.org/

## Installation:

1. 
```shell
	make
```
	
hhvm_stemmer.so will be saved to /etc/hhvm/

2. add "hhvm.extensions[hhvm_stemmer] = hhvm_stemmer.so" -> /etc/hhvm/php.ini and /etc/hhvm/server.ini

3. Service HHVM restart


## Usage:

```hack   
   <?hh
   echo hh_stem("spanish", "bailando");
   // Output: bail
```
