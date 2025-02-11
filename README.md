# CrowdLED RE

CrowdLED reverse engineering efforts

## Packets

```
 0                   1
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                               |
+                               +
|            Unknown            |
+               +-+-+-+-+-+-+-+-+
|               |     CRC8      |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

### CRC8 calculation

CRC8 params were obtained using [RevEng](https://reveng.sourceforge.io/)

```
width=8 poly=0x07 init=0x84 refin=true refout=true xorout=0x00 check=0xcb residue=0x00 name=(none)
```

Correct CRC8 calculation tool: [CRC Calculator (Javascript)](https://www.sunshine2k.de/coding/javascript/crc/crc_js.html)

## Example packets

These packets are confirmed to work with the CrowdLED V3 bracelets with group 22, 23

```
0x5F 0x1C 0x97 0xFF 0x13 0x01 - White(ish)
0x5F 0x23 0x97 0xFF 0x13 0xD6 - Pink
0x5F 0x57 0xFF 0xEF 0x13 0x68 - White(ish)
```

## Credits

- [**MakeTotalSense**](https://github.com/MakeTotalSense/) - [signal recording](https://github.com/MakeTotalSense/Flipper-Concert-bracelets)
