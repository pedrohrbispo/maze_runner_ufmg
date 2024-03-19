#include <stdio.h>
#include <stack>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>


// Matriz de char representnado o labirinto
char** maze; // Voce também pode representar o labirinto como um vetor de vetores de char (vector<vector<char>>)

// Numero de linhas e colunas do labirinto
int num_rows;
int num_cols;

// Representação de uma posição
struct pos_t {
	int i;
	int j;
};

// Estrutura de dados contendo as próximas
// posicões a serem exploradas no labirinto
std::stack<pos_t> valid_positions;
char* splitStringBySpace(char * str);
/* Inserir elemento: 

	 pos_t pos;
	 pos.i = 1;
	 pos.j = 3;
	 valid_positions.push(pos)
 */
// Retornar o numero de elementos: 
//    valid_positions.size();
// 
// Retornar o elemento no topo: 
//  valid_positions.top(); 
// 
// Remover o primeiro elemento do vetor: 
//    valid_positions.pop();

//https://favtutor.com/blogs/split-string-cpp  split function


// void readFile(const char* file_name) {
// 	std::ifstream mazeFile(file_name);
// 	std::string line;

// 	std::string firstLine;
// 	getline(mazeFile, firstLine);
// 	std::cout << firstLine << "file" << "\n";
// 	std::istringstream iss(firstLine);
// 	int num;
// 	std::vector<int> numbers;
	
// 	while (iss >> num) {
// 		numbers.push_back(num);
// 	}

// 	std::cout << numbers[0] << "num 1 \n";
// 	std::cout << numbers[1] << "num2 \n";

// 	if (mazeFile.is_open()) {
// 		while (getline(mazeFile, line)) {
// 			std::cout << line << "\n";
// 		}
// 		mazeFile.close();
//     }
// 	mazeFile.close();
// }

std::vector<int> getRowsAndCols(const char* file_name) {

	std::ifstream mazeFile(file_name);
	std::string firstLine;
	getline(mazeFile, firstLine);
	std::istringstream iss(firstLine);
	int num;
	std::vector<int> numbers;
	
	while (iss >> num) {
		numbers.push_back(num);
	}
	return numbers;
}

// Função que le o labirinto de um arquivo texto, carrega em 
// memória e retorna a posição inicial
pos_t load_maze(const char* file_name) {
	pos_t initial_pos;
	std::ifstream mazeFile(file_name);
	std::string line;
	// Le o numero de linhas e colunas (fscanf) 
	// e salva em num_rows e num_cols

	std::vector<int> rowsAndCols =  getRowsAndCols(file_name);
	num_rows= rowsAndCols[0];
	num_cols = rowsAndCols[1];
	
	std::cout<<num_cols<<"nums 1 \n";
	std::cout<<num_rows<<"nums 1 \n";
	
	// Aloca a matriz maze (malloc)
	for (int i = 0; i < num_rows; ++i)
		// Aloca cada linha da matriz
	
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			// Le o valor da linha i+1,j do arquivo e salva na posição maze[i][j]
			// Se o valor for 'e' salvar o valor em initial_pos
		}
	}
	return initial_pos;
}

// Função que imprime o labirinto
void print_maze() {
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
}


// Função responsável pela navegação.
// Recebe como entrada a posição initial e retorna um booleando indicando se a saída foi encontrada
bool walk(pos_t pos) {
	
	// Repita até que a saída seja encontrada ou não existam mais posições não exploradas
		// Marcar a posição atual com o símbolo '.'
		// Limpa a tela
		// Imprime o labirinto
		
		/* Dado a posição atual, verifica quais sao as próximas posições válidas
			Checar se as posições abaixo são validas (i>0, i<num_rows, j>0, j <num_cols)
		 	e se são posições ainda não visitadas (ou seja, caracter 'x') e inserir
		 	cada uma delas no vetor valid_positions
		 		- pos.i, pos.j+1
		 		- pos.i, pos.j-1
		 		- pos.i+1, pos.j
		 		- pos.i-1, pos.j
		 	Caso alguma das posiçÕes validas seja igual a 's', retornar verdadeiro
	 	*/

		
	
		// Verifica se a pilha de posições nao esta vazia 
		//Caso não esteja, pegar o primeiro valor de  valid_positions, remove-lo e chamar a funçao walk com esse valor
		// Caso contrario, retornar falso
		if (!valid_positions.empty()) {
			pos_t next_position = valid_positions.top();
			valid_positions.pop();
		}
	return false;
}

int main(int argc, char* argv[]) {
	// carregar o labirinto com o nome do arquivo recebido como argumento
    std::cout<<argv[1];
	pos_t initial_pos = load_maze(argv[1]);
	// chamar a função de navegação
	bool exit_found = walk(initial_pos);
	
	// Tratar o retorno (imprimir mensagem)
	
	return 0;
}
