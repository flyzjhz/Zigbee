#define SLEEP_C_

/* ------------------------------------------------------------------------------------------------
 *                                          Includes
 * ------------------------------------------------------------------------------------------------
 */
#include "Sleep.h"

/**************************************************************************************************
 * @fn          Sleep_INT_Init
 * @brief       P1.6�˿�˯���ж����ó�ʼ��(�ж���ʱ�ر�)
 * @param       ��
 * @return      ��
 **************************************************************************************************
 */
void Sleep_INT_Init(void)
{
  
  P1SEL &= ~0x40;   //����P1_6Ϊͨ��I/O��
  P1DIR &= ~0x40;   //����P1_6Ϊ����
  P1INP &= ~0x40;   //����P1_6Ϊ������Ĭ���Ǹߵ�ƽ
  
  //IEN2  |=  0x10;   //�˿�1�ж�ʹ��
  //P1IEN |=  0x40;   //ʹ��P1_6�ж�
  //PICTL |=  0x04;   //������½��ش����ж�
  //P1IFG &=  ~0x40;  //P1.6�жϱ�־��0
}



/**************************************************************************************************
 * @fn          Sleep_Init
 * @brief       ϵͳ˯�߳�ʼ��
 * @param       ��
 * @return      ��
 **************************************************************************************************
 */
void Sleep_Init(void)
{
  ST2   = 0x00;
  ST1   = 0x00;
  ST0   = 0x00;   //32KhZ�¼���
  
  STIE  = 1;      //˯�߶�ʱ���ж�ʹ��
  STIF  = 0;      //˯�߶�ʱ���жϱ�־��0�����ж�δ�� 1���ж�δ��
}


/**************************************************************************************************
 * @fn          Sleep_SetTime
 * @brief       ϵͳ˯��ʱ���趨
 * @param       ��
 * @return      ��
 **************************************************************************************************
 */



void Sleep_SetTime(uint8_t Sleep_Sec)
{
  uint32_t SleepTime = 0;
 
  SleepTime |=  ST0;
  SleepTime |=  (uint32_t)ST1 << 8;
  SleepTime |=  (uint32_t)ST2 << 16;
  SleepTime +=  (uint32_t)Sleep_Sec * (uint32_t)32768;
  ST2        =  (uint8_t)(SleepTime >> 16);
  ST1        =  (uint8_t)(SleepTime >> 8);
  ST0        =  (uint8_t) SleepTime;
  
//  count = sizeof(uint64_t);         //4
//  count = sizeof(uint32_t);         //2
//  count = sizeof(uint16_t);         //2
//  count = sizeof(uint8_t);          //1
  
}


/**************************************************************************************************
 * @fn          Sleep_Set
 * @brief       ϵͳ˯��ʱ���趨1.5S
 * @param       ��
 * @return      ��
 **************************************************************************************************
 */
void Sleep_Set(void)
{
  uint32_t SleepTime = 0;
  
  SleepTime |=  ST0;
  SleepTime |=  (uint32_t)ST1 << 8;
  SleepTime |=  (uint32_t)ST2<< 16;
  SleepTime +=  (uint32_t)36044;    //1.1*32768 1.1s����һ��
  ST2        =  (uint8_t)(SleepTime >> 16);
  ST1        =  (uint8_t)(SleepTime >> 8);
  ST0        =  (uint8_t) SleepTime;
}




/**************************************************************************************************
 * @fn          Sleep_SetMode
 * @brief       ϵͳ����ģʽ�趨
 * @param       ��
 * @return      ��
 **************************************************************************************************
 */
void Sleep_SetMode(uint8_t Sleep_Mode)
{
  if(Sleep_Mode < 4)
  {
    SLEEPCMD &= 0xFC;
    SLEEPCMD |= Sleep_Mode;   //����ϵͳ˯��ģʽ
    PCON      = 1;            //����˯��ģʽ��ͨ���жϻ���
  }
  else
  {
    PCON      = 0;            //����˯��ģʽ
  }
}

///**************************************************************************************************
// * @fn          ST_ISR
// * @brief       ˯�߶�ʱ���ж�
// * @param       ��
// * @return      ��
// **************************************************************************************************
// */
//#pragma vector = ST_VECTOR
//__interrupt void ST_ISR(void)
//{
//  STIF = 0x00;                //����жϱ�־
//  Sleep_SetMode(SLEEP_OFF);   //������������ģʽ
//}