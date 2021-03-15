//Raspberry Pi header configuration, 08/02/2021, Chandler Samuel Keep

#include "jdsimple.h"

void setupSPI(void);
void setupDMA(void);
void gpioConfig(void);
void display(void);
void rpiHandler(void);
void rpi_xfer(const void *send, const void *receive, uint32_t numbytes);
void DMA1_Channel4_5_IRQHandler(void);
void prexfer(void);
void setupReceive(const void *receive, uint32_t numbytes);

#define hdma_spi2_rx LL_DMA_CHANNEL_4
#define hdma_spi2_tx LL_DMA_CHANNEL_5