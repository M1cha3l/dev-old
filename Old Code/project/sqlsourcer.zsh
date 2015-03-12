#!/bin/zsh
# Run some commands on a MySQL database.
# Specify the commands in a file and give it in $1.
# For even more convenience, use process substitution, eg,
# $ ./$0 <(noglob print select * from employee)
emulate -L zsh

# set variables $MUSER, $MPASS, $MDB
. ./dbinfo

# source the file in mysql
mysql -u$MUSER -p$MPASS $MDB -e "source ${1:-create-tables.sql};"
