#!/usr/bin/env python
# vim: sts=4 sw=4 et :

from __future__ import division
import random

num_inmates = 1000
sample_size = 10000

def locate(array, wanted):
    count = 0
    found = array[wanted-1]
    # Walk the boxes till we find 'wanted', or have checked half the boxes
    while count < (num_inmates >> 1):
        if found == wanted:
            return 1
        found = array[found-1]
        count += 1
    return 0

samples_done = 0
failure = 0
success = 0
total_found = 0
boxes = range(1, num_inmates+1)

while samples_done < sample_size:
    random.shuffle(boxes)
    inmate_success = 0
    for i in xrange(0, num_inmates):
        # Find the box with the number i+1 by looking at half the boxes
        inmate_success += locate(boxes, i+1)

    total_found += inmate_success
    samples_done += 1
    if inmate_success == num_inmates:
        success += 1
    elif inmate_success == 0:
        failure += 1

print "Successes: %s%%" % (success*100/sample_size)
print "Partial Successes: %s%%" % ((sample_size-success-failure)*100/sample_size)
print "Failures: %s%%" % (failure*100/sample_size)
print "Individual chances: %s%%" % (total_found*100/(sample_size*num_inmates))
