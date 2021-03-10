# TASK 2

## Objective Brief

in this task, you need to write C library for GPIO periherals of an ARM Cortex-M4 microcontroller from renesas.
please note that you are unable to do any compilation or testing due to the limited resources (need cros-compiler
and need the real hardware). so in the end, we will evalute your code based on the code precision and correctness


## Task Explanation

1. do not change any files inside the folder
2. put your GPIO library inside GPIO_driver folder and write it in gpio_driver.c and gpio_driver.h
3. write your main program code in main.c

follow the specification below for the **Main Program** and the **GPIO Driver**

### Main Program

configuration table
|  PORT | PIN |  MODE  | Value |
|-------|-----|--------|-------|
| PORT0 |  0  | output |  LOW  |
| PORT1 |  0  | output | HIGH  |
| PORT0 |  1  | input  |   -   |



- main program will be calling the initialization function of the GPIO (refer to the configuration table)
- set the output condition of some pins 
- read the input pin condition and print the value
- follow the instruction inside (the comments inside main function)

### GPIO Driver

- driver have a function to modify GPIO mode (act as input, output, analog, alternate function)
- driver have a function to set High or Low for GPIO that configured as output
- driver have a function to read GPIO that configured as input
- driver have a function to set alternate function mode (optional, it is point plus)
- you don't need to follow current template function (that is just for an example), and you can just add/modify the function and design it by yourself