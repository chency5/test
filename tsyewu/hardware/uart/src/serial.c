#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/file.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <sys/time.h>
#include <linux/serial.h>

#include "projdebug.h"
#include "serial.h"
#include "utily.h"

static serialNativeData serialData[MAX_SERIAL_COUNT] = {0};
//static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int initSerial(int type,const char* _port, const char* _settings, int _debug, int _timeout)
{
      memset(&serialData[type],0,sizeof(serialData[type]));
      memset(serialData[type].port, 0, sizeof(serialData[type].port));
      if ((_port != 0) && (strlen(_port) > 0))
      {
	    strcpy(serialData[type].port, _port);
      }

      memset(serialData[type].settings, 0, sizeof(serialData[type].settings));
      if ((_settings != 0) && (strlen(_settings) > 0))
      {
	    strcpy(serialData[type].settings, _settings);
      }

      serialData[type].timeout = _timeout;
      serialData[type].handle = -1;
      serialData[type].baudrate = 1;	
      serialData[type].debug = _debug;
      return 0;
}

int openSerial(int type)
{
    if (serialData[type].handle >= 0)
    {
	return true;
    }
		
    if ((serialData[type].port == 0) || (strlen(serialData[type].port) <= 0) || (serialData[type].settings == 0) || (strlen(serialData[type].settings) <= 0))
    {
	return false;
    }
				
    serialData[type].handle = open(serialData[type].port, O_RDWR | O_NOCTTY | O_NONBLOCK | O_EXCL);
			    
    if (serialData[type].handle < 0)
    {
	return false;
    }
		
    if (!setInternal(type))
    {
       close(serialData[type].handle);
       serialData[type].handle = -1;
       return false;
    }
		
    return true;
}


bool change(int type, const char* _settings, int _debug, int _timeout)
{
	if ((_settings == 0) || (strlen(_settings) <= 0) || (_timeout < 0))
	{
		return false;
	}
		
	serialData[type].timeout = _timeout;

	if (strcmp(serialData[type].settings, _settings) == 0)
	{
		return true;
	}
		
	serialData[type].debug = _debug;
	strcpy(serialData[type].settings, _settings);
	return setInternal(type);
}


int sendSerial(int type, char* buffer, int length)
{
	if (serialData[type].handle < 0)
	{
		return -1;
	}
				
	if ((buffer == 0) || (length <= 0))
	{
		return -1;
	}
		
	int	totalBytesWrite = 0;
	int     rc;
	char* pb = (char*)buffer;
		
	        
	if (serialData[type].timeout > 0)
	{
		rc = waitWritable(type, serialData[type].timeout);
		if (rc <= 0)
		{
			return (rc == 0) ? 0 : -1;
		}
			
		int	retry = 3;
		while (length > 0)
		{
			rc = write(serialData[type].handle, pb, (size_t)length);
			if (rc > 0)
			{
	                   length -= rc;
	                   pb += rc;
		           totalBytesWrite += rc;
		
			   if (length == 0)
			   {
				break;
			   }
			  }
			else
			{
				retry--;
				if (retry <= 0)
				{
					break;
				}
			}
				
			rc = waitWritable(type, 50);
			if (rc <= 0)
			{
				break;
			}
		}
	 }
	 else
	{
		rc = write(serialData[type].handle, pb, (size_t)length);
		if (rc > 0)
		{
				totalBytesWrite += rc;
			}
			else if ((rc < 0) && (errno != EINTR) && (errno != EAGAIN))
			{
				return -1;
			}
		} 
		
		if(serialData[type].debug)
		{
		    TRACE_PROJ_INFO("Serial Tx: ");
                    int i;
                    for(i = 0; i < totalBytesWrite; i++)
        	    {
        		TRACE_PROJ_INFO("%02X ", (buffer[i]) & 0xFF);	
        	    }
        	    TRACE_PROJ_INFO("\n\n");
		}	
	return totalBytesWrite;
}



int recvSerial(int type, char* buffer, int length)
{
	if (serialData[type].handle < 0)
	{
		return -1;
	}

	if ((buffer == 0) || (length <= 0))
	{
		return -1;
	}
	memset(buffer, 0, length);
	
	int	totalBytesRead = 0;
	int rc;
	char* pb = buffer;
	if (serialData[type].timeout > 0)
	{
		rc = waitReadable(type, serialData[type].timeout);
		if (rc <= 0)
		{
			return (rc == 0) ? 0 : -1;
		}
		
		int	retry = 3;
		while (length > 0)
		{
			rc = read(serialData[type].handle, pb, (size_t)length);
			if (rc > 0)
			{
          	            length -= rc;
		            pb += rc;
	   		    totalBytesRead += rc;
		
			    if (length == 0)
			    {
				break;
			     }
			}
			else if (rc < 0)
			{
				retry--;
				if (retry <= 0)
				{
					break;
				}
			}
				
			rc = waitReadable(type, 20);
			if (rc <= 0)
			{
				break;
			}
		}
	}
	else
	{
		rc = read(serialData[type].handle, pb, (size_t)length);
		if (rc > 0)
		{
			totalBytesRead += rc;
		}
		else if ((rc < 0) && (errno != EINTR) && (errno != EAGAIN))
		{
			return -1;
		}
	}
		
	if(serialData[type].debug)
	{
	    TRACE_PROJ_INFO("Serial Rx: ");
            int i;
            for(i = 0; i < totalBytesRead; i++)
            {
        	TRACE_PROJ_INFO("%02X ", (buffer[i]) & 0xFF);	
            }
            TRACE_PROJ_INFO("\n\n");
	}
		
	return totalBytesRead;
    }



void closeSerial(int type)
{
	if (serialData[type].handle < 0)
	{
		return;
	}
		
		//clear the transmit buffer
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 50*1000;
	select(0, NULL, NULL, NULL, &tv);
	tcflush(serialData[type].handle, TCOFLUSH);
		
	//clear the receive buffer
	int	c;
	while (read(serialData[type].handle, &c, 1) > 0);
	tcflush(serialData[type].handle, TCIFLUSH);
	
	close(serialData[type].handle);
	
	serialData[type].handle = -1;
    }


    
   
bool setInternal(int type)
{
	if (serialData[type].handle < 0)
	{
		serialData[type].handle = open(serialData[type].port, O_RDWR | O_NOCTTY | O_NONBLOCK | O_EXCL);
		
		if (serialData[type].handle < 0)
		{
			return false;
		}
	}
			
	char szBaudrate[8], szParity[8], szDatabits[8], szStopbits[8];
	if (sscanf(serialData[type].settings, "%[^,],%[^,],%[^,],%s", szBaudrate, szParity, szDatabits, szStopbits) < 0)
	{
		return false;
	}
	serialData[type].baudrate = atoi(szBaudrate);
	int parity = 0;
	if ((szParity[0] == 'N') || (szParity[0] == 'n'))
	{
                parity = 0;
	}
        else if ((szParity[0] == 'O') || (szParity[0] == 'o'))
	{
                parity = 1;
	}
        else if ((szParity[0] == 'E') || (szParity[0] == 'e'))
	{
        	parity = 2;
	}
        else if ((szParity[0] == 'M') || (szParity[0] == 'm'))
	{
                parity = 3;
	}
        else if ((szParity[0] == 'S') || (szParity[0] == 's'))
	{
                parity = 4;
	}
	int databits = atoi(szDatabits);
	int stopbits = atoi(szStopbits);
	if ((serialData[type].baudrate < 1200) || (parity < 0) || (databits < 5) || (stopbits < 1))
	{
		return false;
	}

	struct termios options;
	static int databitsArray[] = {CS5, CS6, CS7, CS8};
	static unsigned long baudrateArray[] = {B1200, B2400, B4800, B9600, B19200, B38400, B57600, B115200};
	
	// Get the current options
        tcgetattr(serialData[type].handle, &options);

	// Set the baud rate 1200-115200
	if (serialData[type].baudrate == 1200)
	{
		cfsetispeed(&options, baudrateArray[0]);
		cfsetospeed(&options, baudrateArray[0]);
	}
	else if (serialData[type].baudrate == 2400)
	{
		cfsetispeed(&options, baudrateArray[1]);
		cfsetospeed(&options, baudrateArray[1]);
	}
	else if (serialData[type].baudrate == 4800)
	{
		cfsetispeed(&options, baudrateArray[2]);
		cfsetospeed(&options, baudrateArray[2]);
	}
	else if (serialData[type].baudrate == 9600)
	{
		cfsetispeed(&options, baudrateArray[3]);
		cfsetospeed(&options, baudrateArray[3]);
	}
	else if (serialData[type].baudrate == 19200)
	{
		cfsetispeed(&options, baudrateArray[4]);
		cfsetospeed(&options, baudrateArray[4]);
	}
	else if (serialData[type].baudrate == 38400)
	{
		cfsetispeed(&options, baudrateArray[5]);
	        cfsetospeed(&options, baudrateArray[5]);
	}
	else if (serialData[type].baudrate == 57600)
	{
		cfsetispeed(&options, baudrateArray[6]);
	        cfsetospeed(&options, baudrateArray[6]);
	}
	else if (serialData[type].baudrate == 115200)
	{
		cfsetispeed(&options, baudrateArray[7]);
		cfsetospeed(&options, baudrateArray[7]);
	}
    else
    {
    	//非标准波特率
    	struct serial_struct ss,ss_set;
    	
    	cfsetispeed(&options, baudrateArray[5]);
    	cfsetospeed(&options, baudrateArray[5]);
    	
    	tcflush(serialData[type].handle, TCIFLUSH);
    	tcsetattr(serialData[type].handle, TCSANOW, &options);
    	if((ioctl(serialData[type].handle, TIOCGSERIAL, &ss)) < 0)
    	{  
		TRACE_PROJ_INFO("BAUD: error to get the serial_struct info:%s\n",strerror(errno));  
		return false;  
	}

	ss.flags = ASYNC_SPD_CUST;
	ss.custom_divisor = ss.baud_base / serialData[type].baudrate;
	
	if((ioctl(serialData[type].handle, TIOCSSERIAL, &ss)) < 0)
	{  
		TRACE_PROJ_INFO("BAUD: error to set serial_struct:%s\n",strerror(errno));  
		return false;  
	}
		
	ioctl(serialData[type].handle, TIOCGSERIAL, &ss_set);
	TRACE_PROJ_INFO("BAUD: success set baud to %d,custom_divisor=%d,baud_base=%d\n", serialData[type].baudrate, ss_set.custom_divisor, ss_set.baud_base);
    }
    
    // parity 0-n, 1-o, 2-e, 3-m, 4-s
    options.c_cflag &= ~PARENB; // default, no parity
    
    if (parity == 1) // odd
    {
        options.c_cflag |= PARENB;
        options.c_cflag |= PARODD;
    }
    else if (parity == 2) // even
    {
        options.c_cflag |= PARENB;
        options.c_cflag &= ~PARODD;
    }
    else if (parity == 3) // mark
    {
        options.c_cflag |= PARENB;
        options.c_cflag |= PARODD;
        options.c_cflag |= CMSPAR;
    }
    else if (parity == 4) // space
    {
        options.c_cflag |= PARENB;
        options.c_cflag &= ~PARODD;
        options.c_cflag |= CMSPAR;
  }
    
    // data bits 5-8
    options.c_cflag &= ~CSIZE;
    if ((databits >= 5) && (databits <= 8))
    {
    	options.c_cflag |= databitsArray[databits - 5];
    }
    else
    {
    	options.c_cflag |= CS8;
    }
    
	// stop bits 1-2
	if (stopbits == 1)
	{
        options.c_cflag &= ~CSTOPB;    // 1 stop bits
    }
    else if (stopbits == 2)
    {
        options.c_cflag |= CSTOPB;
    }
    else
    {
    	options.c_cflag &= ~CSTOPB;    // 1 stop bits
    }
    
    // input modes
    options.c_iflag = 0;
    if (parity != 0) // enable parity
    {
		//options.c_iflag |= (INPCK|ISTRIP);
	options.c_iflag |= (INPCK);
    }
    else // disable
    {
	options.c_iflag &= ~INPCK;
    }
	options.c_iflag |= IGNPAR;
        
    // control modes
	options.c_cflag |= (CLOCAL | CREAD); //Ignore modem control lines and enable receiver
	options.c_cflag &= ~CRTSCTS; //Disable hardware flow control
	
	options.c_iflag &= ~(IXON | IXOFF | IXANY); //Disable software flow control
			
	// Set raw mode
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Enable data to be processed as raw input
	options.c_oflag = 0;
    		
	tcflush(serialData[type].handle, TCIOFLUSH);

    // Set the new options
    if (tcsetattr(serialData[type].handle, TCSANOW, &options) != 0)
    {
		return false;
    }
    
    return true;
}


int waitReadable(int type,int millis)
{
	if (serialData[type].handle < 0)
	{
		return -1;
	}
	int serial = serialData[type].handle;
	
	fd_set fdset;
    struct timeval tv;
    int rc = 0;
	
	while (millis > 0)
	{
		if (millis < 5000)
		{
			tv.tv_usec = millis % 1000 * 1000;
			tv.tv_sec  = millis / 1000;

			millis = 0;
		}
		else
		{
			tv.tv_usec = 0;
			tv.tv_sec  = 5;

			millis -= 5000;
		}

	        FD_ZERO(&fdset);
		FD_SET(serial, &fdset);
		
		rc = select(serial + 1, &fdset, NULL, NULL, &tv);
		if (rc > 0)
		{
			rc = (FD_ISSET(serial, &fdset)) ? 1 : -1;
			break;
		}
		else if (rc < 0)
		{
			rc = -1;
			break;
		}
	}

    return rc;
  }

int waitWritable(int type,int millis)
{
	if (serialData[type].handle < 0)
	{
		return -1;
	}
	int serial = serialData[type].handle;
	
	fd_set fdset;
        struct timeval tv;
        int rc = 0;
	
	while (millis > 0)
	{
		if (millis < 5000)
		{
			tv.tv_usec = millis % 1000 * 1000;
			tv.tv_sec  = millis / 1000;

			millis = 0;
		}
		else
		{
			tv.tv_usec = 0;
			tv.tv_sec  = 5;

			millis -= 5000;
		}

		FD_ZERO(&fdset);
		FD_SET(serial, &fdset);
		
		rc = select(serial + 1, NULL, &fdset, NULL, &tv);
		if (rc > 0)
		{
			rc = (FD_ISSET(serial, &fdset)) ? 1 : -1;
			break;
		}
		else if (rc < 0)
		{
			rc = -1;
			break;
		}
	}

    return rc;
}

int getBaudrate(int type)
{
      return serialData[type].baudrate;
}


void setDebugMode(int type,int val)
{
    serialData[type].debug = val;
}
