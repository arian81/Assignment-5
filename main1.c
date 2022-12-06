#include <fcntl.h> // Include the fcntl.h header for the open() function
#include <unistd.h>
#include <stdio.h>

// Global variables
char buffer_in[160];            // Buffer for reading from the file
int read_pos = 16;             // Current read position in the buffer
int fd_in = -1;                // File descriptor for the input file
char fname_in[] = "input.txt"; // Name of the input file

char * fname_out; // File name
int fd_out = -1;               // File descriptor (initialized to -1)
char buffer_out[160];           // Write buffer
int buf_pos = 0;               // Current write position in the buffer

// Function to read a character from the file
char buf_in()
{
    // If the buffer is empty, refill it
    if (read_pos >= 16)
    {

        // Read a chunk of data from the file
        int num_read = read(fd_in, buffer_in + read_pos, 16);

        // If we reached the end of the file, return EOF
        if (num_read == 0)
            return '\0';

        // Reset the read position
        read_pos = 0;
    }

    // Return the next character from the buffer
    return buffer_in[read_pos++];
}

void buf_out(char data)
{
    // Check if the file descriptor is not open for writing
    if (fd_out == -1)
    {
        // Open the file for writing
        fd_out = open(fname_out, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

        // Check if the file was opened successfully
        if (fd_out == -1)
        {
            // Print an error message and return
            printf("Error opening file for writing!\n");
            return;
        }
    }

    // Add the character to the write buffer
    buffer_out[buf_pos] = data;

    // Increment the current write position in the buffer
    buf_pos++;

    // Check if the write buffer is full
    if (buf_pos == 16)
    {
        // Write the contents of the buffer to the file
        write(fd_out, buffer_out, 16);

        // Reset the current write position in the buffer
        buf_pos = 0;
    }
}

void buf_flush()
{
    // Check if the buffer is empty
    if (buf_pos == 0)
    {
        // The buffer is empty, so return without writing anything to the file
        return;
    }

    // Write the contents of the buffer to the file
    write(fd_out, buffer_out, buf_pos);

    // Reset the current write position in the buffer
    buf_pos = 0;
}

int main()
{
    // ===============================Testing the code================================
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



    // fname_out = "writetest1.txt";
    // fd_out = open(fname_out, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    // if (fd_out == -1)
    // {
    //     // Handle the error if the file could not be opened
    //     perror("Error opening file");
    //     return -1;
    // }
    // char *str = "Ut anim nulla irure voluptate anim ea Lorem sint incididunt fugiat in. Et incididunt tempor aute reprehenderit sit. Anim aute tempor exercitation. Officia aliqua exercitation quis elit consequat qui elit reprehenderit. Ipsum excepteur deserunt fugiat in non consequat ipsum ex officia sint tempor. Aute commodo enim ut ea dolore tempor ea consectetur esse irure. Duis sunt do proident ex culpa in sunt laboris laboris laborum nostrud aliquip. Ex irure duis fugiat est.";
    // for (int i = 0; i < 468; i++)
    // {
    //     buf_out(str[i]);
    // }
    // buf_flush();
    // close(fd_out);

    // fname_out = "writetest2.txt";
    // fd_out = open(fname_out, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    // if (fd_out == -1)
    // {
    //     // Handle the error if the file could not be opened
    //     perror("Error opening file");
    //     return -1;
    // }
    // str = "Hello world!";
    // for (int i = 0; i < 12; i++)
    // {
    //     buf_out(str[i]);
    // }
    // buf_flush();
    // close(fd_out);
    // // ===============================Evaluation================================
    // fname_in = "beemovie.txt"; // Set the input file name
    // fd_in = open(fname_in, O_RDONLY);
    // if (fd_in == -1)
    // {
    //     // Handle the error if the file could not be opened
    //     perror("Error opening file");
    //     return -1;
    // }
    // while (1)
    // {
    //     char c = buf_in();
    //     if (c == '\0')
    //         break;
    //     printf("%c", c);
    // }
    // close(fd_in);

    return 0;
}