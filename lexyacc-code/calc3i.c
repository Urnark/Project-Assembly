#include <stdio.h>
#include "calc3.h"
#include "artefacts/y.tab.h"

static int lbl;

void test_print(char* str)
{
    printf("\tmovq\t%s,\t%s\n", "$format", "%rdi"); // set pointer to format string as first parameter to printf
    printf("\txor\t%s,\t%s\n", "%rsi", "%rsi"); // zero out rsi (important for printf)
    printf("\tmovq\t%s,\t%s\n", str, "%rsi"); // set the value on the top of the stack as the second parameter
    printf("\txor\t%s,\t%s\n", "%rax", "%rax"); // zero out rax (important for printf)
    printf("\tcall\tprintf\n"); // call the printf function
}

void compare(const char* ope)
{
    printf("\tpopq\t%s\n", "%r11"); // b
    printf("\tpopq\t%s\n", "%r12"); // a
    printf("\txor\t%s,\t%s\n", "%r13", "%r13"); // set %r13 to zero
    printf("\tcmpq\t%s,\t%s\n", "%r11", "%r12"); // compare b and a 
    // Migth be able to change %r13 to %r11 or %r12
    printf("\tset%s\t%s\n", ope, "%r13b"); // set %r13 to 1 if a < b else 0
    printf("\tpushq\t%s\n", "%r13"); // push %r13 to the stack
}

int ex(nodeType *p) {
    int lbl1, lbl2;
    int lbl3, lbl4;

    if (!p) return 0;
    switch(p->type) {
    case typeCon:       
        printf("\tpushq\t$%d\n", p->con.value);
        break;
    case typeId:        
        printf("\tpushq\t%c\n", p->id.i + 'a');
        break;
    case typeOpr:
        switch(p->opr.oper) {
        case WHILE:
            printf("L%03d:\n", lbl1 = lbl++);
            ex(p->opr.op[0]);
            printf("\tpopq\t%s\n", "%r11"); // I think this should be here
            printf("\tcmpb\t%s,\t%s\n", "$0", "%r11b"); // I think this should be here
            printf("\tje\tL%03d\n", lbl2 = lbl++);
            ex(p->opr.op[1]);
            printf("\tjmp\tL%03d\n", lbl1);
            printf("L%03d:\n", lbl2);
            break;
        case IF:
            ex(p->opr.op[0]);
            if (p->opr.nops > 2) {
                /* if else */
                printf("\tpopq\t%s\n", "%r11"); // I think this should be here
                printf("\tcmpb\t%s,\t%s\n", "$0", "%r11b"); // I think this should be here
                printf("\tje\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("\tjmp\tL%03d\n", lbl2 = lbl++);
                printf("L%03d:\n", lbl1);
                ex(p->opr.op[2]);
                printf("L%03d:\n", lbl2);
            } else {
                /* if */
                printf("\tpopq\t%s\n", "%r11"); // I think this should be here
                printf("\tcmpb\t%s,\t%s\n", "$0", "%r11b"); // I think this should be here
                printf("\tje\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("L%03d:\n", lbl1);
            }
            break;
        case PRINT:     
            ex(p->opr.op[0]);
            /*printf("\tmovq\t%s,\t%s\n", "$format", "%rdi"); // set pointer to format string as first parameter to printf
            printf("\txor\t%s,\t%s\n", "%rsi", "%rsi"); // zero out rsi (important for printf)
            printf("\tpopq\t%s\n", "%rsi"); // set the value on the top of the stack as the second parameter
            printf("\txor\t%s,\t%s\n", "%rax", "%rax"); // zero out rax (important for printf)
            printf("\tcall\tprintf\n"); // call the printf function*/

            printf("\tpopq\t%s\n", "%r11");
            printf("\txor\t%s,\t%s\n", "$0", "%r14"); // zero out rax
            printf("jmp\tloop\n");

            printf("loop:\n");
                printf("\txor\t%s,\t%s\n", "%rax", "%rax"); // zero out rax
                printf("\tmovq\t%s,\t%s\n", "%r11", "%rax"); // 4
                printf("\tmovq\t%s,\t%s\n", "$10", "%r12"); // 4
                printf("\tcqto\n");
                printf("\tidivq\t%s\n", "%r12");
                printf("\tmovq\t%s,\t%s\n", "%rax", "%r11");
                printf("\taddq\t%s,\t%s\n", "$48", "%rdx");
                printf("\tpushq\t%s\n", "%rdx");
                printf("\tincq\t%s\n", "%r14"); // i++

                printf("\tcmpq\t%s,\t%s\n", "$0", "%r11");
                printf("\tje out\n");
                printf("\tjmp\tloop\n");
            
            printf("out:\n");
                printf("\tdecq\t%s\n", "%r14"); // i--

                printf("\tmovq\t%s,\t%s\n", "$1", "%rax"); // sys_write
                printf("\tmovq\t%s,\t%s\n", "$1", "%rdi"); // stdout
                printf("\tpopq\t%s\n", "%r15"); // newline
                printf("\tmovq\t%s,\t%s\n", "%r15", "(%rsi)"); // character
                printf("\tmovq\t%s,\t%s\n", "$1", "%rdx"); // size
                printf("\tsyscall\n");

                printf("\tcmpq\t%s,\t%s\n", "$0", "%r14");
                printf("\tjne out\n");

                // sys write
                printf("\tmovq\t%s,\t%s\n", "$1", "%rax"); // sys_write
                printf("\tmovq\t%s,\t%s\n", "$1", "%rdi"); // stdout
                printf("\tmovq\t%s,\t%s\n", "$10", "%r15"); // newline
                printf("\tmovq\t%s,\t%s\n", "%r15", "(%rsi)"); // newline
                printf("\tmovq\t%s,\t%s\n", "$1", "%rdx"); // size
                printf("\tsyscall\n");
            break;
        case '=':       
            ex(p->opr.op[1]);
            printf("\tpopq\t%c\n", p->opr.op[0]->id.i + 'a');
            break;
        case UMINUS:    
            ex(p->opr.op[0]);
            printf("\tpopq\t%s\n", "%r11"); 
            printf("\tnegq\t%s\n", "%r11");
            printf("\tpushq\t%s\n", "%r11");
            break;
        case FACT:
            ex(p->opr.op[0]);
            printf("\tpopq\t%s\n", "%r11"); // n!
            printf("\tmovq\t%s,\t%s\n", "$1", "%r12"); // x
            printf("\tcmpq\t%s,\t%s;\tje out\n", "$0", "%r11");
            printf("\tmovq\t%s,\t%s\n", "$1", "%r13");  // i for loop
            printf("loop:\tcmpq\t%s,\t%s;\tjg then\n", "%r11", "%r13"); // compare i <= n
            printf("\timul\t%s,\t%s\n", "%r13", "%r12"); // x = x * i
            printf("\tincq\t%s\n", "%r13"); // i++
            printf("\tjmp loop\n");
            printf("then:\tpushq\t%s\n", "%r12"); // push x
            printf("out:\tpushq\t%s\n", "%r12"); // push r12, because: 0! = 1
            break;
        case LNTWO:
            ex(p->opr.op[0]);
            //printf("\tlntwo\n");
            printf("\tpopq\t%s\n", "%r11"); // 32
            printf("\txor\t%s,\t%s\n", "%r12", "%r12"); // zero out r12
            printf("\tmovq\t%s,\t%s\n", "$1", "%r12"); // 1
            printf("\txor\t%s,\t%s\n", "%r13", "%r13"); // zero out r13
            printf("\tmovq\t%s,\t%s\n", "$0", "%r13"); // 1
            printf("jmp\tloop\n");

            printf("loop:\n");
                printf("\tcmpq\t%s,\t%s\n", "%r12", "%r11");
                printf("\tjle out\n");
                //a > b
                printf("\timulq\t%s,\t%s\n", "$2", "%r12");
                printf("\tincq\t%s\n", "%r13"); // i++
                printf("\tjmp\tloop\n");
                //a <= b
            printf("out:\n");
                printf("\tpushq\t%s\n", "%r13");
            break;
        default:
            ex(p->opr.op[0]);
            ex(p->opr.op[1]);
            switch(p->opr.oper) {
                case GCD:
                    printf("\n\tpopq\t%s\n", "%r10"); // 12
                    printf("\tpopq\t%s\n", "%r12"); // 6
                    printf("jmp\tloop\n");

                    printf("loop:\n");
                        printf("\tcmpq\t%s,\t%s\n", "$0", "%r10");
                        printf("\tje then\n"); 
                        printf("\tcmpq\t%s,\t%s\n", "$0", "%r12");
                        printf("\tje end\n"); 
                        printf("\tcmpq\t%s,\t%s\n", "%r10", "%r12"); // compare b and a 
                        printf("\tjle\tlow\n");
                        //a > b
                        printf("\tsubq\t%s,\t%s\n", "%r10", "%r12");
                        printf("\tjmp\tloop\n");
                        //a <= b
                        printf("low:\n");
                            printf("\tsubq\t%s,\t%s\n", "%r12", "%r10");
                            printf("\tjmp\tloop\n");

                    printf("then:\n");
                        printf("\tpushq\t%s\n", "%r12"); //if b = 0, print a
                        printf("\tjmp\tout\n");

                    printf("end:\n");
                        printf("\tpushq\t%s\n\n", "%r10"); //if a = 0, print b
                        printf("\tjmp\tout\n");
                    
                    printf("out:\n");
                    break;
                case '+':
                    printf("\tpopq\t%s\n", "%r11");
                    printf("\tpopq\t%s\n", "%r12");
                    printf("\taddq\t%s,\t%s\n", "%r11", "%r12");
                    printf("\tpushq\t%s\n", "%r12");
                    break;
                case '-': // a-b
                    printf("\tpopq\t%s\n", "%r11"); //b
                    printf("\tpopq\t%s\n", "%r12"); //a
                    printf("\tsubq\t%s,\t%s\n", "%r11", "%r12");
                    printf("\tpushq\t%s\n", "%r12");
                    break;
                case '*':
                    printf("\tpopq\t%s\n", "%r11");
                    printf("\tpopq\t%s\n", "%r12");
                    printf("\timul\t%s,\t%s\n", "%r11", "%r12");
                    printf("\tpushq\t%s\n", "%r12");
                    break;
                case '/': // a/b
                    printf("\tpopq\t%s\n", "%r12"); // 2
                    printf("\tpopq\t%s\n", "%rax"); // 4
                    printf("\tcqto\n");
                    printf("\tidivq\t%s\n", "%r12");
                    printf("\tpushq\t%s\n", "%rax"); //pushs quotient first
                    //printf("\tpushq\t%s\n", "%rdx"); //afterwards remainder
                    break;
                case '<': // a < b 
                    compare("l");
                    break;
                case '>': // a > b 
                    compare("g");
                    break;
                case GE: // a >= b
                    compare("ge");
                    break;
                case LE:
                    compare("le");
                    break;
                case NE: // a != b
                    compare("ne");
                    break;
                case EQ:
                    compare("e");
                    /*printf("\tpopq\t%s\n", "%r11"); // b
                    printf("\tpopq\t%s\n", "%r12"); // a
                    printf("\txor\t%s,\t%s\n", "%r13", "r13"); // set %r13 to zero
                    printf("\tcmpq\t%s,\t%s\n", "%r11", "%12"); // compare b and a
                    printf("\tje then\n"); // jump condition
                    printf("\tmovq\t%s,\t%s\n", "$1", "%r13");
                    printf("\tjmp out\n"); 
                    printf("then:\tmovq\t%s,\t%s\n", "$0", "%r13");
                    printf("\tjmp out\n"); 
                    printf("\tout:pushq\t%s\n", "%r13");*/
                    break;
            }
        }
    }
    return 0;
}
