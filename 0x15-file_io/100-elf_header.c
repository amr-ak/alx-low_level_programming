#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>

void print_magic(unsigned char *e_ident)
{
    printf("  Magic:   ");
    for (int i = 0; i < EI_NIDENT; i++)
        printf("%02x ", e_ident[i]);
    printf("\n");
}

void print_class(unsigned char e_ident[EI_NIDENT])
{
    printf("  Class:                             ");
    if (e_ident[EI_CLASS] == ELFCLASSNONE)
        printf("none\n");
    else if (e_ident[EI_CLASS] == ELFCLASS32)
        printf("ELF32\n");
    else if (e_ident[EI_CLASS] == ELFCLASS64)
        printf("ELF64\n");
}

void print_data(unsigned char e_ident[EI_NIDENT])
{
    printf("  Data:                              ");
    if (e_ident[EI_DATA] == ELFDATANONE)
        printf("none\n");
    else if (e_ident[EI_DATA] == ELFDATA2LSB)
        printf("2's complement, little endian\n");
    else if (e_ident[EI_DATA] == ELFDATA2MSB)
        printf("2's complement, big endian\n");
}

void print_version(unsigned char e_ident[EI_NIDENT])
{
    printf("  Version:                           ");
    if (e_ident[EI_VERSION] == EV_NONE)
        printf("none\n");
    else if (e_ident[EI_VERSION] == EV_CURRENT)
        printf("1 (current)\n");
}

void print_osabi(unsigned char e_ident[EI_NIDENT])
{
    printf("  OS/ABI:                            ");
    if (e_ident[EI_OSABI] == ELFOSABI_NONE)
        printf("UNIX - System V\n");
    else if (e_ident[EI_OSABI] == ELFOSABI_HPUX)
        printf("UNIX - HP-UX\n");
    else if (e_ident[EI_OSABI] == ELFOSABI_NETBSD)
        printf("UNIX - NetBSD\n");
    else if (e_ident[EI_OSABI] == ELFOSABI_LINUX)
        printf("UNIX - Linux\n");
}

void print_abiversion(unsigned char e_ident[EI_NIDENT])
{
    printf("  ABI Version:                       %d\n", e_ident[EI_ABIVERSION]);
}

void print_type(Elf64_Half e_type)
{
    printf("  Type:                              ");
    if (e_type == ET_NONE)
        printf("NONE (None)\n");
    else if (e_type == ET_REL)
        printf("REL (Relocatable file)\n");
    else if (e_type == ET_EXEC)
        printf("EXEC (Executable file)\n");
    else if (e_type == ET_DYN)
        printf("DYN (Shared object file)\n");
    else if (e_type == ET_CORE)
        printf("CORE (Core file)\n");
}

void print_entry(Elf64_Addr e_entry)
{
    printf("  Entry point address:               %#lx\n", e_entry);
}

void elf_header(char *filename)
{
    int fd;
    Elf64_Ehdr header;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        exit(98);
    }

    if (read(fd, &header, sizeof(header)) != sizeof(header))
    {
        fprintf(stderr, "Error: Could not read file %s\n", filename);
        exit(98);
    }

    if (header.e_ident[EI_MAG0] != ELFMAG0 ||
        header.e_ident[EI_MAG1] != ELFMAG1 ||
        header.e_ident[EI_MAG2] != ELFMAG2 ||
        header.e_ident[EI_MAG3] != ELFMAG3)
    {
        fprintf(stderr, "Error: %s is not an ELF file\n", filename);
        exit(98);
    }

    print_magic(header.e_ident);
    print_class(header.e_ident);
    print_data(header.e_ident);
    print_version(header.e_ident);
    print_osabi(header.e_ident);
    print_abiversion(header.e_ident);
    print_type(header.e_type);
    print_entry(header.e_entry);

    if (close(fd) == -1)
    {
        fprintf(stderr, "Error: Could not close file %s\n", filename);
        exit(98);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
        exit(98);
    }

    elf_header(argv[1]);

    return (0);
}

