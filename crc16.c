
#include "crc16.h"

static unsigned int crc_register = CRC16_INITIAL_VALUE;

/**
 * @brief Initializes the CRC16 calculation with a specified starting value.
 * 
 * This function sets the internal CRC register to the given initial value. It is typically called before starting a new CRC calculation sequence.
 * 
 * @param value The initial value to load into the CRC register
 *              (e.g. `CRC16_INITIAL_VALUE` or a custom seed).
 * 
 * @note This function must be called before any calls to @ref crc16_update().
 * @see crc16_update(), crc16_result(), CRC16_INITIAL_VALUE
 */
void crc16_init(unsigned int value)
{
	crc_register = value;
}

/**
 * @brief Updates the CRC16 value with a single data byte.
 * 
 * This function processes one byte of data and updates the internal CRC register according to the CRC16 algorithm defined by @ref CRC16_POLYNOM. The implementation follows the method described in the Microchip application note: [Atmel-8936 – CryptoAuth Data Zone CRC Calculation](https://ww1.microchip.com/downloads/en/Appnotes/Atmel-8936-CryptoAuth-Data-Zone-CRC-Calculation-ApplicationNote.pdf).
 * 
 * Each bit of the input byte is processed sequentially. If the current data bit differs from the most significant bit of the CRC register, the polynomial is applied via XOR to update the remainder.
 * 
 * @param data The 8-bit data value to include in the CRC16 computation.
 * 
 * @note Call @ref crc16_init() before using this function to ensure a valid initial state. Subsequent calls to this function extend the CRC over multi-byte data.  
 * 
 * @see crc16_init(), crc16_result(), CRC16_POLYNOM
 */
void crc16_update(unsigned char data)
{
	for (unsigned char shift_register=0x01; shift_register > 0x00; shift_register <<= 1)
	{
		unsigned char data_bit = 0;
		
		if (data & shift_register)
		{
			data_bit = 1;
		}
		
		unsigned char crc_bit = (crc_register>>15) & 1;
		crc_register <<= 1;
		
		if (data_bit != crc_bit)
		{
			crc_register ^= CRC16_POLYNOM;
		}
	}
}

/**
 * @brief Calculates a complete CRC16 checksum over a data buffer.
 * 
 * This function initializes the CRC register with the given start value and processes each byte in the provided data buffer using the CRC16 update routine. It performs a full CRC16 computation over a contiguous block of data.
 * 
 * @param initial  The initial CRC16 value (e.g. `CRC16_INITIAL_VALUE` or a protocol-specific seed).
 * @param data     Pointer to the data buffer to compute the CRC for.
 * @param length   Number of bytes in the data buffer.
 * 
 * @note This function combines @ref crc16_init() and repeated calls to @ref crc16_update() for each byte. After completion, the CRC result can be retrieved with @ref crc16_result() or @ref crc16_result_array().
 * 
 * @see crc16_init(), crc16_update(), crc16_result(), crc16_result_array()
 */
void crc16_calculate(unsigned char initial, unsigned char *data, unsigned char length)
{
	crc16_init(initial);
	
	for (unsigned char i=0; i < length; i++)
	{
		crc16_update(data[i]);
	}
}

/**
 * @brief Returns the current CRC16 result.
 * 
 * This function returns the 16-bit value currently stored in the internal CRC register. It can be called after one or more calls to @ref crc16_update() or after a complete block calculation using @ref crc16_calculate().
 * 
 * @return The 16-bit CRC result as an unsigned integer.
 * 
 * @note The result reflects the current CRC state and is not reset automatically. To start a new calculation, call @ref crc16_init() again.
 * 
 * @see crc16_calculate(), crc16_result_array(), crc16_init()
 */
unsigned int crc16_result(void)
{
	return crc_register;
}

/**
 * @brief Stores the CRC16 result as a two-byte array.
 * 
 * This function retrieves the current 16-bit CRC value (via @ref crc16_result()) and writes it into a two-byte array in little-endian order — the least significant byte first, followed by the most significant byte.
 * 
 * @param crc Pointer to a two-byte buffer that receives the CRC16 result. The array must have space for at least two bytes.
 * 
 * @note Useful when communicating CRC values as byte streams over serial interfaces or storing them in data packets. The byte order follows the convention used in common embedded CRC protocols.
 * 
 * @see crc16_result(), crc16_calculate(), crc16_update()
 */
void crc16_result_array(unsigned char *crc)
{
	crc[0] = (unsigned char)(crc16_result() & 0x00FF);
	crc[1] = (unsigned char)(crc16_result()>>8);
}
