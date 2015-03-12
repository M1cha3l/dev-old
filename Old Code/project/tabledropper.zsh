#!/bin/zsh
# Drop all tables in a database.
emulate -L zsh

# set variables $MUSER, $MPASS, $MDB
. ./dbinfo

# fill an array with table names
TABLES=( $(mysql -u$MUSER -p$MPASS $MDB -e 'show tables;' | awk '{print $1}' | grep -v '^Tables') )

# drop them
case ${#TABLES} in
  0)  print "No tables in $MDB to drop."
      exit 0
      ;;
  *)  print "Deleting the following ${#TABLES} tables from $MDB database:"
      print -l $TABLES | column
      mysql -u$MUSER -p$MPASS $MDB -e "set foreign_key_checks = 0; drop table ${(j:,:)TABLES};"
      exit $?
      ;;
esac
