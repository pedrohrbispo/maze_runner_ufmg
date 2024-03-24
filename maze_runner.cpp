/*
	Para rodar: 
	Compile;
	Rode: ./maze_runner ../data/maze.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <unistd.h>
#include <iostream>

// Matriz de char representando o labirinto
char** maze;

// Número de linhas e colunas do labirinto
int num_rows;
int num_cols;

// Representação de uma posição
struct pos_t {
	int i;
	int j;
};

// Estrutura de dados contendo as próximas posicões a serem exploradas no labirinto
std::stack<pos_t> valid_positions;

// Função que lê o labirinto de um arquivo texto, carrega em memória e retorna a posição inicial
pos_t load_maze(const char* file_name) {
    pos_t initial_pos = {-1, -1}; // Inicializa com valor inválido

    FILE * mazeFile;
    mazeFile = fopen(file_name, "r");
    if (!mazeFile) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    fscanf(mazeFile, "%d %d\n", &num_rows, &num_cols);

	std::cout<<num_cols<<"\n"<<num_rows;

    maze = (char**)malloc(num_rows * sizeof(char*));
    for (int i = 0; i < num_rows; ++i) {
        maze[i] = (char*)malloc(num_cols * sizeof(char));
        for (int j = 0; j < num_cols; ++j) {
            fscanf(mazeFile, "%c ", &maze[i][j]);
            if (maze[i][j] == 'e') {
                initial_pos.i = i;
                initial_pos.j = j;
            }
        }
    }
    
    fclose(mazeFile);
    return initial_pos;
}

// Função que imprime o labirinto
void print_maze() {
    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            if (maze[i][j] == 'o') {
                // Impressão do caractere 'o' em vermelho
                printf("\033[1;31mo\033[0m");
            } else if (maze[i][j] == '.') {
                // Impressão do caractere '.' em vermelho
                printf("\033[1;31m.\033[0m");
            } else {
                printf("%c", maze[i][j]);
            }
        }
        printf("\n");
    }
    // Delay de 80 ms em cada passo
    usleep(80000);
}

// Função responsável pela navegação: recebe como entrada a posição inicial e retorna um boolean indicando se a saída foi encontrada
bool walk(pos_t pos) {
    while (!valid_positions.empty()) {
        bool exitFound = false;

        // Marcar a posição atual com o caractere 'o'
        maze[pos.i][pos.j] = 'o';

        system("clear");

        // Imprimir o labirinto
        print_maze();

        // Define os deslocamentos para as posições adjacentes: acima, abaixo, esquerda, direita
        int di[] = {-1, 1, 0, 0};
        int dj[] = {0, 0, -1, 1};

        // Verificar as posições adjacentes e adiciona à pilha se forem válidas
        for (int k = 0; k < 4; ++k) {
            int next_i = pos.i + di[k];
            int next_j = pos.j + dj[k];

            if (next_i >= 0 && next_i < num_rows && next_j >= 0 && next_j < num_cols) {
                // Verifica se a posição é uma saída
                if (maze[next_i][next_j] == 's') {
                    exitFound = true;
                }
                // Verifica se a posição contém um caminho 'x' não visitado
                else if (maze[next_i][next_j] == 'x') {
                    pos_t next_pos = {next_i, next_j};
                    valid_positions.push(next_pos);
                }
            }
        }

        maze[pos.i][pos.j] = '.';

        if (exitFound) {
            return true;
        }

        // Se a pilha não estiver vazia, obter a próxima posição e continuar
        if (!valid_positions.empty()) {
            pos = valid_positions.top();
            valid_positions.pop();
        }
    }

    // Caso a pilha esteja vazia e a saída não tenha sido encontrada
    return false;
}

int main(int argc, char* argv[]) {
	// Carregar o labirinto com o nome do arquivo recebido como argumento
	pos_t initial_pos = load_maze(argv[1]);

	// Inserir a posição inicial na pilha
	valid_positions.push(initial_pos);

	// Chamar a função de navegação
	bool exit_found = walk(initial_pos);

	// Tratar o retorno: imprimir mensagem
	if (exit_found) {
		printf("Saída encontrada!\n");
	} else {
		printf("Não foi possível encontrar a saída!\n");
	}

	// Liberar memória da matriz maze
	for (int i = 0; i < num_rows; ++i) {
		free(maze[i]);
	}
	free(maze);

	return 0;
}