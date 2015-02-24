#TODO: Print test done/passed/failed status.

NAME = theseus

CC = clang
CFLAGS = -std=c99 -Wall -Wextra

SRC = src
OBJ = obj

ifeq ($(shell uname), Linux)
	LDFLAGS = -lm -lSDL2 -lSDL2_image -lGL
else ifeq ($(OS), Windows_NT)
	CC = gcc
	LDFLAGS = -lm -mwindows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lOpenGL32
else
	LDFLAGS = -lm -lSDL2main -lSDL2 -lSDL2_image -framework OpenGL
endif

OBJECTS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(wildcard $(SRC)/*.c))

.PHONY: asan clean cppcheck gprof valgrind

$(NAME): $(OBJECTS)
	@mkdir -p screenshots
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $(NAME)

$(OBJ)/globals.o: $(addprefix $(SRC)/, globals.c globals.h)
$(OBJ)/main.o: $(addprefix $(SRC)/, main.c globals.h util.h)
$(OBJ)/util.o: $(addprefix $(SRC)/, util.c globals.h util.h)

$(OBJECTS): | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ):
	@mkdir $(OBJ)

asan: prepare
	@+$(MAKE) CFLAGS="$(CFLAGS) -O3 -g -fsanitize=address -fno-omit-frame-pointer" LDFLAGS="$(LDFLAGS) -g -fsanitize=address" --no-print-directory

	@echo -e "\nRunning AddressSanitizer..."
	-@./$(NAME) &> log/asan.txt
	@echo "Log saved as log/asan.txt."

clean:
	@rm -rf bin/ obj/ $(NAME){,.exe}

cppcheck:
	@cppcheck . --enable=all --suppress=missingIncludeSystem --inconclusive --std=c99 --verbose

gprof: prepare
	@$(MAKE) CFLAGS="$(CFLAGS) -pg" LDFLAGS="$(LDFLAGS) -pg" --no-print-directory

	@echo -e "\nRunning gprof..."
	@./$(NAME) && gprof $(NAME) gmon.out > log/gprof.txt && rm gmon.out && echo "Log saved as log/gprof.txt."

prepare: clean
	@mkdir -p log

purge: clean
	@rm -rf log/

release: clean
	@mkdir -p bin/screenshots

	@$(MAKE) CFLAGS="$(CFLAGS) -O3" LDFLAGS="$(LDFLAGS) -s" --no-print-directory

	@cp -r images/ shaders/ -t bin/
	@mv $(NAME) bin/ && ln -s bin/$(NAME) .

valgrind: prepare
	@+$(MAKE) CFLAGS="$(CFLAGS) -g" LDFLAGS="$(LDFLAGS) -g" --no-print-directory

	@echo -e "\nRunning Valgrind..."
	@valgrind --track-origins=yes --leak-check=full ./$(NAME) &> log/valgrind.txt && echo "Log saved as log/valgrind.txt."
