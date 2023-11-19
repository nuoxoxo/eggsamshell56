CC = clang
CFLAGS = -Wall -Wextra -Werror
SRC = mini_serv.cc
OUT = a.out

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@rm -f $(OUT)

fclean: clean
	@rm -f out *.out

f: fclean

re: f all

.PHONY: fclean clean all re f

