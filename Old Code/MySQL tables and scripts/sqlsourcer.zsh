#!/bin/zsh
. ./dbinfo
mysql -u $MUSER -p$MPASS $MDB -e "source ${1:-create-tables.sql};"
