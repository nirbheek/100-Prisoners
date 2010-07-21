#!/usr/bin/env python
# vim: sts=4 sw=4 et :

from __future__ import division
import random

def locate(array, wanted):
    count = 0
    found = array[wanted-1]
    # Walk the boxes till we find 'wanted'
    while count < num_inmates >> 1:
        found = array[found-1]
        if found == wanted:
            return True
        count += 1
    return False

sample_done = 0
sample_size = 100
failure = success = 0
total_found = 0
num_inmates = 100
boxes = range(1, num_inmates+1)
inmates = range(1, num_inmates+1)

while sample_done < sample_size:
    random.shuffle(boxes)
    inmate_success = 0
    for inmate in inmates:
        if locate(boxes, inmate):
            inmate_success += 1
    total_found += inmate_success
    sample_done += 1
    if inmate_success == 100:
        success += 1
    elif inmate_success == 0:
        failure += 1

print "Successes: %s%%" % (success*100/sample_size)
print "Partial Successes: %s%%" % ((sample_size-success-failure)*100/sample_size)
print "Failures: %s%%" % (failure*100/sample_size)
print "Individual chances: %s%%" % (total_found*100/(sample_size*num_inmates))
