// Routines to let C code use special x86 instructions.

static inline uchar
inb(ushort port) // read a character from a port
{
  uchar data;

  asm volatile("in %1,%0" : "=a" (data) : "d" (port)); // =a refers to eax, d refers to edx
  return data;
}

static inline void
insl(int port, void *addr, int cnt) // read cnt 32 bit words from a port (insl stands for input string long)
{
  asm volatile("cld; rep insl" : // cld clears direction register, the direction of movement of pointers after copying the data from source to destination. rep instruction copies repeatedly. Opposite of cld is std (set direction register). if set, the pointers decrement while copying the data.
               "=D" (addr), "=c" (cnt) :
               "d" (port), "0" (addr), "1" (cnt) :
               "memory", "cc");
}

static inline void
outb(ushort port, uchar data) // write byte to a port
{
  asm volatile("out %0,%1" : : "a" (data), "d" (port));
}

static inline void
outw(ushort port, ushort data) // write word to a port
{
  asm volatile("out %0,%1" : : "a" (data), "d" (port));
}

static inline void 
outsl(int port, const void *addr, int cnt) // write cnt number of 32 bit words to a port
{
  asm volatile("cld; rep outsl" :
               "=S" (addr), "=c" (cnt) :
               "d" (port), "0" (addr), "1" (cnt) :
               "cc");
}

static inline void
stosb(void *addr, int data, int cnt) // store string byte
{
  asm volatile("cld; rep stosb" :
               "=D" (addr), "=c" (cnt) :
               "0" (addr), "1" (cnt), "a" (data) :
               "memory", "cc");
}

static inline void
stosl(void *addr, int data, int cnt) // store string long
{
  asm volatile("cld; rep stosl" :
               "=D" (addr), "=c" (cnt) :
               "0" (addr), "1" (cnt), "a" (data) :
               "memory", "cc");
}