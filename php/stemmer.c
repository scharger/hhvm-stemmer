/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2017 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "../snowball/include/libstemmer.h"
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_stemmer.h"

#define PHP_STEMMER_DESCRIPTOR_RES_NAME "stemmer"

/* True global resources - no need for thread safety here */
static int le_stemmer;

static int stemmer_descriptor;

static void php_stemmer_descriptor_dtor(zend_resource *rsrc)
{
    sb_stemmer_delete((struct sb_stemmer *)rsrc->ptr);
}

PHP_FUNCTION(stemmer_create)
{
    int argc = ZEND_NUM_ARGS();
	zend_string *algo = NULL;
	zend_string *enc = NULL;
    if (zend_parse_parameters(argc, "S|S", &algo, &enc) == FAILURE) {
        return;
    }

	char *enc_v = NULL;
	if (argc == 2) {
		enc_v = enc->val;
	}

	struct sb_stemmer *sb = sb_stemmer_new(algo->val, enc_v);
	if (sb == NULL) {
		RETVAL_FALSE;
		goto cleanup;
	}

    RETVAL_RES(zend_register_resource(sb, stemmer_descriptor));

cleanup:
    return;
}

PHP_FUNCTION(stemmer_apply)
{
    struct sb_stemmer *sb;
    zval *sb_resource;
	zend_string *input;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rS", &sb_resource, &input) == FAILURE) {
        RETURN_NULL();
    }

	sb = (struct sb_stemmer *)zend_fetch_resource(
		Z_RES_P(sb_resource), PHP_STEMMER_DESCRIPTOR_RES_NAME, stemmer_descriptor);

	const sb_symbol *result = sb_stemmer_stem(sb, (const sb_symbol *)input->val, input->len);
	if (result == NULL) {
		php_error_docref(NULL, E_WARNING, "stemmer_apply failed");
		RETVAL_FALSE;
		goto cleanup;
	}

    ZVAL_STRING(return_value, (char *)result);

cleanup:
	return;
}

PHP_FUNCTION(stemmer_list)
{
	array_init(return_value);

	const char **list = sb_stemmer_list();
	for (const char **cur = list; *cur != NULL; cur++) {
		add_next_index_string(return_value, *cur);
	}
	return;
}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(stemmer)
{
    stemmer_descriptor = zend_register_list_destructors_ex(
        php_stemmer_descriptor_dtor, NULL, PHP_STEMMER_DESCRIPTOR_RES_NAME,
        module_number);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(stemmer)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(stemmer)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "stemmer support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ stemmer_functions[]
 *
 * Every user visible function must have an entry in stemmer_functions[].
 */
const zend_function_entry stemmer_functions[] = {
	PHP_FE(stemmer_create,	NULL)
	PHP_FE(stemmer_apply,	NULL)
	PHP_FE(stemmer_list,	NULL)
	PHP_FE_END	/* Must be the last line in stemmer_functions[] */
};
/* }}} */

/* {{{ stemmer_module_entry
 */
zend_module_entry stemmer_module_entry = {
	STANDARD_MODULE_HEADER,
	"stemmer",
	stemmer_functions,
	PHP_MINIT(stemmer),
	PHP_MSHUTDOWN(stemmer),
	NULL,
	NULL,
	PHP_MINFO(stemmer),
	PHP_STEMMER_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_STEMMER
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(stemmer)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
