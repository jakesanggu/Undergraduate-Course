#include "./include/gpio.h"

int gpio_export(unsigned int gpio){

int fd, len;
char buf[MAX_BUF];

if( (fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY)) > 0){

len = snprintf(buf, sizeof(buf) , "%d", gpio);
write(fd,buf,len);
close(fd);
}
return 0;
}

int gpio_unexport(unsigned int gpio){

int fd, len;
char buf[MAX_BUF];

if( (fd = open(SYSFS_GPIO_DIR "/unexport", O_WRONLY)) > 0){

len = snprintf(buf, sizeof(buf) , "%d", gpio);
write(fd,buf,len);
close(fd);

return 0;
}
}


int gpio_set_dir(unsigned int gpio, unsigned int dir){

int fd, len;
char buf[MAX_BUF];

len = snprintf(buf,sizeof(buf),SYSFS_GPIO_DIR "/gpio%d/direction", gpio);

if(     (fd = open(buf,O_WRONLY)   ) > 0){

if(dir == GPIO_OUTPUT)
	write(fd,"out",4);
else
	write(fd,"in",3);

close(fd);

return 0;
}
}



int gpio_set_val(unsigned int gpio, unsigned int val){

int fd, len;
char buf[MAX_BUF];
len = snprintf(buf,sizeof(buf) , SYSFS_GPIO_DIR "/gpio%d/value",gpio);

if(  (fd = open(buf,O_WRONLY)) > 0){
	if(val == GPIO_HIGH)
		write(fd,"1",2);
	else
		write(fd,"0",2);

close(fd);
}
return 0;
}


int gpio_get_val(unsigned int gpio, unsigned int*val){

char buf[MAX_BUF];

int fd, len;

len = snprintf(buf,sizeof(buf) , SYSFS_GPIO_DIR "/gpio%d/value",gpio);


if(  (fd = open(buf,O_RDONLY)) > 0){
	read(fd,buf,1);
	close(fd);

	if( *buf == '0')
		*val = GPIO_LOW;
	else
		*val = GPIO_HIGH;


}


return 0;
}


int gpio_read_val(unsigned int gpio){

char buf[MAX_BUF];
int fd, len;

len = snprintf(buf,sizeof(buf) , SYSFS_GPIO_DIR "/gpio%d/value",gpio);


if(  (fd = open(buf,O_RDONLY)) > 0){
	read(fd,buf,1);
	close(fd);

	if( *buf == '0')
		return 0;
	else
		return 1;


}

return 0;
}
