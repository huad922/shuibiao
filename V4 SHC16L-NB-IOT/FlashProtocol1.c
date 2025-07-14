//-------------------------------------------
// FUNCTION FOR FLASH PROGRAMMING A SINGLE BYTE
//
//    This function is called using LOAD button
//-------------------------------------------
void FlashByteProg (unsigned long int inCodeAddress, unsigned char *inData) {
    // Send the programming order
    _WBYTE_SFR(0x91, 0x01);
    
    // Send data to write into Code space
    _WNBYTES_CODE(inCodeAddress, inData, 1);
} /* End of FlashByteProg */



//-------------------------------------------
// FUNCTION FOR FLASH PROGRAMMING A SECTOR
//    OR SEVERAL CONSECUTIVE DATA
//
//    This function is called using LOAD button
//-------------------------------------------
void FlashSectorProg (unsigned long int inCodeAddress, unsigned char *inData, unsigned int inCount) {
    // Send the programming order
    _WBYTE_SFR(0x91, 0x01);

    // Send data to write into Code space
    _WNBYTES_CODE(inCodeAddress, inData, inCount);
} /* End of FlashSectorProg */


//-------------------------------------------
// FUNCTION FOR FLASH ERASE
//
//    This function is called using ERASE or LOAD buttons
//-------------------------------------------
void FlashErase (void) {
    unsigned char theData;

    // Send mass erase order
    _WBYTE_SFR(0x91, 0x03);

    // Send one dummy write into Code space (@0xA00000)
    // to kick off the mass erase order
    theData = 0xFF;
    _WNBYTES_CODE(0xFF0000, &theData, 1);

    // Wait for 100 ms
    _SLEEP(100);
} /* End of FlashErase */


//-------------------------------------------
// FUNCTION FOR FLASH SECTOR ERASE
//
//    This function is called by the BIRD Debug Software
//    to erase the sector corresponding to the given
//    address
//-------------------------------------------
void FlashSectorErase (unsigned long int inCodeAddress) {
    unsigned char theData;

    // Send sector erase order
    _WBYTE_SFR(0x91, 0x02);
    
    // Send one dummy write into Code space
    // to kick off the sector erase order
    theData = 0xFF;
    _WNBYTES_CODE(inCodeAddress, &theData, 1);
    
    // Wait for 20 ms
    _SLEEP(20);
} /* End of FlashSectorErase */


//-------------------------------------------
// FUNCTION FOR FLASH READ
//
//    This function is called to configure
//    the flash in read mode
//-------------------------------------------
void FlashSetupRead (void) {
    // No special order
} /* End of FlashSetupRead */

