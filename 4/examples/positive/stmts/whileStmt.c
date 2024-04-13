int printf(const char *format, ...);

int main() {
  int i = 0;
  while (i < 10) {
    i = i + 1;
    if (i == 5) {
      printf("Encountered 5, breaking loop\n");
      break;
    }
    if (i % 2 == 0) {
      printf("%d is even, continuing loop\n", i);
      continue;
    }
    printf("%d is odd\n", i);
  }
  return 0;
}