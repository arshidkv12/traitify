/* traitify extension for PHP */

#ifndef PHP_TRAITIFY_H
# define PHP_TRAITIFY_H

extern zend_module_entry traitify_module_entry;
# define phpext_traitify_ptr &traitify_module_entry

# define PHP_TRAITIFY_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_TRAITIFY)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_TRAITIFY_H */
