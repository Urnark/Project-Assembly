#!/bin/sh

main()
{
    file=$(readlink -f "$1")

    output=$(./bin/compiler < $file)

    pre=$(echo "$output" | grep -w '[a-z]' | sort -k2 | grep -w 'popq' | uniq -f 1 | cut -f 3 | (
        echo '\n.data\n\tformat:\t.asciz\t"%d\\\\n"'
        echo ".bss"
        while read var; do
            echo "\t$var:\t.quad 0"
        done
        echo ".text\n.globl\tmain\n\nmain:\n"
    ))
    post="\tmovq\t\$1,\t%rdi\n\tcall\texit"

    name=$(basename "$file" ".calc")
    echo "$pre" "\n$output" "\n\n$post" > "$name.s"

    gcc -o "$name" "$name.s" -fno-pie -no-pie
}

main "$1"