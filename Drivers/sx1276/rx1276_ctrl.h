#include <stdbool.h>

//void MX_SPI2_Init(void);
int32_t MX_SPI2_Init(void);
//void MX_SPI2_DeInit(void);
int32_t MX_SPI2_DeInit(void);
void SX1276Reset(void);
void SX1276SetSleep(void);
uint32_t SX1276Init( void );
int32_t SX1276ReadOpmode(void);
uint8_t SX1276Read( uint32_t addr );
void SX1276Write( uint32_t addr, uint8_t data );

typedef enum
{
    RF_IDLE = 0,   //!< The radio is idle
    RF_RX_RUNNING, //!< The radio is in reception state
    RF_TX_RUNNING, //!< The radio is in transmission state
    RF_CAD,        //!< The radio is doing channel activity detection
}RadioState_t;

typedef enum
{
    MODEM_FSK = 0,
    MODEM_LORA,
}RadioModems_t;

typedef struct
{
    int8_t   Power;
    uint32_t Fdev;
    uint32_t Bandwidth;
    uint32_t BandwidthAfc;
    uint32_t Datarate;
    uint16_t PreambleLen;
    bool     FixLen;
    uint8_t  PayloadLen;
    bool     CrcOn;
    bool     IqInverted;
    bool     RxContinuous;
    uint32_t TxTimeout;
    uint32_t RxSingleTimeout;
}RadioFskSettings_t;
typedef struct
{
    uint8_t  PreambleDetected;
    uint8_t  SyncWordDetected;
    int8_t   RssiValue;
    int32_t  AfcValue;
    uint8_t  RxGain;
    uint16_t Size;
    uint16_t NbBytes;
    uint8_t  FifoThresh;
    uint8_t  ChunkSize;
}RadioFskPacketHandler_t;
typedef struct
{
    int8_t   Power;
    uint32_t Bandwidth;
    uint32_t Datarate;
    bool     LowDatarateOptimize;
    uint8_t  Coderate;
    uint16_t PreambleLen;
    bool     FixLen;
    uint8_t  PayloadLen;
    bool     CrcOn;
    bool     FreqHopOn;
    uint8_t  HopPeriod;
    bool     IqInverted;
    bool     RxContinuous;
    uint32_t TxTimeout;
    bool     PublicNetwork;
}RadioLoRaSettings_t;
typedef struct
{
    int8_t SnrValue;
    int16_t RssiValue;
    uint8_t Size;
}RadioLoRaPacketHandler_t;

typedef struct
{
    RadioState_t             State;
    RadioModems_t            Modem;
    uint32_t                 Channel;
    RadioFskSettings_t       Fsk;
    RadioFskPacketHandler_t  FskPacketHandler;
    RadioLoRaSettings_t      LoRa;
    RadioLoRaPacketHandler_t LoRaPacketHandler;
}RadioSettings_t;

typedef struct SX1276_s
{
    uint8_t       RxTx;
    RadioSettings_t Settings;
}SX1276_t;
extern SX1276_t SX1276;

#define RADIO_DELAY_MS                          HAL_Delay

void SX1276SetModem( RadioModems_t modem );

typedef enum
{
  CONF_RFO_LP_HP = 0,
  CONF_RFO_LP = 1,
  CONF_RFO_HP = 2,
  CONF_RFO_LF = 3,
} TxConfig_TypeDef;

uint32_t SX1276ConvertFreqInHzToPllStep( uint32_t freqInHz );
void antSwitch(void);

#define SX1276_XTAL_FREQ                            32000000UL

void SX1276WriteBuffer( uint32_t addr, uint8_t *buffer, uint8_t size );
#define RADIO_MEMCPY8( dest, src, size )        UTIL_MEM_cpy_8( dest, src, size )
#define RX_TX_BUFFER_SIZE                           256

#define MU_ERROR_NONE                    0
#define MU_ERROR_SPI_FAILURE            -8
