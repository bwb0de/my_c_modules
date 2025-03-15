#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

// Função para lidar com um cliente
void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
    char buffer[BUFFER_SIZE];

    printf("Novo cliente conectado!\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);

        if (bytes_read <= 0) {
            printf("Cliente desconectado.\n");
            break;
        }

        printf("Mensagem recebida: %s\n", buffer);

        // Responder ao cliente
        char *response = "Mensagem recebida!";
        send(client_socket, response, strlen(response), 0);
    }

    close(client_socket);
    return NULL;
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    pthread_t thread_id;

    // Criar socket TCP
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Erro ao criar socket");
        exit(EXIT_FAILURE);
    }

    // Configurar endereço do servidor
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Vincular socket ao endereço e porta
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Erro no bind");
        exit(EXIT_FAILURE);
    }

    // Habilitar escuta por conexões
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("Erro no listen");
        exit(EXIT_FAILURE);
    }

    printf("Servidor aguardando conexões na porta %d...\n", PORT);

    while (1) {
        // Aceitar conexão de cliente
        if ((client_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Erro no accept");
            continue;
        }

        // Criar uma nova thread para lidar com o cliente
        if (pthread_create(&thread_id, NULL, handle_client, (void*)&client_socket) != 0) {
            perror("Erro ao criar thread");
        }

        // Opcional: Desvincular a thread para evitar vazamento de memória
        pthread_detach(thread_id);
    }

    close(server_fd);
    return 0;
}
