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
#SPI speed
sMhz = 4000000;
global spi;

def sendData():
    data = [10, 20, 30, 40, 50, 60, 70, 80];
    received = spi.xfer3(data);
    print("received bytes " + str(received));

spi = spidev.SpiDev();
#Disable chip select - only 1 secondary
spi.no_cs;
spi.open(spi_bus, 0);
#Set speed to 4Mhz (same as microbit comm)
spi.max_speed_hz = sMhz;
while(True):
    print("Sending data");
    sendData();
    