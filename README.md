[![Version: 1.0 Release](https://img.shields.io/badge/Version-1.0%20Release-green.svg)](https://github.com/0x007e/utils-crc) ![Build](https://github.com/0x007e/utils-crc/actions/workflows/release.yml/badge.svg) [![License GPLv3](https://img.shields.io/badge/License-GPLv3-lightgrey)](https://www.gnu.org/licenses/gpl-3.0.html)

# `CRC Utils`

This utility can be used to calculate a `crc-checksum` across given data.

## File Structure

![File Structure](https://0x007e.github.io/utils-crc/crc16_8c__incl.png)

```
utils/
└── crc/
    ├── crc16.c
    └── crc16.h
```

> The library is completely patform independent and can be usesd across a wide range of c-compilers.

## Downloads

The library can be downloaded (`zip` or `tar`), cloned or used as submodule in a project.

| Type      | File               | Description              |
|:---------:|:------------------:|:-------------------------|
| Library   | [zip](https://github.com/0x007E/utils-crc/releases/latest/download/library.zip) / [tar](https://github.com/0x007E/utils-crc/releases/latest/download/library.tar.gz) | CRC library that implements checksum calculation |

### Using with `git clone`

``` bash
mkdir -p ./utils/
git clone https://github.com/0x007E/utils-crc.git ./utils
mv ./utils/utils-crc ./utils/crc
```

### Using as `git submodule`

``` bash
git submodule add https://github.com/0x007E/utils-crc.git ./utils/crc
```

## Programming

``` c
#include "../lib/utils/crc/crc16.h"

int main(void)
{
	crc16_init(CRC16_INITIAL_VALUE);

    unsigned char data[] = { 0x01, 0xAF, 0xED, 0x30, 0x41 };
    unsigned int crc;

    // Bytewise
    for (unsigned char i=0; i < (sizeof(data)/sizeof(data[0])); i++)
    {
		crc16_update(data[i]);
    }

    crc = crc16_result();

    // Arraywise
    crc = crc16_calculate(CRC16_INITIAL_VALUE, data, (sizeof(data)/sizeof(data[0]));


    // CRC-checksum as array
    unsigned char checksum[2];
    crc16_result_array(checksum);
}
```

# Additional Information

| Type       | Link               | Description              |
|:----------:|:------------------:|:-------------------------|
| AppNote | [pdf](https://ww1.microchip.com/downloads/en/Appnotes/Atmel-8936-CryptoAuth-Data-Zone-CRC-Calculation-ApplicationNote.pdf) | Application note for CRC16 |

---

R. GAECHTER