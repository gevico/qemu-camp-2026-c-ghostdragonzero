#include "myfile.h"

void print_elf_type(uint16_t e_type) {
    const char *type_str;
    switch (e_type) {
    case ET_NONE:
      type_str = "Unknown (ET_NONE)";
      break;
    case ET_REL:
      type_str = "Relocatable (ET_REL)";
      break;
    case ET_EXEC:
      type_str = "Executable (ET_EXEC)";
      break;
    case ET_DYN:
      type_str = "Shared Object/PIE (ET_DYN)";
      break;
    case ET_CORE:
      type_str = "Core Dump (ET_CORE)";
      break;
    default:
      if (e_type >= ET_LOOS && e_type <= ET_HIOS)
        type_str = "OS-Specific";
      else if (e_type >= ET_LOPROC && e_type <= ET_HIPROC)
        type_str = "Processor-Specific";
      else
        type_str = "Invalid";
    }
    printf("ELF Type: %s (0x%x)\n", type_str, e_type);
}

int __cmd_myfile(const char* filename) {
    char filepath[256];
    int fd;
    Elf64_Ehdr ehdr;

    strcpy(filepath, filename);
    fflush(stdout);
    printf("filepath: %s\n", filepath);

    // TODO: 在这里添加你的代码
    
      //printf("Analyzing file: %s\n", filepath);
      
      // 1. 打开文件
      fd = open(filepath, O_RDONLY);
      if (fd < 0) {
        perror("open");
      }
  
      // 2. 读取 ELF 文件头
      // ELF 文件头位于文件最开始处，大小为一个 Elf64_Ehdr 结构体
      ssize_t bytes_read = read(fd, &ehdr, sizeof(Elf64_Ehdr));
      if (bytes_read != sizeof(Elf64_Ehdr)) {
        perror("read");

      }
  
      // 3. 校验魔数 (Magic Number)
      // ELF 文件的前4个字节必须是 0x7f, 'E', 'L', 'F'
      if (ehdr.e_ident[EI_MAG0] != ELFMAG0 || 
          ehdr.e_ident[EI_MAG1] != ELFMAG1 || 
          ehdr.e_ident[EI_MAG2] != ELFMAG2 || 
          ehdr.e_ident[EI_MAG3] != ELFMAG3) {
        printf("Not a valid ELF file.\n\n");

      }

    print_elf_type(ehdr.e_type);
    close(fd);
    
    return 0;
}