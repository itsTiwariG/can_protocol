#include "can_header.h"
#include <stdio.h>

void CAN_Init(void);
void CAN_Transmit(CAN_Message *message);
void CAN_Receive(CAN_Message *message);

void CAN_Init(void) {
    
    CAN->MCR |= (1 << 0);          // Setting initialization mode
    while (CAN->MSR & (1 << 0));  // Initialization acknowledge
    
    CAN->BTR |= (5 << 0) | (2 << 16); // Time segment 1 = 2 and Baud rate prescaler = 5  {Configure CAN bit timing}
    
  
    CAN->MCR &= 0 << 0;         // Exit initialization mode
}


void CAN_Transmit(CAN_Message *message) {
    
    while (!(CAN->TSR & (1 << 0)));   // Wait until the last request (transmit or abort) has been performed.
    
    
    CAN->TI0R &= 0 << 2;              // set Standard identifier.
    CAN->TI0R |= message->id << 21;    // Standard identifier value (ID)
    
    
    CAN->TDT0R &= 0xF << 0;           // First set all values to zero 
    CAN->TDT0R |= message->length;   //set data length code {This field defines the number of data bytes a data frame contains or a remote frame request.}
    
    
    for (int i = 0; i < message->length; i++) {
        CAN->TDL0R |= message->data[i] << (8 * i);     // Copying the values to mailbox data low register
    }
    
    
    CAN->TI0R |= (1 << 0);        //Request transmission using mailbox identifier register
}


void CAN_Receive(CAN_Message *message) {
    
    if (CAN->RF0R & (1 << 3)) {       // In FIFO 0 register bit 4 bit is set by hardware when a new message has been received
        
        message->id = (CAN->RI0R >> 21) & 0x7FF;      //  get message ID from FIFO mailbox identifier register
        
        
        message->length = CAN->RDT0R & 0xF;           // Get message length from FIFO mailbox data length control and time stamp register
        
        
        for (int i = 0; i < message->length; i++) {
            message->data[i] = (CAN->RDL0R >> (8 * i)) & 0xFF;    //Copy the message to message->data
        }
        
        
        CAN->RF0R |= (1 << 5);       // Release FIFO 0 output mailbox. Bit 5 is set to release the output mailbox of the FIFO.
    }
}


int main(){
	
	CAN_Init();               //  Initialize CAN peripheral
	
	
	CAN_Message txMessage;    // Creating a CAN message data struct
	txMessage.id = 0x4; 
	txMessage.data[0] = 0xA; 
	txMessage.length = 1; 
	CAN_Transmit(&txMessage);  // Transmitt message
	
	
	
	
	

	CAN_Message rxMessage;   // Creating a CAN message data struct
	CAN_Receive(&rxMessage);  // Recieive message that transmitted
	for (int i = 0; i < rxMessage.length; i++) {
			printf("Received Data[%d]: %d\n", i, rxMessage.data[i]);      // Print Values 
	}
}






