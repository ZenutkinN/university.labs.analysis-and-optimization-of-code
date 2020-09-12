@.str.d = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.s = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.f = private unnamed_addr constant [3 x i8] c"%f\00", align 1

@.gVar.1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

define void @NoJSInitglobalVars() {
	ret void
}
define i32 @test(i32, i32) {
	%3 = alloca i32, align 4
	store i32 %0, i32* %3, align 4
	%4 = alloca i32, align 4
	store i32 %1, i32* %4, align 4
	%5 = alloca i32, align 4
	%6 = alloca i32, align 4
	%7 = load i32, i32* %3, align 4
	store i32 %7, i32* %6, align 4
	%8 = load i32, i32* %6, align 4
	store i32 %8, i32* %5, align 4
	%9 = alloca i32, align 4
	%10 = load i32, i32* %4, align 4
	store i32 %10, i32* %9, align 4
	%11 = load i32, i32* %3, align 4
	%12 = load i32, i32* %9, align 4
	store i32 %12, i32* %3, align 4
	%13 = alloca i32, align 4
	%14 = load i32, i32* %5, align 4
	store i32 %14, i32* %13, align 4
	%15 = load i32, i32* %4, align 4
	%16 = load i32, i32* %13, align 4
	store i32 %16, i32* %4, align 4
	%17 = alloca i32, align 4
	%18 = load i32, i32* %3, align 4
	store i32 %18, i32* %17, align 4
	%19 = load i32, i32* %17, align 4
	ret i32 %19
}
define i32 @main() {
	call void @NoJSInitglobalVars()
	%1 = alloca i32, align 4
	store i32 10, i32* %1, align 4
	%2 = load i32, i32* %1, align 4
	%3 = alloca i32, align 4
	store i32 15, i32* %3, align 4
	%4 = load i32, i32* %3, align 4
	%5 = call i32 @test(i32 %2, i32 %4)
	%6 = alloca i32, align 4
	store i32 %5, i32* %6, align 4
	%7 = load i32, i32* %6, align 4
	%8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.d, i32 0, i32 0), i32 %7)
	%9 = alloca [2 x i8], align 1
	%10 = bitcast [2 x i8]* %9 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %10, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.gVar.1, i32 0, i32 0), i64 2, i32 1, i1 false)
	%11 = getelementptr inbounds [2 x i8], [2 x i8]* %9, i32 0, i32 0
	%12 = alloca i8*, align 1
	store i8* %11, i8** %12, align 1
	%13 = load i8*, i8** %12, align 1
	%14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %13)
	%15 = alloca i32, align 4
	store i32 0, i32* %15, align 4
	%16 = load i32, i32* %15, align 4
	ret i32 %16
}

declare i32 @printf(i8*, ...) #0
declare i32 @scanf(i8*, ...) #0
declare void @llvm.memcpy.p0i8.p0i8.i64(i8*, i8*, i64, i32, i1)
declare i8* @strcat(i8*, i8*)

attributes #0 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+sse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}

!0 = !{i32 1, !"wchar_size", i32 4}
