#include<stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

// optimizing code, shortening varibale names ;|

unsigned char * resize_img = NULL;
int pixel_index = 0;
int tone;

void image_generator(int red_count, int green_count, int blue_count)
{
    float weight_red = 0.299, weight_green = 0.587, weight_blue = 0.114;
    int lumin = (red_count * weight_red + green_count * weight_green + blue_count * weight_blue) / 4;
    for (int i = 0; i < tone; i++)
    { 
        // fix division my 0!!!
        int upper_limit = (i == tone -1) ? 255 : (i + 1) * 255 / tone;
        int lower_limit = i * 255 / tone;
        int match = (i == tone -1) ? (lumin >= lower_limit && lumin <= upper_limit) : (lumin >= lower_limit && lumin < upper_limit);
        if (match)
        {
            int scaled_value =  i * 255 / (tone - 1);
            resize_img[pixel_index + 0] = scaled_value;
            resize_img[pixel_index + 1] = scaled_value;
            resize_img[pixel_index + 2] = scaled_value;
            break;
        }
    }
    pixel_index = pixel_index + 3;
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
    unsigned char *data = stbi_load("sample_in/me.jpg", &width, &height, &channels, 0);
    int new_width = width / 2;
    int new_height = height / 2;
    size_t resize_img_size = new_width * new_height * channels;
    resize_img = malloc(resize_img_size);
    printf("Enter output tone (through 1 - 10)\n");
    scanf("%d", &tone);
    if (data == NULL)
    {
        printf("Error in loading image\n");
        exit(EXIT_FAILURE);
    }
    printf("Loaded image of width %d pixels, height %d pixels & %d channels\n", width, height, channels);
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
    stbi_write_png("sample_out/me_test8.png", new_width, new_height, channels, resize_img, new_width * channels);
    stbi_image_free(data);
    free(resize_img);
    return 0;
}

// 4th iteration, image generator, 2st iterataion (does not work well for boundary conditions)

    // for (int i = 0; i < tone; i++)
    // { 
    //     if (lumin >= i * 255 / tone && lumin < (i + 1) * 255 / tone )
    //     {
    //         int scaled_value =  i * 255/(tone - 1);
    //         resize_img[pixel_index + 0] = scaled_value;
    //         resize_img[pixel_index + 1] = scaled_value;
    //         resize_img[pixel_index + 2] = scaled_value;
    //     }
    // }

// 4th iteration, image generator, 1st iterataion (hard coded values XX!)

    // if (tone == 2 ) // binarization (dual tone)
    // {         
    //     if (lumin >= 0 && lumin < 128)
    //     {
    //         resize_img[pixel_index + 0] = 0;
    //         resize_img[pixel_index + 1] = 0;
    //         resize_img[pixel_index + 2] = 0;
    //     }
    //     else if (lumin >= 128 && lumin <= 255)  
    //     {
    //         resize_img[pixel_index + 0] = 255;
    //         resize_img[pixel_index + 1] = 255;
    //         resize_img[pixel_index + 2] = 255;
    //     }
    // }
    // else if (tone == 4) // quantization (quad tone)
    // {   
    //     if (lumin >= 0 && lumin < 1 * 255 / tone)
    //     {
    //         resize_img[pixel_index + 0] = 0 * 255/(tone - 1);//0 all three
    //         resize_img[pixel_index + 1] = 0 * 255/(tone - 1);
    //         resize_img[pixel_index + 2] = 0 * 255/(tone - 1);
    //     }
    //     else if (lumin >= 1 * 255 / tone && lumin < 2 * 255 / tone)
    //     {
    //         resize_img[pixel_index + 0] = 1 * 255/(tone - 1);// 85 all three
    //         resize_img[pixel_index + 1] = 1 * 255/(tone - 1);
    //         resize_img[pixel_index + 2] = 1 * 255/(tone - 1);
    //     }
    //     else if (lumin >= 2 * 255 / tone && lumin < 3 * 255 / tone)
    //     {
    //         resize_img[pixel_index + 0] = 2 * 255/(tone - 1);// 170 all three
    //         resize_img[pixel_index + 1] = 2 * 255/(tone - 1);
    //         resize_img[pixel_index + 2] = 2 * 255/(tone - 1);
    //     }
    //     else if (lumin >= 3 * 255 / tone && lumin <= 4 * 255 / tone)
    //     {
    //         resize_img[pixel_index + 0] = 3 * 255/ (tone - 1);// 255 all three
//         resize_img[pixel_index + 1] = 3 * 255/ (tone - 1);
//         resize_img[pixel_index + 2] = 3 * 255/ (tone - 1);
//     }
// }
    
// 3rd iteration, finally getting somwhere evne though errors, too much reassignment, will cause memmory problems

// for (int y = 0; y <= height; y = y + 2)
// {   
//     for (int x = 0, h = 0; h <= width; h = h + 6)
//     {
//         x = h;
//         unsigned char * top_left = &data[(width * y + x) * channels];
//         x = x + 1;
//         unsigned char * top_right = &data[(width * y + x) * channels];
//         y = y + 1;
//         x = x - 1;
//         unsigned char * bottom_left = &data[(width * y + x) * channels];
//         x = x + 1;
//         unsigned char * bottom_right = &data[(width * y + x) * channels];
//         y = y - 1;
//         x  = x - 1;
//     }
// }

// 2nd iteration, too complicated, bs 

// for (int y = 0; y <= height; y = y + 2)
// {
//  for (int x = 0, x1 = 0; x1 * 2 <= width; x = x + 2) // maybe have to create another var to fix x
//  {
//     x1 = x1 + 1;
//   for (int u = 0 ; u < 4; x++)
//   {
//     u++;

//    int index = (width * (y + 0) +(x + 0)) * channels;
   
//    unsigned char r = data[index];
//    unsigned char g = data[index + 1];
//    unsigned char b = data[index + 2];
//    if (u == 2)
//    {
//      y = y + 1;// check if i can write y++ or x--
//      x = x - 2;
//    } else if (u == 4)
//    {
//     y = 0;
//     x = 0;
//    }
//   }
//  }
// }

// 1st iterartion, not working properly, bottom half of output image is glitched out

//  for (unsigned char * original_image = img, * resize_image = resize_img;
//         original_image != img + resize_img_size;
//         original_image += channels * 2, resize_image += channels * 1)

//     {
//         color = color_converter(original_image, original_image + 1, original_image + 2,
//                                 original_image + 3, original_image + 4, original_image + 5,
//                                 (original_image + (width * 3)), (original_image + (width) * 3 + 1), (original_image + (width) * 3 + 2),
//                                 (original_image + (width * 3) + 3), (original_image + (width) * 3 + 4), (original_image + (width) * 3 + 5));
//         if (color == 0)
//         {
//             *resize_image = 0;
//             *(resize_image + 1) = 0;
//             *(resize_image + 2) = 0;
//         }
//         else if (color == 1)
//         {
//             *resize_image = 85;
//             *(resize_image + 1) = 85;
//             *(resize_image + 2) = 85;
//         }
//         else if (color == 2)
//         {
//             *resize_image = 170;
//             *(resize_image + 1) = 170;
//             *(resize_image + 2) = 170;
//         }
//         else 
//         { 
//             *resize_image = 25;
//             *(resize_image + 1) = 255;
//             *(resize_image + 2) = 255;

//         }

//         if (channels == 4)
//             exit(EXIT_FAILURE);
        
//     }

// int color_converter(unsigned char * red1, unsigned char * green1, unsigned char * blue1,
//                     unsigned char * red2, unsigned char * green2, unsigned char * blue2,
//                     unsigned char * red3, unsigned char * green3, unsigned char * blue3,
//                     unsigned char * red4, unsigned char * green4, unsigned char * blue4);

// yes i write pointers like that ;)
// int color_converter(unsigned char * red1, unsigned char * green1, unsigned char * blue1,
//                     unsigned char * red2, unsigned char * green2, unsigned char * blue2,
//                     unsigned char * red3, unsigned char * green3, unsigned char * blue3,
//                     unsigned char * red4, unsigned char * green4, unsigned char * blue4)
// {
//     int y, y1, y2, y3, y4;
//     y1 = *red1 * 0.299 + *green1 * 0.587 + *blue1 * 0.114;
//     y2 = *red2 * 0.299 + *green2 * 0.587 + *blue2 * 0.114;
//     y3 = *red3 * 0.299 + *green3 * 0.587 + *blue3 * 0.114;
//     y4 = *red4 * 0.299 + *green4 * 0.587 + *blue4 * 0.114;
//     y = (y1 + y2 + y3 + y4)/4;
//     if (y >= 0 && y < 64)
//         return 0;
//     else if ( y >= 64 && y < 128)
//         return 1;
//     else if (y >= 128 && y < 192)
//         return 2;
//     else if (y >= 192 && y <= 255)
//         return 3;
// }

