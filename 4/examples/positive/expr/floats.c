int printf(const char *format, ...);

int main(){
  double x = 5.5, y = 3.3;
  printf("%lf %lf\n", x, y);

  printf("%f + %f = %f\n", x, y, x + y);
  printf("%f - %f = %f\n", x, y, x - y);
  printf("%f * %f = %f\n", x, y, x * y);
  printf("%f / %f = %f\n", x, y, x / y);

  printf("%f < %f = %d\n", x, y, x < y);

  return 0;
}