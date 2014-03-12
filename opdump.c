#include "php.h"
#include "zend_vm_opcodes.h"

#include "opdump.h"
#include "ophandler.h"

zval * opcode_to_array(zend_op *op TSRMLS_DC){

    zval * array;
    MAKE_STD_ZVAL(array);
    array_init_size(array, 4);

    zval * opname;
    MAKE_STD_ZVAL(opname);
    char * s_opname = zend_get_opcode_name(op->opcode);
    if( ! s_opname){
		s_opname = "<i>Unknown</i>";
	}
    ZVAL_STRING(opname, s_opname, 1);

    add_assoc_zval(array, "opname", opname);

    zval *zop1  = format_znode_op(&(op->op1), op->op1_type TSRMLS_CC);
    zval *zop2  = format_znode_op(&op->op2, op->op2_type TSRMLS_CC);
    zval *res   = format_znode_op(&op->result, op->result_type TSRMLS_CC);

	char * shandler = get_op_handler(op->opcode, op);

	zval * zhandler;
    MAKE_STD_ZVAL(zhandler);
    ZVAL_STRING(zhandler, shandler, 1);

    add_assoc_zval(array, "handler", zhandler);

    add_assoc_zval(array, "op1", zop1);
    add_assoc_zval(array, "op2", zop2);
    add_assoc_zval(array, "result", res);

    return array;
}


zval * format_znode_op(znode_op *op, zend_uchar type TSRMLS_DC){
    zval * ret;
    char * buf;

    switch(type){
        case IS_CONST:
            buf = format_zval(op->zv);
            break;
        case IS_VAR:
            {
                buf = (char *)emalloc(sizeof(char) * 10);
                snprintf(buf, 10, "$%d", op->var/sizeof(temp_variable));
                break;
            }
        case IS_TMP_VAR:
            {
                buf = (char *)emalloc(sizeof(char) * 17);
                snprintf(buf, 17, "~%d", op->var/sizeof(temp_variable));
                break;
            }
        case IS_CV:
            {
                buf = (char *)emalloc(sizeof(char) * 3);
                snprintf(buf, 3, "!%d", op->var);
                break;
            }
        case IS_UNUSED:
            {
                buf = estrdup("Unused!");
                break;
            }
        default:
            {
                buf = (char *)emalloc(sizeof(char) * 1);
                buf[0] = '\0';
                break;
            }
    }

    MAKE_STD_ZVAL(ret);
    ZVAL_STRING(ret, buf, 0);

    return ret;
}


char * format_zval(zval * z){
    char * buf;

    switch(Z_TYPE_P(z)){
        case IS_NULL:
            return estrdup("NULL");
        case IS_LONG:
        case IS_BOOL:
            {
                buf = (char *)emalloc(sizeof(char) * 10);
                snprintf(buf, 10, "%d", Z_LVAL_P(z));
                return buf;
            }
        case IS_DOUBLE:
            {
                buf = (char *)emalloc(sizeof(char) * 20);
                snprintf(buf, 20, "%f", Z_DVAL_P(z));
                return buf;
            }
        case IS_STRING:
            {
                buf = (char *)emalloc(sizeof(char) * (Z_STRLEN_P(z)+4) );
                snprintf(buf, Z_STRLEN_P(z)+4, "\"%s\"", Z_STRVAL_P(z));
                return buf;
            }
        case IS_ARRAY:
            return estrdup("Array");
        case IS_OBJECT:
            return estrdup("Object");
        case IS_RESOURCE:
            return estrdup("Resource");
        default:
            return estrdup("Unknown");
    }
}





