@.str.d = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.s = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.f = private unnamed_addr constant [3 x i8] c"%f\00", align 1

@.gVar.1 = private unnamed_addr constant [6 x i8] c"Equal\00", align 1
@.gVar.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.gVar.3 = private unnamed_addr constant [10 x i8] c"Not equal\00", align 1
@.gVar.4 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.gVar.5 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

define void @NoJSInitglobalVars() {
	ret void
}
define i8 @comparison(i32, i32) {
	%3 = alloca i32, align 4
	store i32 %0, i32* %3, align 4
	%4 = alloca i32, align 4
	store i32 %1, i32* %4, align 4
	%5 = alloca i32, align 4
	%6 = load i32, i32* %3, align 4
	store i32 %6, i32* %5, align 4
	%7 = load i32, i32* %5, align 4
	%8 = alloca i32, align 4
	%9 = load i32, i32* %4, align 4
	store i32 %9, i32* %8, align 4
	%10 = load i32, i32* %8, align 4
	%11 = icmp ne i32 %7, %10
	%12 = zext i1 %11 to i8
	%13 = alloca i8, align 1
	store i8 %12, i8* %13, align 1
	%14 = load i8, i8* %13, align 1
	%15 = trunc i8 %14 to i1
	br i1 %15, label %markNoJSiftrue0, label %markNoJSiffalse0

markNoJSiftrue0:
	%16 = alloca i8, align 1
	store i8 0, i8* %16, align 1
	%17 = load i8, i8* %16, align 1
	ret i8 %17

markNoJSiffalse0:
	%18 = alloca i8, align 1
	store i8 1, i8* %18, align 1
	%19 = load i8, i8* %18, align 1
	ret i8 %19

markNoJSendIf0:
	%20 = alloca i8, align 1
	store i8 0, i8* %20, align 1
	%21 = load i8, i8* %20, align 1
	ret i8 %21
}
define i32 @printResult(i8) {
	%2 = alloca i8, align 1
	store i8 %0, i8* %2, align 1
	%3 = alloca i8, align 1
	%4 = load i8, i8* %2, align 1
	store i8 %4, i8* %3, align 1
	%5 = load i8, i8* %3, align 1
	%6 = alloca i8, align 1
	store i8 1, i8* %6, align 1
	%7 = load i8, i8* %6, align 1
	%8 = icmp eq i8 %5, %7
	%9 = zext i1 %8 to i8
	%10 = alloca i8, align 1
	store i8 %9, i8* %10, align 1
	%11 = load i8, i8* %10, align 1
	%12 = trunc i8 %11 to i1
	br i1 %12, label %markNoJSiftrue1, label %markNoJSiffalse1

markNoJSiftrue1:
	%13 = alloca [6 x i8], align 1
	%14 = bitcast [6 x i8]* %13 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %14, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.gVar.1, i32 0, i32 0), i64 6, i32 1, i1 false)
	%15 = getelementptr inbounds [6 x i8], [6 x i8]* %13, i32 0, i32 0
	%16 = alloca i8*, align 1
	store i8* %15, i8** %16, align 1
	%17 = load i8*, i8** %16, align 1
	%18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %17)
	%19 = alloca [2 x i8], align 1
	%20 = bitcast [2 x i8]* %19 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %20, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.gVar.2, i32 0, i32 0), i64 2, i32 1, i1 false)
	%21 = getelementptr inbounds [2 x i8], [2 x i8]* %19, i32 0, i32 0
	%22 = alloca i8*, align 1
	store i8* %21, i8** %22, align 1
	%23 = load i8*, i8** %22, align 1
	%24 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %23)
	br label %markNoJSendIf1

markNoJSiffalse1:
	%25 = alloca [10 x i8], align 1
	%26 = bitcast [10 x i8]* %25 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %26, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.gVar.3, i32 0, i32 0), i64 10, i32 1, i1 false)
	%27 = getelementptr inbounds [10 x i8], [10 x i8]* %25, i32 0, i32 0
	%28 = alloca i8*, align 1
	store i8* %27, i8** %28, align 1
	%29 = load i8*, i8** %28, align 1
	%30 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %29)
	%31 = alloca [2 x i8], align 1
	%32 = bitcast [2 x i8]* %31 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %32, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.gVar.4, i32 0, i32 0), i64 2, i32 1, i1 false)
	%33 = getelementptr inbounds [2 x i8], [2 x i8]* %31, i32 0, i32 0
	%34 = alloca i8*, align 1
	store i8* %33, i8** %34, align 1
	%35 = load i8*, i8** %34, align 1
	%36 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %35)
	br label %markNoJSendIf1

markNoJSendIf1:
	%37 = alloca i32, align 4
	store i32 0, i32* %37, align 4
	%38 = load i32, i32* %37, align 4
	ret i32 %38
}
define i32 @main() {
	call void @NoJSInitglobalVars()
	%1 = alloca i32, align 4
	store i32 0, i32* %1, align 4
	%2 = load i32, i32* %1, align 4
	%3 = alloca i32, align 4
	store i32 1, i32* %3, align 4
	%4 = load i32, i32* %3, align 4
	%5 = call i8 @comparison(i32 %2, i32 %4)
	%6 = alloca i8, align 1
	store i8 %5, i8* %6, align 1
	%7 = load i8, i8* %6, align 1
	%8 = trunc i8 %7 to i1
	%9 = zext i1 %8 to i32
	%10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.d, i32 0, i32 0), i32 %9)
	%11 = alloca [2 x i8], align 1
	%12 = bitcast [2 x i8]* %11 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %12, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.gVar.5, i32 0, i32 0), i64 2, i32 1, i1 false)
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
