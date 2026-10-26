#include<stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

// all under 47 semi-colons ; )
// optimizing code, shortening varibale names ;|

unsigned char * resize_img = NULL;
unsigned char * rasterize_img = NULL;
int pixel_index = 0;
int tone;
int scaled_value;
void image_rasterize()
{
    char ramp[] = {'@', '%', '#', '*', '+', ':', '.'};
    if (scaled_value == 0)
        printf("#");
    else
        printf(",");
}

void image_generator(int red_count, int green_count, int blue_count)
{
    float weight_red = 0.299, weight_green = 0.587, weight_blue = 0.114;
    int lumin = (red_count * weight_red + green_count * weight_green + blue_count * weight_blue) / 4;
    for (int i = 0; i < tone; i++)
    { 
        int upper_limit = (i == tone - 1) ? 255 : (i + 1) * 255 / tone;
        int lower_limit = i * 255 / tone;
        int match = (i == tone - 1) ? (lumin >= lower_limit && lumin <= upper_limit) : (lumin >= lower_limit && lumin < upper_limit);
        if (match)
        {
            scaled_value =  i * 255 / (tone - 1);
            resize_img[pixel_index + 0] = scaled_value;
            resize_img[pixel_index + 1] = scaled_value;
            resize_img[pixel_index + 2] = scaled_value;
            break;
        }
    }
    pixel_index = pixel_index + 3;
    image_rasterize();
}

void color_parser(unsigned char * top_left_pixel, unsigned char * top_rigth_pixel,
                    unsigned char * bottom_left_pixel, unsigned char * bottom_right_pixel)
{
    unsigned char red, green, blue;
    int red_count = 0, green_count = 0, blue_count = 0; 
    unsigned char *pixel_group[] = {top_left_pixel, top_rigth_pixel, bottom_left_pixel, bottom_right_pixel}; 
    for (int i = 0; i <= 3; i++)
    {
        red = pixel_group[i][0];
        red_count += red;
        green = pixel_group[i][1];
        green_count += green; 
        blue = pixel_group[i][2];
        blue_count += blue;
    }
    image_generator(red_count, green_count, blue_count);
}

int main(void)
{
    int width, height, channels;
    unsigned char *data = stbi_load("sample_in/apple100x.jpg", &width, &height, &channels, 0);
    int new_width = width / 2;
    int new_height = height / 2;
    size_t resize_img_size = new_width * new_height * channels;
    resize_img = malloc(resize_img_size);
    rasterize_img = malloc(resize_img_size);
    printf("Loaded image of widt    h %d pixels, height %d pixels & %d channels\n", width, height, channels);
    do 
    {
        printf("Enter output tone (through 2 - 255)\n");
        scanf("%d", &tone);
        if(tone == 1)
            printf("Enter a valid choice\n");
    } while (tone == 1 || tone <= 0 );
    if (data == NULL)
    {
        printf("Error in loading image\n");
        exit(EXIT_FAILURE);
    }
    for (int y = 0; y < height - 1; y = y + 2)
    {
        for (int x = 0; x < width - 1; x = x + 2)
        {   
            unsigned char * top_left = &data[(width * y + x) * channels];
            unsigned char * top_right = &data[(width * y + (x + 1)) * channels];
            unsigned char * bottom_left = &data[(width * (y + 1) + x) * channels];
            unsigned char * bottom_right = &data[(width * (y + 1) + (x + 1)) * channels];

            color_parser(top_left, top_right, bottom_left, bottom_right);
        }
    }
    stbi_write_png("sample_out/apple_test.png", new_width, new_height, channels, resize_img, new_width * channels);
    stbi_write_png("sample_out/apple_test_ascii.png", new_width, new_height, channels, rasterize_img, new_width * channels);
    stbi_image_free(data);
    free(resize_img);
    return 0;
}
