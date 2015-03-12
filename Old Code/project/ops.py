#/usr/bin/python
# make op tuples of the form
# (pIdNo, oIdNo, quantity)
# pIdNo is 1-464, oIdNo is 1-100

from random import randint

for i in range(100):
    for j in range(randint(0,2)):
        print "(%d, %d, %d)," % (randint(1,464), i+1, randint(5,50))
