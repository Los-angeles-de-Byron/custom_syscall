#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/syscalls.h>

int areBracketsBalanced(char *s);

SYSCALL_DEFINE1(balancedp, char *, src)
{
        printk("%s\n", src);
	printk("Memory address of input %p\n", &src);
    
	if (areBracketsBalanced(src)) 
		printk("Balanced \n"); 
	else
		printk("Not Balanced \n"); 
        return 0;
}

int areBracketsBalanced(char *s) 
{ 
  char *q=s;
  char *p;
  for (p=s; *p; p++) 
    switch(*p) {
      case '(': *q++ = ')'; continue;
      case '{': *q++ = '}'; continue;
      case '[': *q++ = ']'; continue;
      case '0': continue; 
      case '1': continue; 
      case '2': continue; 
      case '3': continue; 
      case '4': continue; 
      case '5': continue; 
      case '6': continue; 
      case '7': continue; 
      case '8': continue; 
      case '9': continue; 
      case '+': continue; 
      case '*': continue; 
      case '-': continue; 
      case '/': continue; 
      default: if (q==s || *p != *--q) return 0;
    }
  
  return q==s;
} 
