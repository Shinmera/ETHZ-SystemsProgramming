#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/* Portability: handle differing width of (E/R)FLAGS register. The inline
   assembly below uses no suffix; GCC will choose the appropriate instruction
   ({PUSHFL,POPL} or {PUSHFQ,POPQ}). */
#if defined(__i386__)
typedef uint32_t reg_flags_t;
#elif defined(__amd64__) || defined(__x86_64__)
typedef uint64_t reg_flags_t;
#else
#error unsupported architecture
#endif

/* Enumeration of the supported assembly instructions. */
enum instructions { CMPL, TESTL, ADDL };

/* A struct to store four important condition codes. */
struct ccodes {
  char cf, zf, sf, of;
};

/* Extract the CF, ZF, SF, and OF condition codes from the
   contents of the EFLAGS register passed in as an argument. */
struct ccodes getccodes(reg_flags_t eflags)
{
  struct ccodes ccodes;
  /********************************************************************
   * EDIT CODE BELOW
   *
   * Your task is to extract the condition codes from the EFLAGS
   * register (stored in parameter eflags) and fill the ccodes struct
   * appropriatly.
   *
   * You can find out about the bits that correspond to the condition
   * flags from the Intel Architecture Software Developer's Manual
   * (Volume 1, Section 3.4.3); the link to the document is indicated
   * on the course webpage.
   *********************************************************************/

  // Extract the carry flag from eflags such that bit 0 of ccodes.cf
  // correspond to the value of the carry flag.
  ccodes.cf = 0;

  // Extract the zero flag from eflags.
  ccodes.zf = 0;

  // Extract the sign flag from eflags.
  ccodes.sf = 0;

  // Extract the overflow flag from eflags.
  ccodes.of = 0;

  /********************************************************************
   * END EDITING
   ********************************************************************/

  return ccodes;
}

/* Execute the given instruction with the two operands specified and
   return the resulting contents of the EFLAGS register. */
reg_flags_t geteflags(enum instructions instr, int arg1, int arg2)
{
  reg_flags_t eflags;
  switch (instr) {
  case CMPL:
    asm("movl %2, %%eax; cmpl %1, %%eax; pushf; pop %0"
        // the assembly code string with placeholders
        : "=r" (eflags)
        // output:    %0 is an output register whose value will be copied to eflags
        : "r" (arg1), "r" (arg2)
        // input:     %1 and %2 are two input registers whose values are taken from arg1 and arg2
        : "%eax", "cc");
        // overwrite: the %eax register and condition codes are overwritten by the instruction sequence
    break;

  case TESTL:
    asm("movl %2, %%eax; testl %1, %%eax; pushf; pop %0"
        : "=r" (eflags)
        : "r" (arg1), "r" (arg2)
        : "%eax", "cc");
    break;

  case ADDL:
    asm("movl %2, %%eax; addl %1, %%eax; pushf; pop %0"
        : "=r" (eflags)
        : "r" (arg1), "r" (arg2)
        : "%eax", "cc");
    break;

  default:
    fprintf(stderr, "Error: unsupported instruction.");
    exit(1);
  }
  return eflags;
}

/* Execute the given assembly instruction and print the CD, ZF, SF,
   and OF condition codes to stdout. */
void printccodes(enum instructions instr, int arg1, int arg2)
{
  char *instrstr;
  switch (instr) {
    case CMPL:  instrstr = "cmpl"; break;
    case TESTL: instrstr = "testl"; break;
    case ADDL:  instrstr = "addl"; break;
    default: fprintf(stderr, "Error: unsupported instruction."); exit(1);
  }

  reg_flags_t eflags = geteflags(instr, arg1, arg2);
  struct ccodes ccodes = getccodes(eflags);
  printf("%s 0x%x, 0x%x\n  -> cf = %1d, zf = %1d, sf = %1d, of = %1d\n",
    instrstr, arg1, arg2, ccodes.cf, ccodes.zf, ccodes.sf, ccodes.of);
}

/* The main function. Execute a set of assembly instructions and
   print the resulting condition codes to stdout. */
int main()
{
  printccodes(CMPL, -4, 0xfffffffc);
  printccodes(CMPL, 4, 0xfffffffc);
  printccodes(CMPL, -1, 1);
  printccodes(CMPL, 2, 0x80000000);
  printccodes(CMPL, 0x7fffffff, 0x80000000);
  printccodes(CMPL, 0x80000000, 0x7fffffff);
  printccodes(CMPL, 1, 0x7fffffff);
  printccodes(CMPL, 0x80000000, 0x80000000);
  printccodes(CMPL, 0x7fffffff, 0xffffffff);
  exit(0);
}
