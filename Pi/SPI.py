#Raspberry Pi SPI testing, Chandler Keep, 06/02/2021
import spidev;
#SPI bus 0 pins 
sMosi = 19;
sMiso = 21;
sClck = 23;
sCs = 24;
#Using SPI0
spi_bus = 0;
#SPI secondary
spi_device = 0;
#SPI speed
sMhz = 4000000;

def sendData():
    data = 0x80;
    receive = spi.transfer(data);
    #Checks response
    receive = spi.transfer(data);
    rdata = receive[0];
    if(rdata != 0x80):
        print("rip");
        quit();
    else:
        print("Yay");
        quit();

spi = spidev.SpiDev();
spi.open(spi_bus, 0);
#Set speed to 4Mhz (same as microbit comm)
spi.max_speed_hz = sMhz;







































































    
    loop();