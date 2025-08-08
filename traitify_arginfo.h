/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 4930fae350a73db5e095ee6ce5f4d9034254a349 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Traitify_Singleton_getInstance, 0, 0, IS_OBJECT, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Traitify_Macroable_macro, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, callback, IS_CALLABLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Traitify_Macroable___call, 0, 2, IS_MIXED, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, arguments, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(Traitify_Singleton, getInstance);
ZEND_METHOD(Traitify_Macroable, macro);
ZEND_METHOD(Traitify_Macroable, __call);

static const zend_function_entry class_Traitify_Singleton_methods[] = {
	ZEND_ME(Traitify_Singleton, getInstance, arginfo_class_Traitify_Singleton_getInstance, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_Traitify_Macroable_methods[] = {
	ZEND_ME(Traitify_Macroable, macro, arginfo_class_Traitify_Macroable_macro, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Traitify_Macroable, __call, arginfo_class_Traitify_Macroable___call, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Traitify_Singleton(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Traitify", "Singleton", class_Traitify_Singleton_methods);
#if (PHP_VERSION_ID >= 80400)
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_TRAIT);
#else
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_TRAIT;
#endif

	zval property_instance_default_value;
	ZVAL_NULL(&property_instance_default_value);
	zend_string *property_instance_name = zend_string_init("instance", sizeof("instance") - 1, 1);
	zend_declare_typed_property(class_entry, property_instance_name, &property_instance_default_value, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC, NULL, (zend_type) ZEND_TYPE_INIT_NONE(0));
	zend_string_release(property_instance_name);

	return class_entry;
}

static zend_class_entry *register_class_Traitify_Macroable(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Traitify", "Macroable", class_Traitify_Macroable_methods);
#if (PHP_VERSION_ID >= 80400)
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_TRAIT);
#else
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_TRAIT;
#endif

	zval property_macros_default_value;
	ZVAL_EMPTY_ARRAY(&property_macros_default_value);
	zend_string *property_macros_name = zend_string_init("macros", sizeof("macros") - 1, 1);
	zend_declare_typed_property(class_entry, property_macros_name, &property_macros_default_value, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
	zend_string_release(property_macros_name);

	return class_entry;
}
