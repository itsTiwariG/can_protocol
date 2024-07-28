#define CAN_PROTOCOL_H

#include <stdint.h>

// Define CAN register addresses
#define CAN_BASE_ADDRESS    (0x40006400UL)
#define CAN_MCR_OFFSET      (0x00UL)
#define CAN_MSR_OFFSET      (0x04UL)
#define CAN_TSR_OFFSET      (0x08UL)
#define CAN_RF0R_OFFSET     (0x0CUL)
#define CAN_RF1R_OFFSET     (0x10UL)
#define CAN_BTR_OFFSET      (0x1CUL)
#define CAN_TI0R_OFFSET     (0x180UL)
#define CAN_TDT0R_OFFSET    (0x184UL)
#define CAN_TDL0R_OFFSET    (0x188UL)
#define CAN_TDH0R_OFFSET    (0x18CUL)
#define CAN_RI0R_OFFSET     (0x1B0UL)
#define CAN_RDT0R_OFFSET    (0x1B4UL)
#define CAN_RDL0R_OFFSET    (0x1B8UL)
#define CAN_RDH0R_OFFSET    (0x1BCUL)

// CAN register struct
typedef struct {
    volatile uint32_t MCR;
    volatile uint32_t MSR;
    volatile uint32_t TSR;
    volatile uint32_t RF0R;
    volatile uint32_t RF1R;
    volatile uint32_t RESERVED0[2];
    volatile uint32_t BTR;
    volatile uint32_t RESERVED1[88];
    volatile uint32_t TI0R;
    volatile uint32_t TDT0R;
    volatile uint32_t TDL0R;
    volatile uint32_t TDH0R;
    volatile uint32_t RESERVED2[4];
    volatile uint32_t RI0R;
    volatile uint32_t RDT0R;
    volatile uint32_t RDL0R;
    volatile uint32_t RDH0R;
} CAN_TypeDef;

#define CAN ((CAN_TypeDef *) CAN_BASE_ADDRESS)

// CAN message structure
typedef struct {
    uint32_t id;        // Message ID
    uint8_t data[8];    // Data bytes
    uint8_t length;     // Data length (0-8)
} CAN_Message;

// Function prototypes
void CAN_Init(void);
void CAN_Transmit(CAN_Message *message);
void CAN_Receive(CAN_Message *message);

//#endif /* CAN_PROTOCOL_H */
