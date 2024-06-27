//#include "stm32l4xx_hal_gpio.h"
#include "main.h"
#include "rx1276_ctrl.h"
#define RADIO_RESET_PORT            			GPIOD
#define RADIO_RESET_PIN             			GPIO_PIN_6
void SX1276Reset(void)
{
  GPIO_InitTypeDef initStruct = { 0 };
	__HAL_RCC_GPIOD_CLK_ENABLE();
  initStruct.Mode = GPIO_MODE_OUTPUT_PP;
  initStruct.Pull = GPIO_NOPULL;
  initStruct.Speed = GPIO_SPEED_HIGH;
  initStruct.Pin = RADIO_RESET_PIN;

  // Set RESET pin to 0
  HAL_GPIO_Init(RADIO_RESET_PORT, &initStruct);
  HAL_GPIO_WritePin(RADIO_RESET_PORT, RADIO_RESET_PIN, GPIO_PIN_RESET);

  // Wait 1 ms
  HAL_Delay(1);

  // Configure RESET as input
  initStruct.Mode = GPIO_NOPULL;
  HAL_GPIO_Init(RADIO_RESET_PORT, &initStruct);

  // Wait 6 ms
  HAL_Delay(6);
	__HAL_RCC_GPIOD_CLK_DISABLE();
}

/* SPI2 init function */
static uint32_t SpiFrequency( uint32_t hz )
{
  uint32_t divisor = 0;
  uint32_t SysClkTmp = SystemCoreClock;
  uint32_t baudRate;
  
  while( SysClkTmp > hz)
  {
    divisor++;
    SysClkTmp= ( SysClkTmp >> 1);
    
    if (divisor >= 7)
      break;
  }
  
  baudRate =((( divisor & 0x4 ) == 0 )? 0x0 : SPI_CR1_BR_2  )| 
            ((( divisor & 0x2 ) == 0 )? 0x0 : SPI_CR1_BR_1  )| 
            ((( divisor & 0x1 ) == 0 )? 0x0 : SPI_CR1_BR_0  );
  
  return baudRate;
}

extern SPI_HandleTypeDef hspi2;
/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
//void MX_SPI2_Init(void)
int32_t MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */
  int32_t ret = MU_ERROR_NONE;

  hspi2.Instance  = SPI2;
  if (HAL_SPI_GetState(&hspi2) == HAL_SPI_STATE_RESET)
  {
    /* Init the SPI Msp */
    HAL_SPI_MspInit(&hspi2);

    /* Init the SPI */


  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;			//SPI_DATASIZE_4BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;								//SPI_NSS_HARD_OUTPUT;
  hspi2.Init.BaudRatePrescaler = SpiFrequency( 10000000 );			//SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
//  hspi2.Init.CRCPolynomial = 7;
//  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
//  hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;

	__HAL_RCC_SPI2_CLK_ENABLE();
	
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    //Error_Handler();
		ret = MU_ERROR_SPI_FAILURE;
  }
  /* USER CODE BEGIN SPI2_Init 2 */

	}
  return ret;
  /* USER CODE END SPI2_Init 2 */

}

int32_t MX_SPI2_DeInit(void)
{
//	hspi2.Instance = SPI2;
//	HAL_SPI_DeInit(&hspi2);
	  int32_t ret = MU_ERROR_SPI_FAILURE;

//#if (USE_HAL_SPI_REGISTER_CALLBACKS == 0)
  HAL_SPI_MspDeInit(&hspi2);
//#endif

  if (HAL_SPI_DeInit(&hspi2) == HAL_OK)
  {
    ret = MU_ERROR_NONE;
  }
	
  return ret;
}
	
//void SX1276SetSleep( void )
//{
//    SX1276SetOpMode( RF_OPMODE_SLEEP );

//    // Disable TCXO radio is in SLEEP mode
//    Sx_Board_SetXO( RESET );
//}
#define TIMEOUT_DURATION 10000
#define MU_ERROR_UNKNOWN_FAILURE        -6

/**
  * @brief  Send and Receive data to/from SPI BUS (Full duplex)
  * @param  pData: Data
  * @param  len: Length of data in byte
  * @retval BSP status
  */
int32_t RADIO_SPI_SendRecv(uint8_t *pTxData, uint8_t *pRxData, uint16_t len)
{
  int32_t ret = MU_ERROR_UNKNOWN_FAILURE;

  if (HAL_SPI_TransmitReceive(&hspi2, pTxData, pRxData, len, TIMEOUT_DURATION) == HAL_OK)
  {
    ret = len;
  }
  return ret;
}

uint16_t SX1276_SendRecv(uint16_t txData)
{
  uint16_t rxData ;

  /*RADIO_SPI_SendRecv(( uint8_t * ) &txData, ( uint8_t* ) &rxData, 1);*/
  RADIO_SPI_SendRecv((uint8_t *) &txData, (uint8_t *) &rxData, 1);

  return rxData;
}

#define RADIO_NSS_PORT              			GPIOB
#define RADIO_NSS_PIN               			GPIO_PIN_9
void SX1276ReadBuffer( uint32_t addr, uint8_t *buffer, uint8_t size )
{
    uint8_t i;

    //NSS = 0;
    HAL_GPIO_WritePin(RADIO_NSS_PORT, RADIO_NSS_PIN, GPIO_PIN_RESET);

    SX1276_SendRecv( addr & 0x7F );

    for( i = 0; i < size; i++ )
    {
        buffer[i] = SX1276_SendRecv( 0 );
    }

    //NSS = 1;
    HAL_GPIO_WritePin(RADIO_NSS_PORT, RADIO_NSS_PIN, GPIO_PIN_SET);
}

void SX1276WriteBuffer( uint32_t addr, uint8_t *buffer, uint8_t size )
{
    uint8_t i;

    //NSS = 0;
    HAL_GPIO_WritePin(RADIO_NSS_PORT, RADIO_NSS_PIN, GPIO_PIN_RESET);

    SX1276_SendRecv( addr | 0x80 );
    for( i = 0; i < size; i++ )
    {
        SX1276_SendRecv( buffer[i] );
    }

    //NSS = 1;
    HAL_GPIO_WritePin(RADIO_NSS_PORT, RADIO_NSS_PIN, GPIO_PIN_SET);
}
uint8_t SX1276Read( uint32_t addr )
{
    uint8_t data;
    SX1276ReadBuffer( addr, &data, 1 );
    return data;
}

void SX1276Write( uint32_t addr, uint8_t data )
{
    SX1276WriteBuffer( addr, &data, 1 );
}

#define REG_OPMODE                                  0x01
#define RF_OPMODE_MASK                              0xF8
#define RF_OPMODE_SLEEP                             0x00

void SX1276SetSleep(void)
{
	SX1276Write( REG_OPMODE, ( SX1276Read( REG_OPMODE ) & RF_OPMODE_MASK ) | RF_OPMODE_SLEEP );
}

int32_t forev;
int32_t SX1276ReadOpmode(void)
{
	forev = (int32_t) SX1276Read( REG_OPMODE );
	return forev;
}
#include "sx1276Regs-Fsk.h"
#include "sx1276Regs-LoRa.h"

#define SX1276_PLL_STEP_SHIFT_AMOUNT                ( 8 )
#define SX1276_PLL_STEP_SCALED                      ( SX1276_XTAL_FREQ >> ( 19 - SX1276_PLL_STEP_SHIFT_AMOUNT ) )
#define SX1276_XTAL_FREQ                            32000000UL

static uint32_t SX1276ConvertPllStepToFreqInHz( uint32_t pllSteps )
{
    uint32_t freqInHzInt;
    uint32_t freqInHzFrac;
    
    // freqInHz = pllSteps * ( SX1276_XTAL_FREQ / 2^19 )
    // Get integer and fractional parts of the frequency computed with a PLL step scaled value
    freqInHzInt = pllSteps >> SX1276_PLL_STEP_SHIFT_AMOUNT;
    freqInHzFrac = pllSteps - ( freqInHzInt << SX1276_PLL_STEP_SHIFT_AMOUNT );
    
    // Apply the scaling factor to retrieve a frequency in Hz (+ ceiling)
    return freqInHzInt * SX1276_PLL_STEP_SCALED + 
           ( ( freqInHzFrac * SX1276_PLL_STEP_SCALED + ( 128 ) ) >> SX1276_PLL_STEP_SHIFT_AMOUNT );
}

static uint32_t SX1276ConvertFreqInHzToPllStep( uint32_t freqInHz )
{
    uint32_t stepsInt;
    uint32_t stepsFrac;

    // pllSteps = freqInHz / (SX1276_XTAL_FREQ / 2^19 )
    // Get integer and fractional parts of the frequency computed with a PLL step scaled value
    stepsInt = freqInHz / SX1276_PLL_STEP_SCALED;
    stepsFrac = freqInHz - ( stepsInt * SX1276_PLL_STEP_SCALED );
    
    // Apply the scaling factor to retrieve a frequency in Hz (+ ceiling)
    return ( stepsInt << SX1276_PLL_STEP_SHIFT_AMOUNT ) + 
           ( ( ( stepsFrac << SX1276_PLL_STEP_SHIFT_AMOUNT ) + ( SX1276_PLL_STEP_SCALED >> 1 ) ) /
             SX1276_PLL_STEP_SCALED );
}
//typedef enum
//{
//    RF_IDLE = 0,   //!< The radio is idle
//    RF_RX_RUNNING, //!< The radio is in reception state
//    RF_TX_RUNNING, //!< The radio is in transmission state
//    RF_CAD,        //!< The radio is doing channel activity detection
//}RadioState_t;
//typedef enum
//{
//    MODEM_FSK = 0,
//    MODEM_LORA,
//}RadioModems_t;

SX1276_t SX1276;
void SX1276SetChannel( uint32_t freq )
{
    uint32_t freqInPllSteps = SX1276ConvertFreqInHzToPllStep( freq );

    SX1276.Settings.Channel = freq;

    SX1276Write( REG_FRFMSB, ( uint8_t )( ( freqInPllSteps >> 16 ) & 0xFF ) );
    SX1276Write( REG_FRFMID, ( uint8_t )( ( freqInPllSteps >> 8 ) & 0xFF ) );
    SX1276Write( REG_FRFLSB, ( uint8_t )( freqInPllSteps & 0xFF ) );
}

static void RxChainCalibration( void )
{
    uint8_t regPaConfigInitVal;
    uint32_t initialFreq;

    // Save context
    regPaConfigInitVal = SX1276Read( REG_PACONFIG );

    initialFreq = SX1276ConvertPllStepToFreqInHz( ( ( ( uint32_t )SX1276Read( REG_FRFMSB ) << 16 ) |
                                                    ( ( uint32_t )SX1276Read( REG_FRFMID ) << 8 ) |
                                                    ( ( uint32_t )SX1276Read( REG_FRFLSB ) ) ) );

    // Cut the PA just in case, RFO output, power = -1 dBm
    SX1276Write( REG_PACONFIG, 0x00 );

    // Launch Rx chain calibration for LF band
    SX1276Write( REG_IMAGECAL, ( SX1276Read( REG_IMAGECAL ) & RF_IMAGECAL_IMAGECAL_MASK ) | RF_IMAGECAL_IMAGECAL_START );
    while( ( SX1276Read( REG_IMAGECAL ) & RF_IMAGECAL_IMAGECAL_RUNNING ) == RF_IMAGECAL_IMAGECAL_RUNNING )
    {
    }

    // Sets a Frequency in HF band
    SX1276SetChannel( 868000000 );

    // Launch Rx chain calibration for HF band
    SX1276Write( REG_IMAGECAL, ( SX1276Read( REG_IMAGECAL ) & RF_IMAGECAL_IMAGECAL_MASK ) | RF_IMAGECAL_IMAGECAL_START );
    while( ( SX1276Read( REG_IMAGECAL ) & RF_IMAGECAL_IMAGECAL_RUNNING ) == RF_IMAGECAL_IMAGECAL_RUNNING )
    {
    }

    // Restore context
    SX1276Write( REG_PACONFIG, regPaConfigInitVal );
    SX1276SetChannel( initialFreq );
}

//typedef enum
//{
//    MODEM_FSK = 0,
//    MODEM_LORA,
//}RadioModems_t;

typedef struct
{
    RadioModems_t Modem;
    uint8_t       Addr;
    uint8_t       Value;
}RadioRegisters_t;

#define RADIO_INIT_REGISTERS_VALUE                \
{                                                 \
    { MODEM_FSK , REG_LNA                , 0x23 },\
    { MODEM_FSK , REG_RXCONFIG           , 0x1E },\
    { MODEM_FSK , REG_RSSICONFIG         , 0xD2 },\
    { MODEM_FSK , REG_AFCFEI             , 0x01 },\
    { MODEM_FSK , REG_PREAMBLEDETECT     , 0xAA },\
    { MODEM_FSK , REG_OSC                , 0x07 },\
    { MODEM_FSK , REG_SYNCCONFIG         , 0x12 },\
    { MODEM_FSK , REG_SYNCVALUE1         , 0xC1 },\
    { MODEM_FSK , REG_SYNCVALUE2         , 0x94 },\
    { MODEM_FSK , REG_SYNCVALUE3         , 0xC1 },\
    { MODEM_FSK , REG_PACKETCONFIG1      , 0xD8 },\
    /* FIFO threshold set to 32 (31+1) */         \
    { MODEM_FSK , REG_FIFOTHRESH         , 0x9F },\
    { MODEM_FSK , REG_IMAGECAL           , 0x02 },\
    { MODEM_FSK , REG_DIOMAPPING1        , 0x00 },\
    { MODEM_FSK , REG_DIOMAPPING2        , 0x30 },\
    { MODEM_LORA, REG_LR_PAYLOADMAXLENGTH, 0x40 },\
}

const RadioRegisters_t RadioRegsInit[] = RADIO_INIT_REGISTERS_VALUE;


void SX1276SetModem( RadioModems_t modem )
{
    if( ( SX1276Read( REG_OPMODE ) & RFLR_OPMODE_LONGRANGEMODE_ON ) != 0 )
    {
        SX1276.Settings.Modem = MODEM_LORA;
    }
    else
    {
        SX1276.Settings.Modem = MODEM_FSK;
    }

    if( SX1276.Settings.Modem == modem )
    {
        return;
    }

    SX1276.Settings.Modem = modem;
    switch( SX1276.Settings.Modem )
    {
    default:
    case MODEM_FSK:
				SX1276SetSleep();
        //SX1276SetOpMode( RF_OPMODE_SLEEP );
        SX1276Write( REG_OPMODE, ( SX1276Read( REG_OPMODE ) & RFLR_OPMODE_LONGRANGEMODE_MASK ) | RFLR_OPMODE_LONGRANGEMODE_OFF );

        SX1276Write( REG_DIOMAPPING1, 0x00 );
        SX1276Write( REG_DIOMAPPING2, 0x30 ); // DIO5=ModeReady
        break;
    case MODEM_LORA:
				SX1276SetSleep();
        // SX1276SetOpMode( RF_OPMODE_SLEEP );
        SX1276Write( REG_OPMODE, ( SX1276Read( REG_OPMODE ) & RFLR_OPMODE_LONGRANGEMODE_MASK ) | RFLR_OPMODE_LONGRANGEMODE_ON );

        SX1276Write( REG_DIOMAPPING1, 0x00 );
        SX1276Write( REG_DIOMAPPING2, 0x00 );
        break;
    }
}

#define RADIO_WAKEUP_TIME                           2 // [ms]
#define BOARD_WAKEUP_TIME  0 // no TCXO
uint32_t SX1276Init( void )
{
    uint8_t i;

    // Initialize driver timeout timers
    SX1276Reset( );

    RxChainCalibration( );

    //SX1276SetOpMode( RF_OPMODE_SLEEP );
		SX1276SetSleep();

    //Sx_Board_IoIrqInit( DioIrq );

    for( i = 0; i < sizeof( RadioRegsInit ) / sizeof( RadioRegisters_t ); i++ )
    {
        SX1276SetModem( RadioRegsInit[i].Modem );
        SX1276Write( RadioRegsInit[i].Addr, RadioRegsInit[i].Value );
    }

    SX1276SetModem( MODEM_FSK );

    //SX1276.Settings.State = RF_IDLE;

    return BOARD_WAKEUP_TIME + RADIO_WAKEUP_TIME;
}

void antSwitch(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOE_CLK_ENABLE();
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;		//GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Pin = GPIO_PIN_11;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
	
	__HAL_RCC_GPIOE_CLK_DISABLE(); 
}

