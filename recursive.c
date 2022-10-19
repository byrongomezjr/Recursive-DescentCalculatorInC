/* Byron Gomez */
/* October 19, 2022 */
/* Programming Language Concepts */
/* Recursive-Descent Calculator in C*/

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

int token;

void command();
int expr();
int term();
int factor();
int number();
int digit();

void error(char *message)
{
    printf("parse error: %s\n", message);
    exit(1);
}

void getToken()
{
    token = getchar();
}

void match(char c, char *message)
{
    if (token == c)
        getToken();
    else
        error(message);
}

void command()
{
    int result = expr();
    if (token == '\n')
        printf("The result is: %d\n", result);
    else
        error("tokens after end of expression");
}

/* TASK: Add subtraction term*/
int expr()
{
    int result = term();
    while (token == '+')
    {
        match('+', "+ expected");
        result += term();
    }
    if (token == '-')
    {
        match('-', "- expected");
        result -= term();
    }
    return result;
}

/* TASK: Add division factor*/
int term()
{

    int result = factor();
    while (token == '*')
    {
        match('*', "* expected");
        result *= factor();
    }
    if (token == '/')
    {

        match('/', "/ expected");
        result /= factor();
    }
    return result;
}

int factor()
{

    int result;
    if (token == '(')
    {
        match('(', "( expected");
        result = expr();
        match(')', ") expected");
    }
    else
        result = number();
    return result;
}

int number()
{

    int result = digit();
    while (isdigit(token))

        result = 10 * result + digit();
    return result;
}

int digit()
{

    int result;
    if (isdigit(token))
    {

        result = token - '0';
        match(token, "( expected");
    }
    else
        error("digit expected");
    return result;
}

void parse()
{
    getToken();
    command();
}

int main()
{
    parse();
    return 0;
}