@.str.d = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.s = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.f = private unnamed_addr constant [3 x i8] c"%f\00", align 1

@.gVar.1 = private unnamed_addr constant [10 x i8] c"It's okay\00", align 1
@.gVar.2 = private unnamed_addr constant [11 x i8] c"We strugle\00", align 1
@.gVar.3 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

define void @NoJSInitglobalVars() {
	ret void
}
define i8* @test(i8) {
	%2 = alloca i8, align 1
	store i8 %0, i8* %2, align 1
	%3 = alloca i8*, align 1
	%4 = alloca i8, align 1
	store i8 0, i8* %4, align 1
	%5 = load i8, i8* %4, align 1
	%6 = trunc i8 %5 to i1
	%7 = xor i1 %6, true
	%8 = zext i1 %7 to i8
	store i8 %8, i8* %4, align 1
	%9 = load i8, i8* %4, align 1
	%10 = trunc i8 %9 to i1
	br i1 %10, label %markNoJSiftrue0, label %markNoJSiffalse0

markNoJSiftrue0:
	%11 = alloca [10 x i8], align 1
	%12 = bitcast [10 x i8]* %11 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %12, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.gVar.1, i32 0, i32 0), i64 10, i32 1, i1 false)
	%13 = getelementptr inbounds [10 x i8], [10 x i8]* %11, i32 0, i32 0
	%14 = alloca i8*, align 1
	store i8* %13, i8** %14, align 1
	%15 = load i8*, i8** %3, align 1
	%16 = load i8*, i8** %14, align 1
	store i8* %16, i8** %3, align 1
	br label %markNoJSendIf0

markNoJSiffalse0:
	%17 = alloca [11 x i8], align 1
	%18 = bitcast [11 x i8]* %17 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %18, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.gVar.2, i32 0, i32 0), i64 11, i32 1, i1 false)
	%19 = getelementptr inbounds [11 x i8], [11 x i8]* %17, i32 0, i32 0
	%20 = alloca i8*, align 1
	store i8* %19, i8** %20, align 1
	%21 = load i8*, i8** %3, align 1
	%22 = load i8*, i8** %20, align 1
	store i8* %22, i8** %3, align 1
	br label %markNoJSendIf0

markNoJSendIf0:
	%23 = alloca i8*, align 1
	%24 = load i8*, i8** %3, align 1
	store i8* %24, i8** %23, align 1
	%25 = load i8*, i8** %23, align 1
	ret i8* %25
}
define i32 @main() {
	call void @NoJSInitglobalVars()
	%1 = alloca i8, align 1
	store i8 1, i8* %1, align 1
	%2 = load i8, i8* %1, align 1
	%3 = call i8* @test(i8 %2)
	%4 = alloca i8*, align 1
	store i8* %3, i8** %4, align 1
	%5 = load i8*, i8** %4, align 1
	%6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %5)
	%7 = alloca [2 x i8], align 1
	%8 = bitcast [2 x i8]* %7 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %8, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.gVar.3, i32 0, i32 0), i64 2, i32 1, i1 false)
	%9 = getelementptr inbounds [2 x i8], [2 x i8]* %7, i32 0, i32 0
	%10 = alloca i8*, align 1
	store i8* %9, i8** %10, align 1
	%11 = load i8*, i8** %10, align 1
	%12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %11)
	%13 = alloca i32, align 4
	store i32 0, i32* %13, align 4
	%14 = load i32, i32* %13, align 4
	ret i32 %14
}

declare i32 @printf(i8*, ...) #0
declare i32 @scanf(i8*, ...) #0
declare void @llvm.memcpy.p0i8.p0i8.i64(i8*, i8*, i64, i32, i1)
declare i8* @strcat(i8*, i8*)

attributes #0 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+sse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}

!0 = !{i32 1, !"wchar_size", i32 4}
