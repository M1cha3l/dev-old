#/usr/bin/python
# make supplierPhone tuples of the form
# (phone, supName)
# where supName is a foreign key

from random import randint, choice

names = []
for name in open("listofrandomnames"):
    names.append(name.strip())

for i in range(len(names*2)):
    print "(\"%03d-%04d\", \"%s\")," % (randint(1,999), randint(0,9999), "Supplier-"+choice(names))
