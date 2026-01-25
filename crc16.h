/**
 * @file crc16.h
 * @brief Header file with declarations and macros for CRC16 checksum calculation.
 * 
 * This file provides function prototypes, type definitions, and constants for calculating and handling 16-bit CRC checksums. It supports configurable polynomial and initial values to adapt to different CRC16 implementations.
 * 
 * Available functions include initialization, incremental updates with data bytes, and retrieval of the final CRC result as integer or byte array.
 * 
 * @author g.raf
 * @date 2026-01-25
 * @version 1.0 Release
 * @copyright
 * Copyright (c) 2025 g.raf  
 * Released under the GPLv3 License. (see LICENSE in repository)
 * 
 * @note This file is part of a larger utility library and subject to the license specified in the repository. For updates and the complete revision history, see the GitHub repository.
 * 
 * @see https://github.com/0x007e/util-crc "CRC GitHub Repository"
 */

#ifndef CRC16_H_
#define CRC16_H_
	
	#ifndef CRC16_INITIAL_VALUE
		/**
		 * @def CRC16_INITIAL_VALUE
		 * @brief Default initial value for CRC16 calculation.
		 * 
		 * This constant specifies the starting value for the CRC16 shift register before processing any data. The default value `0x0000` is commonly used in standard CRC16 implementations, but other initial values (e.g. `0xFFFF`) may be required for specific protocols or checksum variants.
		 * 
		 * @note You can override this value before including this header to use a different initial CRC value.
		 * 
		 * @see CRC16_POLYNOM
		 */
		#define CRC16_INITIAL_VALUE 0x0000
	#endif

	#ifndef CRC16_POLYNOM
		/**
		 * @def CRC16_POLYNOM
		 * @brief Default polynomial used for CRC16 calculation.
		 * 
		 * This constant defines the generator polynomial for the CRC16 algorithm. The default value `0x8005` corresponds to the reversed polynomial \(x^{16} + x^{15} + x^2 + 1\), which is commonly used in standard CRC16 implementations.
		 * 
		 * You can override this value before including this header to use a custom polynomial.
		 * 
		 * @note The polynomial is represented without the leading coefficient bit.
		 * @see CRC16_INITIAL_VALUE
		 */
		#define CRC16_POLYNOM 0x8005
	#endif

	        void crc16_init(unsigned int value);
	        void crc16_update(unsigned char data);
	        void crc16_calculate(unsigned char initial, unsigned char *data, unsigned char length);
	unsigned int crc16_result(void);
	        void crc16_result_array(unsigned char *crc);
			
#endif /* CRC16_H_ */