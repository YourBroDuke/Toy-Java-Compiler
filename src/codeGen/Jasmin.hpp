#ifndef JASMIN_H
#define JASMIN_H

#include <string>
#include <vector>
using namespace std;

/*
<jasmin_header> {
    [.bytecode <x.y>]
    [.source <sourcefile>]
    <class_spec>
    <super_spec>
    <implements>
    [.signature "<signature>"]
    [.enclosing method <method_name>]
    [.debug "<debug_source_extension>"]*
    [.inner class [<access>] [<name>] [inner <classname>] [outer <name>]]*
    [.inner interface [<access>] [<name>] [inner <classname>] [outer <name>]]*
}
 */
class JasminHeader{
    private:
        // optional
        string *bytecodeVersion;
        // optinal 
        string *sourceFile;
        string *classSpec;
        string *superSpec;
        string *implements;
        // optinal 
        string *signature;
        //optional
        string *enclosing;
        // todo:innner class or interface
    public:
        JasminHeader();
        ~JasminHeader();
};

/*
<field> {
    .field <access_spec> <field_name> <descriptor> [signature <signature>]
           [ = <value> ]
    |
    .field <access_spec> <field_name> <descriptor> [signature <signature>]
           [ = <value> ]
        [<field_attribute>]*
    .end field
   (...)
}
 */
class JField{
    
};

/*
<method> {
    .method <access_spec> <method_name> <descriptor>
        <statement>*
    .end method
}
 */
class JMethod{
    private:
        string *accessSpec;
        string *methodName;
        string *descriptor;
        vector<JStmt> *JStmts;
    public:
        JMethod();
        ~JMethod();
};

/*
<statement> {
   .limit stack <integer>
   | .limit locals <integer>
   | .line <integer>
   | .var <var_number> is <var_name> <descriptor> [signature <sign>] from <label1> to <label2>
   | .var <var_number> is <var_name> <descriptor> [signature <sign>] from <offset1> to <offset2>
   | .throws <classname>
   | .catch <classname> from <label1> to <label2> using <label3>
   | .catch <classname> from <offset1> to <offset2> using <offset3>
   | .signature "<signature>"
   | .stack
         [offset {<pc> | <label>}]
         [locals <verification_type> [<verification_arg>]]
         (...)
         [stack  <verification_type> [<verification_arg>]]
         (...)
     .end stack
   | .stack use [n] locals
         (...)
     .end stack
   | <instruction> [<instruction_args>]
   | <Label>:
   | .deprecated
   | <generic> ; see below for the use of generic attributes
}
*/

class JStmt{
    public:
        virtual string toString();
};

class JInstructionStmt : public JStmt{
    private:
        // optional
        string *pc;
        string *opcode;
        // optional
        vector<string> *args;
    public:
        string toString();
};

class JClassSpec{
    private:
        string *accessSpec;
        string *className;
    public:
        JClassSpec();
        ~JClassSpec();
};

class JasminFile{
    private:
        JasminHeader *jasminHeader;
        // optional 
        vector<JField> *JFields;
        vector<JMethod> *JMethods;
    
    public:
        JasminFile();
        ~JasminFile();
};

#endif