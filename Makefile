
TARGET = readpe

all = $(TARGET)

CC     = gcc
CFLAGS = -Wall -Wextra $(DEBUG_FLAGS)

$(TARGET): main.c main.o relative_address.o state.o updateStruct.o concat.o SectionSize.o COFFHeader.o readHeader.o OPTHeader.o SectionHeader.o *.h
	$(CC) $(CFLAGS) -o $(TARGET) main.o relative_address.o state.o updateStruct.o concat.o SectionSize.o COFFHeader.o OPTHeader.o SectionHeader.o readHeader.o

debug: DEBUG_FLAGS = -g -DDEBUG
debug: clean $(TARGET)

relative_address.o: relative_address.c relative_address.h
	$(CC) -c $(CFLAGS) relative_address.c
updateStruct.o: updateStruct.h updateStruct.c
	$(CC) -c $(CFLAGS) updateStruct.c
concat.o: concat.h concat.c
	$(CC) -c $(CFLAGS) concat.c
COFFHeader.o: COFFHeader.h COFFHeader.c
	$(CC) -c $(CFLAGS) COFFHeader.c
state.o: state.h state.c
	$(CC) -c $(CFLAGS) state.c
SectionSize.o: SectionSize.c SectionSize.h
	$(CC) -c $(CFLAGS) SectionSize.c
OPTHeader.o: OPTHeader.c OPTHeader.h
	$(CC) -c $(CFLAGS) OPTHeader.c
SectionHeader.o: SectionHeader.c SectionHeader.h
	$(CC) -c $(CFLAGS) SectionHeader.c
readHeader.o: readHeader.h readHeader.c *.h
	$(CC) -c $(CFLAGS) readHeader.c
main.o: main.c *.h
	$(CC) -c $(CFLAGS) main.c
clean:
	rm -f $(TARGET) *.o
#TESTS FOR READPE
test64:
	./readpe catnap64.exe

test32:
	./readpe catnap32.exe