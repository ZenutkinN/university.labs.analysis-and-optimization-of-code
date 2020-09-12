@.str.d = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.s = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.f = private unnamed_addr constant [3 x i8] c"%f\00", align 1

@.gVar.1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

define void @NoJSInitglobalVars() {
	ret void
}
define double @test(double) {
	%2 = alloca double, align 8
	store double %0, double* %2, align 8
	%3 = alloca double, align 8
	%4 = alloca double, align 8
	%5 = load double, double* %2, align 8
	store double %5, double* %4, align 8
	%6 = alloca double, align 8
	%7 = load double, double* %2, align 8
	store double %7, double* %6, align 8
	%8 = load double, double* %4, align 8
	%9 = load double, double* %6, align 8
	%10 = alloca double, align 8
	%11 = fmul double %8, %9
	store double %11, double* %10, align 8
	%12 = load double, double* %10, align 8
	store double %12, double* %3, align 8
	%13 = alloca double, align 8
	%14 = load double, double* %3, align 8
	store double %14, double* %13, align 8
	%15 = load double, double* %13, align 8
	ret double %15
}
define i32 @main() {
	call void @NoJSInitglobalVars()
	%1 = alloca double, align 8
	%2 = alloca double, align 8
	store double -10.0, double* %2, align 8
	%3 = load double, double* %2, align 8
	store double %3, double* %1, align 8
	%4 = alloca double, align 8
	%5 = load double, double* %1, align 8
	store double %5, double* %4, align 8
	%6 = load double, double* %4, align 8
	%7 = call double @test(double %6)
	%8 = alloca double, align 8
	store double %7, double* %8, align 8
	%9 = load double, double* %8, align 8
	%10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.f, i32 0, i32 0), double %9)
	%11 = alloca [2 x i8], align 1
	%12 = bitcast [2 x i8]* %11 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %12, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.gVar.1, i32 0, i32 0), i64 2, i32 1, i1 false)
	%13 = getelementptr inbounds [2 x i8], [2 x i8]* %11, i32 0, i32 0
	%14 = alloca i8*, align 1
	store i8* %13, i8** %14, align 1
	%15 = load i8*, i8** %14, align 1
	%16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %15)
	%17 = alloca i32, align 4
	store i32 0, i32* %17, align 4
	%18 = load i32, i32* %17, align 4
	ret i32 %18
}

declare i32 @printf(i8*, ...) #0
declare i32 @scanf(i8*, ...) #0
declare void @llvm.memcpy.p0i8.p0i8.i64(i8*, i8*, i64, i32, i1)
declare i8* @strcat(i8*, i8*)

attributes #0 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+sse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}

!0 = !{i32 1, !"wchar_size", i32 4}
