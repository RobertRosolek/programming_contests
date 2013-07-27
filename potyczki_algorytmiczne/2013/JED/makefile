CC=g++
FLAGS=-Wall -Weffc++ -pedantic -Wno-long-long\
-pedantic-errors -Wextra  -Wall -Wcast-align \
-Wcast-qual  -Wchar-subscripts  -Wcomment -Wconversion \
-Wdisabled-optimization \
-Werror -Wfloat-equal  -Wformat  -Wformat=2 \
-Wformat-nonliteral -Wformat-security  \
-Wformat-y2k \
-Wimport  -Winit-self  -Winline \
-Winvalid-pch   \
-Wunsafe-loop-optimizations -Wmissing-braces \
-Wmissing-field-initializers -Wmissing-format-attribute   \
-Wmissing-include-dirs -Wmissing-noreturn \
-Wpacked  -Wpadded -Wparentheses  -Wpointer-arith \
-Wredundant-decls -Wreturn-type \
-Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector \
-Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default \
-Wswitch-enum -Wtrigraphs  -Wuninitialized \
-Wunknown-pragmas  -Wunreachable-code -Wunused \
-Wunused-function  -Wunused-label  -Wunused-parameter \
-Wunused-value  -Wunused-variable  -Wvariadic-macros \
-Wvolatile-register-var  -Wwrite-strings
NAME=JED
all: $(NAME).exe

$(NAME).exe: $(NAME).cpp
	$(CC) $(FLAGS) $(NAME).cpp -o $(NAME).exe
