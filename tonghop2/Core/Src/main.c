/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
#include <math.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdbool.h"
#include "stm32_hal_legacy.h"

 static volatile uint16_t  c_key_num =0,d[10],num_b=0,count_temp=0;
  static volatile float Y1;
uint16_t adc_timer;
static volatile uint16_t stop=0,_key_ =0,_write=0,key_x =0, key_c =0,start=0,check =0,data_flash=0;
static volatile uint8_t _num =0,wait =0;
#define ROW1_PIN GPIO_PIN_12
#define ROW2_PIN GPIO_PIN_13
#define ROW3_PIN GPIO_PIN_14
#define ROW4_PIN GPIO_PIN_15
#define COL1_PIN GPIO_PIN_8
#define COL2_PIN GPIO_PIN_9
#define COL3_PIN GPIO_PIN_10
#define COL4_PIN GPIO_PIN_11
#define GPIO_KEY_ROW GPIOA

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
char buf[16];		
void bufcl(uint8_t a, uint8_t b)
{
	lcd_put_cur(a,b);
for(int i=0; i<16; i++)
	{
	buf[i]=' ';
	}

}
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM3_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM2_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t key;

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */



/* Private variables ---------------------------------------------------------*/

DMA_HandleTypeDef hdma_adc1;

I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim2;


/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM2_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
 static volatile uint32_t count =0;
/* USER CODE END PFP */


	//***************************//TIMER DELAY\\***************************************	
	
void delay_1ms(void)
{
 __HAL_TIM_SetCounter(&htim2, 0);
 while (__HAL_TIM_GetCounter(&htim2)<20);
	
}

uint32_t millis()
{
 delay_1ms();

 count ++;
		//char t[3];
		///		bufcl(1,0);
		//	sprintf(t,"T:%d", count);
		//lcd_send_string ( t);
return count;
}
void millis_p(uint8_t t){
count += t;
}
uint32_t count_tem(){
	delay_1ms();
count_temp++;
	
	return count_temp;
}
void count_tem_t(){
count_temp =0;
}
void delay(uint16_t a){
	
for(uint16_t i =0; i<a; i++)
	{
delay_1ms();

	}

}

void timer_t(){

count =0;
}


	//***************************//END -TIMER DELAY\\***************************************	
	
	bool none_key(){		
if((HAL_GPIO_ReadPin(GPIO_KEY_ROW,COL1_PIN)==0)|(HAL_GPIO_ReadPin(GPIO_KEY_ROW,COL2_PIN)==0)|(HAL_GPIO_ReadPin(GPIO_KEY_ROW,COL3_PIN)==0)|(HAL_GPIO_ReadPin(GPIO_KEY_ROW,COL4_PIN)==0)){
return true;
	
}else{
return false;
	}
}
	//***************************//BAN PHIM 44\\***************************************	
	
uint8_t Keypad_Read()
{
	
    // M?ng luu tr? các giá tr? c?a hàng và c?t
    
					int8_t keypad[4][4] = {
						{'1', '4', '7', 'E'},
						{'2', '5', '8', '0'},
						{'3', '6', '9', 'F'},
						{'A', 'B', 'C', 'D'},
				
					};
 
    uint16_t row_pins[4] = {ROW1_PIN, ROW2_PIN, ROW3_PIN, ROW4_PIN};

  
		
    for (uint8_t row = 0; row < 4; row++)
    {
			 HAL_GPIO_WritePin(GPIOB, ROW1_PIN| ROW2_PIN| ROW3_PIN| ROW4_PIN, GPIO_PIN_SET);
      	delay(1);
				//HAL_GPIO_WritePin(GPIOA, row_pins[row], GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, row_pins[row], 0);
			
				//uint8_t check_roe = row;
				uint16_t col_pins[4] = {COL1_PIN, COL2_PIN, COL3_PIN, COL4_PIN};
						
      for (uint8_t col = 0; col < 4; col++)
        {
				
          if (HAL_GPIO_ReadPin(GPIOA, col_pins[col]) == 0)
						{

						return keypad[row][col];

				
                				
				}		
			
						
      }
					
    } return 0x01;
}

	//***************************//END-BAN PHIM 44\\***************************************	
	



int32_t map(int32_t value, int32_t inputMin, int32_t inputMax, int32_t outputMin, int32_t outputMax)
{
    return (value - inputMin) * (outputMax - outputMin) / (inputMax - inputMin) + outputMin;
}
 _Bool TCF=0;                                          
uint8_t DATARX[2];                                  
int af=0;

float tem=0;
float get_adc(uint16_t Temp){

return Temp;
}
 uint16_t check_max=0;




float voltageDividerR1 = 10000;
float BValue = 3770;
float R1 = 10000;
float T1 = 298.15;

float R2 ;
float T2 ;
 
float a ;
float b ;
float c ,d2;

float e = 2.718281828 ;
 
float tempSampleRead = 0;
float tempLastSample = 0;
float tempSampleSum = 0;
float tempSampleCount = 0;
float tempMean ;
 float rawValue;


uint8_t total=0;

float  num_adc(){
	
	
	
	//***************************//CAM BIEN PT LOAI K MAX6675\\***************************************	
	
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,1);
float Temp=0; 
		
	for(uint8_t i =0; i<2;i++)
	{
	//	if(i !=0)
		//	{
		uint8_t DATARX[2]; 
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
		HAL_SPI_Receive(&hspi1, DATARX, 2, 100);
		
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
								 
//rawValue = rawValue+(Temp*=0.25);   
	
		TCF=(((DATARX[0]|(DATARX[1]<<8))>>2)& 0x0001);        // State of Connecting
		Temp=((((DATARX[0]|DATARX[1]<<8)))>>3);   
		HAL_Delay(500); 
		//delay(5);
		Temp= Temp*0.25;
	
		
		//	}
	}
			bufcl(1,0);
			//rawValue/5;
			sprintf(buf,"N:%.1f",Temp);
		if(Temp<250&& ((rawValue-Temp) <10| (Temp-rawValue) <10))
			{
	//	lcd_send_string (buf);	// Waits for Chip Ready(according to Datasheet, the max time for conversion is 220ms)
	//	HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
			rawValue = Temp;
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,0);
			//float temperature = (rawValue	>>3)*0.25;
			return Temp;
  
			}
	//***************************//END-CAM BIEN PT LOAI K MAX6675\\***************************************	
	
			
			
	//***************************//CAM BIEN NTC 1000K\\***************************************	
		
			/*
			
		uint32_t ti =count_tem();
			//	if(ti >2){

				uint16_t adcValue; 


			HAL_StatusTypeDef adcStartStatus = HAL_ADC_Start(&hadc1);
		if (adcStartStatus != HAL_OK) {
			
				return 0;
		}

		HAL_StatusTypeDef adcConversionStatus = HAL_ADC_PollForConversion(&hadc1, 1000);
		if (adcConversionStatus != HAL_OK) {
			
			 return 0;
		}

		uint32_t adcValue2 = HAL_ADC_GetValue(&hadc1);
		tempSampleSum = adcValue2;
		if (adcValue2 ==  0xFFFF) {
			 return 0;
		}

		// D?ng ADC
		HAL_StatusTypeDef adcStopStatus = HAL_ADC_Stop(&hadc1);
		if (adcStopStatus != HAL_OK) {
				return 0;
		}
			
	
	

		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);

		HAL_Delay(500);
		timer_t();

		//	if (total >=5){
		tempMean = tempSampleSum ;

		R2 = (voltageDividerR1*tempMean)/(4095-tempMean);				
		a = 1/T1;
		b = log10(R1/R2);
		c = b / log10(e);
		d2 = c / BValue ;
		T2 = 1 / (a- d2);
		 
			total =0;
			tempSampleSum = 0;
			tempSampleCount = 0;
			tempMean =0;
			
				bufcl(0,0);
					
				char y[16];
					
				sprintf(y,"u%.1f,%.5f",T2,T2 -273.15);
				lcd_send_string (y);
		
				bufcl(1,0);
				sprintf(buf,"%.1f,%.4f",b,c);
				lcd_send_string (buf);

	
	
			return (T2-273.15);

			//	}else{
				
			//return 0;
			//}
			
			//		}else{
			//		return 0;
				//	}
				
			
			*/
			
		//***************************//END-CAM BIEN NTC 1000K\\***************************************	
	
	
	
	
	
}


 
void num_write_flash(){  // GHI SO CHU KY VA NHIET DO
	
	uint8_t a=0, i=0,b=0;  		
	//Flash_Write_Array_16bit(uint16_t* _Array_DATA_, uint32_t _ADDRESS_DATA_, uint16_t _LENGTH_);
	uint16_t data =0,buf_data=0 ;
	
	HAL_Delay(1000);
	//lcd_put_cur(0,4);
	//lcd_send_string ("chuky T/N");
	lcd_put_cur(0,0);
bool _ch = true;
//***************************//LUU GIA TRI CHI KY\\***************************************	

lcd_send_string ("chuky");
	while(1)
	{
		delay(2);
		uint8_t k_1 =	(uint8_t)Keypad_Read();
		
		lcd_put_cur(0,0);
		lcd_send_string ("chuky:");
		if(k_1 != 0x01 && k_1  < 58){ 
		data= buf_data*10 +k_1 -48;
			buf_data =data;

		bufcl(0,0);
		sprintf(buf,"chuky:%d",data );
		lcd_send_string (buf);
		}else if(k_1 == 69){ // * 69
		data =0;
			buf_data=0;
			lcd_clear ();
	
		}else if(k_1 == 67)  /// # 70 C 67 D 68
			{
			
			break;
			}	
//***************************//END-LUU GIA TRI CHI KY\\***************************************	

	delay(10);

	}
	data ;
	
		data_flash = data +1;
		HAL_Delay(10);
		uint16_t flash_write_T[data_flash];
		uint16_t flash_write_N[data_flash];
		
		
	lcd_clear(); 
			
	bufcl(0,0);
	sprintf(buf,"da chon:%d",data);
		lcd_send_string (buf);
		
		HAL_Delay(1000);
	
	
		uint8_t num_nhiet=0,num_time =0;
	lcd_clear(); 
	lcd_put_cur(0,0);
	
	lcd_send_string ("Nhiet Do: A");
	lcd_put_cur(1,0);
	lcd_send_string ("Thoi Gian: B");
	uint8_t length1 =0,length2 =0;
	uint16_t da =0,buf_da=0;
	bool check_N = false, check_T = false;
	delay(200);
		lcd_clear(); 
		
		lcd_put_cur(0,0);
		lcd_send_string ("%d-N%d");
		lcd_put_cur(0,8);
		lcd_send_string ("%d-T%d");
		
		uint16_t time_data_p_s =0;
		
	do{// ------------------------------------ stop =1 break;
//***************************//THIET LAP CAC GIA TRI BAN PHIM\\***************************************	

			delay(2);
			uint8_t k_2 =(uint8_t)	Keypad_Read();	
		delay(10);
		if(k_2 != 0x01 && k_2<58 ){
			da= buf_da*10 +k_2 -48;
			buf_da =da;
			if(time_data_p_s ==0)
			{
			bufcl(1,0);
				sprintf(buf,"K:%d",da);
		lcd_send_string (buf);
			}else
			{
			bufcl(1,5);
				sprintf(buf,"%d",da);
					lcd_send_string (buf);
			}
			
					
		}else if(k_2 == 69){
					buf_da=0;		da =0;	lcd_put_cur(1,0);	lcd_send_string ("        ");		
					time_data_p_s =0;
		}else if(k_2 == 70){// ----------------------------------------------- thoi gian #
			if(da <100)
			{
			bufcl(1,4); lcd_send_string ("P");
				time_data_p_s = da*60;
				buf_da=0;		da =0;lcd_put_cur(1,0);	//lcd_send_string ("        ");	
			}
		//break;
		}
//***************************//END -THIET LAP CAC GIA TRI BAN PHIM\\***************************************	
		
						// 65 A
//***************************//nhan A luu gia tri NHIET DO\\********************************	
	
		if( k_2 == 65 && num_nhiet==0) 		// ---------- NHAN x DE THEM NHIET DO
			{    					
					
				flash_write_N[length1] =  da;
					
				bufcl(0,0);
				lcd_send_string ("        ");	
				bufcl(0,0);
				
				sprintf(buf,"%d-N%d ",length1,flash_write_N[length1]);
				
				lcd_send_string (buf);
				key_x =0;
			
			if(length1 >= (data))
				{
						lcd_put_cur(0,0);
					lcd_send_string ("/-/-/");
				check_N = true;
					num_nhiet=1;
				}else{length1 ++;
			
				}buf_da=0;		da =0;	
		lcd_put_cur(1,4);
		lcd_send_string ("       ");
				buf_da=0;		da =0;	lcd_put_cur(1,0);	lcd_send_string ("K:     ");	
				delay(2);
				// 66 B
		}
			
//***************************//END-nhan A luu gia tri NHIET DO\\********************************	

		
//***************************//nhan B luu gia tri thoi gian\\********************************	
		
		else if(k_2 ==66 && num_time ==0) // 	// ---------- NHAN + DE THEM TH
		{										
		if(da >60)
		{
		bufcl(1,12);
		lcd_send_string ("p<60");
			continue;
		}
		flash_write_T[length2] =  time_data_p_s +da;  		//if(length2 >= data){continue ;};
		bufcl(0,8);
		lcd_send_string ("        ");	
		bufcl(0,8);
		
		sprintf(buf,"%d-T%d",length2,	flash_write_T[length2]);
		lcd_send_string (buf);	
		key_c =0;
			
			
				if(length2 >= (data))
				{
				lcd_put_cur(0,8);
				lcd_send_string ("/-/-/");
			check_N = true;
				num_time=1;
				}else{length2 ++;
				
				
				}
			time_data_p_s =0;
		lcd_put_cur(1,4);
		lcd_send_string ("       ");
		buf_da=0;		da =0;	lcd_put_cur(1,0);	lcd_send_string ("K:     ");	
				lcd_put_cur(1,0);
					delay(2);
	}
//***************************//end -nhan B luu gia tri thoi gian\\********************************	
	
	delay(2);

if(k_2 == 67)
		{
		lcd_clear();
		lcd_send_string ("dang luu");
		delay(20);
																	/*#define _PAGE_127_ 		 	((uint32_t)0x0801FC02)
																#define _PAGE_126_ 		 	((uint32_t)0x0801F802)
																#define _PAGE_125_ 		 	((uint32_t)0x0801F402)
																#define _PAGE_124_ 		 	((uint32_t)0x0801F002)
																#define _PAGE_123_ 		 	((uint32_t)0x0801EC02)
																#define _PAGE_122_ 		 	((uint32_t)0x0801E802)
																#define _PAGE_121_ 		 	((uint32_t)0x0801E402)
																#define _PAGE_120_ 		 	((uint32_t)0x0801E002)
																#define _PAGE_119_ 		 	((uint32_t)0x0801DC02)
																#define _PAGE_118_ 		 	((uint32_t)0x0801D802) */
		
		
			lcd_clear();
//***************************//hien thi gia tri vua thiet lap\\********************************	
				
	for(uint8_t in=0;in<=data; in++)
			{
			bufcl(0,0);
				
			sprintf(buf,"%d: temp: %d",in,flash_write_N[in]);
		lcd_send_string (buf);
			bufcl(1,3);
				
			sprintf(buf,"time: %d",flash_write_T[in]);
		lcd_send_string (buf);
 
			delay(50);
		
			}
//***************************//end -hien thi gia tri vua thiet lap\\********************************	
				
//***************************//luu vao cac thanh ghi flash page123,1234,126\\********************************	
				
			uint32_t	flash_length = 0x08000000 +1024*123;
			Flash_Write_Uint(data_flash, flash_length);
			delay(100);
	
			uint32_t	ris_temp 	=	0x08000000 +1024*124;
			uint32_t	ris_timer =  0x08000000 +1024*126;	
			
			Flash_Write_Array_16bit(&flash_write_N[0],ris_temp, data_flash);
			delay(100);
			Flash_Write_Array_16bit(&flash_write_T[0],ris_timer , data_flash);
			delay(100);
			
//***************************//end -luu vao cac thanh ghi flash page123,1234,126\\********************************	
				
			
			
			bufcl(0,0);
			lcd_clear();		
			lcd_send_string ("da luu"); 
		
			delay(50);
			_write =0;
		lcd_clear();		//	Flash_Read_Array_16bit(arr_Read_1,ris_1, data+1);

		
			lcd_clear(); 
			lcd_put_cur(0,0);
			lcd_send_string ("run: D | Write: C");
			delay(100);
			check =2;
			return;
	
		}delay(10);
	}while(1);				//Flash_Write_Uint(data, 1)
		
}






void num_read_fl(){

//	num_key_timer()
	
//***************************//doc flash tu thanh ghi page123,1234,126\\********************************	
	
			uint32_t	flash_length = 0x08000000 +1024*123;

			uint16_t num_arr_read = Flash_Read_Uint(	flash_length );
			lcd_clear();
			bufcl(0,0);
			sprintf(buf,"so da luu:%d",num_arr_read);
			lcd_send_string (buf);
		
			delay(20);
			uint16_t arr_flash_temp[num_arr_read] ;
			uint16_t arr_flash_timer[num_arr_read] ;
				
			uint32_t	ris_temp 	=	0x08000000 +1024*124;
			uint32_t	ris_timer =  0x08000000 +1024*126;	
		
			Flash_Read_Array_16bit(arr_flash_temp ,ris_temp, num_arr_read);
	
			Flash_Read_Array_16bit(arr_flash_timer ,ris_timer, num_arr_read );

//***************************//end-doc flash tu thanh ghi page123,1234,126\\********************************	
	
uint8_t tec_cong =70;


//***************************//hien thi gia tri vua doc tu flash\\********************************	
	for(int t =0; t<num_arr_read; t++)
	{
	
	bufcl(1,0);					sprintf(buf,"%d|N:%d-T:%d|",t ,arr_flash_temp[t],arr_flash_timer[t] );
					lcd_send_string (buf);	
		delay(50);
	}
	
	
//***************************//end-hien thi gia tri vua doc tu flash\\********************************	
		

			lcd_clear(); 
			lcd_put_cur(0,0);
			lcd_send_string ("da doc du lieu");
			delay(20);
		
							uint16_t check_temp =1,t=80,c=80;
							uint16_t check_timer =0;
							uint8_t flash_start =0;

							HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
							HAL_GPIO_WritePin(GPIOA , GPIO_PIN_5,1);			
					
				uint16_t TEC =0;	

	
		
					
		
					float TEC2;
			
					for(int i =0; i<num_arr_read; i++){
				
					delay(50);
				
							

		
					check_temp  = arr_flash_temp[i];
					check_timer = arr_flash_timer[i];
		
					bufcl(0,0);					sprintf(buf,"%d|N:%d-T:%d|%d",i ,check_temp,check_timer,num_arr_read );
					lcd_send_string (buf);	
//***************************//gia nhiet cho so nong lanh\\********************************									
						while(1)
							{

					
							HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
							HAL_GPIO_WritePin(GPIOB , GPIO_PIN_1,0);
							HAL_Delay(250);
					
							uint16_t dd = (uint16_t)num_adc();
									if(dd != 0&&dd != 250)
										{
										TEC2 =	dd;
										}
							HAL_Delay(100);
						
							bufcl(1,10);
							sprintf(buf,"%d:%.1f\r\n",check_temp,TEC2);
							lcd_send_string (buf);
								
									
						if(TEC2 <(check_temp ))
							{
								HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
								HAL_GPIO_WritePin(GPIOB , GPIO_PIN_1,0);
								//	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,100);
								//		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,0);
								
							}else if(TEC2 >(check_temp +3))
							{
								HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
								HAL_GPIO_WritePin(GPIOB , GPIO_PIN_1,1);
								//__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,0);
								//		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,100);
								
							}else 
							{							
							break;							
							}
							
							HAL_Delay(3000);
							//delay(50);
						}
//***************************//end -gia nhiet cho so nong lanh\\********************************							
						delay(10);
						unsigned long abc=0;
						
						
//***************************//delay sau khi gia nhiet xong\\********************************						
						while(1){
						
							//	HAL_Delay(3000);
							delay(30);
							HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
							HAL_GPIO_WritePin(GPIOB , GPIO_PIN_1,0);
							HAL_Delay(500);
													delay(5);
							
								TEC	 =(uint16_t) num_adc();
								if(TEC	 != 0 && TEC != 250)
									{
									TEC2 =	TEC	;
									}
				
						//HAL_Delay(100);
						  delay(1);
							bufcl(1,10);
							sprintf(buf,"%d:%.1f\r\n",check_temp,TEC2);
							lcd_send_string (buf);
							bufcl(1,0);
							millis_p(12);
							abc= millis()/10 ;
								
							sprintf(buf,"T:%d:%d",abc,check_timer);
							lcd_send_string (buf);
							if(abc >= check_timer)
								{
								break;
								}
									
								
				if(TEC2	< check_temp)
				{
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
					HAL_GPIO_WritePin(GPIOB , GPIO_PIN_1,0);
				
					//	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,tec_cong);
					//		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,0);
					tec_cong+= 5;
				

				}else if(TEC2>= check_temp +5){
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
					HAL_GPIO_WritePin(GPIOB , GPIO_PIN_1,1);
					//	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,0);
					//			__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,tec_cong);
				
					tec_cong-= 5;
				}	
						
						}
//***************************//end-delay sau khi gia nhiet xong\\********************************		
						
//***************************//tam dung qua trinh\\*****************************************	*****									
						while(wait ==1)
						{
										
							bufcl(0,0);					
							sprintf(buf,"****tam dung****");
							lcd_send_string (buf);
							delay(10);
						}
	//***************************//end-tam dung qua trinh\\*****************************************	
						
				if(stop ==1)
					{
					return;
					}
					
					
					
			
					}
					
						lcd_clear(); 
						lcd_put_cur(0,0);
						lcd_send_string ("xong");
						delay(100);
						timer_t() ;
	
	
	
		/*
				if(TEC	< check_temp)
				{
				
							HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
							HAL_GPIO_WritePin(GPIOB , GPIO_PIN_1,0);
					
				
					delay(5);

				}else if(TEC>= check_temp +5){
					
							HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
							HAL_GPIO_WritePin(GPIOB , GPIO_PIN_1,1);
						delay(5);
					
				}	
					
			*/
				
	
						
		
					
					
			
					
					
	


}




/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM2_Init(void);

	
	
	void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) // interrup
{ 
  /* Prevent unused argument(s) compilation warning */
	

  UNUSED(GPIO_Pin);

 // if(GPIO_Pin==GPIO_PIN_0){
	//	  start = !start;
	
  //}
	if(GPIO_Pin==GPIO_PIN_1){
      wait= !wait;
  }
	
	if(GPIO_Pin==GPIO_PIN_2){
	start =0;
	stop = !stop;
	
  }
}

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){

if(hadc->Instance== hadc1.Instance){
adc_timer = HAL_ADC_GetValue(hadc);
}
}
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_TIM3_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
lcd_init ();
  /* USER CODE END 2 */
HAL_ADC_Start_IT(&hadc1);
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	//lcd_send_string ("dsass");
TIM3->CCR1 = 100;
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  			HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	//lcd_send_string ("dsass");
	 HAL_TIM_Base_Start(&htim2);
			lcd_send_string ("0");
				__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,0);
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,0);
	
	
	 

							HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
							HAL_GPIO_WritePin(GPIOB , GPIO_PIN_1,0);
	
	
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
							HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
							HAL_GPIO_WritePin(GPIOA , GPIO_PIN_5,0);
										
		uint16_t dsa =(uint16_t)num_adc();				
	if( dsa != 0 && dsa != 250){
	tem = dsa ;
		
			
	} 
			
	bufcl(1,9);
			sprintf(buf,"N:%.1f", tem );
			lcd_send_string (buf);
		
		
	
			lcd_put_cur(0,0);
			lcd_send_string ("run: D|Write: C");
			delay(1);

			uint8_t k_= Keypad_Read(); /// 68 D read
															// 70 # write
			delay(2);
			if(k_ != 0x01  )
				{
			
				bufcl(1,0);
				lcd_send_string ("    ");
				bufcl(1,0);	
				sprintf(buf,"k:%d", k_ -48 );
				lcd_send_string (buf);
		
				}

			
				if(k_ == 67) // C
					{
					lcd_clear ();
					num_write_flash();
					}else if(k_ == 68) // D
					{
						lcd_clear ();
				 num_read_fl(); // docj lai gia tri da luwu
					}
			
		
   
    /*for(int t =0;t<100;t++){
	
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,t);
		delay(100);
	}


*/
				
	//__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,100);
	//__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,0);

	
		

    /* USER CODE BEGIN 3 */
  
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES_RXONLY;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 35999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 71;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 99;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA2 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB13 PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA8 PA9 PA10 PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
