#include <stdio.h>
#include "calc3.h"
#include "artefacts/y.tab.h"

static int lbl;

/**
 * Function for comparison
 * 
 * ope: variable for each of the different comparison types
 * 
 * types:
 *      l: <
 *      g: >
 *      le: <=
 *      ge: >=
 *      e: ==
 *      ne: !=
 * */
void compare(const char* ope)
{
    printf("\tpopq\t%s\n", "%r11");
    printf("\tpopq\t%s\n", "%r12");
    printf("\txor\t%s,\t%s\n", "%r13", "%r13"); // set %r13 to zero
    printf("\tcmpq\t%s,\t%s\n", "%r11", "%r12"); // compare b and a
    printf("\tset%s\t%s\n", ope, "%r13b"); // set %r13 to 1 if type is true else 0
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
            printf("\tpopq\t%s\n", "%r11");
            printf("\tcmpb\t%s,\t%s\n", "$0", "%r11b");
            printf("\tje\tL%03d\n", lbl2 = lbl++);
            ex(p->opr.op[1]);
            printf("\tjmp\tL%03d\n", lbl1);
            printf("L%03d:\n", lbl2);
            break;
        case IF:
            ex(p->opr.op[0]);
            if (p->opr.nops > 2) {
                /* if else */
                printf("\tpopq\t%s\n", "%r11");
                printf("\tcmpb\t%s,\t%s\n", "$0", "%r11b");
                printf("\tje\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("\tjmp\tL%03d\n", lbl2 = lbl++);
                printf("L%03d:\n", lbl1);
                ex(p->opr.op[2]);
                printf("L%03d:\n", lbl2);
            } else {
                /* if */
                printf("\tpopq\t%s\n", "%r11");
                printf("\tcmpb\t%s,\t%s\n", "$0", "%r11b");
                printf("\tje\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("L%03d:\n", lbl1);
            }
            break;
        case PRINT:     
            ex(p->opr.op[0]);
            // With printf
            /*printf("\tmovq\t%s,\t%s\n", "$format", "%rdi"); // set pointer to format string as first parameter to printf
            printf("\txor\t%s,\t%s\n", "%rsi", "%rsi"); // zero out rsi (important for printf)
            printf("\tpopq\t%s\n", "%rsi"); // set the value on the top of the stack as the second parameter
            printf("\txor\t%s,\t%s\n", "%rax", "%rax"); // zero out rax (important for printf)
            printf("\tcall\tprintf\n"); // call the printf function*/

            // With syscall
            printf("\tpopq\t%s\n", "%r9"); // get value to print from the top of the stack
            printf("\txor\t%s,\t%s\n", "%r14", "%r14"); // zero out r14 used for counting how many character to print

            // Loop to get single digits out of a number and convert it to ascii code
            printf("LF%03d:\n", lbl3 = lbl++);
                printf("\txor\t%s,\t%s\n", "%rax", "%rax"); // zero out rax
                // Divide the number to print by 10
                printf("\tmovq\t%s,\t%s\n", "%r9", "%rax");
                printf("\tmovq\t%s,\t%s\n", "$10", "%r12");
                printf("\tcqto\n");
                printf("\tidivq\t%s\n", "%r12");
                printf("\tmovq\t%s,\t%s\n", "%rax", "%r9"); // Save quotient in r9
                printf("\taddq\t%s,\t%s\n", "$48", "%rdx"); // Convert integer(reminder) to ascii
                printf("\tpushq\t%s\n", "%rdx"); // Push ascii character to the stack
                printf("\tincq\t%s\n", "%r14"); // i++

                // If quotient is 0 go out of the loop
                printf("\tcmpq\t%s,\t%s\n", "$0", "%r9");
                printf("\tje\tLF%03d\n", lbl4 = lbl++);
                printf("\tjmp\tLF%03d\n", lbl3);
            
            printf("LF%03d:\n", lbl4);
                printf("\tdecq\t%s\n", "%r14"); // i--

                // Pop ascii character from the stack and print it to stdout
                printf("\tmovq\t%s,\t%s\n", "$1", "%rax"); // sys_write
                printf("\tmovq\t%s,\t%s\n", "$1", "%rdi"); // stdout
                printf("\tmovq\t%s,\t%s\n", "$mychar", "%rsi"); // character
                printf("\tpopq\t%s\n", "(%rsi)"); // character
                printf("\tmovq\t%s,\t%s\n", "$1", "%rdx"); // size
                printf("\tsyscall\n");

                // Check how many characters are left on the stack
                printf("\tcmpq\t%s,\t%s\n", "$0", "%r14");
                printf("\tjne\tLF%03d\n", lbl4);

                // Print newline character at the end
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
        case UMINUS: // Convert a positive number to a negative number
            ex(p->opr.op[0]);
            printf("\tpopq\t%s\n", "%r11"); 
            printf("\tnegq\t%s\n", "%r11");
            printf("\tpushq\t%s\n", "%r11");
            break;
        case FACT:
            ex(p->opr.op[0]);
            printf("\tpopq\t%s\n", "%rdi");
            printf("\tcall\tfact\n");
            printf("\tpushq\t%s\n", "%rax");
            break;
        case LNTWO:
            ex(p->opr.op[0]);
            printf("\tpopq\t%s\n", "%rdi");
            printf("\tcall\tlntwo\n");
            printf("\tpushq\t%s\n", "%rax");
            break;
        default:
            ex(p->opr.op[0]);
            ex(p->opr.op[1]);
            switch(p->opr.oper) {
                case GCD:
                    printf("\n\tpopq\t%s\n", "%rdi");
                    printf("\tpopq\t%s\n", "%rsi");
                    printf("\tcall\tgcd\n");
                    printf("\tpushq\t%s\n", "%rax");
                    break;
                case '+':
                    printf("\tpopq\t%s\n", "%r11");
                    printf("\tpopq\t%s\n", "%r12");
                    printf("\taddq\t%s,\t%s\n", "%r11", "%r12");
                    printf("\tpushq\t%s\n", "%r12");
                    break;
                case '-':
                    printf("\tpopq\t%s\n", "%r11");
                    printf("\tpopq\t%s\n", "%r12");
                    printf("\tsubq\t%s,\t%s\n", "%r11", "%r12");
                    printf("\tpushq\t%s\n", "%r12");
                    break;
                case '*':
                    printf("\tpopq\t%s\n", "%r11");
                    printf("\tpopq\t%s\n", "%r12");
                    printf("\timul\t%s,\t%s\n", "%r11", "%r12");
                    printf("\tpushq\t%s\n", "%r12");
                    break;
                case '/': // Divide rax by r12 and push the qoutient to the top of the stack
                    // remainder is ignored due the use of integers
                    printf("\tpopq\t%s\n", "%r12");
                    printf("\tpopq\t%s\n", "%rax");
                    printf("\tcqto\n");
                    printf("\tidivq\t%s\n", "%r12");
                    printf("\tpushq\t%s\n", "%rax"); //pushs quotient
                    break;
                case '<':
                    compare("l");
                    break;
                case '>':
                    compare("g");
                    break;
                case GE:
                    compare("ge");
                    break;
                case LE:
                    compare("le");
                    break;
                case NE:
                    compare("ne");
                    break;
                case EQ:
                    compare("e");
                    break;
            }
        }
    }
    return 0;
}
