@.str.d = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.s = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.f = private unnamed_addr constant [3 x i8] c"%f\00", align 1


define void @NoJSInitglobalVars() {
	ret void
}
define i32 @main() {
	call void @NoJSInitglobalVars()
	%1 = alloca i32, align 4
	%2 = alloca i32, align 4
	store i32 1, i32* %2, align 4
	%3 = load i32, i32* %2, align 4
	store i32 %3, i32* %1, align 4
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
	%12 = load i8, i8* %11, align 1
	%13 = trunc i8 %12 to i1
	br i1 %13, label %markNoJSiftrue0, label %markNoJSendIf0

markNoJSiftrue0:
	%14 = alloca i32, align 4
	%15 = alloca i32, align 4
	store i32 2, i32* %15, align 4
	%16 = load i32, i32* %15, align 4
	store i32 %16, i32* %14, align 4
	br label %markNoJSendIf0

markNoJSendIf0:
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
