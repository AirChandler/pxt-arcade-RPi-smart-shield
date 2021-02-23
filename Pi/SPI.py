#Raspberry Pi SPI Comms, Chandler Keep, 06/02/2021
from time import sleep;
import spidev;

class Handler:

    #SPI bus 0 pins 
    sMosi = 19;
    sMiso = 21;
    sClck = 23;
    sCs = 24;
    #Using SPI0
    global spi_bus;
    #SPI secondary CE
    global spi_device;
    #SPI speed on STM32f0 Bus
    global sMhz;
    global spi;
    global fps;
    global numBytes;
    fps = 60;
    spi_bus = 0;
    spi_device = 0;
    sMhz = 2400000;
    numBytes = 4;

    def __init__(self):
        self.spi = spidev.SpiDev();
        self.spi.open(spi_bus, spi_device);
        #Set speed to 4Mhz (same as microbit comm)
        self.spi.max_speed_hz = sMhz;

    def response(self):
        #give time for response
        #sleep(1/fps);
        res = self.spi.readbytes(numBytes);
        return res;

    def sendData(self):
        data = [1, 0, 0, 1];
        #Transfer bytes
        self.spi.xfer(data);
        #Retrieve response
        resp = self.response();
        print("received bytes " + str(resp));
        return resp;


    