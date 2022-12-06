#include <fcntl.h> // Include the fcntl.h header for the open() function
#include <unistd.h>
#include <stdio.h>

// Global variables
char buffer_in[16];            // Buffer for reading from the file
int read_pos = 0;             // Current read position in the buffer
int fd_in = -1;                // File descriptor for the input file
char fname_in[] = "input.txt"; // Name of the input file

char buf_in()
{
    if (read_pos >= 16)
    {

        // Read a chunk of data from the file
        int num_read = read(fd_in, buffer_in, 16);

        // If we reached the end of the file, return EOF
        if (num_read == 0)
            return '\0';

        // Reset the read position
        read_pos = 0;
    }


    // Return the next character from the buffer
    return buffer_in[read_pos++];
}

int main(){
  // fname_in = "input.txt"; // Set the input file name
  fd_in = open(fname_in, O_RDONLY);
  if (fd_in == -1)
  {
      // Handle the error if the file could not be opened
      perror("Error opening file");
      return -1;
  }
  while (1)
    {
        char c = buf_in();
        if (c == '\0')
            break;
        printf("%c", c);
    }
}