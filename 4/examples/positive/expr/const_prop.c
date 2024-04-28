int printf(const char *format, ...);

int main()
{
   int a = 30;
   int b = 9 - (a / 5);
   int c;

   c = b * 4;

   if (c > 10) {
      c = c - 10;
   } else {
      c = 5;
   }

   //  while (c > 0) {
   //    c = c - 1;  
   // }

   printf("%d\n", c*(60/a));
   return c * (60 / a);
}