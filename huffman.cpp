#include<fstream>
#include<iostream>

using namespace std;

struct NoHuffman {
	char caracter;
	int frequencia;
	NoHuffman *esquerda;
	NoHuffman *direita;
};

/**
 * Processo para garantir a estrutura heap na tabela de frequências
 *
 * @param v: Vetor a ser ordenado com a estrutura da árvore de huffman
 * @param i: Indice do vetor (considerando 1--n)
 * @param n: Tamanho do vetor
 **/
void heapify(NoHuffman **v, int i, int n) {
	NoHuffman *tmp;

	if(i > n) {
		return;
	}

	heapify(v,2*i,n);
	heapify(v,2*i+1,n);

	if(2*i <= n && v[2*i-1]->frequencia < v[i-1]->frequencia) {
		tmp = v[i-1];
		v[i-1] = v[2*i-1];
		v[2*i-1] = tmp;
	}

	if(2*i+1 <= n && v[2*i]->frequencia < v[i-1]->frequencia) {
		tmp = v[i-1];
		v[i-1] = v[2*i];
		v[2*i] = tmp;
	}
}

/**
 * Constrói a árvore de huffman
 *
 * @param freq: Tabela com as frequências encontradas no arquivo fonte
 * @param n: Tamanho da tabela
 * @return: Nó raiz da árvore
 */
NoHuffman *construir_arvore(NoHuffman **freq,int n) {
	NoHuffman *tmp;
	NoHuffman **tmp_freq;

	while(n > 1) {
		// Busca os 2 itens com menor frequencia
		heapify(freq,1,n);
		heapify(freq+1,1,n-1);

		// Cria o novo nó
		tmp = new NoHuffman();
		tmp->frequencia = freq[0]->frequencia + freq[1]->frequencia;
		tmp->esquerda = freq[0];
		tmp->direita = freq[1];

		// Reconstrói a lista
		tmp_freq = new NoHuffman*[n-1];
		tmp_freq[0] = tmp;

		for(int i=2;i<n;i++) {
			tmp_freq[i-1] = freq[i];
		}

		freq = tmp_freq;
		n--;
	}

	return freq[0];
}

/**
 * Escreve no arquivo de saída a tabela de codificação
 * @param no: Nó corrente da árvore
 * @param codigo: Código binário
 * @param arq: Arquivo de saída
 **/
void gerar_tabela(NoHuffman *no,string codigo,fstream &arq) {
	cout << no->frequencia << " " << (int)no->caracter << " " << codigo << endl;

	if(no->esquerda == NULL && no->direita == NULL) {
		arq << (int)no->caracter << "\t" << codigo << endl;
	}else{
		gerar_tabela(no->esquerda,codigo+"0",arq);
		gerar_tabela(no->direita,codigo+"1",arq);
	}
}

/**
 * Gera a tabela de frequencia
 * @param arq: Arquivo de entrada
 * @param n: Quantidade de elementos da tabela (saída)
 * @return: Ponteiro da tabela de freqencia
 **/
NoHuffman **gerar_frequencia(fstream &arq, int &n) {
	int cont[255];
	char c;
	int k = 0;
	NoHuffman **freq;
	n = 0;

	// Conta a frequencia de caracteres
	for(int i=0;i<255;i++) {
		cont[i] = 0;
	}

	while(!arq.eof()) {
		arq.read(&c,1);
		cont[c]++;
	}

	// Conta os elementos existentes
	for(int i=0;i<255;i++) {
		if(cont[i] > 0) {
			n++;
		}
	}

	// Gera a tabela de frequencia
	freq = new NoHuffman*[n];

	for(int i=0;i<255;i++) {
		if(cont[i] > 0) {
			freq[k] = new NoHuffman();
			freq[k]->caracter = (unsigned char)i;
			freq[k]->frequencia = cont[i];
			freq[k]->esquerda = NULL;
			freq[k]->direita = NULL;
			k++;
		}
	}

	return freq;
}

/**
 * Carrega a tabela de códigos binários
 * @param huffman_table: Nome do arquivo com a tabela de códigos
 * @param tamanho: Quantidade de caracteres do arquivo original
 * @return: Lista de códigos
 */
string *carregar_tabela(string huffman_table, int &tamanho) {
	string *tabela = new string[255];
	fstream f(huffman_table.c_str(),ios::in|ios::binary);
	int k;
	string codigo;

	f >> tamanho;

	while(!f.eof()) {
		f >> k;
		f >> codigo;
		tabela[k] = codigo;
	}

	return tabela;
}

void comprimir(fstream &entrada,string *codigo,fstream &saida) {
	char c;
	unsigned char base = 128;
	unsigned char byte=0;

	while(!entrada.eof()) {
		entrada.read(&c,1);

		for(int i=0;i<codigo[c].length();i++) {
			if(codigo[c][i] == '1') {
				byte += base;
			}

			if(base == 1) {
				saida.write((char*)&byte,1);
				base = 128;
			}else{
				base /= 2;
			}
		}
	}

	// Se terminar no meio de algum byte, escreve no fim do arquivo
	if(base < 128) {
		saida.write((const char*)&byte,1);
	}
}

/**
 * Descomprime o arquivo de entrada usando a tabela de código imprimindo-o
 * na saída padrão
 * @param entrada: Arquivo de entrada
 * @param codigo: Tabela de código
 * @param n: Quantidade de caracteres do arquivo fonte
 **/
void descomprimir(fstream &entrada,string *codigo,int n) {
	string codigo_atual = "";
	unsigned char byte;
	unsigned char base = 1;

	for(int i=0;i<n;i++) {
		// Busca o próximo bit da entrada
		do {
			if(base == 1) {
				base = 128;
				entrada.read((char*)&byte,1);
			}else{
				base /= 2;
			}

			//cout << (int)base << "-" << (int)byte << " " << codigo_atual << endl;

			if(byte & base > 0) {
				codigo_atual += "1";
			}else{
				codigo_atual += "0";
			}

			// Verifica se o código está na tabela
			for(int j=0;j<255;j++) {
				if(codigo[j] == codigo_atual) {
					cout << (char)j;
					codigo_atual = "";
					break;
				}
			}
		}while(codigo_atual != "");
	}
}

int main(int argc,char **argv) {
	NoHuffman **freq;
	NoHuffman *raiz;
	fstream entrada;
	fstream saida;
	fstream tabela_entrada;
	string *codigo;
	int n;

	if(argc == 2) {
		// Constrói a tabela de freqencia e a árvore
		entrada.open(argv[1],ios::in|ios::binary);
		freq = gerar_frequencia(entrada,n);
		raiz = construir_arvore(freq,n);

		// Escreve a tabela
		tabela_entrada.open(string(string(argv[1])+".huffman.table").c_str(),ios::out);
		tabela_entrada << raiz->frequencia << endl;
		gerar_tabela(raiz,"",tabela_entrada);
		tabela_entrada.close();

		// Lê a tabela gerada e grava arquivo comprimido
		codigo = carregar_tabela(string(string(argv[1])+".huffman.table").c_str(),n);
		saida.open(string(string(argv[1])+".huffman.data").c_str(),ios::out|ios::binary);
		entrada.clear();
		entrada.seekg(0,ios::beg);
		comprimir(entrada,codigo,saida);
		saida.close();
		entrada.close();
	}else if(argc == 3){
		codigo = carregar_tabela(argv[1],n);
		entrada.open(argv[2],ios::in|ios::binary);
		descomprimir(entrada,codigo,n);
		entrada.close();
	}

	return 0;
}