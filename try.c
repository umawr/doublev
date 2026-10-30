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
    FILE *read_char = fopen("sample_out/try.txt", "r");// open try.txt
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
    char *sampling_canvas_array = malloc(number_of_char * sizeof(char));// allocating memmory for the output image
    if (sampling_canvas_array == NULL)// fallback statement
    {
        printf("Memory allocation failed\n");
        fclose(read_char);
        exit(EXIT_FAILURE);
    }    
    for (int i = 0; i < number_of_char; i++)//read read_char into sampling_canvas_array
        fscanf(read_char, "%c", &sampling_canvas_array[i]);
    fclose(read_char);// close the file try.txr
    for (int j = 0; j < number_of_char - 1; j++)// print sampling_canvas_array
        printf("%c", sampling_canvas_array[j]);
    FILE *font_file = fopen("arialfont.ttf","rb");// open arialfont.ttf
    if(!font_file)// fallback statement
        printf("Could not open the font file\n");
    fseek(font_file, 0,SEEK_END);// point to the end of the arialfont.ttf file 
    long font_size = ftell(font_file);// save it to font_size
    fseek(font_file , 0, SEEK_SET);// point to index 0 of arialfont.ttf
    printf("\n%ld", font_size);// print the size of arialfont.ttf
    
    free(sampling_canvas_array);
}
