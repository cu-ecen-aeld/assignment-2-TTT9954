#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int fd;
    ssize_t written;
    const char *filepath;
    const char *text;

    /* Setup syslog */
    openlog("writer", LOG_PID | LOG_CONS, LOG_USER);

    /* Check arguments */
    if (argc != 3) {
        syslog(LOG_ERR, "Invalid number of arguments. Usage: %s <file> <string>", argv[0]);
        closelog();
        return 1;
    }

    filepath = argv[1];
    text = argv[2];

    /* Open (or create) file */
    fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        syslog(LOG_ERR, "Error opening file %s: %s", filepath, strerror(errno));
        closelog();
        return 1;
    }

    /* Write string to file */
    written = write(fd, text, strlen(text));
    if (written == -1) {
        syslog(LOG_ERR, "Error writing to file %s: %s", filepath, strerror(errno));
        close(fd);
        closelog();
        return 1;
    }

    /* Log successful write */
    syslog(LOG_DEBUG, "Writing %s to %s", text, filepath);

    /* Cleanup */
    if (close(fd) == -1) {
        syslog(LOG_ERR, "Error closing file %s: %s", filepath, strerror(errno));
        closelog();
        return 1;
    }

    closelog();
    return 0;
}

