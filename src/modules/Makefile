DIR = ./
SRC = imu/imu.c
OBJ = $(SRC:.c=.o)
NAME = lib/libperseus.a
TMS = 
TMO = $(TMS:.c=.o)
TMN = test_perseus
LIBS = -lperseus
LIBPATH = ./lib
RM = rm -f

all: $(OBJ)
	ar -rc $(NAME) $(OBJ)
	ranlib $(NAME)

test: $(NAME) $(TMO)
	cc -L$(LIBPATH) $(TMO) $(LIBS) -o $(TMN)

clean:
	-$(RM) $(OBJ)
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.core

fclean: clean
	-$(RM) $(NAME)
	-$(RM) $(TMN)

re: fclean all

$(NAME): all

ftest: fclean test
