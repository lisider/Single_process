#include <stdio.h>
#include <unistd.h>
#include "print_color.h"
/*
 * "\e[0;30m" 这样的一个字符串 定义后面的格式输出, 直到 一个新的这样的 字符串 A
 * 出现 ,才可以消除格式. 然后就延续 A 的格式 ,默认的格式 是 "\e[0m"
 *
 * 所以可以用 "\e[0m" 来消除之前格式的影响
 *
 * */

int main(void)
{
	printf("\033[31mThis text is red  This text has default color\n");  
	printf("\033[31;43mThis text is red with yellow background \033[0mThis text has default color\n");  
    printf("This is a character control test!\n" );
    sleep(3);
    printf("[%2u]" CLEAR "CLEAR\n" NONE, __LINE__);

    printf("[%2u]" BLACK "BLACK " L_BLACK "L_BLACK\n" NONE, __LINE__);
    printf("[%2u]" RED "RED " L_RED "L_RED\n" NONE, __LINE__);
    printf("[%2u]" RED "REF " L_RED "L_RED\n" NONE, __LINE__);
    printf("[%2u]" GREEN "GREEN " L_GREEN "L_GREEN\n" NONE, __LINE__);
    printf("[%2u]" BROWN "BROWN " YELLOW "YELLOW\n" NONE, __LINE__);
    printf("[%2u]" BLUE "BLUE " L_BLUE "L_BLUE\n" NONE, __LINE__);
    printf("[%2u]" PURPLE "PURPLE " L_PURPLE "L_PURPLE\n" NONE, __LINE__);
    printf("[%2u]" CYAN "CYAN " L_CYAN "L_CYAN\n" NONE, __LINE__);
    printf("[%2u]" GRAY "GRAY " WHITE "WHITE\n" NONE, __LINE__);

    printf("[%2u]\e[1;31;40m Red \e[0m\n",  __LINE__);

    printf("[%2u]" BOLD "BOLD\n" NONE, __LINE__);
    printf("[%2u]" UNDERLINE "UNDERLINE\n" NONE, __LINE__);
    printf("[%2u]" BLINK "BLINK\n" NONE, __LINE__);
    printf("[%2u]" REVERSE "REVERSE\n" NONE, __LINE__);
    printf("[%2u]" HIDE "HIDE\n" NONE, __LINE__);

    printf("Cursor test begins!\n" );
    printf("=======!\n" );
    sleep(10);
    printf("[%2u]" "\e[2ACursor up 2 lines\n" NONE, __LINE__);
    sleep(10);
    printf("[%2u]" "\e[2BCursor down 2 lines\n" NONE, __LINE__);
    sleep(5);
    printf("[%2u]" "\e[?25lCursor hide\n" NONE, __LINE__);
    sleep(5);
    printf("[%2u]" "\e[?25hCursor display\n" NONE, __LINE__);
    sleep(5);

    printf("Test ends!\n" );
    sleep(3);
    printf("[%2u]" "\e[2ACursor up 2 lines\n" NONE, __LINE__);
    sleep(5);
    printf("[%2u]" "\e[KClear from cursor downward\n" NONE, __LINE__);

    return 0 ;
}
