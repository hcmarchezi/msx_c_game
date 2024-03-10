## MSX Sound

### Introduction

MSX Sound is a BASIC command to instruct a PSG audio chip to make sounds.
It is composed of 3 channels. Each channel can produce audio vibration suitable for music or noise.

MSX sound is composed of 14 registers numbered from 0 to 13. Each of them has specific functionality. Some registers are channel specific while others configure all the channels.

### Register Reference

#### Channel 0

|register|range     |description                                                    |
|--------|----------|---------------------------------------------------------------|
|   0    | 0 - 255  |Least significant bits for frequency value                     |
|   1    | 0 - 15   |High significant bits for frequency value                      |
|   8    | 0 - 16   |Sound volume                                                   |

#### Channel 1

|register|range     |description                                                    |
|--------|----------|---------------------------------------------------------------|
|   2    | 0 - 255  |Least significant bits for frequency value                     |
|   3    | 0 - 15   |High significant bits for frequency value                      |
|   9    | 0 - 16   |Sound volume                                                   |

#### Channel 2

|register|range     |description                                                    |
|--------|----------|---------------------------------------------------------------|
|   4    | 0 - 255  |Least significant bits for frequency value                     |
|   5    | 0 - 15   |High significant bits for frequency value                      |
|   10   | 0 - 16   |Sound volume                                                   |

#### All Channels

|register|range     |description                                                    |
|--------|----------|---------------------------------------------------------------|
|   6    | 0 - 31   |Noise generator freq                                           |
|   7    | 128 - 191|Mixer settings (See mixer settings section)                    |
|   11   | 0 - 255  |Least significant bits of envelop period                       |
|   12   | 0 - 255  |Most significant bits of envelop period                        |
|   13   | 0 - 15   |Envelope shape                                                 |

#### Mixer settings (register 7)

Bit-based configuraation.

| Bit 7 | Bit 6 | Bit 5         | Bit 4         | Bit 3         | Bit 2        | Bit 1        | Bit 0        |
|-------|-------|---------------|---------------|---------------|--------------|--------------|--------------|
|       |       | disable noise | disable noise | disable noise | disable tone | disable tone | disable tone |
|  1    | 0     | channel C     | channel B     | channel A     | channel C    | channel B    | channel A    |

##### Envelope shape and period

Envelope shape is set by register 13:

| Value | Shape         |
|-------|---------------|
| 0~3   | ＼＿＿＿＿＿＿＿ |
| 4~7   | ／＿＿＿＿＿＿＿ |    
| 8     | ＼＼＼＼＼＼＼＼ |
| 9     | ＼＿＿＿＿＿＿＿ |
| 10    | ＼／＼／＼／＼／ |
| 11    | ＼￣￣￣￣￣￣￣ |
| 12    | ／／／／／／／／ |
| 13    | ／￣￣￣￣￣￣￣ |
| 14    | ／＼／＼／＼／＼ |
| 15    | ／＿＿＿＿＿＿＿ |

Envelope period is 16 bit value set by registers 11 and 12:

|most significant bits|least significant bits|
|---------------------|----------------------|
|register 12          |register 11           |


#### Note table

Musical notes can be produced from tone registers:
* registers 0 and 1 for channel A
* registers 2 and 3 for channel B
* registers 4 and 5 for channel C

Frequency below should be mapped to registers, as in the example:
* For C4, value is 0x1AC mapped as 'register 1'=`0x01` and 'register 0'=`0xAC`

Table below shows register values (12 bits) for musical notes from octaves 1 to 8.

|Note|1   |2   |3   |4   |5   |6   |7   |8   |
|----|----|----|----|----|----|----|----|----|
|C   |D5Dh|6AFh|357h|1ACh|0D6h|06Bh|035h|01Bh|
|C#  |C9Ch|64Eh|327h|194h|0CAh|065h|032h|019h|
|D   |BE7h|5F4h|2FAh|17Dh|0BEh|05Fh|030h|018h|
|D#  |B3Ch|59Eh|2CFh|168h|0B4h|05Ah|02Dh|016h|
|E   |A9Bh|54Eh|2A7h|153h|0AAh|055h|02Ah|015h|
|F   |A02h|501h|281h|140h|0A0h|050h|028h|014h|
|F#  |973h|4BAh|25Dh|12Eh|097h|04Ch|026h|013h|
|G   |8EBh|476h|23Bh|11Dh|08Fh|047h|024h|012h|
|G#  |86Bh|436h|21Bh|10Dh|087h|043h|022h|011h|
|A   |7F2h|3F9h|1FDh|0FEh|07Fh|040h|020h|010h|
|A#  |780h|3C0h|1E0h|0F0h|078h|03Ch|01Eh|00Fh|
|B   |714h|38Ah|1C5h|0E3h|071h|039h|01Ch|00Eh|















