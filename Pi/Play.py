#Raspberry Pi Arcade screen, Chandler Keep, 06/02/2021
import pygame;
import SPI;
import time;

spiHandle = SPI.Handler();
pygame.init();
window = pygame.display.set_mode((360, 240));

run = True;
while run:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False;

    window.fill(0);
    #Fetech reference to display pixel_array to draw
    pixel_array = pygame.PixelArray(window);
    
    #Edit each pixel
    for x in range(len(pixel_array)):
        for y in range(len(pixel_array[x])):
            color = (spiHandle.sendData()[0], 0, 0);
            pixel_array[x, y] = color;
        break;
    pixel_array.close();
    pygame.display.flip();

pygame.quit();
exit();