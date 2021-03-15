//Raspberry Pi Handler for pxt-arcade Smart Shield, 08/03/2021, Chandler Samuel Keep
#include "rpi_flow.h"

jd_frame_t tempSend, tempRecv;

static inline bool DMA_HasFlag(DMA_TypeDef *DMAx, uint8_t ch, uint8_t flag) {
    return (DMAx->ISR & (1 << (4 * (ch - 1) + flag))) != 0;
}

void rpiHandler(){
    //Init SPI2
    setupSPI();
    //Init DMA channels
    setupDMA();
    //Handle Interrupts
    //Call on Display input & Sound
    //Call on controller receive
    setupReceive(&tempRecv, 8);
    tempSend.data[0] = 1;
    tempSend.data[1] = 2;
    tempSend.data[2] = 3;
    tempSend.data[3] = 4;
    tempSend.data[4] = 5;
    tempSend.data[5] = 6;
    tempSend.data[6] = 7;
    tempSend.data[7] = 8;
}

void prexfer(){
  uint8_t data[8] = {1, 2, 3, 4, 5, 6, 7, 8};
  rpi_xfer(&data, &tempRecv, sizeof(data));
}

void setupReceive(const void *receive, uint32_t numbytes){
  /* Reset the threshold bit */
    CLEAR_BIT(SPI2->CR2, SPI_CR2_LDMATX | SPI_CR2_LDMARX);
  // Reception setup
    LL_DMA_ConfigAddresses(DMA1, hdma_spi2_rx, (uint32_t) & (SPI2->DR), (uint32_t) receive,
                           LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
    LL_DMA_SetDataLength(DMA1, hdma_spi2_rx, 8);
    // Enable SPI
    LL_SPI_EnableDMAReq_RX(SPI2);
    LL_SPI_Enable(SPI2);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_4);
}

void rpi_xfer(const void *send, const void *receive, uint32_t numbytes){
  /* Reset the threshold bit */
    CLEAR_BIT(SPI2->CR2, SPI_CR2_LDMATX | SPI_CR2_LDMARX);
  // Reception setup
    LL_DMA_ConfigAddresses(DMA1, hdma_spi2_rx, (uint32_t) & (SPI2->DR), (uint32_t) receive,
                           LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
    LL_DMA_SetDataLength(DMA1, hdma_spi2_rx, numbytes);
  // Transfer setup
    LL_DMA_ConfigAddresses(DMA1, hdma_spi2_tx, (uint32_t) send, (uint32_t) & (SPI2->DR),
                           LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
    LL_DMA_SetDataLength(DMA1, hdma_spi2_tx, numbytes);
  // Enable SPI
    LL_SPI_EnableDMAReq_RX(SPI2);
    LL_SPI_EnableDMAReq_TX(SPI2);
    LL_SPI_Enable(SPI2);
    LL_DMA_EnableChannel(DMA1, hdma_spi2_rx);
    LL_DMA_EnableChannel(DMA1, hdma_spi2_tx);
}

void display(){

}

void input(){

}

/**
  * @brief This function handles DMA1 channel 4 and 5 interrupts.
  */
void DMA1_Channel4_5_IRQHandler(void)
{
    /* USER CODE BEGIN DMA1_Channel4_5_IRQn 0 */
    /* USER CODE END DMA1_Channel4_5_IRQn 0 */
    if (DMA_HasFlag(DMA1, LL_DMA_CHANNEL_4, DMA_ISR_TCIF1_Pos)) {
        LL_DMA_ClearFlag_GI4(DMA1);
        LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_4);
        LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_5);
        prexfer();
    } else if (DMA_HasFlag(DMA1, LL_DMA_CHANNEL_4, DMA_ISR_HTIF1_Pos)) {
        LL_DMA_ClearFlag_GI4(DMA1);
    }

}