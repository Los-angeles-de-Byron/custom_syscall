# Custom syscall in linux kernel

Operating systems project

* [About the Project](#about-the-project)
  * [General process of linux boot](#general-process-of-linux-boot)
  * [Understanding the process behind a syscall](#understanding-the-process-behind-a-syscall)
    * [Conceptual diagram](#conceptual-diagram)
    * [Memory management](#memory-management)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Steps to install](#steps-to-install)
* [Usage](#usage)
* [References](#references)

## About the Project

This project is aimed to cover the following features:

1. Develop a function that determines if an arithmetic expression is found correctly closed. The function should return true if the expression is correctly closed and false otherwise

    <small> It is understood by closed the fact that each symbol of parentheses and / or open bracket must have its corresponding closing. Example (5 + 5), [(1 + 1) * (2 + 2)], (((([1])))) </small>

2. This function must be implemented in a system call that must receive as a parameter a pointer to the string containing the expression

3. The student must use C++ (or C) and the Linux kernel to add the system call

4. You will need to compile the operating system kernel to add the custom system call

5. You must create a program that receives as command line input the string to use and make use of the system call implemented in the operating system

### General process of linux boot

### Understanding the process behind a syscall

#### **Conceptual diagram**

#### **Memory management**

## Getting Started

### Prerequisites

* Ubuntu (64 bit) system

<i> In this project we used [Ubuntu VM (Virtualbox)](https://www.linuxvmimages.com/images/ubuntu-1604/)</i>

### Steps to install

<i> <strong>Tip: </strong> type sudo -s in your terminal before executing the upcoming commands so you will have a super user terminal session</i>

0. Type ```uname -r``` to know your current kernel version. Remember this information because you'll use it to compare to the installed one

1. Download kernel source

    ```sh
    wget https://www.kernel.org/pub/linux/kernel/v4.x/linux-4.17.4.tar.xz
    ```

2. Extract the kernel source code

    ```sh
    sudo tar -xvf linux-4.17.4.tar.xz -C/usr/src/
    ```

    <small>
    tar: stores and extracts files from a tape or disk archive

    -x: extract files from an archive

    -v: requested using the –verbose option, when extracting archives

    -f: file archive; use archive file or device archive

    -C: extract to the directory specified after it.(in this case /usr/src/)
    </small>

    Switch to directory

    ```sh
    cd /usr/src/linux-4.17.4/
    ```

3. Define a new system call

    a. Create a directory named balancedp/ and change the directory to balancedp/:

    ```sh
    mkdir balancedp
    cd balancedp
    ```

    b. Create a file balancedp.c

    ```sh
    gedit balancedp.c
    ```

    c. Write the following code:

    ```c

    ```

    d. Create a “Makefile” in the balancedp directory:

    ```sh
    gedit Makefile
    ```

    e. Add the following line to it:

    ```Makefile
    obj-y := balancedp.o
    ```

    <small> This is to ensure that the balancedp.c file is compiled and included in the kernel source code </small>

4. Adding balancedp/ to the kernel’s Makefile:

    a. Go to parent dir (``` cd ../ ```) and open "Makefile"

    ```sh
    gedit Makefile
    ```

    Search for core-y in the document, you’ll find this line as the second instance of your search:

    ```Makefile
    core-y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/
    ```

    Add "balancedp/" to the end of this line:

    ```Makefile
    core-y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/ balancedp/
    ```

    <small> This is to tell the compiler that the source files of our new system call (sys_balancedp()) are in present in the balancedp directory </small>

5. Add the new system call to the system call table:

    a. Go to directory inside linux-4.17.4/:

    ```sh
    cd arch/x86/entry/syscalls/
    ```

    Edit the table

    ```sh
    gedit syscall_64.tbl
    ```

    b. Go to the last line of the first chunk and write:

    ```tbl
    333       64        balancedp          sys_balancedp
    ```

    <small> 

    * We wrote 333 because in the previous line the number entry was 332. This number it will be used in later steps
    * We wrote 64 because our system is 64 bit

    </small>

6. Add new system call to the system call header file:

    a. Go to the linux-4.17.4/ directory and type:

    ```sh
    cd include/linux/
    gedit syscalls.h
    ```

    b. Add the following line to the end of the document before the #endif statement:

    ```h
    asmlinkage long sys_balancedp(char *);
    ```

    <small> This defines the prototype of the function of our system call. "asmlinkage" is a key word used to indicate that all parameters of the function would be available on the stack. </small>

7. Compile the kernel:

    a. Install necessary packages

    ```sh
    apt-get install gcc
    apt-get install libncurses5-dev
    apt-get install bison
    apt-get install flex
    apt-get install libssl-dev
    apt-get install libelf-dev
    apt-get update
    apt-get upgrade
    ```

    b. To configure your kernel use the following command in your linux-4.17.4/ directory:

    ```sh
    make menuconfig
    ```

    <small> You will get a pop up window with the list of menus and you can select the items for the new configuration. If your unfamiliar with the configuration just check for the file systems menu and check whether “ext4” is chosen or not, if not select it and save the configuration. </small>

    c. Compile the kernel

    ```sh
    make
    ```

8. Install / update Kernel:

    a. Run the following command in your terminal:

    ```sh
    make modules_install install
    ```

    b. To update the kernel in your system you will need to reboot

    ```sh
    shutdown -r now
    ```

    After rebooting you can verify the kernel version:

    ```sh
    uname -r
    ```

    You can compare it to the one you saw before and it must be different

## Usage

1. Go to any directory and create a <file_name>.c file

    <i> To keep simpicity we did it in the desktop </i>

2. Write the following code in the file:

    ```c
    ```

3. Compile and run the program:

    ```sh
    gcc <file_name>.c
    ./a.out
    ```

    Enter an expression to check parentheses. The address of the input you entered will be displayed as well as the return of the program

4. Check the message of your kernel run:

    ```sh
    dmesg
    ```

    This will display the input you entered before and the address that the kernel used to handle it. Down below you will see if your input has balanced parentheses or not

## References

* [Adding a Hello World System Call to Linux Kernel](https://medium.com/anubhav-shrimal/adding-a-hello-world-system-call-to-linux-kernel-dad32875872)
