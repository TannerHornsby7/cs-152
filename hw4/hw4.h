// flips the capitalization of each letter in a string without altering input
char* flip_case(char* s);

// takes a string to search for and a string to search in and gives # of matches
char** matches(char* s, char* pat, unsigned int* nmatches);

// concatenates two strings
char* concat_strings(char** strings, unsigned int num_strings, char delim);

// measurement functionality
struct measurement {
    double value;
    char* units;
    unsigned int exponent;
};

struct measurement add_measurements(struct measurement m1, struct measurement m2);
struct measurement scale_measurement(struct measurement m, double lambda);
struct measurement multiply_measurements(struct measurement m1, struct measurement m2);
char* measurement_tos(struct measurement m);

struct conversion {
    char *from, *to;
    double mult_by;
};

struct measurement convert_units(struct conversion* conversions,
                                 unsigned int n_conversions,
                                 struct measurement m, 
                                 char* to);