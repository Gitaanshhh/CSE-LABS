#include <LPC17xx.h>

unsigned char tohex[10] = {0x3F, 0X06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
unsigned int i=0, j=0;

long int arr[4] = {9,9,9,9};

int main(){
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_GPIO0->FIODIR |= 0xFF0;
	LPC_GPIO1->FIODIR |= 0xF<<23;
	
	for(arr[3]=0; ; arr[3]--){
		for(arr[2]=9; arr[1]>=0; arr[1]--)
			for(arr[0]=9; arr[0]>=0;arr[0]--){
				for(i=0; i<4; i++){
					LPC_GPIO1->FIOPIN=i<<23;
					LPC_GPIO0->FIOPIN=tohex[arr[i]]<<4;
					for(j=0; j<100000; j++);
				}
				for(j=0; j<100000; j++);
				LPC_GPIO0->FIOCLR|=0xFF0;
			}
		if(arr[3]==0)
			arr[3] = 10;
	}
}
