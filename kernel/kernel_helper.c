#define _GNU_SOURCE
#include <assert.h>
#include <fcntl.h>
#include <linux/userfaultfd.h>
#include <poll.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

int die(char *text){                
    printf("Die: %s\n", text);
    exit(-1);
} 

int hexdump(char *target, int size){                
    for (int i=0; i<size/8; i++){                 
        printf("0x%x: 0x%llx\n", i*8, *(unsigned long*)(target+(i*8)));                                  
    }                                                                                                
}

static void* fault_handler_thread(void *arg) {
  char *dummy_page;
  static struct uffd_msg msg;
  struct uffdio_copy copy;
  struct pollfd pollfd;
  long uffd;
  static int fault_cnt = 0;

  uffd = (long)arg;

  dummy_page = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (dummy_page == MAP_FAILED) die("mmap(dummy)");

  puts("[+] fault_handler_thread: waiting for page fault...");
  pollfd.fd = uffd;
  pollfd.events = POLLIN;

  while (poll(&pollfd, 1, -1) > 0) {
    if (pollfd.revents & POLLERR || pollfd.revents & POLLHUP)
      die("poll");

    /* ページフォルト待機 */
    if (read(uffd, &msg, sizeof(msg)) <= 0) die("read(uffd)");
    assert (msg.event == UFFD_EVENT_PAGEFAULT);

    printf("[+] uffd: flag=0x%llx\n", msg.arg.pagefault.flags);
    printf("[+] uffd: addr=0x%llx\n", msg.arg.pagefault.address);

    /* 要求されたページとして返すデータを設定 */
    // function here

    //----------------------------------------------

    copy.src = (unsigned long)dummy_page;
    copy.dst = (unsigned long)msg.arg.pagefault.address & ~0xfff;
    copy.len = 0x1000;
    copy.mode = 0;
    copy.copy = 0;
    if (ioctl(uffd, UFFDIO_COPY, &copy) == -1) die("ioctl(UFFDIO_COPY)");
  }

  return NULL;
}

int register_uffd(void *addr, size_t len) {
  struct uffdio_api uffdio_api;
  struct uffdio_register uffdio_register;
  long uffd;
  pthread_t th;

  /* userfaultfdの作成 */
  uffd = syscall(__NR_userfaultfd, O_CLOEXEC | O_NONBLOCK);
  if (uffd == -1) die("userfaultfd");

  uffdio_api.api = UFFD_API;
  uffdio_api.features = 0;
  if (ioctl(uffd, UFFDIO_API, &uffdio_api) == -1)
    die("ioctl(UFFDIO_API)");

  /* ページをuserfaultfdに登録 */
  uffdio_register.range.start = (unsigned long)addr;
  uffdio_register.range.len = len;
  uffdio_register.mode = UFFDIO_REGISTER_MODE_MISSING;
  if (ioctl(uffd, UFFDIO_REGISTER, &uffdio_register) == -1)
    die("UFFDIO_REGISTER");

  /* ページフォルトを処理するスレッドを作成 */
  if (pthread_create(&th, NULL, fault_handler_thread, (void*)uffd))
    die("pthread_create");

  return 0;
}