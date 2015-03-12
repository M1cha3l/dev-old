#!/bin/zsh
# use sqlsourcer.zsh to insert all our table data
emulate -L zsh

# drop table
./tabledropper.zsh

# create table
./sqlsourcer.zsh

# insert tuples
for datafile in insert-*.sql; do
    print inserting $datafile...
    ./sqlsourcer.zsh $datafile
done
