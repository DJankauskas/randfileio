#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <fcntl.h>
#include <unistd.h>

void print_random_numbers(int *array, size_t len) {
    for(size_t i = 0; i < len; i++) {
        printf("Random %zd: %d\n", i, array[i]);
    }
}

void handle_file_error(int fd) {
    if (fd < 0) {
        printf("File error %d: %s\n", errno, strerror(errno));
        exit(1);
    }
}

int main() {
    printf("Opening /dev/random:\n");
    int rand_fd = open("/dev/random", O_RDONLY);
    handle_file_error(rand_fd);

    int random_numbers[10];
    printf("Reading random numbers:\n");
    read(rand_fd, random_numbers, sizeof(random_numbers));
    print_random_numbers(random_numbers, 10);
    close(rand_fd);

    printf("\nWriting to file:\n");
    int write_fd = open("./randnums", O_CREAT | O_WRONLY, 0666);
    handle_file_error(write_fd);
    if(write(write_fd, random_numbers, sizeof(random_numbers)) < 0) {
        printf("Write failed: %s.\n", strerror(errno));
        exit(1);
    }
    close(write_fd);

    printf("Reading from file:\n");
    int read_fd = open("./randnums", O_RDONLY);
    handle_file_error(read_fd);
    int read_numbers[10];
    if(read(read_fd, read_numbers, sizeof read_numbers) < 0) {
        printf("Read failed: %s.\n", strerror(errno));
        exit(0);
    }
    printf("\nVerification written numbers are the same:\n");
    print_random_numbers(read_numbers, 10);
    close(read_fd);

    return 0;
}