
/*
  +------------------------------------------------------------------------+
  | Zephir Language                                                        |
  +------------------------------------------------------------------------+
  | Copyright (c) 2011-2014 Zephir Team (http://www.zephir-lang.com)       |
  +------------------------------------------------------------------------+
  | This source file is subject to the New BSD License that is bundled     |
  | with this package in the file docs/LICENSE.txt.                        |
  |                                                                        |
  | If you did not receive a copy of the license and are unable to         |
  | obtain it through the world-wide-web, please send an email             |
  | to license@zephir-lang.com so we can send you a copy immediately.      |
  +------------------------------------------------------------------------+
  | Authors: Andres Gutierrez <andres@zephir-lang.com>                     |
  |          Eduar Carvajal <eduar@zephir-lang.com>                        |
  |          Vladimir Kolesnikov <vladimir@extrememember.com>              |
  +------------------------------------------------------------------------+
*/

#ifndef ZEPHIR_KERNEL_EXCEPTIONS_H
#define ZEPHIR_KERNEL_EXCEPTIONS_H

#include "Zend/zend.h"

/** Exceptions */
#define ZEPHIR_THROW_EXCEPTION_STR(class_entry, message) \
	do { \
		zephirt_throw_exception_string(class_entry, message, strlen(message) TSRMLS_CC); \
		ZEPHIR_MM_RESTORE(); \
	} while (0)

#define ZEPHIR_THROW_EXCEPTION_DEBUG_STR(class_entry, message, file, line) \
  do { \
    zephirt_throw_exception_string_debug(class_entry, message, strlen(message), file, line TSRMLS_CC); \
    ZEPHIR_MM_RESTORE(); \
  } while (0)

#define ZEPHIR_THROW_EXCEPTION_ZVAL(class_entry, message) \
	do { \
		zephirt_throw_exception_zval(class_entry, message TSRMLS_CC); \
		ZEPHIR_MM_RESTORE(); \
	} while (0)

#define ZEPHIR_THROW_EXCEPTION_DEBUG_ZVAL(class_entry, message, file, line) \
  do { \
    zephirt_throw_exception_zval(class_entry, message, file, line TSRMLS_CC); \
    ZEPHIR_MM_RESTORE(); \
  } while (0)


#define ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(class_entry, message, file, line) zephirt_throw_exception_string_debug(class_entry, message, strlen(message), file, line TSRMLS_CC)
#define ZEPHIR_THROW_EXCEPTION_STRW(class_entry, message) zephirt_throw_exception_string(class_entry, message, strlen(message) TSRMLS_CC)
#define ZEPHIR_THROW_EXCEPTION_ZVALW(class_entry, message) zephirt_throw_exception_zval(class_entry, message TSRMLS_CC)
#define ZEPHIR_THROW_EXCEPTION_DEBUG_ZVALW(class_entry, message, file, line) zephirt_throw_exception_zval_debug(class_entry, message, file, line TSRMLS_CC)

/** Throw Exceptions */
void zephirt_throw_exception(zval *object TSRMLS_DC);
void zephirt_throw_exception_debug(zval *object, const char *file, zend_uint line TSRMLS_DC);
void zephirt_throw_exception_string_debug(zend_class_entry *ce, const char *message, zend_uint message_len, const char *file, zend_uint line TSRMLS_DC);
void zephirt_throw_exception_string(zend_class_entry *ce, const char *message, zend_uint message_len TSRMLS_DC);
void zephirt_throw_exception_zval(zend_class_entry *ce, zval *message TSRMLS_DC);
void zephirt_throw_exception_zval_debug(zend_class_entry *ce, zval *message, const char *file, zend_uint line TSRMLS_DC);
void zephirt_throw_exception_internal(zval *exception TSRMLS_DC);

#endif /* ZEPHIR_KERNEL_EXCEPTIONS_H */
