/*  RAT IN A MAZE PUZZLE     */
				
#include <lpc21xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUZZ 7
#define RS (1<<0)
#define RW (1<<1)
#define E (1<<2)
#define bit(x) (1<<x)
#define bit_(x) (0<<x)
unsigned int range=0,i;


/* --------- LCD ---------*/
void LCD_command(unsigned char command);
void delay_ms(int time);
void LCD_data(unsigned char data);
void LCD_write_string(char *string);
void LCD_init(void);
//int StartGame();

/* --------- BUZZER ---------*/
void delay_buzzer();

/* ------- Main -------*/
int main()
{
		char player[10][20];
		int score[10],length[10];
		char scr=0,no,winning_index,winning_path[10],ind,winner;
		int i=0,j=0,k=0,n,cnt=0,max=0,result,winning_length,flag=0,mark=0,flag2=0,index=0; //max = maximum score
		int value=0,multiple_winners[10];
		PINSEL1 = 0x00000000;  //Configure PORT0 as GPIO
		PINSEL2 = 0X00000000;  //Configure PORT1 as GPIO
		PINSEL0 = 0x00; //Configure Port0.7 as GPIO
		IODIR1 |= 0x00780000 | (0<<23)|(0<<24)|(0<<25)|(0<<26)|(0<<27)|(0<<28)|(0<<29)|(0<<30)|(0<<31); //Configure P1.18, P1.17, P1.16 as output(for rows and column) ,explicitly making switch pins as Input
		IODIR0 |= 0x00FF0007 | 0xffffffff;  //Configure P0.23 - P0.16 & P0.7as output for lcd data & P0.0,P0.1,P0.2 for lcd control lines.
		IO0PIN=0;											 	//Clear all IO Pins in P0
		VPBDIV=0x01;                    	//PCLK = 60MHz

		/* -------- LCD --------- */
		LCD_init();    //Initialize LCD 16x2
		LCD_command(0x01); //Make LCD Clear

		//n= StartGame();
		n=10; // set no of iterations as 10 by default

		/* ---- Play game n times ----- */
		while(index<n)
		{
				if(mark==0){									//if mark is zero scan no of players
						LCD_command(0x01);
						delay_ms(50);
						LCD_write_string("NO.OF PLAYERS :");
						LCD_command(0xc0);  //second line 1st position

						/* ------ Get Number of player through keypad ----- */
						while(mark<1){

								IOCLR1|=(1<<19);               //Making row1 LOW
								IOSET1|=(1<<20)|(1<<21)|(1<<22); //Making rest of the rows '1'
								if(!(IOPIN1&(1<<16))) {         //Scan for key press
									while(!(IOPIN1&(1<<16)));
									LCD_data('1');
									value=1;
									mark=1;
								}
								if(!(IOPIN1&(1<<17))) {
									while(!(IOPIN1&(1<<17)));
									LCD_data('2');
									value=2;
									mark=1;
								}
								if(!(IOPIN1&(1<<18))) {
									while(!(IOPIN1&(1<<18)));
									LCD_data('3');
									value=3;
									mark=1;
								}
								IOCLR1|=(1<<20);
								IOSET1|=(1<<21)|(1<<22)|(1<<19);
								if(!(IOPIN1&(1<<16))) {
									while(!(IOPIN1&(1<<16)));
										LCD_data('4');
							    	value=4;
									mark=1;
								}
								if(!(IOPIN1&(1<<17))) {
									while(!(IOPIN1&(1<<17)));
									LCD_data('5');
									value=5;
									mark=1;
								}
								if(!(IOPIN1&(1<<18))) {
									while(!(IOPIN1&(1<<18)));
										LCD_data('6');
									value=6;
									mark=1;
								}
								IOCLR1|=(1<<21);
								IOSET1|=(1<<22)|(1<<20)|(1<<19);
								if(!(IOPIN1&(1<<16))) {
									while(!(IOPIN1&(1<<16)));
									LCD_data('7');
									value=7;
									mark=1;
								}
								if(!(IOPIN1&(1<<17))) {
								 while(!(IOPIN1&(1<<17)));
										LCD_data('8');
									value=8;
									mark=1;
								}
								if(!(IOPIN1&(1<<18))) {
									while(!(IOPIN1&(1<<18)));
									LCD_data('9');
									value=9;
									mark=1;
								 }
								IOCLR1|=(1<<22);
								IOSET1|=(1<<19)|(1<<20)|(1<<21);
								if(!(IOPIN1&(1<<16)))
								{
									while(!(IOPIN1&(1<<16)));
									LCD_command(0x01);
									LCD_command(0x80); //1st line 1st position
									LCD_write_string("INVALID CHOICE");
									LCD_command(0xc0);  //second line 1st position
									LCD_write_string("RESTART GAME");
									delay_ms(300);
									//value=StartGame();
								 }
								if(!(IOPIN1&(1<<17)))
								{
									while(!(IOPIN1&(1<<17)));
									LCD_command(0x01);
									LCD_command(0x80); //1st line 1st position
									LCD_write_string("INVALID CHOICE");
									LCD_command(0xc0);  //second line 1st position
									LCD_write_string("RESTART GAME");
									delay_ms(300);
									//value=StartGame();
								}
								if(!(IOPIN1&(1<<18)))
								{
									while(!(IOPIN1&(1<<18)));
									LCD_command(0x01);
									LCD_command(0x80); //1st line 1st position
									LCD_write_string("INVALID CHOICE");
									LCD_command(0xc0);  //second line 1st position
									LCD_write_string("RESTART GAME");
									delay_ms(300);
									//value=StartGame();
								}

						}//while closed

				}// if closed (mark ==0)

				if(mark==1){											//if mark ==1 start the game

						if(flag2==0){
								n=value;							//set no of iterations of game
								/* ------ Start Game ----- */
								delay_ms(100);
								LCD_command(0x01);
								LCD_write_string("PLAYERS : ");
								LCD_command(0x0C); //display on cursor off
								no=n+'0';
								LCD_data((char)no);
								flag2=1;						//make falg 1 so that this if cant execute again
						}

						delay_ms(200);
						LCD_command(0x01);
						ind=index+'1';
						LCD_write_string("PLAYER ");
						LCD_data((char)ind);
						delay_ms(200);
						LCD_command(0x01);
						LCD_write_string("ENTER PATH : ");
						LCD_command(0x0E);  //Display on , cursor blinking
						LCD_command(0xc0);  //second line 1st position
						i=0;
						cnt=0;
						while(1)
						{
								IOCLR1|=(1<<19);               //Making row1 LOW
								IOSET1|=(1<<20)|(1<<21)|(1<<22); //Making rest of the rows '1'
								if(!(IOPIN1&(1<<16)))             //Scan for key press
								{
										while(!(IOPIN1&(1<<16)));
										LCD_data('1');
										player[index][i]='1';
										i++;
										// motor 1
										if(IOPIN1 & (1<<23))
										{
												IOCLR0 = bit(3);

										}
										else
										{
												IOSET0 = bit(3);
												IOSET0 = bit(7);
												delay_buzzer();
												IOCLR0 = bit(7);
												cnt++;
										}

								}
								if(!(IOPIN1&(1<<17)))
								{
										while(!(IOPIN1&(1<<17)));
										 LCD_data('2');
										player[index][i]='2';
										i++;
										// motor 2
										if(IOPIN1 & (1<<24))
										{
												 IOCLR0 = bit(4);
										}
										else
										{
												 IOSET0 = bit(4);
												 IOSET0 = bit(7);
												 delay_buzzer();
												 IOCLR0 = bit(7);
												 cnt++;

										}
								}
								if(!(IOPIN1&(1<<18)))
								{
										while(!(IOPIN1&(1<<18)));
										LCD_data('3');
										player[index][i]='3';
										i++;
										// motor 3
										if(IOPIN1 & (1<<25))
										{
												IOCLR0 = bit(5);
										}
										else
										{
												IOSET0 = bit(5);
												IOSET0 = bit(7);
												delay_buzzer();
												IOCLR0 = bit(7);
												cnt++;
										}
								}
								IOCLR1|=(1<<20);
								IOSET1|=(1<<21)|(1<<22)|(1<<19);
								if(!(IOPIN1&(1<<16)))
								{
										while(!(IOPIN1&(1<<16)));
										LCD_data('4');
										player[index][i]='4';
										i++;
										 // motor 4
										if(IOPIN1 & (1<<26))
										{
												IOCLR0 = bit(11);
										}
										else
										{
												IOSET0 = bit(11);
												IOSET0 = bit(7);
												delay_buzzer();
												IOCLR0 = bit(7);
												cnt++;
										}
								}
								if(!(IOPIN1&(1<<17)))
								{
										while(!(IOPIN1&(1<<17)));
										LCD_data('5');
										player[index][i]='5';
										i++;
										// motor 5
										if(IOPIN1 & (1<<27))
										{
												IOCLR0 = bit(14);
										}
										else
										{
												IOSET0 = bit(14);
												IOSET0 = bit(7);
												delay_buzzer();
												IOCLR0 = bit(7);
												cnt++;
										}
								}
								if(!(IOPIN1&(1<<18)))
								{
										while(!(IOPIN1&(1<<18)));
										LCD_data('6');
										player[index][i]='6';
										i++;
										// motor 6
										if(IOPIN1 & (1<<28))
										{
												IOCLR0 = bit(25);
										}
										else
										{
												IOSET0 = bit(25);
												IOSET0 = bit(7);
												delay_buzzer();
												IOCLR0 = bit(7);
												cnt++;
										}
								}
								IOCLR1|=(1<<21);
								IOSET1|=(1<<22)|(1<<20)|(1<<19);
								if(!(IOPIN1&(1<<16)))
								{
										while(!(IOPIN1&(1<<16)));
										LCD_data('7');
										player[index][i]='7';
										i++;
										// motor 7
										if(IOPIN1 & (1<<29))
										{
												IOCLR0 = bit(28);
										}
										else
										{
												IOSET0 = bit(28);
												IOSET0 = bit(7);
												delay_buzzer();
												IOCLR0 = bit(7);
												cnt++;
										}
								}
								if(!(IOPIN1&(1<<17)))
								{
										while(!(IOPIN1&(1<<17)));
										LCD_data('8');
										player[index][i]='8';
										i++;
										// motor 8
										if(IOPIN1 & (1<<30))
										{
												IOCLR0 = bit(29);
										}
										else
										{
												IOSET0 = bit(29);
												IOSET0 = bit(7);
												delay_buzzer();
												IOCLR0 = bit(7);
												cnt++;
										}
								}
								if(!(IOPIN1&(1<<18)))
								{
										while(!(IOPIN1&(1<<18)));
										LCD_data('9');
										player[index][i]='9';
										i++;
										// motor 9
										if(IOPIN1 & (1<<31))
										{
												IOCLR0 = bit(30);
										}
										else
										{
												IOSET0 = bit(30);
												IOSET0 = bit(7);
												delay_buzzer();
												IOCLR0 = bit(7);
												cnt++;
										}
								}
								IOCLR1|=(1<<22);
								IOSET1|=(1<<19)|(1<<20)|(1<<21);
								if(!(IOPIN1&(1<<16)))
								{
										while(!(IOPIN1&(1<<16)));
										LCD_write_string("INVALID PATH");
								}
								if(!(IOPIN1&(1<<17)))
								{
										while(!(IOPIN1&(1<<17)));
										LCD_command(0x01);
										LCD_write_string("GAME END");
										LCD_command(0x0C); //display on cursor off
										delay_ms(100);
										LCD_command(0x01);						//Make LCD clear
										//STOP ALL ROTATIONS
										IOCLR0 |= (1<<3)|(1<<4)|(1<<5)|(1<<11)|(1<<14)|(1<<25)|(1<<28)|(1<<29)|(1<<30);
										break;
								}
								if(!(IOPIN1&(1<<18)))
								{
										while(!(IOPIN1&(1<<18)));
										LCD_write_string("INVALID PATH");
								}
						}//while loop end (getting path)
				}//if closed

				player[index][i]='\0';
				score[index]=cnt;			//save score of that player
				length[index]=i;					//save path length of player
				index++;
		}//while loop end (Game end)
		
		LCD_command(0x0c);  //screen on cursor off
		max=score[0];
		for(index=0;index<n;index++){ //find maximum score
				if(max<score[index]){
					max=score[index];
				}
		}

		for(index=0;index<n;index++){
				if(score[index]==max){
					winning_length=length[index];// set length of 1st player who got max paneer as winner  to comapre paths
					winner=index+'1';
					//copy(winning_path,player[index][]);
					j=0;
					while(player[index][j]!='\0'){
						winning_path[j]=player[index][j];
						j++;
					}
					winning_path[j]='\0';
					multiple_winners[0]=index+1;
					flag=0;			//Single winner
					break;
				}
		}

		k=index;
		for(index=k+1;index<n;index++){
				i=1;  // to count multiple winners
				if(score[index]==max){

					if(winning_length<length[index]) { result=1;} //winner remains same
					else if(winning_length>length[index]) {result=-1;} //change winner
					else if(winning_length==length[index]) {result=0;} //multiple WINNERS
					else {}

					if(result==1){
						//Do nothing
					}
					else if(result==-1){
						winning_length=length[index];
						winner=index+'1';
						//copy(winning_path,player[index][]);
						j=0;
						while(player[index][j]!='\0'){
							winning_path[j]=player[index][j];
							j++;
						}
						winning_path[j]='\0';
						multiple_winners[0]=index+1;
						flag=0;					//single winner
					}
					else {
						multiple_winners[i]=index+1;
						i++;
						flag=1;				//multiple winners
					}
				}
		}

		if(flag==0){  //single winner
				scr=max+'0';							//int to char conversion
				delay_ms(300);
				LCD_command(0x80);
				LCD_write_string("WINNER :");
				delay_ms(200);
				LCD_write_string("PLAYER ");
				LCD_data((char)winner);
				LCD_command(0x0c);  //screen on cursor off
				delay_ms(300);
				LCD_command(0x01);				//make lcd clear
				LCD_command(0x80);     //1st line 1st position
				LCD_write_string("PATH : ");
				LCD_write_string((char*)winning_path);
				LCD_command(0x0c);  //screen on cursor off
				delay_ms(100);
				LCD_command(0xc0);  //second line 1st position
				LCD_write_string("SCORE : ");
				LCD_data((char)scr);
				LCD_command(0x0c);  //screen on cursor off
				delay_ms(1000);

		}
		if(flag==1){
				scr=max+'0';							//int to char conversion
				delay_ms(300);
				LCD_command(0x80);
				LCD_write_string("WINNERS : ");
				for(j=0;j<i;j++){
						winning_index=multiple_winners[j]+'0'; //int to char conversion
						LCD_data((char)winning_index);
						LCD_write_string(" ");
				}
				delay_ms(300);
				for(j=0;j<i;j++){
					//copy(winning_path,player[index][]);
					k=0;
					index=multiple_winners[j]-1;
					while(player[index][k]!='\0'){
						winning_path[k]=player[index][k];
						k++;
					}
					winning_path[k]='\0';
					LCD_command(0x80);     //1st line 1st position
					LCD_write_string("PATH");
					ind=j+'1';
					LCD_data((char)ind);
					LCD_write_string(" : ");
					LCD_write_string((char*)winning_path);
					LCD_command(0x0c);  //screen on cursor off
					LCD_command(0xc0);  //second line 1st position
					LCD_write_string("SCORE : ");
					LCD_data((char)scr);
					LCD_command(0x0c);  //screen on cursor off
					delay_ms(1000);
				}	
		}
		delay_ms(200);
		LCD_command(0x01);				//make lcd clear
		LCD_write_string("CONGRATS :)");
		LCD_command(0x0c);  //screen on cursor off
		return 0;
}


/* ----- LCD Function ----*/
//Function to generate software delay
//Calibrated to 1ms

void  delay_ms(int time)
{
			unsigned int  i, j;
			for (j=0; j<time; j++)
			{
				for(i=0; i<8002; i++){}
			}
}

void LCD_command(unsigned char command)
{
			IOCLR0 = 0xFF<<16; // Clear LCD Data lines
			IOCLR0=RS;     // RS=0 for command
			IOCLR0=RW;     // RW=0 for write
			IOSET0=command<<16; // put command on data line
			IOSET0=E;   // en=1
			delay_ms(10) ;   // delay
			IOCLR0=E;    // en=0
}

void LCD_data(unsigned char data)
{
			IOCLR0 = 0xFF<<16; // Clear LCD Data lines
			IOSET0=RS;     // RS=1 for data
			IOCLR0=RW;     // RW=0 for write
			IOSET0= data<<16;  // put command on data line
			IOSET0=E;   //en=1
			delay_ms(10) ;    //delay
			IOCLR0=E;   //en=0
}

void LCD_write_string(char *string)
{
			int i=0;
			while(string[i]!='\0')//Check for End of String
			{
					LCD_data(string[i]);
					i=i+1;
			}
}

void LCD_init()
{
			LCD_command(0x38); //8bit mode and 5x8 dotes (function set)
			delay_ms(10) ;   // delay
			LCD_command(0x0c); //display on, cursor off, cursor char blinking off(display on/off)
			delay_ms(10) ;   // delay
			LCD_command(0x0e);  //cursor increment and display shift(entry mode set)
			delay_ms(10) ;   // delay
			LCD_command(0x01);  //clear lcd (clear command)
			delay_ms(10) ;   // delay
			LCD_command(0x80);
			delay_ms(10) ;//set cursor to 0th location 1st lne
}


/* ----- BUZZER Function ----*/
void delay_buzzer()
{
			unsigned int j=0,i=0;
			for(j=0;j<1000;j++)
			{
				for(i=0;i<3000;i++);
			}
}
