#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h> // 包含 ELF 相关的结构体定义

// 打印 ELF 文件类型
void print_elf_type(uint16_t e_type) {
  const char *type_str;
  switch (e_type) {
    // TODO: 在这里添加你的代码
    case ET_NONE:   type_str = "No file type";          break;
    case ET_REL:    type_str = "Relocatable file";      break;
    case ET_EXEC:   type_str = "Executable file";       break;
    case ET_DYN:    type_str = "Shared Object/PIE";    break;
    case ET_CORE:   type_str = "Core file";             break;
    default:        type_str = "Unknown type";          break;
  }
  printf("ELF Type: %s (0x%x)\n", type_str, e_type);
}

int main(int argc, char *argv[]) {
  char filepath[2][256] = {
    "./17_myfile.o",
    "./17_myfile",
  };

  int fd;
  Elf64_Ehdr ehdr; // 64位 ELF 文件头结构体

  // TODO: 在这里添加你的代码
  for (int i = 0; i < 2; i++) {
    printf("Analyzing file: %s\n", filepath[i]);
    
    // 1. 打开文件
    fd = open(filepath[i], O_RDONLY);
    if (fd < 0) {
      perror("open");
      continue; // 如果打开失败，跳过本次循环
    }

    // 2. 读取 ELF 文件头
    // ELF 文件头位于文件最开始处，大小为一个 Elf64_Ehdr 结构体
    ssize_t bytes_read = read(fd, &ehdr, sizeof(Elf64_Ehdr));
    if (bytes_read != sizeof(Elf64_Ehdr)) {
      perror("read");
      close(fd);
      continue;
    }

    // 3. 校验魔数 (Magic Number)
    // ELF 文件的前4个字节必须是 0x7f, 'E', 'L', 'F'
    if (ehdr.e_ident[EI_MAG0] != ELFMAG0 || 
        ehdr.e_ident[EI_MAG1] != ELFMAG1 || 
        ehdr.e_ident[EI_MAG2] != ELFMAG2 || 
        ehdr.e_ident[EI_MAG3] != ELFMAG3) {
      printf("Not a valid ELF file.\n\n");
      close(fd);
      continue;
    }

    // 4. 调用函数打印类型
    print_elf_type(ehdr.e_type);
    
    printf("\n"); // 打印空行分隔

    // 5. 关闭文件
    close(fd);
  }
  
  return 0;
}