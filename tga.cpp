#include "tga.h"

Tga Tga::LoadTGAFile(const char *filename)
{
    Tga tgaFile;
    
    FILE *filePtr;
    unsigned char ucharBad;
    short int sintBad;
    long imageSize;
    int colorMode;
    unsigned char colorSwap;
    
    // Open the TGA file.
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL)
    {
        std::cout << "can't open tga:" << filename << std::endl;
        exit(0);
        }
        
        // Read the two first bytes we don't need.
        fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
        fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
        
        // Which type of image gets stored in imageTypeCode.
        fread(&tgaFile.imageTypeCode, sizeof(unsigned char), 1, filePtr);
        
        // For our purposes, the type code should be 2 (uncompressed RGB image)
        // or 3 (uncompressed black-and-white images).
        if (tgaFile.imageTypeCode != 2 && tgaFile.imageTypeCode != 3)
        {
            std::cout << "wrong tga format:" << filename << std::endl;
            fclose(filePtr);
            exit(0);
        }
        
        // Read 13 bytes of data we don't need.
        fread(&sintBad, sizeof(short int), 1, filePtr);
        fread(&sintBad, sizeof(short int), 1, filePtr);
        fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
        fread(&sintBad, sizeof(short int), 1, filePtr);
        fread(&sintBad, sizeof(short int), 1, filePtr);
        
        // Read the image's width and height.
        fread(&tgaFile.imageWidth, sizeof(short int), 1, filePtr);
        fread(&tgaFile.imageHeight, sizeof(short int), 1, filePtr);
        
        // Read the bit depth.
        fread(&tgaFile.bitCount, sizeof(unsigned char), 1, filePtr);
        
        // Read one byte of data we don't need.
        fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
        
        // Color mode -> 3 = BGR, 4 = BGRA.
        colorMode = tgaFile.bitCount / 8;
        imageSize = tgaFile.imageWidth * tgaFile.imageHeight * colorMode;
        
        // Allocate memory for the image data.
        tgaFile.imageData = (unsigned char*)malloc(sizeof(unsigned char)*imageSize);
        
        // Read the image data.
        fread(tgaFile.imageData, sizeof(unsigned char), imageSize, filePtr);
        
        // Change from BGR to RGB so OpenGL can read the image data.
        for (int imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode)
        {
            colorSwap = tgaFile.imageData[imageIdx];
            tgaFile.imageData[imageIdx] = tgaFile.imageData[imageIdx + 2];
            tgaFile.imageData[imageIdx + 2] = colorSwap;
        }
        
        fclose(filePtr);
        return tgaFile;
    }