CC = $(CROSS_COMPILE)gcc
CFLAGS = -O2 -Wall

LDFLAGS += -L$(NFSROOT)/lib
#LIBS += -lopenobex -lbluetooth -lmisc

OBJS = eventdump.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o eventdump

uim:
	$(CC) $(CFLAGS) $(LDFLAGS) uim_rfkill/$@.c -o $@

static: $(OBJS) 
	$(CC) $(LDFLAGS) --static $(OBJS) $(LIBS) -o eventdump

install:
	@echo Copy files to ${DEST_DIR}${BIN_DIR}
	@mkdir -p ${DEST_DIR}${BIN_DIR}
	@cp -f ./eventdump ${DEST_DIR}${BIN_DIR}
	@chmod 755 ${DEST_DIR}${BIN_DIR}/eventdump

clean:
	@rm -f *.o eventdump