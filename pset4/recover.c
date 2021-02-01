#include <stdio.h>
#include <stdlib.h>
# include <stdint.h>
# include <string.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2){
        fprintf(stderr, "Usage: ./recover image\n");
        // Here is the use stream stderr - standard error
    }

    // Open File
    FILE *file = fopen(argv[1], "r");

    // Check file
    if (file == NULL) {
        printf(" Cannot open file\n ");
        return 1;
    }

    // Khoi tao bien
     BYTE buffer[512];

     // Set ve 0;
     memset(buffer, 0, sizeof(buffer));

     int counter = 0;
     FILE *fp;
     // file pointer

     char filename[21] = {0} ;

    // Check for JPEG file while reading 512 bytes

    while (!feof(file)){
        fread(buffer, sizeof(BYTE), sizeof(buffer), file);
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0 ) {
            break;
        }
    }

    // Create a new script to copy picture to

    while (!feof(file)){
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0 ) {
            sprintf(filename, "%03i.jpg", counter++); // tao file de luu anh
            fp = fopen(filename, "w"); // tao pointer de store output
        }
        // Writing file
        fwrite(buffer, sizeof(BYTE), sizeof(buffer), fp);
        fread(buffer, sizeof(BYTE), sizeof(buffer), file);

    }
    // Close file
    fclose(file);
    return 0;
}
