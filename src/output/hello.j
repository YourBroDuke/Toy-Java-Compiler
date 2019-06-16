.class public  test
.super java/lang/Object
.method public static  main([Ljava/lang/String;)V
        .limit stack 7
        .limit locals 4
        ldc 1
        istore 1
        ldc 0
        istore 2
        ldc 2
        istore 2
        iload 1
        iload 2
        invokestatic test/AddTwoInt(II)I
        istore 3
        getstatic java/lang/System/out Ljava/io/PrintStream;
        iload 3
        invokevirtual java/io/PrintStream/println(I)V
        return
.end method
.method private static  AddTwoInt(II)I
        .limit stack 3
        .limit locals 3
        iload 0
        iload 1
        iadd
        istore 2
        iload 2
        ireturn
.end method