DIR = ./
SRC = imu/imu.c pathing/pathview.c
OBJ = $(SRC:.c=.o)
NAME = lib/libperseus.a
TESTDIR = ./test
LIBS = -lperseus
LIBPATH = ./lib
RM = rm -f
CFLAGS = `pkg-config --cflags --libs gtk+-2.0`

all: $(OBJ)
	ar -rc $(NAME) $(OBJ)
	ranlib $(NAME)

pathing: all
	cc -L$(LIBPATH) $(TESTDIR)/pathing.c $(LIBS) -o pathing

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
