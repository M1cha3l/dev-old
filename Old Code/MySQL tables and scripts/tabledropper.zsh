#!/bin/zsh
. ./dbinfo

TABLES=( $(mysql -u $MUSER -p$MPASS $MDB -e 'show tables' | awk '{ print $1}' | grep -v '^Tables') )

[[ ${(w)#TABLES} -gt 0 ]] && (
    print "Deleting tables ${(j: :)TABLES} from $MDB database..."
    mysql -u $MUSER -p$MPASS $MDB -e "set foreign_key_checks = 0; drop table ${(j:,:)TABLES};"
) || (
    print "No tables in $MDB to drop."
)
