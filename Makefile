SRC	= main.cpp
SUBDIRS	= Graphic TFT
TARGET	= HelloWorld

PREFIX	= arm-linux-gnueabihf-
CC	= $(PREFIX)g++
OBJS	= $(subst .c,.o,$(subst .cpp,.o,$(SRC)))
CFLAGS	= -g -I. -I./Graphic -I./TFT -Wall -Wsign-compare -Werror -O3
LDFLAGS	= -g -L./Graphic -lGraphic -L./TFT -lTFT -lbcm2835

.PHONE: all
all: $(TARGET)

# Subdirectories

.PHONY: subdirs $(SUBDIRS)
subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

$(TARGET): subdirs $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONE: clean
clean:
	for d in $(SUBDIRS); do (cd $$d; $(MAKE) clean); done
	rm -f $(TARGET) $(OBJS) $(OBJS:.o=.d) *.d.*

.PHONE: run
run: all
	ssh 192.168.3.24 'killall $(TARGET); /mnt/NFS$(PWD)/$(TARGET)'

-include $(OBJS:.o=.d)

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
