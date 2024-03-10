# StemOS8, simple OS with console for STM8S Discovery board

But not really an OS. It can't load another app.
What you can do is limited to implemented system commands.
To see command list simply hit enter from console.
Console is connected to PD5/UART2_TX and PD6/UART2_RX.
To use this app, compile it with 'make', and then when
board is connected to PC type 'make flash'.
You will need sdcc compiler to compile it, and stm8flash
for flashing (and of course STM8S discovery board from
ST Microeletronics).

# Responsibility, copyright

I take completely no responsibility for this code.
You can use it at your own risk. It's made for educational
purposes only, but if it help you in some of your struggles
with stm8s, even on production it will be great. I've added
GPL v2 license because i think there should be license in
something that is placed publicly on the internet.

I've tested spi with mcp32s17 IO extender, and i2c with 
two at24c64 memories.
