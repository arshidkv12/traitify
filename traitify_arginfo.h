/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 54b0ffc3af871b189435266df516f7575c1b9675 */


ZEND_METHOD(Singleton, getInstance);

ZEND_BEGIN_ARG_INFO(arginfo_get_instance, 0)
ZEND_END_ARG_INFO()

static const zend_function_entry singleton_methods[] = {
    ZEND_ME(Singleton, getInstance, arginfo_get_instance, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    ZEND_FE_END
};


PHP_METHOD(Macroable, macro);
PHP_METHOD(Macroable, __call);

ZEND_BEGIN_ARG_INFO_EX(arginfo_macro, 0, 0, 2)
    ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(0, callback, IS_CALLABLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo___call, 0, 0, 2)
    ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(0, arguments, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

static const zend_function_entry macroable_methods[] = {
	PHP_ME(Macroable, macro, arginfo_macro, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Macroable, __call, arginfo___call, ZEND_ACC_PUBLIC)
    ZEND_FE_END
};
