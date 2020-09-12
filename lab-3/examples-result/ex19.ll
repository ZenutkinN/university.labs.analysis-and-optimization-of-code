@.str.d = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.s = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.f = private unnamed_addr constant [3 x i8] c"%f\00", align 1

@.gVar.1 = private unnamed_addr constant [5 x i8] c"test\00", align 1

define void @NoJSInitglobalVars() {
	ret void
}
define i32 @main() {
	call void @NoJSInitglobalVars()
	%1 = alloca i8*, align 1
	%2 = alloca [5 x i8], align 1
	%3 = bitcast [5 x i8]* %2 to i8*
	call void @llvm.memcpy.p0i8.p0i8.i64(i8* %3, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.gVar.1, i32 0, i32 0), i64 5, i32 1, i1 false)
	%4 = getelementptr inbounds [5 x i8], [5 x i8]* %2, i32 0, i32 0
	%5 = alloca i8*, align 1
	store i8* %4, i8** %5, align 1
	%6 = load i8*, i8** %5, align 1
	store i8* %6, i8** %1, align 1
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
