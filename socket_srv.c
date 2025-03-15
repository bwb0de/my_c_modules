#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // Criar socket TCP (AF_INET = IPv4, SOCK_STREAM = TCP)
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Erro ao criar socket");
        exit(EXIT_FAILURE);
    }

    // Configurar endereço do servidor
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Aceita conexões em qualquer interface
    address.sin_port = htons(PORT); // Converte porta para formato de rede

    // Vincular socket ao endereço e porta
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Erro no bind");
        exit(EXIT_FAILURE);
    }

    // Habilitar escuta por conexões (até 3 na fila)
    if (listen(server_fd, 3) < 0) {
        perror("Erro no listen");
        exit(EXIT_FAILURE);
    }

    printf("Servidor aguardando conexões na porta %d...\n", PORT);

    // Aceitar conexões de clientes
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Erro no accept");
        exit(EXIT_FAILURE);
    }

    printf("Cliente conectado.\n");

    // Receber mensagem do cliente
    int bytes_read = read(new_socket, buffer, BUFFER_SIZE);
    printf("Mensagem recebida: %s\n", buffer);

    // Enviar resposta ao cliente
    char *response = "Mensagem recebida com sucesso!";
    send(new_socket, response, strlen(response), 0);

    // Fechar socket
    close(new_socket);
    close(server_fd);
    return 0;
}
