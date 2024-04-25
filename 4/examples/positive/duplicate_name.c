int printf(const char *format, ...);

int main(){
  int x = 1;
  {
    int x = 2;
    printf("%d\n", x);
  }
  {
    int x = 3;
    printf("%d\n", x);
  }
  printf("%d\n", x);

  return 0;
}