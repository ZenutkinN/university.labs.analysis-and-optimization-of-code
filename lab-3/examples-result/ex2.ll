@.str.d = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.s = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.f = private unnamed_addr constant [3 x i8] c"%f\00", align 1

define void @NoJSInitglobalVars() {
    ret void
}

define i32 @Test(i32) {
    %2 = alloca i32, align 4
    store i32 %0, i32* %2, align 4
    %3 = alloca i32, align 4
    %4 = alloca i32, align 4
    store i32 0, i32* %4, align 4
    %5 = load i32, i32* %4, align 4
    store i32 %5, i32* %3, align 4
    br label %markNoJS.checkCycle0
    markNoJS.checkCycle0:
    %6 = alloca i32, align 4
    %7 = load i32, i32* %3, align 4
    store i32 %7, i32* %6, align 4
    %8 = load i32, i32* %6, align 4
    %9 = alloca i32, align 4
    %10 = load i32, i32* %2, align 4
    store i32 %10, i32* %9, align 4
    %11 = load i32, i32* %9, align 4
    %12 = icmp sle i32 %8, %11
    %13 = zext i1 %12 to i8
    %14 = alloca i8, align 1
    store i8 %13, i8* %14, align 1
    %15 = load i8, i8* %14, align 1
    %16 = trunc i8 %15 to i1
    br i1 %16, label %markNoJS.cycle0, label %markNoJS.endCycle0
    markNoJS.cycle0:
    %17 = load i32, i32* %3, align 4
    %18 = add i32 %17, 1
    store i32 %18, i32* %3, align 4
    br label %markNoJS.checkCycle0
    markNoJS.endCycle0:
    %19 = alloca i32, align 4
    %20 = load i32, i32* %3, align 4
    store i32 %20, i32* %19, align 4
    %21 = load i32, i32* %19, align 4
    ret i32 %21
}

define i32 @main() {
    call void @NoJSInitglobalVars()
    %1 = alloca i32, align 4
    store i32 6, i32* %1, align 4
    %2 = load i32, i32* %1, align 4
    %3 = call i32 @Test(i32 %2)
    %4 = alloca i32, align 4
    store i32 %3, i32* %4, align 4
    %5 = load i32, i32* %4, align 4
    %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]*
    @.str.d, i32 0, i32 0), i32 %5)
    %7 = alloca i32, align 4
    store i32 0, i32* %7, align 4
    %8 = load i32, i32* %7, align 4
    ret i32 %8
}

declare i32 @printf(i8*, ...) #0
declare i32 @scanf(i8*, ...) #0
declare void @llvm.memcpy.p0i8.p0i8.i64(i8*, i8*, i64, i32, i1)
declare i8* @strcat(i8*, i8*)

attributes #0 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-
calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-
frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false"
"no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-
buffer-size"="8"
"target-cpu"="x86-64"
"target-
features"="+fxsr,+mmx,+sse,+sse2,+sse3,+x87" "unsafe-fp-math"="false" "use-soft-
float"="false" }

!llvm.module.flags = !{!0}

!0 = !{i32 1, !"wchar_size", i32 4}