.class public  Test
.super java/lang/Object
.method public static  main([Ljava/lang/String;)V
        .limit stack 23
        .limit locals 6
        ldc 0.0
        fstore 1
        ldc 5
        istore 2
        ldc 1
        istore 3
        ldc 3.000000
        fstore 4
        ldc 0
        istore 5
        L0:
        iload 5
        iload 2
        isub
        ifge L1
        getstatic java/lang/System/out Ljava/io/PrintStream;
        iload 3
        invokevirtual java/io/PrintStream/println(I)V
        iload 3
        ldc 2
        iadd
        istore 3
        iload 5
        ldc 1
        iadd
        istore 5
        goto L0
        L1:
        getstatic java/lang/System/out Ljava/io/PrintStream;
        ldc "Hello World!"
        invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
        iload 2
        ldc 0
        isub
        ifeq L2
        fload 4
        fload 1
        fadd
        fstore 1
        goto L3
        L2:
        fload 4
        fstore 1
        L3:
        return
.end method