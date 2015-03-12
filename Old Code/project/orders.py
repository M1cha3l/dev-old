#/usr/bin/python
# make order tuples of the form
# (NULL, supName)

from random import choice

names = []
for name in open("listofrandomnames"):
    names.append(name.strip())

for i in range(100):
    print "(NULL, \"Supplier-%s\")," % choice(names)
