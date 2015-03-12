#/usr/bin/python
# make part tuples of the form
# (NULL, price, desc, stock)

from random import random, randint

for part in open("List_of_auto_parts"):
    print "(NULL, %.2f, \"%s\", %d)," % (random()*1000, part.strip(), randint(0,500))
