#/usr/bin/python
# make supplier tuples of the form
# (name, addr)

from random import randint, choice

addrs = []
for street in open("listofstreets"):
    addrs.append(street.strip())

for name in open("listofrandomnames"):
    print "(\"%s\", \"%d %s\")," % ("Supplier-"+name.strip(), randint(1000,9000), choice(addrs))
