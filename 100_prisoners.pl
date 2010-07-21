#!/usr/bin/env perl -w
# vim: sts=4 sw=4 et :

use strict;
use List::Util 'shuffle';

my $sample_done = 0;
my $sample_size = 100;
my $failure = 0;
my $success = 0;
my $total_found = 0;
my $num_inmates = 100;
my @boxes = (1 .. $num_inmates);
my @inmates = (1 .. $num_inmates);

sub locate {
    my $array = shift;
    my $wanted = shift;
    my $count = 0;
    my @array = @$array;
    my $found = $array[$wanted-1];
    # Walk the boxes till we find 'wanted'
    while ($count < ($num_inmates >> 1)) {
        $found = $array[$found-1];
        if ($found == $wanted) {
            return 1;
        }
        $count += 1;
    }
    return 0;
}

while ($sample_done < $sample_size) {
    @boxes = shuffle(@boxes);
    my $inmate_success = 0;
    foreach (@inmates) {
        if (locate(\@boxes, $_)) {
            $inmate_success += 1;
        }
    }
    $total_found += $inmate_success;
    $sample_done += 1;
    if ($inmate_success == 100) {
        $success += 1;
    } elsif ($inmate_success == 0) {
        $failure += 1;
    }
}
 
print "Successes: ".($success*100.0/$sample_size)."%\n";
print "Partial Successes: ".($sample_size-$success-$failure)*100.0/$sample_size."%\n";
print "Failures: ".($failure*100.0/$sample_size)."%\n";
print "Individual chances: ".($total_found*100.0/($sample_size*$num_inmates))."%\n";
