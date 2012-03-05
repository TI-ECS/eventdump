#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define KEY_PLAYCD              200
#define KEY_STOPCD              166
#define KEY_PAUSECD             201
#define KEY_NEXTSONG            163
#define KEY_PREVIOUSSONG        165
#define KEY_REWIND              168
#define KEY_FASTFORWARD         208

static struct {
        const char *name;
        __u16 uinput;
} key_map[] = {
        { "PLAY",               KEY_PLAYCD },
        { "STOP",               KEY_STOPCD },
        { "PAUSE",              KEY_PAUSECD },
        { "FORWARD",            KEY_NEXTSONG },
        { "BACKWARD",           KEY_PREVIOUSSONG },
        { "REWIND",             KEY_REWIND },
        { "FAST FORWARD",       KEY_FASTFORWARD },
        { NULL,			0 },
};

int main(int argc, char **argv)
{
	int fd,i;
	if(argc < 2) {
		printf("usage: %s <device>\n", argv[0]);
		return 1;
	}
	fd = open(argv[1], O_RDONLY);
	struct input_event ev;

	while (1) {
		read(fd, &ev, sizeof(struct input_event));
		
		if ( ev.type == 1 && ev.value == 1 ) {
			for (i=0; (key_map[i].name != NULL) && (key_map[i].uinput != ev.code); i++);
			
			if (key_map[i].name != NULL) {
				printf("%s\n",key_map[i].name);
			}
			else {
				printf("Key %i State %i\n", ev.code, ev.value);
			}	
		}
	}
}

