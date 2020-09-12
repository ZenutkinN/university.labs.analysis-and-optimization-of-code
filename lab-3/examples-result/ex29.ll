@.str.d = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.s = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.f = private unnamed_addr constant [3 x i8] c"%f\00", align 1

@.gVar.1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.gVar.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.gVar.3 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.gVar.4 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.gVar.5 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.gVar.6 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

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
	%4 = alloca i32, align 4
	%5 = alloca i32, align 4
	store i32 1, i32* %5, align 4
	%6 = load i32, i32* %5, align 4
	store i32 %6, i32* %4, align 4
	%7 = alloca i32, align 4
	%8 = alloca i32, align 4
	store i32 2, i32* %8, align 4
	%9 = load i32, i32* %8, align 4
	store i32 %9, i32* %7, align 4
	%10 = alloca i32, align 4
	%11 = load i32, i32* %1, align 4
	store i32 %11, i32* %10, align 4
	%12 = load i32, i32* %10, align 4
	%13 = alloca i32, align 4
	%14 = load i32, i32* %4, align 4
	store i32 %14, i32* %13, align 4
	%15 = load i32, i32* %13, align 4
	%16 = icmp sge i32 %12, %15
	%17 = zext i1 %16 to i8
	%18 = alloca i8, align 1
	store i8 %17, i8* %18, align 1
	%19 = load i8, i8* %18, align 1
	%20 = trunc i8 %19 to i1
	br i1 %20, label %markNoJSiftrue0, label %markNoJSiffalse0

markNoJSiftrue0:
	%21 = alloca i32, align 4
	%22 = load i32, i32* %1, align 4
	store i32 %22, i32* %21, align 4
	%23 = load i32, i32* %21, align 4
	%24 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.d, i32 0, i32 0), i32 %23)
	%25 = alloca [2 x i8], align 1
	%26 = bitcast [2 x i8]* %25 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %26, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.gVar.1, i32 0, i32 0), i64 2, i32 1, i1 false)
	%27 = getelementptr inbounds [2 x i8], [2 x i8]* %25, i32 0, i32 0
	%28 = alloca i8*, align 1
	store i8* %27, i8** %28, align 1
	%29 = load i8*, i8** %28, align 1
	%30 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %29)
	%31 = alloca i32, align 4
	%32 = load i32, i32* %4, align 4
	store i32 %32, i32* %31, align 4
	%33 = load i32, i32* %31, align 4
	%34 = alloca i32, align 4
	%35 = load i32, i32* %7, align 4
	store i32 %35, i32* %34, align 4
	%36 = load i32, i32* %34, align 4
	%37 = icmp slt i32 %33, %36
	%38 = zext i1 %37 to i8
	%39 = alloca i8, align 1
	store i8 %38, i8* %39, align 1
	%40 = load i8, i8* %39, align 1
	%41 = trunc i8 %40 to i1
	br i1 %41, label %markNoJSiftrue1, label %markNoJSiffalse1

markNoJSiftrue1:
	%42 = alloca i32, align 4
	%43 = load i32, i32* %7, align 4
	store i32 %43, i32* %42, align 4
	%44 = load i32, i32* %42, align 4
	%45 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.d, i32 0, i32 0), i32 %44)
	%46 = alloca [2 x i8], align 1
	%47 = bitcast [2 x i8]* %46 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %47, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.gVar.2, i32 0, i32 0), i64 2, i32 1, i1 false)
	%48 = getelementptr inbounds [2 x i8], [2 x i8]* %46, i32 0, i32 0
	%49 = alloca i8*, align 1
	store i8* %48, i8** %49, align 1
	%50 = load i8*, i8** %49, align 1
	%51 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %50)
	br label %markNoJSendIf1

markNoJSiffalse1:
	%52 = alloca i32, align 4
	%53 = load i32, i32* %4, align 4
	store i32 %53, i32* %52, align 4
	%54 = load i32, i32* %52, align 4
	%55 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.d, i32 0, i32 0), i32 %54)
	%56 = alloca [2 x i8], align 1
	%57 = bitcast [2 x i8]* %56 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %57, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.gVar.3, i32 0, i32 0), i64 2, i32 1, i1 false)
	%58 = getelementptr inbounds [2 x i8], [2 x i8]* %56, i32 0, i32 0
	%59 = alloca i8*, align 1
	store i8* %58, i8** %59, align 1
	%60 = load i8*, i8** %59, align 1
	%61 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %60)
	br label %markNoJSendIf1

markNoJSendIf1:
	br label %markNoJSendIf0

markNoJSiffalse0:
	%62 = alloca i32, align 4
	%63 = load i32, i32* %4, align 4
	store i32 %63, i32* %62, align 4
	%64 = load i32, i32* %62, align 4
	%65 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.d, i32 0, i32 0), i32 %64)
	%66 = alloca [2 x i8], align 1
	%67 = bitcast [2 x i8]* %66 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %67, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.gVar.4, i32 0, i32 0), i64 2, i32 1, i1 false)
	%68 = getelementptr inbounds [2 x i8], [2 x i8]* %66, i32 0, i32 0
	%69 = alloca i8*, align 1
	store i8* %68, i8** %69, align 1
	%70 = load i8*, i8** %69, align 1
	%71 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %70)
	%72 = alloca i32, align 4
	%73 = load i32, i32* %4, align 4
	store i32 %73, i32* %72, align 4
	%74 = load i32, i32* %72, align 4
	%75 = alloca i32, align 4
	%76 = load i32, i32* %7, align 4
	store i32 %76, i32* %75, align 4
	%77 = load i32, i32* %75, align 4
	%78 = icmp sgt i32 %74, %77
	%79 = zext i1 %78 to i8
	%80 = alloca i8, align 1
	store i8 %79, i8* %80, align 1
	%81 = load i8, i8* %80, align 1
	%82 = trunc i8 %81 to i1
	br i1 %82, label %markNoJSiftrue2, label %markNoJSiffalse2

markNoJSiftrue2:
	%83 = alloca i32, align 4
	%84 = load i32, i32* %7, align 4
	store i32 %84, i32* %83, align 4
	%85 = load i32, i32* %83, align 4
	%86 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.d, i32 0, i32 0), i32 %85)
	%87 = alloca [2 x i8], align 1
	%88 = bitcast [2 x i8]* %87 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %88, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.gVar.5, i32 0, i32 0), i64 2, i32 1, i1 false)
	%89 = getelementptr inbounds [2 x i8], [2 x i8]* %87, i32 0, i32 0
	%90 = alloca i8*, align 1
	store i8* %89, i8** %90, align 1
	%91 = load i8*, i8** %90, align 1
	%92 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %91)
	br label %markNoJSendIf2

markNoJSiffalse2:
	%93 = alloca i32, align 4
	%94 = load i32, i32* %4, align 4
	store i32 %94, i32* %93, align 4
	%95 = load i32, i32* %93, align 4
	%96 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.d, i32 0, i32 0), i32 %95)
	%97 = alloca [2 x i8], align 1
	%98 = bitcast [2 x i8]* %97 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %98, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.gVar.6, i32 0, i32 0), i64 2, i32 1, i1 false)
	%99 = getelementptr inbounds [2 x i8], [2 x i8]* %97, i32 0, i32 0
	%100 = alloca i8*, align 1
	store i8* %99, i8** %100, align 1
	%101 = load i8*, i8** %100, align 1
	%102 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %101)
	br label %markNoJSendIf2

markNoJSendIf2:
	br label %markNoJSendIf0

markNoJSendIf0:
	%103 = alloca i32, align 4
	store i32 0, i32* %103, align 4
	%104 = load i32, i32* %103, align 4
	ret i32 %104
}

declare i32 @printf(i8*, ...) #0
declare i32 @scanf(i8*, ...) #0
declare void @llvm.memcpy.p0i8.p0i8.i64(i8*, i8*, i64, i32, i1)
declare i8* @strcat(i8*, i8*)

attributes #0 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+sse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}

!0 = !{i32 1, !"wchar_size", i32 4}
