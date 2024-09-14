#include <stdio.h>
#include <stdint.h>
#include <machine/endian.h>

#include "sigar.h"
#include "sigar_private.h"
#include "sigar_util.h"
#include "sigar_os.h"

#define EI_CLASS    4
#define ELFCLASS32  1
#define ELFCLASS64  2

#define EI_DATA     5
#define ELFDATA2LSB 1
#define ELFDATA2MSB 2

#define EI_NIDENT 16

union elf_ehdr {
    struct {
        unsigned char e_ident[EI_NIDENT];
        uint16_t e_type;
        uint16_t e_machine;
        uint32_t e_version;
        uint32_t e_entry;
        uint32_t e_phoff;
        uint32_t e_shoff;
        uint32_t e_flags;
        uint16_t e_ehsize;
        uint16_t e_phentsize;
        uint16_t e_phnum;
        uint16_t e_shentsize;
        uint16_t e_shnum;
        uint16_t e_shstrndx;
    } elf32;

    struct {
        unsigned char e_ident[EI_NIDENT];
        uint16_t e_type;
        uint16_t e_machine;
        uint32_t e_version;
        uint64_t e_entry;
        uint64_t e_phoff;
        uint64_t e_shoff;
        uint32_t e_flags;
        uint16_t e_ehsize;
        uint16_t e_phentsize;
        uint16_t e_phnum;
        uint16_t e_shentsize;
        uint16_t e_shnum;
        uint16_t e_shstrndx;
    } elf64;
};

static const char * elf_em_to_str(int em)
{
    switch (em) {
        case 0: return "none";
        case 1: return "m32";
        case 2: return "sparc";
        case 3: return "x86";
        case 4: return "68k";
        case 5: return "88k";
        case 7: return "860";
        case 8: return "mips";
        case 9: return "s370";
        case 10: return "mips_rs3_le";
        case 15: return "parisc";
        case 17: return "vpp500";
        case 18: return "sparc32plus";
        case 19: return "960";
        case 20: return "ppc";
        case 21: return "ppc64";
        case 22: return "s390";
        case 36: return "v800";
        case 37: return "fr20";
        case 38: return "rh32";
        case 39: return "rce";
        case 40: return "arm";
        case 41: return "fake_alpha";
        case 42: return "sh";
        case 43: return "sparcv9";
        case 44: return "tricore";
        case 45: return "arc";
        case 46: return "h8_300";
        case 47: return "h8_300h";
        case 48: return "h8s";
        case 49: return "h8_500";
        case 50: return "ia_64";
        case 51: return "mips_x";
        case 52: return "coldfire";
        case 53: return "68hc12";
        case 54: return "mma";
        case 55: return "pcp";
        case 56: return "ncpu";
        case 57: return "ndr1";
        case 58: return "starcore";
        case 59: return "me16";
        case 60: return "st100";
        case 61: return "tinyj";
        case 62: return "x86_64";
        case 63: return "pdsp";
        case 66: return "fx66";
        case 67: return "st9plus";
        case 68: return "st7";
        case 69: return "68hc16";
        case 70: return "68hc11";
        case 71: return "68hc08";
        case 72: return "68hc05";
        case 73: return "svx";
        case 74: return "st19";
        case 75: return "vax";
        case 76: return "cris";
        case 77: return "javelin";
        case 78: return "firepath";
        case 79: return "zsp";
        case 80: return "mmix";
        case 81: return "huany";
        case 82: return "prism";
        case 83: return "avr";
        case 84: return "fr30";
        case 85: return "d10v";
        case 86: return "d30v";
        case 87: return "v850";
        case 88: return "m32r";
        case 89: return "mn10300";
        case 90: return "mn10200";
        case 91: return "pj";
        case 92: return "openrisc";
        case 93: return "arc_a5";
        case 94: return "xtensa";
        case 113: return "altera_nios2";
        case 183: return "aarch64";
        case 188: return "tilepro";
        case 189: return "microblaze";
        case 191: return "tilegx";
        case 192: return "num";
        case 0x9026: return "alpha";
        default: return "unknown";
    }
}

static int elf_file_get_em(const char *path)
{
    int em = -1;
    union elf_ehdr hdr;
    FILE *f = fopen(path, "rb");
    if (f) {
        if (fread(&hdr, 1, sizeof(hdr), f) != sizeof(hdr)) {
            goto out;
        }
        if (hdr.elf32.e_ident[EI_CLASS] == ELFCLASS32) {
            if (hdr.elf32.e_ident[EI_DATA] == ELFDATA2LSB) {
                em = le16toh(hdr.elf32.e_machine);
            } else if (hdr.elf32.e_ident[EI_DATA] == ELFDATA2MSB) {
                em = be16toh(hdr.elf32.e_machine);
            }
        } else if (hdr.elf32.e_ident[EI_CLASS] == ELFCLASS64) {
            if (hdr.elf64.e_ident[EI_DATA] == ELFDATA2LSB) {
                em = le16toh(hdr.elf64.e_machine);
            } else if (hdr.elf64.e_ident[EI_DATA] == ELFDATA2MSB) {
                em = be16toh(hdr.elf64.e_machine);
            }
        }
    }

out:
    if (f) {
        fclose(f);
    }
    return em;
}

const char *sigar_elf_file_get_arch(const char *path)
{
    int em = elf_file_get_em(path);
    return (em != -1) ? elf_em_to_str(em) : NULL;
}

const char *sigar_elf_file_guess_arch(sigar_t *sigar, const char *path)
{
    int em = -1;
    if (path != NULL && strlen(path) > 0)
        em = elf_file_get_em(path);
    return (em != -1) ? elf_em_to_str(em) : sigar->arch;
}
