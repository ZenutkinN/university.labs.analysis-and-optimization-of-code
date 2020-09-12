@.str.d = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.s = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.f = private unnamed_addr constant [3 x i8] c"%f\00", align 1

@.gVar.1 = private unnamed_addr constant [28 x i8] c"Enter number from 0 to 10: \00", align 1
@.gVar.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.gVar.3 = private unnamed_addr constant [29 x i8] c"Вы ввели число: \00", align 1

define void @NoJSInitglobalVars() {
	ret void
}
define i32 @main() {
	call void @NoJSInitglobalVars()
	%1 = alloca i32, align 4
	%2 = alloca i32, align 4
	store i32 0, i32* %2, align 4
	%3 = load i32, i32* %2, align 4
	store i32 %3, i32* %1, align 4
	br label %markNoJS.cycle0

markNoJS.checkCycle0:
	%4 = alloca i32, align 4
	%5 = load i32, i32* %1, align 4
	store i32 %5, i32* %4, align 4
	%6 = load i32, i32* %4, align 4
	%7 = alloca i32, align 4
	store i32 0, i32* %7, align 4
	%8 = load i32, i32* %7, align 4
	%9 = icmp slt i32 %6, %8
	%10 = zext i1 %9 to i8
	%11 = alloca i8, align 1
	store i8 %10, i8* %11, align 1
	%12 = alloca i32, align 4
	%13 = load i32, i32* %1, align 4
	store i32 %13, i32* %12, align 4
	%14 = load i32, i32* %12, align 4
	%15 = alloca i32, align 4
	store i32 10, i32* %15, align 4
	%16 = load i32, i32* %15, align 4
	%17 = icmp sgt i32 %14, %16
	%18 = zext i1 %17 to i8
	%19 = alloca i8, align 1
	store i8 %18, i8* %19, align 1
	%20 = load i8, i8* %11, align 1
	%21 = trunc i8 %20 to i1
	%22 = load i8, i8* %19, align 1
	%23 = trunc i8 %22 to i1
	%24 = alloca i8, align 1
	br label %boolargNoJS0
boolargNoJS0:
	br i1 %21, label %boolargNoJS2, label %boolargNoJS1
boolargNoJS1:
	br i1 %23, label %boolargNoJS2, label %boolargNoJS3
boolargNoJS2:
	store i8 1, i8* %24, align 1
	br label %boolargNoJS4
boolargNoJS3:
	store i8 0, i8* %24, align 1
	br label %boolargNoJS4
boolargNoJS4:
	%25 = load i8, i8* %24, align 1
	%26 = trunc i8 %25 to i1
	br i1 %26, label %markNoJS.cycle0, label %markNoJS.endCycle0

markNoJS.cycle0:
	%27 = alloca [28 x i8], align 1
	%28 = bitcast [28 x i8]* %27 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %28, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.gVar.1, i32 0, i32 0), i64 28, i32 1, i1 false)
	%29 = getelementptr inbounds [28 x i8], [28 x i8]* %27, i32 0, i32 0
	%30 = alloca i8*, align 1
	store i8* %29, i8** %30, align 1
	%31 = load i8*, i8** %30, align 1
	%32 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %31)
	%33 = alloca [2 x i8], align 1
	%34 = bitcast [2 x i8]* %33 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %34, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.gVar.2, i32 0, i32 0), i64 2, i32 1, i1 false)
	%35 = getelementptr inbounds [2 x i8], [2 x i8]* %33, i32 0, i32 0
	%36 = alloca i8*, align 1
	store i8* %35, i8** %36, align 1
	%37 = load i8*, i8** %36, align 1
	%38 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %37)
	%39 = load i32, i32* %1, align 4
	%40 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.d, i32 0, i32 0), i32 %39)
	store i32 %39, i32* %1, align 4
	br label %markNoJS.checkCycle0

markNoJS.endCycle0:
	%41 = alloca [29 x i8], align 1
	%42 = bitcast [29 x i8]* %41 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %42, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.gVar.3, i32 0, i32 0), i64 29, i32 1, i1 false)
	%43 = getelementptr inbounds [29 x i8], [29 x i8]* %41, i32 0, i32 0
	%44 = alloca i8*, align 1
	store i8* %43, i8** %44, align 1
	%45 = load i8*, i8** %44, align 1
	%46 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %45)
	%47 = alloca i32, align 4
	%48 = load i32, i32* %1, align 4
	store i32 %48, i32* %47, align 4
	%49 = load i32, i32* %47, align 4
	%50 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.d, i32 0, i32 0), i32 %49)
	%51 = alloca i32, align 4
	store i32 0, i32* %51, align 4
	%52 = load i32, i32* %51, align 4
	ret i32 %52
}

declare i32 @printf(i8*, ...) #0
declare i32 @scanf(i8*, ...) #0
declare void @llvm.memcpy.p0i8.p0i8.i64(i8*, i8*, i64, i32, i1)
declare i8* @strcat(i8*, i8*)

attributes #0 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+sse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}

!0 = !{i32 1, !"wchar_size", i32 4}
