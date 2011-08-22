/* vim: sts=4 sw=4 et :
 * Author(s): Nirbheek Chauhan
 * License: MIT
 *
 * Solve the 100 prisoners problem
 * http://www.r-bloggers.com/100-prisoners-100-lines-of-code/
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define num_inmates 1000
#define sample_size 10000

int locate (int array[], int wanted)
{
    int count;
    int found = array[wanted-1];
    // Walk the boxes till we find 'wanted', or have checked half the boxes
    for (count = 0; count < (num_inmates >> 1); count++) {
        if (found == wanted)
            return 1;
        found = array[found-1];
    }
    return 0;
}

int main()
{
    int i, samples_done;
    int success = 0;
    int failure = 0;
    int total_found = 0;
    int boxes[num_inmates];
    // Initialize boxes
    for (i = 0; i < num_inmates; i++)
        boxes[i] = i + 1;
#ifdef OMP
    #pragma omp parallel for reduction(+:total_found, success, failure) \
        firstprivate(boxes) private(i)
#endif
    for (samples_done = 0; samples_done < sample_size; samples_done++) {
        int inmate_success, j;
        // Shuffle boxes
        srandom(time(NULL));
        for (i = num_inmates-1; i > 0; i--) {
            //j = (int) (i * (random() / (RAND_MAX + 1.0)));
            j = random() % i; // CLOSE ENOUGH.
            if (i == j)
                continue;
            boxes[i] = boxes[i] ^ boxes[j];
            boxes[j] = boxes[i] ^ boxes[j];
            boxes[i] = boxes[i] ^ boxes[j];
        }

        inmate_success = 0;
#ifdef OMP
        #pragma omp parallel for reduction(+:inmate_success) private(i)
#endif
        for (i = 0; i < num_inmates; i++)
            // Find the box with the number i+1 by looking at half the boxes
            inmate_success += locate(boxes, i+1);

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
