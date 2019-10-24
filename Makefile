
PROG = bin/compiler
COMPILER_C = calc3i.c

LEXTAXX_DIR = lexyacc-code
ARTIFACTS_DIR = $(LEXTAXX_DIR)/artefacts

YACC_FILE = $(LEXTAXX_DIR)/calc3.y
LAX_FILE = $(LEXTAXX_DIR)/calc3.l

# get all source files in the source directory
SRCS = $(wildcard $(ARTIFACTS_DIR)/*.c)
# substitute each source file with its corresponding object file
OBJS = $(patsubst $(ARTIFACTS_DIR)/%.c,$(ARTIFACTS_DIR)/%.o,$(SRCS))

all: $(PROG)

#$(ARTIFACTS_DIR)/y.tab.c:
#	bison -y -d $(YACC_FILE)

#$(ARTIFACTS_DIR)/lex.yy.c:
#	flex $(LAX_FILE)

#$(ARTIFACTS_DIR)/%.o: $(ARTIFACTS_DIR)/%.c
#	gcc -c $^

$(PROG): #$(OBJS)
	# Compile the compiler
	bison -y -d $(YACC_FILE) -o $(ARTIFACTS_DIR)/y.tab.c
	flex -o $(ARTIFACTS_DIR)/lex.yy.c $(LAX_FILE)
	gcc -c $(ARTIFACTS_DIR)/lex.yy.c -o $(ARTIFACTS_DIR)/lex.yy.o
	gcc -c $(ARTIFACTS_DIR)/y.tab.c -o $(ARTIFACTS_DIR)/y.tab.o
	gcc $(ARTIFACTS_DIR)/y.tab.o $(ARTIFACTS_DIR)/lex.yy.o $(LEXTAXX_DIR)/$(COMPILER_C) -o $(PROG)

	# Compile library
	gcc -g -c src/funclib.s -o src/artefacts/funclib.o
	ar rcs lib/funclib.a src/artefacts/funclib.o

clean:
	/bin/rm $(PROG) $(ARTIFACTS_DIR)/y.tab.c $(ARTIFACTS_DIR)/y.tab.o $(ARTIFACTS_DIR)/lex.yy.c $(ARTIFACTS_DIR)/lex.yy.o src/artefacts/funclib.o lib/funclib.a