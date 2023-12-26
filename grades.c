/* Woojune Lee */
/* 117440560 */
/* june2002 */

#define MAX 50

static double compute_mean(int score_pen[],int num_assignments);
static double compute_sd(int score_pen[],int num_assignments);

int main(){
    int penalty, drop_count, num_assignments, assignment_number, min_temp, drop_index, weight_total = 0,
    numeric_score_total = 0, weight_total_numeric = 0;
    char stats_check, comma;
    int i,j,k;
    int score_array[MAX], weight_array[MAX], days_late_array[MAX], score_after_penalty[MAX], 
    numeric_score_array[MAX], value[MAX], after_drop[MAX], score_pen[MAX], weight_print[MAX];
    float numeric_score = 0, mean, sd;

    scanf("%d", &penalty); /* reading points penalty */
    scanf(" %d", &drop_count); /* reading number of dropped assignments */
    scanf(" %c", &stats_check); /* reading if stats are to be displayed or not */
    scanf(" %d", &num_assignments); /* reading for number of assignments */

    /* reading assignment details */
    for (i = 0; i < num_assignments; i ++){ 
      scanf(" %d", &assignment_number);
      scanf("%c", &comma);
      scanf(" %d", &score_array[assignment_number-1]);
      scanf("%c", &comma);
      scanf(" %d", &weight_array[assignment_number-1]);
      scanf("%c", &comma);
      scanf(" %d", &days_late_array[assignment_number-1]);
    }

    /* adding weights of assignment to see if it adds up to 100 */
    for (i = 0; i < num_assignments; i ++){
        weight_total += weight_array[i];
    }
    /* if weight does not add up to 100, print error message and exit progeam */
    if (weight_total != 100){ 
        printf("ERROR: Invalid values provided");
        exit(0);
    }
    /* copying the array of weights to weight_print as weight_array will be modified for dropping assignments */
    for (i = 0; i < num_assignments; i++){
        weight_print[i] = weight_array[i];
    }
    /* getting an array of values by multiplying scores and weights */
    for (i = 0; i < num_assignments; i ++){
        value[i] = score_array[i] * weight_array[i];
    }
    /* finding the lowest value assignments the amount of times drop_count specifies */
    for (i = 0; i < drop_count; i++){
        min_temp = value[0];
        /* comparing scores to see what is lower and setting it to min_temp */
        for (k = 0; k < num_assignments; k ++){
            if (min_temp > value[k] && value[k] != -1){
                min_temp = value[k];
                drop_index = k;
            }
        }
        value[drop_index] = -1; 
    }
    /* making the assignments valued at -1 to 0 to use in numeric score calculation */
    for ( i = 0; i < num_assignments; i++){
            after_drop[i] = value[i];
            if (value[i] == -1){
                after_drop[i] = 0;
            }
    }
    for ( i = 0; i < num_assignments; i ++){
        after_drop[i] = (after_drop[i]/weight_array[i]);
    }
    
    /* factoring in penalties for days late */
    for (i = 0; i < num_assignments; i++){
        score_after_penalty[i] = after_drop[i] - (penalty * days_late_array[i]);
        if (score_after_penalty[i] < 0){ /* if score after penalty is less than 0, it is set to 0 */
            score_after_penalty[i] = 0;
            weight_array[i] = 0;
        }
        numeric_score_array[i] = score_after_penalty[i] * (weight_array[i]);
    }
    /* adding sum of values and remaining weights */
    for (i = 0; i < num_assignments; i ++){
        numeric_score_total += numeric_score_array[i];
        weight_total_numeric += weight_array[i];
    }
    /* dividing values with weights to get final numeric score */
    numeric_score = ((float)numeric_score_total / weight_total_numeric);
    /* getting array of scores after penalties for mean and standard deviation calculation */
    for (i = 0; i < num_assignments; i ++){
        score_pen[i] = score_array[i] - (penalty * days_late_array[i]);
    }

    mean = compute_mean(score_pen,num_assignments);
    sd = compute_sd(score_pen,num_assignments);

    /* printing results */
    printf("Numeric Score: %5.4f\n",numeric_score);
    printf("Points Penalty Per Day Late: %d\n", penalty);
    printf("Number of Assignments Dropped: %d\n", drop_count);
    printf("Values Provided:\n");
    printf("Assignment, Score, Weight, Days Late\n");

    for (j = 0; j < num_assignments; j++){
        printf("%d,", j+1);
        printf(" %d,", score_array[j]);
        printf(" %d,", weight_print[j]);
        printf(" %d", days_late_array[j]);
        printf("\n");
    }
    /* if user wants to check stats */
    if (stats_check == 'Y' || stats_check == 'y'){
    printf("Mean: %5.4f, ", mean);
    printf("Standard Deviation: %5.4f\n", sd);
    }
}
/* function to compute mean */
static double compute_mean(int score_pen[],int num_assignments){
    double total = 0;
    int length = num_assignments;
    double mean_in_func;
    int i;
    for (i = 0; i < length ; i ++){
        total += score_pen[i];
    }
    mean_in_func = (total/length);
    return mean_in_func;
}

/* function to compute standard deviation */
static double compute_sd(int score_pen[],int num_assignments){
    double sd_top;
    double sd = 0;
    double before_root;
    int i;
    double mean;
    mean = compute_mean(score_pen,num_assignments);
    for (i = 0; i < num_assignments; i ++){
        sd_top += (score_pen[i]-mean)*(score_pen[i]-mean);
    }
    before_root = (sd_top/(float)num_assignments);
    sd = sqrt(before_root);
    return sd;
}


