
file nạp code: ...\ABT_project1\tonghop\MDK-ARM\tonghop\tonghop.hex
file dự phòng chỉnh sửa cuối ngày 11h:10/4/2024 :...\ABT_project1\protues

chân digital B0,B1 đang đươcj thiết lập trong codee sử dụng do module BTS
sử dụng PWM thay đổi chân L_pwm và R_pwm trên module BTS
chỉnh sửa và thay đổi code ở dòng 800 đến 817 bằng code sau
ví dụ:

:800
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
817:							}

sẽ được thay đổi thành 
800:
if(TEC2 <(check_temp ))
							{
								//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
								//HAL_GPIO_WritePin(GPIOB , GPIO_PIN_1,0);
									__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,100);
										__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,0);
								
							}else if(TEC2 >(check_temp +3))
							{
								//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
								//HAL_GPIO_WritePin(GPIOB , GPIO_PIN_1,1);
								__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,0);
								__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,100);
								
							}else 
							{							
							break;							
							}
    817:
tiếp tục thay đổi code từ dòng 860 đến 877:
ví dụ:
860:
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
877:				}	
sẽ được đôỉ thành 
	if(TEC2	< check_temp)
				{
				//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
				//	HAL_GPIO_WritePin(GPIOB , GPIO_PIN_1,0);
				
						__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,tec_cong);
							__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,0);
					tec_cong+= 5;
				

				}else if(TEC2>= check_temp +5){
				//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
				//	HAL_GPIO_WritePin(GPIOB , GPIO_PIN_1,1);
					__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,0);
					__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,tec_cong);
				
					tec_cong-= 5;
				}	
