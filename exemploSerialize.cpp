#include <iostream>
#include <fstream>
using namespace std;
 
int main() {
    int i, a = 65, pos = 0;
    /*
        Abertura do arquivo

        O primeiro parâmetro especifica o nome do arquivo
        O segundo parâmetro especifica que o arquivo será aberto para escrita
        O terceiro parâmetro especifica que o arquivo será aberto para leitura
        O quarto parâmetro especifica a posição inicial para modificação como o fim do arquivo
        O quinto parâmetro especifica o modo binário para escrita e leitura
    */
    fstream file("data.dat", ios::in | ios::out | ios::ate | ios::binary);

    /*
        Verifica se existe um arquivo através da função is_open(),
        que retorna o valor verdadeiro se existir, e falso caso não exista.
        Caso retorne falso, as três linhas servirão para criar um arquivo através da função open()
        da mesma forma que foi feita inicialmente.
    */

    if (!file.is_open()) { // first run will create the file
        file.open("data.dat", ios::out);
        file.close();
        file.open("data.dat", ios::in | ios::out | ios::ate | ios::binary);
    }
    
    /*
        Verifica se existe um arquivo aberto através da função is_open()
        Executará somente se ela retornar verdadeiro
    */
    if (file.is_open()) {
        // fstream::seekp moves the writing head to the designated byte
        // fstream::write writes the specified number of bytes (chars) to file

        // O laço lê 10 números inteiros e verifica a integridade dos dados
        for (i = 0; i < 10 && file.good(); i++) {
            // A posição é multiplicada por 4, equivalente ao tamanho de 4 bytes de um número inteiro
            pos = i * 4;
            // Define a posição do arquivo que será reescrita
            file.seekp(pos); 
            // O primeiro argumento usa um ponteiro para char com os dados, ou seja, a variável a
            // O segundo argumento define o tamanho do bloco alocado para o ponteiro
            file.write(reinterpret_cast<char*>(&a), sizeof(int));
            // Itera o valor para que o próximo caractere, em ordem alfabética, seja obtido
            a++;
        }

        // setting an arbitrary value to a to show the reading
        a = 1000;
        cout << "a: " << a << endl;
        pos = 0;

        // fstream::seekg moves the reading head to the designated byte
        // fstream::read read the specified number of bytes (char) from file

        // O laço lê 10 números inteiros e verifica a integridade dos dados
        for (i = 0; i < 10 && file.good(); i++) {
            // A posição é multiplicada por 4, equivalente ao tamanho de 4 bytes de um número inteiro
            pos = i * 4;
            // Define a posição do arquivo que será lida
            file.seekg(pos);
            // O primeiro argumento usa um ponteiro para char com os dados, ou seja, a variável a
            // O segundo argumento define o tamanho do bloco alocado para o ponteiro
            file.read(reinterpret_cast<char*>(&a), sizeof(int));
            // Imprime o valor apontado, equivalente ao valor respectivo da tabela ASCII
            cout << "Read data from pos " << i << ": " << a << endl;
        }
        // Fecha o processo de escrita e leitura do arquivo
        file.close();
    } else {
        cerr << "Couldn't open file!" << endl;
    }
        return 0;
}