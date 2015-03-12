#/usr/bin/python
# make repair tuples of the form
# (transNo, idNo, custNo, cost, date)
# where idNo is 1-23, custNo is 1-23

from random import randint, sample, choice, random

for idNo in sample(range(1,24), 6):
    custNo = choice(range(1,25))
    for i in range(randint(0,3)):
        print "(NULL, %d, %d, %.2f, \'%04d-%02d-%02d\')," % (idNo, custNo, random()*500, randint(2000,2012), randint(1,12), randint(1,28))
