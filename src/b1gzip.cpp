/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2022 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 2.02 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available at through the world-wide-web at                           |
  | http://www.php.net/license/2_02.txt.                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: B1G Software (info@b1g.de)                                   |
  +----------------------------------------------------------------------+

*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

extern "C" {
        #include "php.h"
        #include "php_ini.h"
        #include "ext/standard/info.h"
}

#include "php_b1gzip.h"
#include <ZipArchive.h>


/* True global resources - no need for thread safety here */
static int le_b1gzip;

struct zip_res {
        CZipArchive zip;
        CZipMemFile out;
};

/* {{{ b1gzip_functions[]
 *
 * Every user visible function must have an entry in b1gzip_functions[].
 */
zend_function_entry b1gzip_functions[] = {
        PHP_FE(b1gzip_create, NULL)
        PHP_FE(b1gzip_add, NULL)
        PHP_FE(b1gzip_final, NULL)
//PHP_FE(confirm_b1gzip_compiled,       NULL)           /* For testing, remove later. */
        {NULL, NULL, NULL}      /* Must be the last line in b1gzip_functions[] */
};

zend_module_entry b1gzip_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
        STANDARD_MODULE_HEADER,
#endif
        "b1gzip",
        b1gzip_functions,
        PHP_MINIT(b1gzip),
        PHP_MSHUTDOWN(b1gzip),
        PHP_RINIT(b1gzip),              /* Replace with NULL if there's nothing to do at request start */
        PHP_RSHUTDOWN(b1gzip),  /* Replace with NULL if there's nothing to do at request end */
        PHP_MINFO(b1gzip),
#if ZEND_MODULE_API_NO >= 20010901
        "0.1", /* Replace with version number for your extension */
#endif
        STANDARD_MODULE_PROPERTIES
};

 /* }}} */

#ifdef COMPILE_DL_B1GZIP
BEGIN_EXTERN_C()
ZEND_GET_MODULE(b1gzip)
END_EXTERN_C()
#endif

static CZipArchive zip;
static CZipMemFile out;

static void zip_res_dtor(zend_resource *rsrc)
{

}

PHP_MINIT_FUNCTION(b1gzip)
{
        le_b1gzip = zend_register_list_destructors_ex(zip_res_dtor, NULL, "zip res", module_number);

        return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(b1gzip)
{
        return SUCCESS;
}

PHP_RINIT_FUNCTION(b1gzip)
{
        return SUCCESS;
}

/* Remove if there's nothing to do at request end */
PHP_RSHUTDOWN_FUNCTION(b1gzip)
{
        return SUCCESS;
}

PHP_MINFO_FUNCTION(b1gzip)
{
        php_info_print_table_start();
        php_info_print_table_header(2, "b1gzip support", "enabled");
		php_info_print_table_row(2, "version", "0.1");
        php_info_print_table_end();
}

PHP_FUNCTION(b1gzip_add)
{
        char *arg = NULL;
        char *fn = NULL;
        size_t arg_len, fn_len;
        CZipMemFile newfile;
        zval *rid = NULL;

        zip_res *handle = NULL;

        if (zend_parse_parameters(ZEND_NUM_ARGS(), "rss", &rid, &arg, &arg_len, &fn, &fn_len) == FAILURE) {
                return;
        }

        handle = (zip_res*)zend_fetch_resource(Z_RES_P(rid), "zip res", le_b1gzip);
        newfile.Attach((BYTE *)arg, arg_len);
        handle->zip.AddNewFile(newfile, fn);
}

PHP_FUNCTION(b1gzip_final)
{
        size_t zip_len = 0;
        zip_res *handle = NULL;
        zval *rid;

		if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &rid) == FAILURE)   {
			return;
		}
        handle = (zip_res*)zend_fetch_resource(Z_RES_P(rid), "zip res", le_b1gzip);
        handle->zip.Close();
        zip_len = handle->out.GetLength();

        zend_list_delete(Z_RES_P(rid));

        RETURN_STRINGL((char *)handle->out.Detach(), zip_len);
}

PHP_FUNCTION(b1gzip_create)
{
        zip_res *handle = new zip_res;
        handle->zip.Open(handle->out, CZipArchive::zipCreate);
        RETURN_RES(zend_register_resource(handle, le_b1gzip));
}


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */