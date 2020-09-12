@.str.d = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.s = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.f = private unnamed_addr constant [3 x i8] c"%f\00", align 1

@.gVar.1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.gVar.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.gVar.3 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.gVar.4 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

define void @NoJSInitglobalVars() {
	ret void
}
define i32 @test(i32, i32) {
	%3 = alloca i32, align 4
	store i32 %0, i32* %3, align 4
	%4 = alloca i32, align 4
	store i32 %1, i32* %4, align 4
	%5 = alloca i32, align 4
	%6 = load i32, i32* %3, align 4
	store i32 %6, i32* %5, align 4
	%7 = load i32, i32* %5, align 4
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
	%16 = load i32, i32* %4, align 4
	store i32 %16, i32* %15, align 4
	%17 = load i32, i32* %15, align 4
	%18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.d, i32 0, i32 0), i32 %17)
	%19 = alloca [2 x i8], align 1
	%20 = bitcast [2 x i8]* %19 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %20, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.gVar.2, i32 0, i32 0), i64 2, i32 1, i1 false)
	%21 = getelementptr inbounds [2 x i8], [2 x i8]* %19, i32 0, i32 0
	%22 = alloca i8*, align 1
	store i8* %21, i8** %22, align 1
	%23 = load i8*, i8** %22, align 1
	%24 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %23)
	%25 = alloca i32, align 4
	%26 = load i32, i32* %3, align 4
	store i32 %26, i32* %25, align 4
	%27 = load i32, i32* %25, align 4
	%28 = alloca i32, align 4
	%29 = load i32, i32* %4, align 4
	store i32 %29, i32* %28, align 4
	%30 = load i32, i32* %28, align 4
	%31 = icmp ne i32 %27, %30
	%32 = zext i1 %31 to i8
	%33 = alloca i8, align 1
	store i8 %32, i8* %33, align 1
	%34 = load i8, i8* %33, align 1
	%35 = trunc i8 %34 to i1
	br i1 %35, label %markNoJSiftrue0, label %markNoJSendIf0

markNoJSiftrue0:
	%36 = alloca i32, align 4
	%37 = load i32, i32* %3, align 4
	store i32 %37, i32* %36, align 4
	%38 = load i32, i32* %4, align 4
	%39 = load i32, i32* %36, align 4
	store i32 %39, i32* %4, align 4
	br label %markNoJSendIf0

markNoJSendIf0:
	%40 = alloca i32, align 4
	%41 = load i32, i32* %3, align 4
	store i32 %41, i32* %40, align 4
	%42 = load i32, i32* %40, align 4
	%43 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.d, i32 0, i32 0), i32 %42)
	%44 = alloca [2 x i8], align 1
	%45 = bitcast [2 x i8]* %44 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %45, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.gVar.3, i32 0, i32 0), i64 2, i32 1, i1 false)
	%46 = getelementptr inbounds [2 x i8], [2 x i8]* %44, i32 0, i32 0
	%47 = alloca i8*, align 1
	store i8* %46, i8** %47, align 1
	%48 = load i8*, i8** %47, align 1
	%49 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %48)
	%50 = alloca i32, align 4
	%51 = load i32, i32* %4, align 4
	store i32 %51, i32* %50, align 4
	%52 = load i32, i32* %50, align 4
	%53 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.d, i32 0, i32 0), i32 %52)
	%54 = alloca [2 x i8], align 1
	%55 = bitcast [2 x i8]* %54 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %55, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.gVar.4, i32 0, i32 0), i64 2, i32 1, i1 false)
	%56 = getelementptr inbounds [2 x i8], [2 x i8]* %54, i32 0, i32 0
	%57 = alloca i8*, align 1
	store i8* %56, i8** %57, align 1
	%58 = load i8*, i8** %57, align 1
	%59 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %58)
	%60 = alloca i32, align 4
	store i32 0, i32* %60, align 4
	%61 = load i32, i32* %60, align 4
	ret i32 %61
}
define i32 @main() {
	call void @NoJSInitglobalVars()
	%1 = alloca i32, align 4
	store i32 0, i32* %1, align 4
	%2 = load i32, i32* %1, align 4
	%3 = alloca i32, align 4
	store i32 1, i32* %3, align 4
	%4 = load i32, i32* %3, align 4
	%5 = call i32 @test(i32 %2, i32 %4)
	%6 = alloca i32, align 4
	store i32 %5, i32* %6, align 4
	%7 = alloca i32, align 4
	store i32 0, i32* %7, align 4
	%8 = load i32, i32* %7, align 4
	ret i32 %8
}

declare i32 @printf(i8*, ...) #0
declare i32 @scanf(i8*, ...) #0
declare void @llvm.memcpy.p0i8.p0i8.i64(i8*, i8*, i64, i32, i1)
declare i8* @strcat(i8*, i8*)

attributes #0 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+sse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}

!0 = !{i32 1, !"wchar_size", i32 4}
