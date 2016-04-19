TP1: main.c funcoes.c
	gcc -o exec main.c funcoes.c

run:
	clear
	gcc -o exec main.c funcoes.c
	./exec input/exemplo_cena.pgm input/exemplo_objeto.pgm output/imagem_saida.txt

val:
	clear
	gcc -g -o exec main.c funcoes.c
	valgrind --leak-check=full ./exec input/exemplo_cena.pgm input/exemplo_objeto.pgm output/imagem_saida.txt

clean:
	rm exec