#include <stdio.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    unsigned char buffer[512];
	int firstJPEGFound = 0;
	int currentFileNumber = 1;
	char currentFilename[8];
	FILE* currentImg = NULL;

    while (fread(&buffer, 1, 512, inptr) == 512)
    {
		if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // start of a JPEG identified
			if (firstJPEGFound == 0)
			{
				firstJPEGFound = 1;
			}
			if (currentImg != NULL)
			{
				fclose(currentImg);
			}
			sprintf(currentFilename, "%03i.jpg", currentFileNumber++);
    		currentImg = fopen(currentFilename, "w");
			fwrite(buffer, 512, 1, currentImg);
        }
        else
        {
			if (firstJPEGFound == 0)
			{
				// no start of JPEG identified and no JPEG yet identified
				continue;
			}
			else
			{
				// continuation of an existing JPEG
				fwrite(buffer, 512, 1, currentImg);
			}
        }
    }

    // close infile
    fclose(inptr);

    // success
    return 0;
}