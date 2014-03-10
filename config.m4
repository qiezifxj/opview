
PHP_ARG_WITH(opview, for opview support,
dnl Make sure that the comment is aligned:
[  --with-opview             Include opview support])


if test "$PHP_OPVIEW" != "no"; then
  PHP_NEW_EXTENSION(opview, opview.c opdump.c, $ext_shared)
fi
