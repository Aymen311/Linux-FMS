
This program is written in C language and consists of three functions: Liste_Disques, Lire_Secteur, and Afficher_Secteur. The program allows you to list all available physical disks on your system, read a specific sector from a chosen disk, and display its content in hexadecimal format.

### Requirements
This program requires a C compiler to be installed on your system, such as GCC.

### Usage
- Compile the program with the following command:
```bash 
gcc -o program program.c
```
- Run the program with the following command:

```bash
./program
``` 

- The program will display a list of available physical disks on your system. Enter the name of the disk you want to read and the sector number you want to read.

- The program will display the content of the sector in hexadecimal format.

### Functions
**Liste_Disques()** : 
This function lists all available physical disks on the system. It reads the contents of the /proc/partitions file and searches for disks that have the prefix "sd" or "hd" and have a length of four characters.

**Lire_Secteur()**:
This function reads the sector with the given sector number from the specified disk and stores its content in a buffer. It uses the fopen() and fread() functions to read the sector.

**Afficher_Secteur()**:
This function calls the Lire_Secteur() function to read the sector with the given sector number from the specified disk and then displays its content in hexadecimal format. It uses a loop to iterate over the buffer and print each byte in hexadecimal format.
