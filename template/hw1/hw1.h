/* Determines if an object is buoyant based on weight and radius */
int is_buoyant(double weight, double radius);

/* Determines the number of pods (a multiple of 96) to buy for a family */
unsigned int pods_to_order(unsigned int people, unsigned int cups_per_day,
                           unsigned int days); 

/* Determines the greatest common divisor between two numbers */
unsigned int gcd(unsigned int n, unsigned int m);