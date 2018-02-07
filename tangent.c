// g(x) returns x^2 + 2x
double g(double x) {
  return x*x + 2*x;
}

// dabs(x) returns the absolute value of x
double dabs(double x){
  return x > 0 ? x : -x;
}

// h(x) returns 2x^2 - 2x + 5
double h(double x) {
  return 2*x*x + 2*x + 5;
}

double sqr(double x) {
  return x * x;
}

void get_tangent(double (*f)(double x), double px, 
                 double *slope, double *yintercept,
                 double tolerance_sqr, double h_init) {
  double h = h_init;
  double mid_y = 0;
  double d = 0;
  do {
    mid_y = (f(px + h) + f(px - h)) / 2;
    d = sqr(mid_y - f(px));
    h = h / 2;
  } while(d > tolerance_sqr);
  h = 2 * h; //unmutate
  
  *slope = (f(px + h) - f(px - h));
  *slope = *slope / (2 * h);
  
  *yintercept = f(px) - (*slope * px);
}

int main(void) {

  double (*fp)(double) = g;
  double (*hp)(double) = h;
  double slope = 0;
  double yintercept = 0;
  double tolerance = 0.01;
  double h_init = 0.1;

  get_tangent(fp, 1, &slope, &yintercept, tolerance * tolerance, h_init);
  assert(dabs(slope - 4.00) < tolerance);
  assert(dabs(yintercept - (-1.00)) < tolerance);
  
  get_tangent(fp, -1, &slope, &yintercept, tolerance * tolerance, h_init);
  assert(dabs(slope) < tolerance);
  assert(dabs(yintercept - (-1)) < tolerance);
  
  get_tangent(hp, -0.5, &slope, &yintercept, tolerance * tolerance, h_init);
  assert(dabs(slope) < tolerance);
  assert(dabs(yintercept - 4.5) < tolerance);
  
  get_tangent(hp, 6, &slope, &yintercept, tolerance * tolerance, h_init);
  assert(dabs(slope - 26) < tolerance);
  assert(dabs(yintercept - (-67)) < tolerance);
}