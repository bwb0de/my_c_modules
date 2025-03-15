#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE] = {0};

    // Criar socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Erro ao criar socket");
        exit(EXIT_FAILURE);
    }

    // Configurar endereço do servidor
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Converter endereço IP para binário
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Endereço inválido");
        exit(EXIT_FAILURE);
    }

    // Conectar ao servidor
    if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Erro na conexão");
        exit(EXIT_FAILURE);
    }

    // Enviar mensagem ao servidor
    char *message = "Olá, servidor!";
    send(sock, message, strlen(message), 0);
    printf("Mensagem enviada: %s\n", message);

    // Receber resposta do servidor
    int bytes_read = read(sock, buffer, BUFFER_SIZE);
    printf("Resposta do servidor: %s\n", buffer);

    // Fechar socket
    close(sock);
    return 0;
}
