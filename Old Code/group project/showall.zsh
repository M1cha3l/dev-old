#!/bin/zsh
# Shows the number of tuples in each table of a database.
emulate -L zsh

# set variables $MUSER, $MPASS, $MDB
. ./dbinfo

# fill an array with table names
TABLES=( $(mysql -u$MUSER -p$MPASS $MDB -e 'show tables;' | awk '{print $1}' | grep -v '^Tables') )

# show their tuple counts
for table in $TABLES; do
    print Showing $table...
    mysql -u$MUSER -p$MPASS $MDB -e "select count(*) from $table;"
done
