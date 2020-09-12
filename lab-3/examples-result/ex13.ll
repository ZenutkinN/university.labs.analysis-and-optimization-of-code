@.str.d = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.s = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.f = private unnamed_addr constant [3 x i8] c"%f\00", align 1

@.gVar.1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

define void @NoJSInitglobalVars() {
	ret void
}
define i32 @fact(i32) {
	%2 = alloca i32, align 4
	store i32 %0, i32* %2, align 4
	%3 = alloca i32, align 4
	%4 = load i32, i32* %2, align 4
	store i32 %4, i32* %3, align 4
	%5 = load i32, i32* %3, align 4
	%6 = alloca i32, align 4
	store i32 0, i32* %6, align 4
	%7 = load i32, i32* %6, align 4
	%8 = icmp eq i32 %5, %7
	%9 = zext i1 %8 to i8
	%10 = alloca i8, align 1
	store i8 %9, i8* %10, align 1
	%11 = alloca i32, align 4
	%12 = load i32, i32* %2, align 4
	store i32 %12, i32* %11, align 4
	%13 = load i32, i32* %11, align 4
	%14 = alloca i32, align 4
	store i32 1, i32* %14, align 4
	%15 = load i32, i32* %14, align 4
	%16 = icmp eq i32 %13, %15
	%17 = zext i1 %16 to i8
	%18 = alloca i8, align 1
	store i8 %17, i8* %18, align 1
	%19 = load i8, i8* %10, align 1
	%20 = trunc i8 %19 to i1
	%21 = load i8, i8* %18, align 1
	%22 = trunc i8 %21 to i1
	%23 = alloca i8, align 1
	br label %boolargNoJS0
boolargNoJS0:
	br i1 %20, label %boolargNoJS2, label %boolargNoJS1
boolargNoJS1:
	br i1 %22, label %boolargNoJS2, label %boolargNoJS3
boolargNoJS2:
	store i8 1, i8* %23, align 1
	br label %boolargNoJS4
boolargNoJS3:
	store i8 0, i8* %23, align 1
	br label %boolargNoJS4
boolargNoJS4:
	%24 = load i8, i8* %23, align 1
	%25 = trunc i8 %24 to i1
	br i1 %25, label %markNoJSiftrue0, label %markNoJSiffalse0

markNoJSiftrue0:
	%26 = alloca i32, align 4
	store i32 1, i32* %26, align 4
	%27 = load i32, i32* %26, align 4
	ret i32 %27

markNoJSiffalse0:
	%28 = alloca i32, align 4
	%29 = load i32, i32* %2, align 4
	store i32 %29, i32* %28, align 4
	%30 = load i32, i32* %28, align 4
	%31 = alloca i32, align 4
	store i32 1, i32* %31, align 4
	%32 = load i32, i32* %31, align 4
	%33 = icmp sgt i32 %30, %32
	%34 = zext i1 %33 to i8
	%35 = alloca i8, align 1
	store i8 %34, i8* %35, align 1
	%36 = load i8, i8* %35, align 1
	%37 = trunc i8 %36 to i1
	br i1 %37, label %markNoJSiftrue1, label %markNoJSiffalse1

markNoJSiftrue1:
	%38 = alloca i32, align 4
	%39 = load i32, i32* %2, align 4
	store i32 %39, i32* %38, align 4
	%40 = alloca i32, align 4
	%41 = load i32, i32* %2, align 4
	store i32 %41, i32* %40, align 4
	%42 = alloca i32, align 4
	store i32 1, i32* %42, align 4
	%43 = load i32, i32* %40, align 4
	%44 = load i32, i32* %42, align 4
	%45 = alloca i32, align 4
	%46 = sub i32 %43, %44
	store i32 %46, i32* %45, align 4
	%47 = load i32, i32* %45, align 4
	%48 = call i32 @fact(i32 %47)
	%49 = alloca i32, align 4
	store i32 %48, i32* %49, align 4
	%50 = load i32, i32* %38, align 4
	%51 = load i32, i32* %49, align 4
	%52 = alloca i32, align 4
	%53 = mul i32 %50, %51
	store i32 %53, i32* %52, align 4
	%54 = load i32, i32* %52, align 4
	ret i32 %54

markNoJSiffalse1:
	%55 = alloca i32, align 4
	store i32 -1, i32* %55, align 4
	%56 = load i32, i32* %55, align 4
	ret i32 %56

markNoJSendIf1:
	br label %markNoJSendIf0

markNoJSendIf0:
	%57 = alloca i32, align 4
	store i32 0, i32* %57, align 4
	%58 = load i32, i32* %57, align 4
	ret i32 %58
}
define i32 @main() {
	call void @NoJSInitglobalVars()
	%1 = alloca i32, align 4
	store i32 6, i32* %1, align 4
	%2 = load i32, i32* %1, align 4
	%3 = call i32 @fact(i32 %2)
	%4 = alloca i32, align 4
	store i32 %3, i32* %4, align 4
	%5 = load i32, i32* %4, align 4
	%6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.d, i32 0, i32 0), i32 %5)
	%7 = alloca [2 x i8], align 1
	%8 = bitcast [2 x i8]* %7 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %8, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.gVar.1, i32 0, i32 0), i64 2, i32 1, i1 false)
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
