/*
 * Author: Edoardo De Marchi
 * Date: 07/04/13
 * Notes: OV7670 + FIFO AL422B camera test
*/

#include "main.h"


#define timer_read_f(x)     chrono::duration<float>((x).elapsed_time()).count()
#define timer_read_s(x)     chrono::duration_cast<chrono::seconds>((x).elapsed_time()).count();
#define timer_read_ms(x)    chrono::duration_cast<chrono::milliseconds>((x).elapsed_time()).count()
#define timer_read_us(x)    (x).elapsed_time().count()





#define VGA     307200         //640*480
#define QVGA    76800          //320*240
#define QQVGA   19200          //160*120

static char format = ' ';
static int resolution = 0;

////////////
static UnbufferedSerial pc(USBTX, USBRX);
char word[4096] = {0};
int wordLen=0;
char buf4[512] = {0};


void pc_recv()
{
    new_send = true;
       if (wordLen<4096)
   {
    pc.read(&word[wordLen], sizeof(word[wordLen]));  //  Got 1 char
    wordLen++;
   }
else {
 wordLen=0;
}
}






/////////////////////

/*
void rxCallback(MODSERIAL_IRQ_INFO *q) 
{
     new_send = true;
}

*/


int main() 
{  
////////////////
    pc.attach(&pc_recv, UnbufferedSerial::RxIrq);
 //   dev.attach(&dev_recv, UnbufferedSerial::RxIrq);
 //   rak811.attach(&rak811_recv, UnbufferedSerial::RxIrq);    
  
  //  pc.baud(115200);
      pc.baud(921600);   
 //  dev.baud(9600);
//   rak811.baud(115200);


////////////////////////

    pc.baud(921600);       
 //   pc.printf("SystemCoreClock: %dMHz\r\n", SystemCoreClock/1000000);       // print the clock frequency
  //  led4 = 0;
  
    t.start();
 //   pc.attach(&rxCallback, MODSERIAL::RxIrq);

    while(1) 
    { 
        if(new_send)
        {
            int i = 0;
       /*
            while(pc.readable())
            {
                word[i] = pc.getc();
                i++;
            }
            */
            parse_cmd(); 
        }            
      //  wait_ms(50);
        ThisThread::sleep_for(50);
    }
}



void parse_cmd()
{
            new_send = false;
            
            
            
            //if(strcmp("snap", word) == 0) 



for (int j = 0; j < wordLen; j++) 
{
        if((word[j] == 's')&&(word[j+1] == 'n')&&(word[j+2] == 'a')&&(word[j+3] == 'p')&&(word[j+4] == '\r')&&(word[j+5] == '\n'))

            {
                    CameraSnap();
                    memset(word, 0, sizeof(word));      
            }else



         //   if(strcmp("init_bw_VGA", word) == 0)                    // Set up for 640*480 pixels RAW    
            
               
            
                if((word[j] == 'i')&&(word[j+1] == 'n')&&(word[j+2] == 'i')&&(word[j+3] == 't')&&
                (word[j+4] == '_')&&(word[j+5] == 'b')&&(word[j+6] == 'w')&&(word[j+7] == '_')&&
                (word[j+8] == 'V')&&(word[j+9] == 'G')&&(word[j+10] == 'A')&&(word[j+11] == '\r')&&(word[j+12] == '\n'))

            {
                   format = 'b';
                    resolution = VGA;
                    if(camera.Init('b', VGA) != 1)
                    {
                   //   pc.printf("Init Fail\r\n");
                    sprintf(buf4,"Init Fail\r\n"); 
                    for (uint8_t i = 0; i < 11; i++) {
                     pc.write(&buf4[i], sizeof(buf4[i]));
                    }

                    }
               //     pc.printf("Initializing done\r\n");

            sprintf(buf4,"Initializing done\r\n"); 
            for (uint8_t i = 0; i < 19; i++) {
             pc.write(&buf4[i], sizeof(buf4[i]));
                    }

                    memset(word, 0, sizeof(word));    
            }

/*
            else  
            if(strcmp("init_yuv_QVGA", word) == 0)                  // Set up for 320*240 pixels YUV422   
            {
                    format = 'y';
                    resolution = QVGA;
                    if(camera.Init('b', QVGA) != 1)
                    {
                      pc.printf("Init Fail\r\n");
                    }
                    pc.printf("Initializing done\r\n");
                    memset(word, 0, sizeof(word));
            }else  
            if(strcmp("init_rgb_QVGA", word) == 0)                  // Set up for 320*240 pixels RGB565   
            {
                    format = 'r';
                    resolution = QVGA;
                    if(camera.Init('r', QVGA) != 1)
                    {
                      pc.printf("Init Fail\r\n");
                    }
                    pc.printf("Initializing done\r\n");
                    memset(word, 0, sizeof(word));
            }else 
            if(strcmp("init_bw_QVGA", word) == 0)                  // Set up for 320*240 pixels YUV (Only Y)         
            {
                    format = 'b';
                    resolution = QVGA;
                    if(camera.Init('b', QVGA) != 1)
                    {
                      pc.printf("Init Fail\r\n");
                    }
                    pc.printf("Initializing done\r\n");
                    memset(word, 0, sizeof(word));
            }else  
            if(strcmp("init_yuv_QQVGA", word) == 0)                 // Set up for 160*120 pixels YUV422
            {                            
                    format = 'y';
                    resolution = QQVGA;
                    if(camera.Init('b', QQVGA) != 1)
                    {
                      pc.printf("Init Fail\r\n");
                    }
                    pc.printf("Initializing done\r\n");
                    memset(word, 0, sizeof(word));
            }else   
            if(strcmp("init_rgb_QQVGA", word) == 0)                 // Set up for 160*120 pixels RGB565
            {                            
                    format = 'r';
                    resolution = QQVGA;
                    if(camera.Init('r', QQVGA) != 1)
                    {
                      pc.printf("Init Fail\r\n");
                    }
                    pc.printf("Initializing done\r\n");
                    memset(word, 0, sizeof(word));
            }else
            if(strcmp("init_bw_QQVGA", word) == 0)                 // Set up for 160*120 pixels YUV (Only Y)
            {                        
                    format = 'b';
                    resolution = QQVGA;
                    if(camera.Init('b', QQVGA) != 1)
                    {
                      pc.printf("Init Fail\r\n");
                    }
                    pc.printf("Initializing done\r\n");
                    memset(word, 0, sizeof(word));
            }
            
            else


            if(strcmp("reset", word) == 0)              
            {
                    mbed_reset();        
            }else
            if(strcmp("time", word) == 0)              
            {
                    pc.printf("Tot time acq + send (mbed): %dms\r\n", t2-t1);
                    memset(word, 0, sizeof(word));
            }else
            if(strcmp("reg_status", word) == 0)              
            {  
                    int i = 0;
                    pc.printf("AD : +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F");
                    for (i=0;i<OV7670_REGMAX;i++) 
                    {
                        int data;
                        data = camera.ReadReg(i); // READ REG
                        if ((i & 0x0F) == 0) 
                        {
                            pc.printf("\r\n%02X : ",i);
                        }
                        pc.printf("%02X ",data);
                    }
                    pc.printf("\r\n");

            }
 */         
            memset(word, 0, sizeof(word));
            
            
}
}


void CameraSnap()
{
     //   led4 = 1;

                // Kick things off by capturing an image
        camera.CaptureNext();
        while(camera.CaptureDone() == false);      
                // Start reading in the image data from the camera hardware buffer                   
        camera.ReadStart();  
        t1 = t.read_ms();
        
        for(int x = 0; x<resolution; x++)
        {
 // Read in the first half of the image
               if(format == 'b' && resolution != VGA)
               {
                camera.ReadOnebyte();
               }else
               if(format == 'y' || format == 'r')
               {
                //    pc.putc(camera.ReadOnebyte());
                sprintf(buf4, "%c", camera.ReadOnebyte());
                pc.write(&buf4[0], sizeof(buf4[0]));
               }     
               // Read in the Second half of the image
              //pc.putc(camera.ReadOnebyte());      // Y only  
              
                sprintf(buf4, "%c", camera.ReadOnebyte());
                pc.write(&buf4[1], sizeof(buf4[1]));           
        }
       
        camera.ReadStop();
        t2 = t.read_ms(); 
        
        camera.CaptureNext();
        while(camera.CaptureDone() == false);             
        
       
       
     //   pc.printf("Snap_done\r\n");   
        sprintf(buf4,"Snap_done\r\n"); 
  for (uint8_t i = 0; i < 11; i++) {
    pc.write(&buf4[i], sizeof(buf4[i]));
  }
        //led4 = 0;
}