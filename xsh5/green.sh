c++ -Werror -Wextra -Wall *.cc && ./a.out;
c++ -Werror -Wextra -Wall -fsanitize=address *.cc && \
    ./a.out | cat -e | diff - todiff.2 -s && rm *.out

