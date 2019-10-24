#!/bin/sh

main()
{
    # from relative path to absolute path
    file=$(readlink -f "$1")

    # compile the file with our compiler
    output=$(./bin/compiler < $file)

    # required prologue
    pre=$(echo "$output" | grep -w '[a-z]' | sort -k2 | grep -w 'popq' | uniq -f 1 | cut -f 3 | (
        echo '\n.data\n\tformat:\t.asciz\t"%d\\\\n"
        mychar:	.asciz	"00000000"'
        echo ".bss"
        while read var; do
            echo "\t$var:\t.quad 0"
        done
        echo ".text\n.globl\tmain\n\nmain:\n"
    ))

    # required epilogue
    post="\tmovq\t\$1,\t%rdi\n\tcall\texit"

    # basename of the file
    name=$(basename "$file" ".calc")
    
    # create assembly file with the prologue, output and epilogue
    echo "$pre" "\n$output" "\n\n$post" > "$name.s"

    # compile the assembly file to an executable
    gcc -g -o "$name" "$name.s" lib/funclib.a -fno-pie -no-pie
}

main "$1"