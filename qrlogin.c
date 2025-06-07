#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zbar.h>


//sudo apt install zbar-tools libzbar-dev fswebcam

#define IMAGE_PATH "qrcode.jpg"
#define AUTHORIZED_QR "usuario123"  // QR code esperado

// Captura uma imagem da webcam
void capture_image() {
    #ifdef _WIN32
        system("ffmpeg -f dshow -i video=\"Integrated Camera\" -frames:v 1 " IMAGE_PATH);
    #else
        system("fswebcam -r 640x480 --no-banner " IMAGE_PATH);
    #endif
}

// Processa a imagem e tenta ler o QR code
int scan_qr_code() {
    FILE *file = fopen(IMAGE_PATH, "rb");
    if (!file) {
        printf("❌ Erro ao abrir a imagem.\n");
        return 0;
    }
    fclose(file);

    // Criar um scanner ZBar
    zbar_image_scanner_t *scanner = zbar_image_scanner_create();
    zbar_image_scanner_set_config(scanner, ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

    // Carregar imagem com OpenCV (ou outro método)
    zbar_image_t *image = zbar_image_create();
    zbar_image_set_format(image, *(int*)"Y800");
    zbar_image_set_size(image, 640, 480);

    // Processar imagem
    int n = zbar_scan_image(scanner, image);
    if (n > 0) {
        const zbar_symbol_t *symbol = zbar_image_first_symbol(image);
        while (symbol) {
            const char *qr_data = zbar_symbol_get_data(symbol);
            printf("🔍 QR Code detectado: %s\n", qr_data);

            if (strcmp(qr_data, AUTHORIZED_QR) == 0) {
                printf("✅ Acesso autorizado!\n");
                zbar_image_destroy(image);
                zbar_image_scanner_destroy(scanner);
                return 1;
            }
            symbol = zbar_symbol_next(symbol);
        }
    }

    printf("❌ Nenhum QR code válido detectado.\n");
    zbar_image_destroy(image);
    zbar_image_scanner_destroy(scanner);
    return 0;
}

void show_menu() {
    printf("\n✅ Login efetuado com sucesso!\n");
    printf("🔹 Escolha uma opção:\n");
    printf("1. Ver perfil\n");
    printf("2. Configurações\n");
    printf("3. Sair\n");

    int option;
    printf("Digite uma opção: ");
    scanf("%d", &option);

    switch (option) {
        case 1:
            printf("👤 Exibindo perfil...\n");
            break;
        case 2:
            printf("⚙️ Abrindo configurações...\n");
            break;
        case 3:
            printf("🔚 Saindo...\n");
            exit(0);
        default:
            printf("❌ Opção inválida!\n");
    }
}

int main() {
    capture_image();
    if (scan_qr_code()) {
        show_menu();
    } else {
        printf("❌ Login falhou.\n");
    }
    return 0;
}

