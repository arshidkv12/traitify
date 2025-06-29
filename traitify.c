/* traitify extension for PHP */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "zend_interfaces.h"
#include "php_traitify.h"
#include "traitify_arginfo.h"
#include "zend_exceptions.h"

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


/* {{{ Singleton::getInstance() */
ZEND_METHOD(Traitify_Singleton, getInstance)
{
    zend_class_entry *called_scope = zend_get_called_scope(execute_data);
    zval *instance;
    zend_string *property_instance_name = zend_string_init("instance", sizeof("instance") - 1, 0);

    instance = zend_read_static_property_ex(called_scope, property_instance_name, 0);

    if (Z_TYPE_P(instance) == IS_OBJECT && instanceof_function(Z_OBJCE_P(instance), called_scope)) {
		zend_string_release(property_instance_name);
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
	
    zend_update_static_property_ex(called_scope, property_instance_name, return_value);

    zend_string_release(property_instance_name);
}
/* }}} */


/* {{{ proto void Traitify\Macroable::macro(string $name, callable $callback) */
PHP_METHOD(Traitify_Macroable, macro)
{
    zend_string *name;
    zval *callback;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(name)
        Z_PARAM_ZVAL(callback)
    ZEND_PARSE_PARAMETERS_END();

    if (!zend_is_callable(callback, 0, NULL)) {
        zend_throw_exception(NULL, "Second argument must be callable", 0);
        RETURN_THROWS();
    }

	zend_string *property_macros_name = zend_string_init("macros", sizeof("macros") - 1, 0);
	zend_class_entry *called_scope = zend_get_called_scope(execute_data);
	zval *macros =zend_read_static_property_ex(called_scope, property_macros_name, 0);

	if (Z_TYPE_P(macros) != IS_ARRAY) {
        zval tmp;
        array_init(&tmp);
        zend_update_static_property_ex(called_scope, property_macros_name, &tmp);
		zval_ptr_dtor(&tmp); 
        macros = zend_read_static_property_ex(called_scope, property_macros_name, 0);
    } else {
		SEPARATE_ARRAY(macros); 
	}

    zval cb_copy;
    ZVAL_COPY(&cb_copy, callback);
    zend_hash_update(Z_ARRVAL_P(macros), name, &cb_copy);
	zend_string_release(property_macros_name);

}
/* }}} */

/* {{{ */
PHP_METHOD(Traitify_Macroable, __call)
{
    zend_string *name;
    zval *args_array;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(name)
        Z_PARAM_ARRAY(args_array)
    ZEND_PARSE_PARAMETERS_END();

    zend_string *property_macros_name = zend_string_init("macros", sizeof("macros") - 1, 0);
    zend_class_entry *called_scope = zend_get_called_scope(execute_data);
    zval *macros = zend_read_static_property_ex(called_scope, property_macros_name, 0);
    zend_string_release(property_macros_name);

    if (!macros || Z_TYPE_P(macros) != IS_ARRAY) {
        zend_throw_exception(NULL, "No macros registered", 0);
        RETURN_THROWS();
    }

    zval *callback = zend_hash_find(Z_ARRVAL_P(macros), name);
    if (!callback) {
        zend_throw_exception_ex(NULL, 0, "Macro '%s' not found", ZSTR_VAL(name));
        RETURN_THROWS();
    }

    uint32_t argc = zend_hash_num_elements(Z_ARRVAL_P(args_array));
    zval *params = safe_emalloc(argc, sizeof(zval), 0);

    uint32_t i = 0;
    zval *entry;
    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(args_array), entry) {
        ZVAL_COPY(&params[i], entry);
        i++;
    } ZEND_HASH_FOREACH_END();

    zval retval;
    if (call_user_function(EG(function_table), NULL, callback, &retval, argc, params) == SUCCESS) {
        for (uint32_t j = 0; j < argc; ++j) {
            zval_ptr_dtor(&params[j]);
        }
        efree(params);
        RETURN_ZVAL(&retval, 1, 1);
    } else {
        for (uint32_t j = 0; j < argc; ++j) {
            zval_ptr_dtor(&params[j]);
        }
        efree(params);
        zend_throw_exception(NULL, "Failed to call macro", 0);
        RETURN_THROWS();
    }
}
/* }}} */


/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(traitify)
{

    register_class_Traitify_Singleton();
	register_class_Traitify_Macroable();

    return SUCCESS;
}
/* }}} */



/* {{{ traitify_module_entry */
zend_module_entry traitify_module_entry = {
	STANDARD_MODULE_HEADER,
	"traitify",					    /* Extension name */
	NULL,				            /* zend_function_entry */
	PHP_MINIT(traitify),            /* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(traitify),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(traitify),			/* PHP_MINFO - Module info */
	PHP_TRAITIFY_VERSION,		    /* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_TRAITIFY
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(traitify)
#endif
