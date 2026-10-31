#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_library/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_library/stb_image_write.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_library/stb_truetype.h"
int main(void)
{
    FILE *read_char = fopen("sample_in/try.txt", "rb");//open txt file
    if (read_char == NULL)// fallback statement
    {
        printf("Error in reading .txt file\n");
        return EXIT_FAILURE;
    }

    fseek(read_char, 0, SEEK_END);// point read_char to the end the .txt file
    long number_of_char = ftell(read_char);// store the last last value of the that in number_of_char
    rewind(read_char);// point read_char to the begining of the array
    printf("%ld\n", number_of_char);// print number_of_char in .txt file

    char *text_array = malloc(number_of_char + 1);// allocate memory to store the txt file in heap that +! is for the \0 char
    if (text_array == NULL)// fallback statement
    {
        printf("Memory allocation failed\n");
        fclose(read_char);
        return EXIT_FAILURE;
    }

    size_t text_read = fread(text_array, sizeof(char), number_of_char, read_char);//text_read tells the no. of bytes read from the file, freaad (pointer of memory, size of individual element, no. of elements to read, the txt file)
    // above we are using fread to know the "true" size of the test array but not using it when malloc is because fread already needs the buffer (temp. storage) to exist
    text_array[text_read] = '\0'; // last elementof text_array is \0
    fclose(read_char);// close the txt file

    printf("%s", text_array);// print the text in the .txt file

    FILE *font_file = fopen("arialfont.ttf", "rb");// open the .ttf file
    if (!font_file)// fallback statement
    {
        printf("Could not open the font file\n");
        free(text_array);
        return EXIT_FAILURE;
    }

    fseek(font_file, 0, SEEK_END);// go to end of font_file
    long font_size = ftell(font_file);// saves the current (which is the last) position of font_file to font_size
    fseek(font_file, 0, SEEK_SET);// resets the position of font_file to the start
    printf("\nsize of arialfont.ttf in bytes %ld\n", font_size);// print size of .ttf file

    unsigned char *font_data = malloc(font_size);// allocate memory (size of font_file / value of font_size) for the .ttf file in heap
    if (font_data == NULL)// fallback statement
    {
        printf("Memory allocation failed for font\n");
        fclose(font_file);
        free(text_array);
        return EXIT_FAILURE;
    }

    size_t got = fread(font_data, 1, font_size, font_file);// got tells the size of font_file
    fclose(font_file);// close the font_file
    printf("bytes read: %zu\n", got);// bytes of the font_file

    if (got != (size_t)font_size)// fallback statement
    {
        printf("Short read on font file\n");
        free(font_data);
        free(text_array);
        return EXIT_FAILURE;
    }

    stbtt_fontinfo font;
    int offset = stbtt_GetFontOffsetForIndex(font_data, 0);
    int ok = stbtt_InitFont(&font, font_data, offset);
    printf("InitFont: %d\n", ok);   /* should be 1 */

    if (!ok)
    {
        free(font_data);
        free(text_array);
        return EXIT_FAILURE;
    }

    int ascent, descent, lineGap;
    stbtt_GetFontVMetrics(&font, &ascent, &descent, &lineGap);
    printf("%d %d %d\n", ascent, descent, lineGap);

    float scale = stbtt_ScaleForPixelHeight(&font, 32);
    int lineHeight = (int)((ascent - descent + lineGap) * scale);
    printf("lineHeight at 32px: %d\n", lineHeight);

    free(font_data);   /* must stay alive as long as `font` is used */
    free(text_array);
    return 0;
}
