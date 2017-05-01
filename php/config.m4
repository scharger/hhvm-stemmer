dnl $Id$
dnl config.m4 for extension stemmer

dnl If your extension references something external, use with:

PHP_ARG_WITH(stemmer, for stemmer support,
[  --enable-stemmer             Enable stemmer support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(stemmer, whether to enable stemmer support,
dnl Make sure that the comment is aligned:
dnl [  --enable-stemmer           Enable stemmer support])

if test "$PHP_STEMMER" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-stemmer -> check with-path
  dnl SEARCH_PATH="/usr/local /usr /opt/local
  dnl SEARCH_FOR="/include/stemmer.h"
  dnl if test -r $PHP_stemmer/$SEARCH_FOR; then # path given as parameter
  dnl   stemmer=$PHP_SNOWBALL
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for stemmer files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       SNOWBALL_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$SNOWBALL_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the stemmer distribution])
  dnl fi

  dnl # --with-stemmer -> add include path

  dnl # --with-stemmer -> check for lib and symbol presence
  dnl LIBNAME=snowball # you may want to change this
  dnl LIBSYMBOL=snowball # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $SNOWBALL_DIR/$PHP_LIBDIR, SNOWBALL_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_SNOWBALLLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong stemmer lib version or lib not found])
  dnl ],[
  dnl   -L$SNOWBALL_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(SNOWBALL_SHARED_LIBADD)

  PHP_NEW_EXTENSION(stemmer, stemmer.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
  EXTRA_LDFLAGS=../snowball/libstemmer.o
fi
