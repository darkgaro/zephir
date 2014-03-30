
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"


ZEPHIR_INIT_CLASS(Test_MethodArgs) {

	ZEPHIR_REGISTER_CLASS(Test, MethodArgs, test, methodargs, test_methodargs_method_entry, 0);

	zend_declare_property_null(test_methodargs_ce, SL("a"), ZEND_ACC_PUBLIC TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Test_MethodArgs, setCallable) {

	zval *a;

	zephir_fetch_params(0, 1, 0, &a);



	zephir_update_property_this(this_ptr, SL("a"), a TSRMLS_CC);

}

PHP_METHOD(Test_MethodArgs, setObject) {

	zval *a;

	zephir_fetch_params(0, 1, 0, &a);



	zephir_update_property_this(this_ptr, SL("a"), a TSRMLS_CC);

}

PHP_METHOD(Test_MethodArgs, setCallableStrict) {

	zval *a;

	zephir_fetch_params(0, 1, 0, &a);

	if (zephir_is_callable(a TSRMLS_CC) != 1) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'a' must be callable") TSRMLS_CC);
		RETURN_NULL();
	}



	zephir_update_property_this(this_ptr, SL("a"), a TSRMLS_CC);

}

PHP_METHOD(Test_MethodArgs, setObjectStrict) {

	zval *a;

	zephir_fetch_params(0, 1, 0, &a);

	if (Z_TYPE_P(a) != IS_OBJECT) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'a' must be an object") TSRMLS_CC);
		RETURN_NULL();
	}



	zephir_update_property_this(this_ptr, SL("a"), a TSRMLS_CC);

}

PHP_METHOD(Test_MethodArgs, setResourceStrict) {

	zval *a;

	zephir_fetch_params(0, 1, 0, &a);

	if (Z_TYPE_P(a) != IS_RESOURCE) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'a' must be an resource") TSRMLS_CC);
		RETURN_NULL();
	}



	zephir_update_property_this(this_ptr, SL("a"), a TSRMLS_CC);

}

