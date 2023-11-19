CXX			= c++
CXXFLAGS	= -Werror -Wextra -Wall
SRC			= mini_serv.cc
OUT			= a.out
PORT		= 8080

all		: $(OUT)

$(OUT)	: $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@
	./$(OUT) $(PORT)

clean	:
	@rm -f $(OUT)

fclean	: clean
	@rm -f out *.out

f		: fclean

re		: f all

.PHONY	: fclean clean all re f
