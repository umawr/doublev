#include<stdio.h>
#include<stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_library/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_library/stb_image_write.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_library/stb_truetype.h"

int main()
{
    FILE *read_char = fopen("sample_in/try.txt", "r");// open try.txt
    if (read_char == NULL)// fallback statement
    {
        printf("Error in reading .txt file\n");
        exit(EXIT_FAILURE);
    }
    fseek(read_char, 0, SEEK_END);// read_char points to last index 
    long number_of_char = ftell(read_char);// initializes the read_char (which points to the last index)
    printf("%ld\n", number_of_char);// prints number of char(s) in try.txt
    rewind(read_char);// read_char points to index 0
    size_t sampling_canvas = number_of_char;
    char *text_array = malloc(number_of_char * sizeof(char));// allocating memmory for the text that has to be read from try.txt
    if (text_array == NULL)// fallback statement
    {
        printf("Memory allocation failed\n");
        fclose(read_char);
        exit(EXIT_FAILURE);
    }    
    for (int i = 0; i < number_of_char; i++)//read read_char into sampling_canvas_array
        fscanf(read_char, "%c", &text_array[i]);
    fclose(read_char);// close the file try.txr
    for (int j = 0; j < number_of_char - 1; j++)// print text_array
        printf("%c", text_array[j]);
    FILE *font_file = fopen("arialfont.ttf","rb");// open arialfont.ttf
    if(!font_file)// fallback statement
    {
        printf("Could not open the font file\n");
        return 1;
    }
    fseek(font_file, 0,SEEK_END);// point to the end of the arialfont.ttf file 
    long font_size = ftell(font_file);// save it to font_size
    fseek(font_file, 0, SEEK_SET);// point to index 0 of arialfont.ttf
    printf("\nsize of arialfont.ttf in bytes %ld", font_size);// print the size of arialfont.ttf

    unsigned char * font_data = malloc(font_size);// allocate memmory for the font file
    fread(font_data, 1, font_size, font_file);// pointer, size of individual element, total number of element(size of .ttf in bytes), source

    // stbtt_fontinfo font;// font_file holds the data (math) on how to font is printed
    // stbtt_InitFont(&font, font_data, 0);// parses through font_data and finds how (math) to write char(s)
    // float scale = stbtt_ScaleForPixelHeight(&font, 32);// scale the font size to 32px
    // int ascent, descent, lineGap;
    // stbtt_GetFontVMetrics(&font, &ascent, &descent, &lineGap);
    // printf("%d %d %d\n", ascent, descent, lineGap);
    // int lineHeight = (int)((ascent - descent + lineGap) * scale);// ??
    
    
    size_t got = fread(font_data, 1, sizeof(font_data), font_file);
    fseek(font_data, 0, SEEK_SET);// point to index 0 of arialfont.ttf
    printf("\nbytes read: %zu\n", got);      // should be around 770000
    fclose(font_file);
    
    stbtt_fontinfo font;
    int ok = stbtt_InitFont(&font, font_data, 0);
    printf("InitFont: %d\n", ok);          // should be 1
    
    int ascent, descent, lineGap;
    stbtt_GetFontVMetrics(&font, &ascent, &descent, &lineGap);
    printf("%d %d %d\n", ascent, descent, lineGap);
    
    
    fclose(font_file);// close font_file
    free(font_data);
    free(text_array);
}
