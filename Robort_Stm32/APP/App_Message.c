#include "App_Message.h"
#include "APP_GPS.H"
u8 Message_uPload_Buff[50]={0};

int Robort_Receive_Frame(App_Robort_Dat_Tag *pdata)
{
    uint8 ret = 0;
    
    ret = STM32_UART_Read(STM32_UART1, pdata, sizeof(App_Robort_Dat_Tag));
    if (ret==0)
    {
        return RET_ERROR;
    }
    
    return RET_OK;    
}

static int Crc16(u8 *ptr, int count)
{
	int crc, i;
	crc = 0;
	while (--count >= 0){
		crc = (crc ^ (((int)*ptr++) << 8));
		for (i = 0; i < 8; ++i)
		if (crc & 0x8000)
		crc = ((crc << 1) ^ 0x1021);
		else
		crc = crc << 1;
	}
	return (crc & 0xFFFF);
}

void Robort_Send_Frame(App_Robort_Dat_Tag *pdata)
{
     STM32_UART_Write(STM32_UART1, pdata, sizeof(App_Robort_Dat_Tag));
}

/*************************************************************************************
*��������GPS_Message_Upload
*��������:�ϴ�GPS���ݸ�·����
*ʱ�䣺2016-10-15
*************************************************************************************/
void GPS_Message_Upload( void)
{
  int Crc;
//	while( DMA1_Uart1_Status_Get())			                //��ѯDMA_UART�Ƿ����
//	{
//		;
//	}
	
	Message_uPload_Buff[0]=0xff;                        //��װ���ݰ�֡ͷ
	Message_uPload_Buff[1]=0x02;
	Message_uPload_Buff[2]=18;
	Message_uPload_Buff[3]=0;
	Message_uPload_Buff[4]=0x10;
				
	for( u8 i=0;i<5;i++)                                 //װ�뾭����Ϣ
	{
		Message_uPload_Buff[i+5]=GPS_Info_Data.lat.uLat[i];
	}
				
	for( u8 i=0;i<4;i++)                                 //װ��γ����Ϣ
	{
		Message_uPload_Buff[i+9]=GPS_Info_Data.lon.uLon[i];
	}
				
	for( u8 i=0;i<4;i++)                                  //װ�뺽����Ϣ
	{
		Message_uPload_Buff[i+13]=GPS_Info_Data.direction.uDir[i];
	}				
				
	for( u8 i=0;i<4;i++)                                  //װ���ٶ���Ϣ
	{
		Message_uPload_Buff[i+17]=GPS_Info_Data.speed.uSpeed[i];
	}	 
	Message_uPload_Buff[21]=GPS_Info_Data.sAtinfo_iNuse;   //����������Ŀ
	Message_uPload_Buff[22]=GPS_Info_Data.sAtinfo_iNview;  //�ɼ�������Ŀ
	Crc=Crc16(Message_uPload_Buff,22);
	Message_uPload_Buff[23]=Crc&0xff;
	Message_uPload_Buff[24]=(Crc>>8)&0xff;
//	STM32_UART_Write(1,Message_uPload_Buff,25);
	STM32_UART1_Write(Message_uPload_Buff,25);
}



void Robort_Uart_Init(void)
{
    UART_Init();
}
