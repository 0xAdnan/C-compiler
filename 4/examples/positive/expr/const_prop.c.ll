; ModuleID = '/home/adnan/Documents/col728lab/compiler_assignment/4/examples/positive/expr/const_prop.c'
source_filename = "/home/adnan/Documents/col728lab/compiler_assignment/4/examples/positive/expr/const_prop.c"

define i32 @main() {
entry:
  %a = alloca i32, align 4
  store i32 30, ptr %a, align 4
  %b = alloca i32, align 4
  %0 = load i32, ptr %a, align 4
  %1 = sdiv i32 %0, 5
  %2 = sub i32 9, %1
  store i32 %2, ptr %b, align 4
  %c = alloca i32, align 4
  %3 = load i32, ptr %b, align 4
  %4 = mul i32 %3, 4
  store i32 %4, ptr %c, align 4
  %5 = load i32, ptr %c, align 4
  %6 = icmp slt i32 %5, 10
  %7 = icmp ne i1 %6, false
  br i1 %7, label %then, label %else

then:                                             ; preds = %entry
  %8 = load i32, ptr %c, align 4
  %9 = sub i32 %8, 10
  store i32 %9, ptr %c, align 4
  br label %ifcont

else:                                             ; preds = %entry
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  %10 = load i32, ptr %c, align 4
  %11 = load i32, ptr %a, align 4
  %12 = sdiv i32 60, %11
  %13 = mul i32 %10, %12
  ret i32 %13
}
