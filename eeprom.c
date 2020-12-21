


#include <stdio.h>
#include <wiringPi.h>
#include <string.h>

unsigned int mem[1024];
char input[1024] = "C30308";		//instructions in hexadecimal

char lo, ho;

int cs, oe;

const char ADDR[] = {15, 16, 1, 4, 5, 6, 10, 11, 31, 26};		//setting address pins

int main() {
  /***************INITIAL-CONFIG****************/
  wiringPiSetup();

  pinMode(8, INPUT);    //setting data pins to in order to not to mess with data lines at startup
  pinMode(9, INPUT);
  pinMode(7, INPUT);
  pinMode(0, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);


  pinMode(15, INPUT);   //setting adress pins to input
  pinMode(16, INPUT);
  pinMode(1, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(31, INPUT);
  pinMode(26, INPUT);

  pinMode(27, INPUT);   //chipselect
  pinMode(28, INPUT);   //Output-Enable
  //pinMode(29, INPUT);   //Data-Read


  /*****************************************/

  /*****Converting Char to 8-bit number*****/
  for (int i = 0; i < 2048; i += 2) {
    ho = input[i];
    lo = input[i + 1];
    int son = 0;

    switch (ho) {
      case '0':
        son += 0;
        break;
      case '1':
        son += 16;
        break;
      case '2':
        son += 32;
        break;
      case '3':
        son += 48;
        break;
      case '4':
        son += 64;
        break;
      case '5':
        son += 80;
        break;
      case '6':
        son += 96;
        break;
      case '7':
        son += 112;
        break;
      case '8':
        son += 128;
        break;
      case '9':
        son += 144;
        break;
      case 'A':
        son += 160;
        break;
      case 'B':
        son += 176;
        break;
      case 'C':
        son += 192;
        break;
      case 'D':
        son += 208;
        break;
      case 'E':
        son += 224;
        break;
      case 'F':
        son += 240;
        break;
    }
    switch (lo) {
      case '0':
        son += 0;
        break;
      case '1':
        son += 1;
        break;
      case '2':
        son += 2;
        break;
      case '3':
        son += 3;
        break;
      case '4':
        son += 4;
        break;
      case '5':
        son += 5;
        break;
      case '6':
        son += 6;
        break;
      case '7':
        son += 7;
        break;
      case '8':
        son += 8;
        break;
      case '9':
        son += 9;
        break;
      case 'A':
        son += 10;
        break;
      case 'B':
        son += 11;
        break;
      case 'C':
        son += 12;
        break;
      case 'D':
        son += 13;
        break;
      case 'E':
        son += 14;
        break;
      case 'F':
        son += 15;
        break;
    }

    mem[i / 2] = son;
    son = 0;

  }
  /*****************************************/

	/***************Main-loop***************/
  while (1) {				//loop

    cs = digitalRead(27);
    oe = digitalRead(28);

    if (cs == 0 && oe == 0) {		//chip select and output enable 

      pinMode(8, OUTPUT);   //setting data pins to output
      pinMode(9, OUTPUT);
      pinMode(7, OUTPUT);
      pinMode(0, OUTPUT);
      pinMode(2, OUTPUT);
      pinMode(3, OUTPUT);
      pinMode(12, OUTPUT);
      pinMode(13, OUTPUT);

      unsigned int address = 0;
      printf("Asked for  ");
      for (int n = 0; n < 10; n += 1) {					//creating address in int form in range of 0-255
        int bit = digitalRead(ADDR[n]) ? 1 : 0;
        printf("%d", bit);
        address = (address << 1) + bit;
      }
      
      /*****Converting 8-bit number to binary*****/
      int dec = mem[address];
      int b[8];
      for (int i; i < 8; i += 1) {
        b[i] = 0;
      }

      if (dec >= 128) {
        b[7] = 1;
        dec -= 128;
      }
      if (dec >= 64) {
        b[6] = 1;
        dec -= 64;
      }
      if (dec >= 32) {
        b[5] = 1;
        dec -= 32;
      }
      if (dec >= 16) {
        b[4] = 1;
        dec -= 16;
      }
      if (dec >= 8) {
        b[3] = 1;
        dec -= 8;
      }
      if (dec >= 4) {
        b[2] = 1;
        dec -= 4;
      }
      if (dec >= 2) {
        b[1] = 1;
        dec -= 2;
      }
      if (dec >= 1) {
        b[0] = 1;
        dec -= 1;
      }

/*****Setting 8-bit output to data bus*****/

      digitalWrite(8, b[0]);
      digitalWrite(9, b[1]);
      digitalWrite(7, b[2]);
      digitalWrite(0, b[3]);
      digitalWrite(2, b[4]);
      digitalWrite(3, b[5]);
      digitalWrite(12, b[6]);
      digitalWrite(13, b[7]);


      printf("   ");
      printf("%d", address);
      printf("   ");
      printf("Answer is");
      printf("   ");
      printf("PINS   ");
      printf("%d", b[7]);
      printf("%d", b[6]);
      printf("%d", b[5]);
      printf("%d", b[4]);
      printf("%d", b[3]);
      printf("%d", b[2]);
      printf("%d", b[1]);
      printf("%d", b[0]);
      printf("   ");
      printf("%d", mem[address]);
      printf("\n");
      delay(1);

    } else {
      pinMode(8, INPUT);    //setting data pins to output
      pinMode(9, INPUT);
      pinMode(7, INPUT);
      pinMode(0, INPUT);
      pinMode(2, INPUT);
      pinMode(3, INPUT);
      pinMode(12, INPUT);
      pinMode(13, INPUT);
    }
  }
  return 0 ;
}

