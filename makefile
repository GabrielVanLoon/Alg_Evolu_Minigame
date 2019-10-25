# define quais acoes devem ser executadas indiferente 
# de um arquivo estar atualizado ou nao.
.PHONY = all clean 


BUILD_DIR := ./build/
NN_SRCS   := ./network/matrix.cpp ./network/neural-network.cpp
NN_BINS   := $(NN_SRCS:%.c=%)
AG_SRCS   := ./genetics/individual.cpp ./genetics/population.cpp ./genetics/crossover.cpp
AG_BINS   := $(AG_SRCS:%.c=%)

EITA := "olaaa"

all: ${NN_BINS} ${AG_BINS}
	@echo "Relizando build..."
	g++ -o exec ${NN_BINS} ${AG_BINS} main.cpp
 
%: %.o
	@echo "Gerando binarios..."
	g++ $< -o $@

%.o: %.c
	@echo "Gerando objetos..."
	g++ -c $<

run:
	./exec

verify:
	valgrind --leak-check=full --track-origins=yes ./exec 

clean:
	@echo "Removindo arquivos..."
	rm exec
	@echo "limpeza completa!"
