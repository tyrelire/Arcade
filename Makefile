##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Arcade
##

NAME		=	arcade

IFLAGS		=	-I ./src/ -I ./src/Core/ -I ./src/Game/ -I ./src/Graphic/ -I ./src/Graphic/Ncurses -I ./src/Graphic/Sfml/ -I ./src/Graphic/Sdl2/

CPPFLAGS	=	 $(IFLAGS) -std=c++11

PATH_SRC         =   ./src/

PATH_MAIN        =  $(PATH_SRC)main.cpp                             \

PATH_SFML 	     = 	$(PATH_SRC)Graphic/Sfml/lib_Sfml.cpp 				\

PATH_SDL2 	     = 	$(PATH_SRC)Graphic/Sdl2/lib_Sdl2.cpp 				\

PATH_NCURSES    = 	$(PATH_SRC)Graphic/Ncurses/lib_Ncurses.cpp 			\

PATH_SNAKE 	    = 	$(PATH_SRC)Game/Snake/Snake.cpp 				\

PATH_NIBBLER 	= 	$(PATH_SRC)Game/Nibbler/Nibbler.cpp 			\

all: graphic game core

game:
	g++ -shared -fPIC -o ./lib/arcade_snake.so $(PATH_SNAKE) -fno-gnu-unique
	g++ -shared -fPIC -o ./lib/arcade_nibbler.so $(PATH_NIBBLER) -fno-gnu-unique

core:
	g++ $(PATH_MAIN) $(PATH_SRC)Core/ICore.cpp -ldl -o $(NAME) -fno-gnu-unique

graphic:
	g++ -shared -fPIC -o ./lib/arcade_sfml.so $(PATH_SFML) -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
	g++ -shared -fPIC -o ./lib/arcade_sdl2.so $(PATH_SDL2) -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lSDL2 -lSDL2main -fno-gnu-unique
	g++ -shared -fPIC -o ./lib/arcade_ncurses.so $(PATH_NCURSES) -fno-gnu-unique -lncurses -lmenu -lform

clean:
	rm -f ./lib/*.so

fclean: clean
	rm -f $(NAME)

re: fclean all
