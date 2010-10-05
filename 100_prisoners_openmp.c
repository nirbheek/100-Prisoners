// vim: sts=4 sw=4 et :

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
//#include <glib.h>

static int num_inmates = 100;
static int sample_size = 100;

int locate (int array[], int wanted) {
    int count = 0;
    int found = array[wanted-1];
    // Walk the boxes till we find 'wanted'
    while (count < (num_inmates >> 1)) {
        if (found == wanted)
            return 1;
        found = array[found-1];
        count++;
    }
    return 0;
}

int main() {
    int samples_done = 0;
    int success = 0;
    int failure = 0;
    int total_found = 0;
    int inmate_success;
    int boxes[num_inmates];
    int inmate_success_list[num_inmates];
    int i, j;
    // Initialize boxes
    for (i = 0; i < num_inmates; i++)
        boxes[i] = i+1;
    srandom(time(NULL));
    while (samples_done < sample_size) {
        // Shuffle boxes
        for (i = num_inmates-1; i > 0; i--) {
            //j = g_random_int_range (0, i+1);
            //j = (int) (i * (random() / (RAND_MAX + 1.0)));
            j = random() % i; // i is a power of 10
            if (i == j)
                continue;
            boxes[i] = boxes[i] ^ boxes[j];
            boxes[j] = boxes[i] ^ boxes[j];
            boxes[i] = boxes[i] ^ boxes[j];
        }
        inmate_success = 0;
        #pragma omp parallel for
        for (i = 0; i < num_inmates; i++)
            // Use a list to store the results => don't need locking
            // uses up a lot more memory though
            inmate_success_list[i] = locate(boxes, i+1);
        for (i = 0; i < num_inmates; i++)
            inmate_success += inmate_success_list[i];
        samples_done++;
        total_found += inmate_success;
        if (inmate_success == num_inmates)
            success++;
        else if (inmate_success == 0)
            failure++;
    }

    printf ("Successes: %f\n", success * 100.0 / sample_size);
    printf ("Partial Successes: %f\n", (sample_size - success - failure) * 100.0 / sample_size);
    printf ("Failures: %f\n", failure * 100.0 / sample_size);
    printf ("Individual chances: %f\n", total_found * 100.0 / (sample_size * num_inmates));
    return 0;
}
