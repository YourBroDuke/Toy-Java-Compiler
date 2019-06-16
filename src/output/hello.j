.class public  Test
.super java/lang/Object
.field private  testNum I
.method public static  main([Ljava/lang/String;)I
        .limit stack 16
        .limit locals 5
        ldc 0
        istore 1
        ldc 3
        dstore 2
        dload 2
        istore 1
        ldc 1
        iadd
        ldc 0
        istore 4
        L0:     iload 4
        dload 2
        isub
        iflt L1
        getstatic java/lang/System/out Ljava/io/PrintStream;
        ldc "Hello World!"
        invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
        L1:     iload 4
        ldc 0
        isub
        ifeq L2
        iload 1
        istore 0
        goto L3
        L2:     L3:     ldc 0
        ireturn
.end method