// https://github.com/rtfeldman/c-workshop-v1/blob/dd100eb96ab3c5b56d884c7cd46f2545ff129f01/exercises/5.c

#include <stdio.h>
// #include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <errno.h>

const int PORT = 8080;
// const int MAX_REQUEST_BYTES = 32768;
const char* DEFAULT_FILE = "index.html";

// Workaround clang warning "variable length array folded to constant array" .
// https://stackoverflow.com/a/18435398
#define MAX_REQUEST_BYTES 32768

char *to_path(char *req) {
  char *start, *end;

  for (start = req; start[0] != ' '; start++) {
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

const char *ERR_400 = "HTTP/1.1 400 Bad Request\n\n";
const char *ERR_404 = "HTTP/1.1 404 Not Found\n\n";
const char *ERR_413 = "HTTP/1.1 413 Content Too Large\n\n";
const char *ERR_500 = "HTTP/1.1 500 Internal Server Error\n\n";

int handle_req(char *request, int socket_fd) {
  char *path = to_path(request);

  if (path == NULL) {
    // printf("HTTP/1.1 400 Bad Request\n\n");
    write(socket_fd, ERR_400, strlen(ERR_400));
    return -1;
  }

  int fd = open(path, O_RDONLY);

  if (fd == -1) {
    if (errno == ENOENT) {
      // printf("HTTP/1.1 404 Not Found\n\n");
      write(socket_fd, ERR_404, strlen(ERR_404));
    } else {
      // printf("HTTP/1.1 500 Internal Server Error\n\n");
      write(socket_fd, ERR_500, strlen(ERR_500));
    }

    return -1;
  }

  struct stat stats;

  if (fstat(fd, &stats) == -1) {
    // printf("HTTP/1.1 500 Internal Server Error\n\n");
    write(socket_fd, ERR_500, strlen(ERR_500));
    return -1;
  }

  {
    const char *OK = "HTTP/1.1 200 OK\n\n";
    size_t bytes_written = 0;
    size_t bytes_to_write = strlen(OK);

    while (bytes_to_write) {
      bytes_written = write(socket_fd, OK + bytes_written, bytes_to_write);

      if (bytes_written == -1) {
        // printf("HTTP/1.1 500. Internal Server Error\n\n");
        write(socket_fd, ERR_500, strlen(ERR_500));
        return -1;
      }

      bytes_to_write -= bytes_written;
    }
  }

  {
    char buffer[4096];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof((buffer)))) > 0) {
      ssize_t bytes_written = 0;
      ssize_t bytes_remaining = bytes_read;

      while (bytes_remaining > 0) {
        ssize_t result = write(socket_fd, buffer + bytes_written, bytes_remaining);

        if (result == -1) {
          write(socket_fd, ERR_500, strlen(ERR_500));
          return -1;
        }

        bytes_written += result;
        bytes_remaining -= result;
      }
    }

    if (bytes_read == -1) {
      write(socket_fd, ERR_500, strlen(ERR_500));
      return -1;
    }
  }

  close(fd);

  return 0;
}

int main() {
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_fd == -1) {
    printf("Opening socket failed.\n");
    return -1;
  }

  int opt = 1;

  if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
    printf("Setting socket options failed.\n");
    return -1;
  }

  struct sockaddr_in address;

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
    printf("bind() failed.\n");
    return -1;
  }

  if (listen(socket_fd, 4) == -1) {
    printf("listen() failed.\n");
    return -1;
  }

  printf("Listening on port %d\n", PORT);

  char req[MAX_REQUEST_BYTES + 1];
  int addrlen = sizeof(address);

  while (1) {
    int req_socket_fd = accept(socket_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    if (req_socket_fd >= 0) {
      ssize_t bytes_read = read(req_socket_fd, req, MAX_REQUEST_BYTES);

      if (bytes_read < MAX_REQUEST_BYTES) {
        req[bytes_read] = '\0';
        handle_req(req, req_socket_fd);
      } else {
        // printf("HTTP/1.1 413 Content Too Large\n\n");
        write(socket_fd, ERR_413, strlen(ERR_413));
      }

      close(req_socket_fd);
    }
  }

  return 0;
}
