#Raspberry Pi SPI Main, Chandler Keep, 06/02/2021
from time import sleep;
import spidev;
#SPI bus 0 pins 
sMosi = 19;
sMiso = 21;
sClck = 23;
sCs = 24;
#Using SPI0
spi_bus = 0;
#SPI secondary CE
spi_device = 0;
#SPI speed on STM32f0 Bus
sMhz = 2400000;
global spi;

def response():
    #give time for response
    sleep(0.001);
    res = spi.readbytes(1);
    #Cycle buffer
    sleep(0.001);
    return res;

def sendData():
    data = [2];
    #Transfer bytes
    spi.xfer(data);
    #Retrieve response
    resp = response();
    print("received bytes " + str(resp));

spi = spidev.SpiDev();
#Disable chip select - only 1 secondary
#spi.no_cs;
spi.open(spi_bus, 0);
#Set speed to 4Mhz (same as microbit comm)
spi.max_speed_hz = sMhz;
while(True):
    sendData();
    #Enables 60 updates per second;
    sleep(1/60);


    