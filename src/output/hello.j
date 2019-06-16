.class public  Test
.super java/lang/Object
.method public static  main([Ljava/lang/String;)V
        .limit stack 17
        .limit locals 5
        ldc 0.0
        fstore 1
        ldc 1
        istore 2
        ldc 3.000000
        fstore 3
        ldc 0
        istore 4
        L0:
        iload 4
        iload 2
        isub
        ifgt L1
        getstatic java/lang/System/out Ljava/io/PrintStream;
        ldc "Hello World!"
        invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
        iload 4
        ldc 1
        iadd
        istore 4
        L1:
        iload 2
        ldc 0
        isub
        ifeq L2
        fload 3
        fload 1
        fadd
        fstore 1
        goto L3
        L2:
        fload 3
        fstore 1
        L3:
        return
.end method