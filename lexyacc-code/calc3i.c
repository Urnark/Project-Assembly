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
                printf("\tpopq\t%s\n", "%r11"); // I think this should be here
                printf("\tcompq\t%s,\t%s\n", "%1", "%r11"); // I think this should be here
                printf("\tjz\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("\tjmp\tL%03d\n", lbl2 = lbl++);
                printf("L%03d:\n", lbl1);
                ex(p->opr.op[2]);
                printf("L%03d:\n", lbl2);
            } else {
                /* if */
                printf("\tpopq\t%s\n", "%r11"); // I think this should be here
                printf("\tcompq\t%s,\t%s\n", "%1", "%r11"); // I think this should be here
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
                case '-':
                    printf("\tpopq\t%s\n", "%r11");
                    printf("\tpopq\t%s\n", "%r12");
                    printf("\tsub\t%s,\t%s\n", "%r11", "%r12");
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
                    printf("\tpopq\t%s\n", "%r11"); // b
                    printf("\tpopq\t%s\n", "%r12"); // a
                    printf("\tcmpq\t%s,\t%s\n", "%r11", "%12"); // compare b and a 
                    // Migth be able to change %r13 to %r11 or %r12
                    printf("\txor\t%s,\t%s\n", "%r13", "r13"); // set %r13 to zero
                    printf("\tsetl\t%s\n", "%13"); // set %r13 to 1 if a < b else 0
                    printf("\tpushq\t%s\n", "%r13"); // push %r13 to the stack
                    break;
                case '>': // a > b 
                    printf("\tpopq\t%s\n", "%r12"); // b
                    printf("\tpopq\t%s\n", "%r8"); // a
                    //check a
                    printf("\tmovq\t%s,\t%s\n", "%r8", "%r9"); //copy a
                    printf("\tmovq\t%s,\t%s\n", "$-1", "%r10"); 
                    printf("\timul\t%s,\t%s\n", "%r8", "%r10"); // a * -1
                    printf("\tcmpq\t%s,\t%s\n", "%r9", "%10"); // a = -a
                    printf("\tje thone\n"); // jump condition
                    printf("\tmovq\t%s,\t%s\n", "$1", "%r11"); // a is positiv = 1
                    printf("\tjmp out\n"); // jump 
                    printf("thone:\tmovq\t%s,\t%s\n", "$-1", "%r11"); // a is negativ = -1
                    printf("\tjmp out\n"); // jump 
                    //check b
                    printf("out:\txor\t%s,\t%s\n", "%r10", "%r10");
                    printf("\tmovq\t%s,\t%s\n", "%r12", "%r13"); //copy b
                    printf("\tmovq\t%s,\t%s\n", "$-1", "%r10"); 
                    printf("\timul\t%s,\t%s\n", "%r12", "%r10"); // b * -1
                    printf("\tcmpq\t%s,\t%s\n", "%r13", "%10"); // b = -b
                    printf("\tje thtwo\n"); // jump condition
                    printf("\tcmpq\t%s,\t%s\n", "%r11", "$1"); // if a is positiv
                    printf("\tje ththree\n"); // jump condition
                    printf("\tjmp ploop\n"); // jump 
                    printf("ththree:\tjmp corr\n"); // jump out because b is negativ
                    printf("thtwo:\tcmpq\t%s,\t%s\n", "%r11", "$-1"); // if a is positiv
                    printf("\tje thfour\n"); // jump condition
                    printf("\tjmp nloop\n"); // jump 
                    printf("thfour:\tjmp wrong\n"); // jump out because a is negativ
                    //positive loop
                    printf("ploop:\txor\t%s,\t%s\n", "%r10", "%r10");
                    printf("\tcmpq\t%s,\t%s\n", "%r9", "%13"); //if a=b
                    printf("\tje thfive\n"); // jump condition
                    printf("\tjmp pcount\n"); // jump 
                    printf("pcount:\tcmpq\t%s,\t%s\n", "%r13", "%10"); //if b = i; i++
                    printf("\tje thsix\n"); // jump condition
                    printf("\tcmpq\t%s,\t%s\n", "%r9", "%10"); //if a = i
                    printf("\tje theight\n"); // jump condition
                    printf("\tincq\t%s\n", "%r10"); //i++
                    printf("\tjmp pcount\n"); // jump 
                    printf("theight:\tjmp wrong\n"); // jump out because a < b
                    printf("thsix:\tcmpq\t%s,\t%s\n", "%r9", "%10"); //if a = i
                    printf("\tje thseven\n"); // jump condition
                    printf("\tjmp corr\n"); // jump out because b < a 
                    printf("thseven:\tjmp wrong\n"); // jump out because a = i = b (not that this could happen, but...)
                    printf("thfive:\tjmp wrong\n"); // jump out because a = b
                    //negative loop
                    printf("ploop:\txor\t%s,\t%s\n", "%r10", "%r10");
                    printf("\tcmpq\t%s,\t%s\n", "%r9", "%13"); //if a=b
                    printf("\tje thnine\n"); // jump condition
                    printf("\tnegq\t%s\n", "%r9"); // sets -a to a
                    printf("\tnegq\t%s\n", "%r13"); // sets -b to b
                    printf("\tjmp ncount\n"); // jump 
                    printf("ncount:\tcmpq\t%s,\t%s\n", "%r9", "%10"); //if a = i; i++
                    printf("\tje thten\n"); // jump condition
                    printf("\tcmpq\t%s,\t%s\n", "%r13", "%10"); //if b = i
                    printf("\tje theleven\n"); // jump condition
                    printf("\tincq\t%s\n", "%r10"); //i++
                    printf("\tjmp ncount\n"); // jump 
                    printf("theleven:\tnegq\t%s\n", "%r9"); // sets a to -a
                    printf("\tnegq\t%s\n", "%r13"); // sets b to -b
                    printf("\tjmp corr\n"); // jump out because b < a
                    printf("thten:\tcmpq\t%s,\t%s\n", "%r13", "%10"); //if b = i
                    printf("\tje thtwelv\n"); // jump condition
                    printf("\tnegq\t%s\n", "%r9"); // sets a to -a
                    printf("\tnegq\t%s\n", "%r13"); // sets b to -b
                    printf("\tjmp wrong\n"); // jump out because a < b 
                    printf("thtwelv:\tjmp wrong\n"); // jump out because a = i = b (not that this could happen, but...)
                    printf("thnine:\tjmp wrong\n"); // jump out because a = b
                    //result
                    printf("corr:\txor\t%s,\t%s\n", "%rax", "%rax");
                    printf("\tmovq\t%s,\t%s\n", "$0", "%rax");
                    printf("\tjmp clean\n"); 
                    printf("wrong:\txor\t%s,\t%s\n", "%rax", "%rax");
                    printf("\tmovq\t%s,\t%s\n", "$1", "%rax");
                    printf("\tjmp clean\n"); 
                    //clean up
                    printf("\tpushq\t%s\n", "%rax"); // push result
                    printf("\txor\t%s,\t%s\n", "%r8", "%r8");
                    printf("\txor\t%s,\t%s\n", "%r9", "%r9");
                    printf("\txor\t%s,\t%s\n", "%r10", "%r10");
                    printf("\txor\t%s,\t%s\n", "%r11", "%r11");
                    printf("\txor\t%s,\t%s\n", "%r12", "%r12");
                    printf("\txor\t%s,\t%s\n", "%r13", "%r13");
                    break;
                case GE: // a >= b
                    printf("\tpopq\t%s\n", "%r11"); // b
                    printf("\tpopq\t%s\n", "%r12"); // a
                    printf("\tcmpq\t%s,\t%s\n", "%r11", "%12"); // compare b and a
                    printf("\txor\t%s,\t%s\n", "%r13", "r13"); // set %r13 to zero
                    printf("\tsetge\t%s\n", "%13"); // set %r13 to 1 if a >= b else 0
                    printf("\tpushq\t%s\n", "%r13"); // push %r13 to the stack
                    break;
                case LE:
                    printf("\tpopq\t%s\n", "%r12"); // b
                    printf("\tpopq\t%s\n", "%r8"); // a
                    //check a
                    printf("\tmovq\t%s,\t%s\n", "%r8", "%r9"); //copy a
                    printf("\tmovq\t%s,\t%s\n", "$-1", "%r10"); 
                    printf("\timul\t%s,\t%s\n", "%r8", "%r10"); // a * -1
                    printf("\tcmpq\t%s,\t%s\n", "%r9", "%10"); // a = -a
                    printf("\tje thone\n"); // jump condition
                    printf("\tmovq\t%s,\t%s\n", "$1", "%r11"); // a is positiv = 1
                    printf("\tjmp out\n"); // jump 
                    printf("thone:\tmovq\t%s,\t%s\n", "$-1", "%r11"); // a is negativ = -1
                    printf("\tjmp out\n"); // jump 
                    //check b
                    printf("out:\txor\t%s,\t%s\n", "%r10", "%r10");
                    printf("\tmovq\t%s,\t%s\n", "%r12", "%r13"); //copy b
                    printf("\tmovq\t%s,\t%s\n", "$-1", "%r10"); 
                    printf("\timul\t%s,\t%s\n", "%r12", "%r10"); // b * -1
                    printf("\tcmpq\t%s,\t%s\n", "%r13", "%10"); // b = -b
                    printf("\tje thtwo\n"); // jump condition
                    printf("\tcmpq\t%s,\t%s\n", "%r11", "$1"); // if a is positiv
                    printf("\tje ththree\n"); // jump condition
                    printf("\tjmp ploop\n"); // jump 
                    printf("ththree:\tjmp corr\n"); // jump out because b is negativ
                    printf("thtwo:\tcmpq\t%s,\t%s\n", "%r11", "$-1"); // if a is positiv
                    printf("\tje thfour\n"); // jump condition
                    printf("\tjmp nloop\n"); // jump 
                    printf("thfour:\tjmp wrong\n"); // jump out because a is negativ
                    //positive loop
                    printf("ploop:\txor\t%s,\t%s\n", "%r10", "%r10");
                    printf("\tcmpq\t%s,\t%s\n", "%r9", "%13"); //if a=b
                    printf("\tje thfive\n"); // jump condition
                    printf("\tjmp pcount\n"); // jump 
                    printf("pcount:\tcmpq\t%s,\t%s\n", "%r9", "%10"); //if a = i; i++
                    printf("\tje thsix\n"); // jump condition
                    printf("\tcmpq\t%s,\t%s\n", "%r13", "%10"); //if b = i
                    printf("\tje theight\n"); // jump condition
                    printf("\tincq\t%s\n", "%r10"); //i++
                    printf("\tjmp pcount\n"); // jump 
                    printf("theight:\tjmp wrong\n"); // jump out because b < a
                    printf("thsix:\tcmpq\t%s,\t%s\n", "%r13", "%10"); //if b = i
                    printf("\tje thseven\n"); // jump condition
                    printf("\tjmp corr\n"); // jump out because a < b 
                    printf("thseven:\tjmp corr\n"); // jump out because a = i = b
                    printf("thfive:\tjmp corr\n"); // jump out because a = b
                    //negative loop
                    printf("ploop:\txor\t%s,\t%s\n", "%r10", "%r10");
                    printf("\tcmpq\t%s,\t%s\n", "%r9", "%13"); //if a=b
                    printf("\tje thnine\n"); // jump condition
                    printf("\tnegq\t%s\n", "%r9"); // sets -a to a
                    printf("\tnegq\t%s\n", "%r13"); // sets -b to b
                    printf("\tjmp ncount\n"); // jump 
                    printf("ncount:\tcmpq\t%s,\t%s\n", "%r13", "%10"); //if b = i; i++
                    printf("\tje thten\n"); // jump condition
                    printf("\tcmpq\t%s,\t%s\n", "%r9", "%10"); //if a = i
                    printf("\tje theleven\n"); // jump condition
                    printf("\tincq\t%s\n", "%r10"); //i++
                    printf("\tjmp ncount\n"); // jump 
                    printf("theleven:\tnegq\t%s\n", "%r9"); // sets a to -a
                    printf("\tnegq\t%s\n", "%r13"); // sets b to -b
                    printf("\tjmp wrong\n"); // jump out because a > b
                    printf("thten:\tcmpq\t%s,\t%s\n", "%r9", "%10"); //if a = i
                    printf("\tje thtwelv\n"); // jump condition
                    printf("\tnegq\t%s\n", "%r9"); // sets a to -a
                    printf("\tnegq\t%s\n", "%r13"); // sets b to -b
                    printf("\tjmp corr\n"); // jump out because a < b 
                    printf("thtwelv:\tjmp corr\n"); // jump out because a = i = b
                    printf("thnine:\tjmp corr\n"); // jump out because a = b
                    //result
                    printf("corr:\txor\t%s,\t%s\n", "%rax", "%rax");
                    printf("\tmovq\t%s,\t%s\n", "$0", "%rax");
                    printf("\tjmp clean\n"); 
                    printf("wrong:\txor\t%s,\t%s\n", "%rax", "%rax");
                    printf("\tmovq\t%s,\t%s\n", "$1", "%rax");
                    printf("\tjmp clean\n"); 
                    //clean up
                    printf("\tpushq\t%s\n", "%rax"); // push result
                    printf("\txor\t%s,\t%s\n", "%r8", "%r8");
                    printf("\txor\t%s,\t%s\n", "%r9", "%r9");
                    printf("\txor\t%s,\t%s\n", "%r10", "%r10");
                    printf("\txor\t%s,\t%s\n", "%r11", "%r11");
                    printf("\txor\t%s,\t%s\n", "%r12", "%r12");
                    printf("\txor\t%s,\t%s\n", "%r13", "%r13");
                    break;
                case NE: // a != b
                    printf("\tpopq\t%s\n", "%r11"); // b
                    printf("\tpopq\t%s\n", "%r12"); // a
                    printf("\tcmpq\t%s,\t%s\n", "%r11", "%12"); // compare b and a
                    printf("\txor\t%s,\t%s\n", "%r13", "r13"); // set %r13 to zero
                    printf("\tsetne\t%s\n", "%13"); // set %r13 to 1 if a != b else 0
                    printf("\tpushq\t%s\n", "%r13"); // push %r13 to the stack
                    break;
                case EQ: 
                    printf("\tpopq\t%s\n", "%r11"); // b
                    printf("\tpopq\t%s\n", "%r12"); // a
                    printf("\tcmpq\t%s,\t%s\n", "%r11", "%12"); // compare b and a
                    printf("\txor\t%s,\t%s\n", "%r13", "r13"); // set %r13 to zero
                    printf("\tsetge\t%s\n", "%13"); // set %r13 to 1 if a >= b else 0
                    printf("\tpushq\t%s\n", "%r13"); // push %r13 to the stack
                    break;
            }
        }
    }
    return 0;
}
