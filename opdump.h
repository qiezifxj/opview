#ifndef OPDUMP_H
#define OPDUMP_H

#define OPNAME_BUFFLEN 40

zval * opcode_to_array(zend_op *op TSRMLS_DC);

zval * format_znode_op(znode_op *op, zend_uchar type TSRMLS_DC);

char * format_zval(zval * z);

#endif
