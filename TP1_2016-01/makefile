# -- parte obrigatória --

#make
#compila o código
TP1: main.c funcoes.c
	gcc -o exec main.c funcoes.c

# -- parte opcional --

#make recursivo
#compila e roda o programa recursivo
recursivo:
	clear
	gcc -o exec main.c funcoes.c
	./exec input/input.txt espada.txt 0

#make iterativo
#compila e roda o programa iterativo
iterativo:
	clear
	gcc -o exec main.c funcoes.c
	./exec input/input.txt espada.txt 1

#make valr
#compila e testa o programa recursivo no valgrind
valr:
	clear
	gcc -g -o exec main.c funcoes.c
	valgrind --leak-check=full --track-origins=yes ./exec input/input.txt espada.txt 0

#make vali
#compila e testa o programa iterativo no valgrind
vali:
	clear
	gcc -g -o exec main.c funcoes.c
	valgrind --leak-check=full --track-origins=yes ./exec input/input.txt espada.txt 1

#make clean
#apaga os arquivos gerado pelo programa (para submeter o tp)
clean:
	rm exec
	rm espada.txt