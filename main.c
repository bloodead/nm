#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <elf.h>

int	my_read(int fd, void* addr, size_t size)
{
	ssize_t	ret;

	ret = read(fd, addr, size);
	if ((size_t)ret != size)
		return (-1);
	return (ret);
}

int	main(int argc, char** argv)
{
	int		fd;
	Elf32_Ehdr	header;
	char		elfheader[5];

	elfheader[0] = ELFMAG0;
	elfheader[1] = ELFMAG1;
	elfheader[2] = ELFMAG2;
	elfheader[3] = ELFMAG3;
	elfheader[4] = 0;
	if(argc > 1)
	{
		fd = open(argv[1], O_RDONLY, 0700);
		if (fd < 0)
			return (42);
		read(fd, &header, sizeof(header));
		if (strncmp(header.e_ident, elfheader, 4) == 0)
		{
			printf("Section offset: %d\n", header.e_shoff);
			printf("Section num: %d\n", header.e_shnum);
		}
		else
			printf("NOT AN ELF\n");
		lseek(fd, header.e_shoff, SEEK_SET);
	}
	return (0);
}
