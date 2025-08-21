#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1)
typedef struct {
    unsigned short type;
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;       
    unsigned int offset;
} BMPHeader;

typedef struct {
    unsigned int size;
    int width;
    int height;
    unsigned short planes;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    int xPixelsPerMeter;
    int yPixelsPerMeter;
    unsigned int colorsUsed;
    unsigned int importantColors;
} DIBHeader;

#pragma pack(pop)



int main() {
    FILE *file = fopen("cat3.bmp", "rb");
    if (file == NULL) {
        printf("Error opening file");
        return EXIT_FAILURE;
    }
    BMPHeader bmp; DIBHeader dib;
    fread(&bmp, sizeof(BMPHeader), 1, file);
    fread(&dib, sizeof(DIBHeader), 1, file);

    char ASCII[] = "@%#*+=-:. ";
    int width = dib.width;
    int height = dib.height;
    int rowSize = ((width * 3) + 3) / 4 * 4;

    char *row = (char*)malloc(rowSize);

    for (int y = height-1; y>0; y--)
    {
        fread(row, sizeof(char), rowSize, file);
        for (int x = 0; x<width; x++)
        {
            char b = row[x*3];
            char g = row[x*3+1];
            char r = row[x*3+2];
            int avg = ((b*0.3+g*0.5+r*0.2));
            int index = avg*(10.0/255.0);
            printf("%c ", ASCII[index]);
        }
        printf("\n");
    }
    free(row);
    fclose(file);



}