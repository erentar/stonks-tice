# A TI-84CE stocks investment game
![](https://gist.githubusercontent.com/erentar/0feff18f942f888cf9b09cab33aedc59/raw/079466742d3ce63e01dc715b298398f9e254bcb5/stonks.png)

Keys:<br>
`[y=]` to buy stocks<br>
`[graph]` to sell stocks<br>
`[clear]` to exit<br>

<br>

Precompiled binaries will be in releases. You can download the game from there.

### build instructions
1\. install the [CE-Programming C SDK](https://github.com/CE-Programming/toolchain)<br>
2\. run `cproto -q -I $CEDEV/include src/functions.c > src/functions.h 2>/dev/null;make`

the output will be at bin/STONKS.8xp