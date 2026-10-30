#include<stdio.h>
#include<stdlib.h>

// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_library/stb_image.h"

// #define STB_IMAGE_WRITE_IMPLEMENTATION
// #include "stb_library/stb_image_write.h"

// #define STB_TRUETYPE_IMPLEMENTATION
// #include "stb_library/stb_truetype.h"
int main()
{
    FILE *read_char = fopen("sample_out/try.txt", "r");// reading char(s) from try.txt
    if (read_char == NULL)
    {
        printf("Error in reading .txt file\n");
        exit(EXIT_FAILURE);
    }
    fseek(read_char, 0, SEEK_END);// read_char points to last index 
    long number_of_char = ftell(read_char);
    printf("%ld\n", number_of_char);// prints number of char(s) in try.txt
    rewind(read_char);// read_cahr points to index 0
    size_t sampling_canvas = number_of_char;
    char *sampling_canvas_array = malloc(number_of_char * sizeof(char));// allocating memmory for 
    if (sampling_canvas_array == NULL) 
    {
        printf("Memory allocation failed\n");
        fclose(read_char);
        exit(EXIT_FAILURE);
    }    
    for (int i = 0; i < f; i++)
        fscanf(read_char, "%c", &sampling_canvas_array[i]);
    for (int j = 0; j < f - 1; j++)
        printf("%c", sampling_canvas_array[j]);
    FILE *font = fopen("arialfont.ttf","rb");
    if(!font)
        printf("Could not open the font file\n");
    fseek(font, 0,SEEK_END);
    long font_size = ftell(font);
    fseek(font , 0, SEEK_SET);
    printf("%ld", font_size);
    
    fclose(read_char);
    free(sampling_canvas_array);
}