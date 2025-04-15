#include <stdio.h>      // 표준 입출력 함수 사용 (printf, fprintf, fopen 등)
#include <stdint.h>     // 고정 크기 정수형 사용 (uint32_t 등)
#include <stdlib.h>     // 표준 라이브러리 함수 사용 (예: exit, malloc 등)
#include <arpa/inet.h>  // 네트워크 바이트 순서 변환 함수 사용 (ntohl 등)

int main(int argc, char *argv[]) {
    // 프로그램 실행 시 인자의 개수가 2개 이상인지 확인 (실행 파일 이름 + 최소 1개 파일 이름)
    if (argc < 2) {
        // 인자가 부족하면 사용법 출력 후 종료
        fprintf(stderr, "syntax : %s <file1> [<file2>...]\n", argv[0]);
        return 1;
    }

    uint32_t total = 0;  // 모든 파일에서 읽은 정수의 합을 저장할 변수

    // 파일 인자들을 순서대로 처리
    for (int i = 1; i < argc; i++) {
        // 파일을 바이너리 읽기 모드("rb")로 열기
        FILE *fp = fopen(argv[i], "rb");
        if (fp == NULL) {
            // 파일을 열 수 없는 경우 에러 메시지 출력 후 종료
            fprintf(stderr, "Could not open file: %s\n", argv[i]);
            return 1;
        }

        uint32_t num;  // 파일에서 읽어올 4바이트 정수를 저장할 변수
        // fread 함수로 4바이트를 읽어옴. 성공 시 1 반환
        size_t read_bytes = fread(&num, sizeof(uint32_t), 1, fp);
        if (read_bytes != 1) {
            // 읽은 바이트 수가 1이 아니면 에러 처리
            fprintf(stderr, "Failed to read 4 bytes from file: %s\n", argv[i]);
            fclose(fp);  // 파일 닫기
            return 1;
        }

        fclose(fp);  // 파일 닫기

        // 네트워크 바이트 순서(빅엔디안) → 호스트 바이트 순서(리틀엔디안)로 변환
        uint32_t host_num = ntohl(num);

        // 변환된 정수 값을 출력 (10진수와 16진수)
        printf("%u(0x%08x)", host_num, host_num);

        // 마지막 파일이 아니라면 + 출력
        if (i < argc - 1)
            printf(" + ");

        // 총합에 더하기
        total += host_num;
    }

    // 전체 합 출력 (10진수와 16진수)
    printf(" = %u(0x%08x)\n", total, total);

    return 0;  // 프로그램 정상 종료
}
