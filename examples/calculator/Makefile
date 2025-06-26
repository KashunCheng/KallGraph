CC      := clang
CFLAGS  := -Wno-error -O0 -fno-discard-value-names -finline-functions -g -Xclang -finline-functions -Xclang -disable-O0-optnone -Xclang -flegacy-pass-manager -Xclang -load -Xclang $$IRDumperPath
TARGET  := dynamic_call

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGET)
