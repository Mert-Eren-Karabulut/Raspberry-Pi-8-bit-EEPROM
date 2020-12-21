# Rasperry Pi as an EEPROM!

Using a Raspberry Pi laying around as an EEPROM for your 8-bit project is a great idea. Since writing on commercial EEPROMs can require adapters and special tools, it is not very practical to use them in trial and error 8-bit projects. I have entountered on this problem and decided to create a C program that simulates an EEPROM.

# How is the timing done?

If you are working with an 8-bit project with multiple ICs, you already know that timing of each element must be suitable with each other in order to obtain a solid communication between components. As we know that clock of Raspberry Pi is way higher than any 8-bit microproccessor or microcontroller. So Raspberry pi makes data available in data bus right after **chip select** and **output enable** pins are low. It happens so fast compared to a machine cycle of our 8-bit microprocessor since Pi's clock is way faster. So data bus is set correctly in any time it is asked for. Simple yet effective. I also added a 1 milisecond delay at the end of each loop in the code in order to let Pi rest a little.

## Where will I put my instructions and in which format?

There is an char array in the beginning of the file named **input[2048]**. This array is your input in **hexadecimal** format. As you already know, 2 characters in hexadecimal is stored in one byte. So each pair of characters from beggining is being taken as **one byte** in our simulated EEPROM. As we have a space of [2048] character in our input array, our EEPROM has 1024 byte of space. 

## Which pins are address and data pins?

Address pins and data pins are set in the beginning of the code. You can look them up in there. As we have 1024 bytes, we have 10 address pins.

## Console output

When program is executed, it prints out the adress pins and according data pins in both decimal and binary format. That is a great feature to follow what is going on. I used **Geany** as the IDE as it has **wiringPi** library included.
