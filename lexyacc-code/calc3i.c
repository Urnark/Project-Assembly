#include <stdio.h>
#include "calc3.h"
#include "artefacts/y.tab.h"

static int lbl;

void compare(const char* ope)
{
    printf("\tpopq\t%s\n", "%r11"); // b
    printf("\tpopq\t%s\n", "%r12"); // a
    printf("\tcmpq\t%s,\t%s\n", "%r11", "%r12"); // compare b and a 
    // Migth be able to change %r13 to %r11 or %r12
    printf("\txor\t%s,\t%s\n", "%r13", "%r13"); // set %r13 to zero
    printf("\tset%s\t%s\n", ope, "%r13b"); // set %r13 to 1 if a < b else 0
    printf("\tpushq\t%s\n", "%r13"); // push %r13 to the stack
}

int ex(nodeType *p) {
    int lbl1, lbl2;

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
            printf("\tcmpq\t%s,\t%s\n", "$1", "%r11"); // I think this should be here
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
                printf("\tcmpq\t%s,\t%s\n", "$1", "%r11"); // I think this should be here
                printf("\tje\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("\tjmp\tL%03d\n", lbl2 = lbl++);
                printf("L%03d:\n", lbl1);
                ex(p->opr.op[2]);
                printf("L%03d:\n", lbl2);
            } else {
                /* if */
                printf("\tpopq\t%s\n", "%r11"); // I think this should be here
                printf("\tcmpq\t%s,\t%s\n", "$1", "%r11"); // I think this should be here
                printf("\tje\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("L%03d:\n", lbl1);
            }
            break;
        case PRINT:     
            ex(p->opr.op[0]);
            printf("\tmovq\t%s,\t%s\n", "$format", "%rdi"); // set pointer to format string as first parameter to printf
            printf("\tpopq\t%s\n", "%rsi"); // set the value on the top of the stack as the second parameter
            printf("\txor\t%s,\t%s\n", "%rax", "%rax"); // zero out rax (important for printf)
            printf("\tcall\tprintf\n"); // call the printf function
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
            printf("\tcmpq\t%s,\t%s;\tje out\n", "%r11", "$0");
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
            printf("\tlntwo\n");
            break;
        default:
            ex(p->opr.op[0]);
            ex(p->opr.op[1]);
            switch(p->opr.oper) {
                case GCD:
                    printf("\tpopq\t%s\n", "%r11"); // b
                    printf("\tpopq\t%s\n", "%r12"); // a
                    printf("loop:\tcmpq\t%s,\t%s\n", "%r11", "$0");
                    printf("\tje then\n"); 
                    printf("\tcmpq\t%s,\t%s\n", "%r12", "$0");
                    printf("\tje end\n"); 
                    printf("\tcmpq\t%s,\t%s;\tjle low\n", "%r11", "%r12"); // compare b and a 
                    //a > b
                    printf("\tsubq\t%s,\t%s\n", "%r11", "%r12");
                    printf("\tjmp loop\n");
                    //a < b
                    printf("low:\tsubq\t%s,\t%s\n", "%r12", "%r11");
                    printf("\tjmp loop\n");
                    printf("then:\tpushq\t%s\n", "%r12"); //if b = 0, print a
                    printf("end:\tpushq\t%s\n", "%r11"); //if a = 0, print b
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
                    printf("\tpopq\t%s\n", "%rax");
                    printf("\tpopq\t%s\n", "%rdx");
                    printf("\tcqto\n");
                    printf("\tidivl\t%s\n", "%rdx");
                    printf("\tpushq\t%s\n", "%rax"); //pushs quotient first
                    printf("\tpushq\t%s\n", "%rdx"); //afterwards remainder
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
