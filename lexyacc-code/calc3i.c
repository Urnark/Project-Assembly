#include <stdio.h>
#include "calc3.h"
#include "artefacts/y.tab.h"

static int lbl;

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
            printf("\tjz\tL%03d\n", lbl2 = lbl++);
            ex(p->opr.op[1]);
            printf("\tjmp\tL%03d\n", lbl1);
            printf("L%03d:\n", lbl2);
            break;
        case IF:
            ex(p->opr.op[0]);
            if (p->opr.nops > 2) {
                /* if else */
                printf("\tjz\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("\tjmp\tL%03d\n", lbl2 = lbl++);
                printf("L%03d:\n", lbl1);
                ex(p->opr.op[2]);
                printf("L%03d:\n", lbl2);
            } else {
                /* if */
                printf("\tjz\tL%03d\n", lbl1 = lbl++);
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
            printf("\tneg\n");
            break;
        case FACT:
            ex(p->opr.op[0]);
            printf("\tfact\n");
            break;
        case LNTWO:
            ex(p->opr.op[0]);
            printf("\tlntwo\n");
            break;
        default:
            ex(p->opr.op[0]);
            ex(p->opr.op[1]);
            switch(p->opr.oper) {
                case GCD:   printf("\tgcd\n"); break;
                case '+':
                    printf("\tpopq\t%s\n", "%r11");
                    printf("\tpopq\t%s\n", "%r12");
                    printf("\taddq\t%s,\t%s\n", "%r11", "%r12");
                    printf("\tpushq\t%s\n", "%r12");
                    break;
                case '-':   printf("\tsub\n"); break; 
                case '*':
                    printf("\tpopq\t%s\n", "%r11");
                    printf("\tpopq\t%s\n", "%r12");
                    printf("\timul\t%s,\t%s\n", "%r11", "%r12");
                    printf("\tpushq\t%s\n", "%r12");
                    break;
                case '/':   printf("\tdiv\n"); break;
                case '<': // a < b
                    printf("\tpopq\t%s\n", "%r11"); // b
                    printf("\tpopq\t%s\n", "%r12"); // a
                    printf("\tcmpq\t%s,\t%s\n", "%r11", "%12"); // compare b and a
                    // Migth be able to change %r13 to %r11 or %r12
                    printf("\txor\t%s,\t%s\n", "%r13", "r13"); // set %r13 to zero
                    printf("\tsetl\t%s\n", "%13"); // set %r13 to 1 if a < b else 0
                    printf("\tpushq\t%s\n", "%r13"); // push %r13 to the stack
                    break;
                case '>':   printf("\tcompGT\n"); break;
                case GE: // a >= b
                    printf("\tpopq\t%s\n", "%r11"); // b
                    printf("\tpopq\t%s\n", "%r12"); // a
                    printf("\tcmpq\t%s,\t%s\n", "%r11", "%12"); // compare b and a
                    printf("\txor\t%s,\t%s\n", "%r13", "r13"); // set %r13 to zero
                    printf("\tsetge\t%s\n", "%13"); // set %r13 to 1 if a >= b else 0
                    printf("\tpushq\t%s\n", "%r13"); // push %r13 to the stack
                    break;
                case LE:    printf("\tcompLE\n"); break;
                case NE: // a != b
                    printf("\tpopq\t%s\n", "%r11"); // b
                    printf("\tpopq\t%s\n", "%r12"); // a
                    printf("\tcmpq\t%s,\t%s\n", "%r11", "%12"); // compare b and a
                    printf("\txor\t%s,\t%s\n", "%r13", "r13"); // set %r13 to zero
                    printf("\tsetne\t%s\n", "%13"); // set %r13 to 1 if a != b else 0
                    printf("\tpushq\t%s\n", "%r13"); // push %r13 to the stack
                    break;
                case EQ:    printf("\tcompEQ\n"); break;
            }
        }
    }
    return 0;
}
