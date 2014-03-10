/*
  +----------------------------------------------------------------------+
  | PHP Opview Version 1                                                 |
  +----------------------------------------------------------------------+
  | Author:   fengxingjie                                                |
  +----------------------------------------------------------------------+
*/


#ifndef PHP_OPVIEW_H
#define PHP_OPVIEW_H

extern zend_module_entry opview_module_entry;
#define phpext_opview_ptr &opview_module_entry

#define PHP_OPVIEW_VERSION "1.0.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_OPVIEW_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_OPVIEW_API __attribute__ ((visibility("default")))
#else
#	define PHP_OPVIEW_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(opview);
PHP_MSHUTDOWN_FUNCTION(opview);
PHP_RINIT_FUNCTION(opview);
PHP_RSHUTDOWN_FUNCTION(opview);
PHP_MINFO_FUNCTION(opview);

PHP_FUNCTION(confirm_opview_compiled);	/* For testing, remove later. */

PHP_FUNCTION(opview_string);


ZEND_BEGIN_ARG_INFO_EX(opview_string_params, 0, 0, 1)
    ZEND_ARG_INFO(0, phpcode_string)
ZEND_END_ARG_INFO()


#ifdef ZTS
#define OPVIEW_G(v) TSRMG(opview_globals_id, zend_opview_globals *, v)
#else
#define OPVIEW_G(v) (opview_globals.v)
#endif

#define RETURN_OP_ARRAY(op_array)                               \
    int i = 0;                                                  \
    for(i=0; i < op_array->last; i++){                          \
        zend_op * op = &(op_array->opcodes[i]);                 \
        add_next_index_zval(return_value, opcode_to_array(op TSRMLS_CC)); \
    }

#endif	/* PHP_OPVIEW_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
