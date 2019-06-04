/*
  +----------------------------------------------------------------------+
  | PHP Version 4                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2003 The PHP Group                                |
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

  $Id: header,v 1.10.8.1 2003/07/14 15:59:18 sniper Exp $ 
*/

#ifndef PHP_B1GZIP_H
#define PHP_B1GZIP_H

extern zend_module_entry b1gzip_module_entry;
#define phpext_b1gzip_ptr &b1gzip_module_entry

#ifdef PHP_WIN32
#define PHP_B1GZIP_API __declspec(dllexport)
#else
#define PHP_B1GZIP_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(b1gzip);
PHP_MSHUTDOWN_FUNCTION(b1gzip);
PHP_RINIT_FUNCTION(b1gzip);
PHP_RSHUTDOWN_FUNCTION(b1gzip);
PHP_MINFO_FUNCTION(b1gzip);

//#PHP_FUNCTION(confirm_b1gzip_compiled);	/* For testing, remove later. */
PHP_FUNCTION(b1gzip_create);
PHP_FUNCTION(b1gzip_add);
PHP_FUNCTION(b1gzip_final);
/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(b1gzip)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(b1gzip)
*/

/* In every utility function you add that needs to use variables 
   in php_b1gzip_globals, call TSRM_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as B1GZIP_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define B1GZIP_G(v) TSRMG(b1gzip_globals_id, zend_b1gzip_globals *, v)
#else
#define B1GZIP_G(v) (b1gzip_globals.v)
#endif

#endif	/* PHP_B1GZIP_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
