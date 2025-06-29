/* traitify extension for PHP */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "zend_interfaces.h"
#include "php_traitify.h"
#include "traitify_arginfo.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

 

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(traitify)
{
#if defined(ZTS) && defined(COMPILE_DL_TRAITIFY)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(traitify)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "traitify support", "enabled");
	php_info_print_table_end();
}
/* }}} */



zend_class_entry *traitify_singleton_ce;

/* {{{ Singleton::getInstance() */
ZEND_METHOD(Singleton, getInstance)
{
    zend_class_entry *called_scope = zend_get_called_scope(execute_data);
    zval *instance;
    zend_string *key = zend_string_init("instance", sizeof("instance") - 1, 0);

    instance = zend_read_static_property_ex(called_scope, key, 0);

    if (Z_TYPE_P(instance) == IS_OBJECT && instanceof_function(Z_OBJCE_P(instance), called_scope)) {
        RETURN_ZVAL(instance, 1, 0);
    }

    object_init_ex(return_value, called_scope);

	zend_function *constructor = Z_OBJCE_P(return_value)->constructor;
    if (constructor && constructor->common.fn_flags) {
        zval retval;
        if (zend_call_method_with_0_params(Z_OBJ_P(return_value), called_scope, &constructor, "__construct", &retval) == NULL) {
            php_error_docref(NULL, E_WARNING, "Constructor call failed");
        } else {
            zval_ptr_dtor(&retval); 
        }
    }
	
    zend_update_static_property_ex(called_scope, key, return_value);

    zend_string_release(key);
}
/* }}} */


/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(traitify)
{
    zend_class_entry ce;

    INIT_NS_CLASS_ENTRY(ce, "Traitify", "Singleton", singleton_trait_methods);
    traitify_singleton_ce = zend_register_internal_class(&ce);

    traitify_singleton_ce->ce_flags |= ZEND_ACC_TRAIT;

    zend_declare_property_null(traitify_singleton_ce, "instance", sizeof("instance") - 1, ZEND_ACC_PROTECTED | ZEND_ACC_STATIC);

    return SUCCESS;
}
/* }}} */



/* {{{ traitify_module_entry */
zend_module_entry traitify_module_entry = {
	STANDARD_MODULE_HEADER,
	"traitify",					/* Extension name */
	NULL,				/* zend_function_entry */
	PHP_MINIT(traitify),       // MINIT,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(traitify),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(traitify),			/* PHP_MINFO - Module info */
	PHP_TRAITIFY_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_TRAITIFY
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(traitify)
#endif
