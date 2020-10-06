int main (int argc, const char * argv[]) {

    /* number of students in the trip */

    /* the total sum of money spent */

    /* the total amount of money to exchange in order to equalize */

    /* the equalized trip amount to be payed by each student */

    /* difference between the equalized amount and the amount spent */

    /* sum of all negative differences */

    /* sum of all positive differences */

    while(scanf("%ld", &amp;numOfStudents) != EOF) {

        /* 0, ends the program */

        /* keeps the amount of money spent by each student */

        double amountSpent[numOfStudents];      

        for (i = 0; i &lt; numOfStudents; i++) {

            scanf("%lf\n", &amp;amountSpent[i]);

        equalizedAmount = total / numOfStudents;

        for (i = 0; i &lt; numOfStudents; i++) {

            /* to ensure 0.01 precision */

            diff = (double) (long) ((amountSpent[i] - equalizedAmount) * 100.0) / 100.0;

        /* when the total amount is even, these sums do not differ. otherwise, they differ in one cent */

        exchange = (-negativeSum &gt; positiveSum) ? -negativeSum : positiveSum;

        printf("$%.2lf\n", exchange);
     }
        return 0;
        }
