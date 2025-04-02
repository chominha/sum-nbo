#include <stddef.h> // for size_t
#include <stdint.h> // for uint8_t
#include <stdio.h> // for printf
#include <netinet/in.h> // for htons, htonl

void dump(void* p, size_t n) {
	uint8_t* u8 = static_cast<uint8_t*>(p);
	size_t i = 0;
	while (true) {
		printf("%02X ", *u8++);
		if (++i >= n) break;
		if (i % 8 == 0)
			printf("\n");
	}
	printf("\n");
}

void write_4660() {
	uint16_t port = 4660; // 0x1234
	printf("port number = %d\n", port);
	dump(&port, sizeof(port));
}

void  write_0x1234() {
	uint8_t network_buffer[] = { 0x12, 0x34 };
	uint16_t* p = reinterpret_cast<uint16_t*>(network_buffer);
	uint16_t n = *p; // TODO
	printf("16 bit number=0x%x\n", n);
}

void  write_0x12345678() {
	uint8_t network_buffer[] = { 0x12, 0x34, 0x56, 0x78 };
	uint32_t* p = reinterpret_cast<uint32_t*>(network_buffer);
	uint32_t n = *p; // TODO
	printf("32 bit number=0x%x\n", n);
}

void htons_test() {
	uint16_t n1;
	scanf("%hu", &n1);
	uint16_t n2 = htons(n1);
	printf("%04x\n", n2);
}

void htonl_test() {
	uint32_t n1;
	scanf("%u", &n1);
	uint32_t n2 = htonl(n1);
	printf("%08x\n", n2);
}

int main() {
	write_4660();
	write_0x1234();
	write_0x12345678();
	htons_test();
	htonl_test();
}
