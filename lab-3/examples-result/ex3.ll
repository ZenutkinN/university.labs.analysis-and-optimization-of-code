@.str.d = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.s = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.f = private unnamed_addr constant [3 x i8] c"%f\00", align 1

@.gVar.1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

define void @NoJSInitglobalVars() {
	ret void
}
define i8 @test(i32) {
	%2 = alloca i32, align 4
	store i32 %0, i32* %2, align 4
	%3 = alloca i8, align 1
	%4 = alloca i32, align 4
	%5 = load i32, i32* %2, align 4
	store i32 %5, i32* %4, align 4
	%6 = load i32, i32* %4, align 4
	%7 = alloca i32, align 4
	store i32 1, i32* %7, align 4
	%8 = load i32, i32* %7, align 4
	%9 = icmp ne i32 %6, %8
	%10 = zext i1 %9 to i8
	%11 = alloca i8, align 1
	store i8 %10, i8* %11, align 1
	%12 = load i8, i8* %11, align 1
	%13 = trunc i8 %12 to i1
	br i1 %13, label %markNoJSiftrue0, label %markNoJSiffalse0

markNoJSiftrue0:
	%14 = alloca i8, align 1
	store i8 0, i8* %14, align 1
	%15 = load i8, i8* %3, align 1
	%16 = load i8, i8* %14, align 1
	store i8 %16, i8* %3, align 1
	br label %markNoJSendIf0

markNoJSiffalse0:
	%17 = alloca i8, align 1
	store i8 1, i8* %17, align 1
	%18 = load i8, i8* %3, align 1
	%19 = load i8, i8* %17, align 1
	store i8 %19, i8* %3, align 1
	br label %markNoJSendIf0

markNoJSendIf0:
	%20 = alloca i8, align 1
	%21 = load i8, i8* %3, align 1
	store i8 %21, i8* %20, align 1
	%22 = load i8, i8* %20, align 1
	ret i8 %22
}
define i32 @main() {
	call void @NoJSInitglobalVars()
	%1 = alloca i32, align 4
	%2 = alloca i32, align 4
	store i32 5, i32* %2, align 4
	%3 = alloca i32, align 4
	store i32 3, i32* %3, align 4
	%4 = load i32, i32* %2, align 4
	%5 = load i32, i32* %3, align 4
	%6 = alloca i32, align 4
	%7 = sub i32 %4, %5
	store i32 %7, i32* %6, align 4
	%8 = load i32, i32* %6, align 4
	store i32 %8, i32* %1, align 4
	%9 = alloca i32, align 4
	%10 = load i32, i32* %1, align 4
	store i32 %10, i32* %9, align 4
	%11 = load i32, i32* %9, align 4
	%12 = call i8 @test(i32 %11)
	%13 = alloca i8, align 1
	store i8 %12, i8* %13, align 1
	%14 = load i8, i8* %13, align 1
	%15 = trunc i8 %14 to i1
	%16 = zext i1 %15 to i32
	%17 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.d, i32 0, i32 0), i32 %16)
	%18 = alloca [2 x i8], align 1
	%19 = bitcast [2 x i8]* %18 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %19, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.gVar.1, i32 0, i32 0), i64 2, i32 1, i1 false)
	%20 = getelementptr inbounds [2 x i8], [2 x i8]* %18, i32 0, i32 0
	%21 = alloca i8*, align 1
	store i8* %20, i8** %21, align 1
	%22 = load i8*, i8** %21, align 1
	%23 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %22)
	%24 = alloca i32, align 4
	store i32 0, i32* %24, align 4
	%25 = load i32, i32* %24, align 4
	ret i32 %25
}

declare i32 @printf(i8*, ...) #0
declare i32 @scanf(i8*, ...) #0
declare void @llvm.memcpy.p0i8.p0i8.i64(i8*, i8*, i64, i32, i1)
declare i8* @strcat(i8*, i8*)

attributes #0 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+sse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}

!0 = !{i32 1, !"wchar_size", i32 4}
