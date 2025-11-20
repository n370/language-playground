// https://github.com/rtfeldman/c-workshop-v1/blob/dd100eb96ab3c5b56d884c7cd46f2545ff129f01/exercises/4.c

#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

const char* DEFAULT_FILE = "index.html";

char *to_path(char *req) {
  char *start, *end;

  for (start = req; start[0] != ' '; start ++) {
    if (!start[0]) {
      return NULL;
    }
  }

  start++;

  for (end = start; end[0] != ' '; end++) {
    if (!end[0]) {
      return NULL;
    }
  }

  if (end[-1] != '/') {
    end[0] = '/';
    end++;
  }

  if (end + strlen(DEFAULT_FILE) > req + strlen(req)) {
    return NULL;
  }

  memcpy(end, DEFAULT_FILE, strlen(DEFAULT_FILE) + 1);

  return start + 1;
}

void print_file(const char *path) {
  int fd = open(path, O_RDONLY);

  if (fd == -1) {
    return;
  }

  struct stat metadata;

  if (fstat(fd, &metadata) == -1) {
    close(fd);
    return;
  }

  // char buf[metadata.st_size + 1];
  char *buf = malloc(metadata.st_size + 1);

  if (buf == NULL) {
    close(fd);
    return;
  }

  ssize_t bytes_read = read(fd, buf, metadata.st_size);

  if (bytes_read == -1) {
    free(buf);
    close(fd);
    return;
  }

  buf[bytes_read] = '\0';
  printf("\n%s contents:\n\n%s\n", path, buf);

  free(buf);
  close(fd);
}

int main() {
  char req1[] = "GET / HTTP/1.1\nHost: example.com";
  print_file(to_path(req1));

  char req2[] = "GET /blog HTTP/1.1\nHost: example.com";
  print_file(to_path(req2));

  return 0;
}
