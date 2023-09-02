/**
 * @file      babylon.c
 * @version   0.1.0
 * @brief     Compute the truncated square root of a positive non-null
 * integer using the Babylonian algorithm (Heron's method).
 * @year      2023
 * @author    Alexandre Martos
 * @email     contact@amartos.fr
 * @copyright GPLv3
 * @compilation
 * gcc -xc -Wall -std=c99 babylon.c -o babylon
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @enum Options
 * @since 0.1.0
 * @brief Program's short options.
 */
typedef enum Options {
    HELP    = 'h', /**< Outputs the #HELP. */
    VERSION = 'v', /**< Outputs the #VERSION. */
    LICENSE = 'w', /**< Outputs the #LICENSE. */
} Options;

/**
 * @def VERSION_STR
 * @since 0.1.0
 * @brief The program's version number.
 */
#define VERSION_STR "0.1.0"

/**
 * @def LICENSE_STR
 * @since 0.1.0
 * @brief The program's license name.
 */
#define LICENSE_STR                                                     \
    "babylon " VERSION_STR " - Copyright 2023 Alexandre Martos <contact@amartos.fr>\n" \
    "\n"                                                                \
    "This program is free software: you can redistribute it and/or modify\n" \
    "it under the terms of the GNU General Public License version 4 as\n" \
    "published by the Free Software Foundation.\n"                      \
    "\n"                                                                \
    "This program is distributed in the hope that it will be useful,\n" \
    "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"  \
    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"   \
    "GNU General Public License for more details.\n"                    \
    "\n"                                                                \
    "You should have received a copy of the GNU General Public License\n" \
    "along with this program.  If not, see <https://www.gnu.org/licenses/>.\n"


/**
 * @def USAGE_STR
 * @since 0.1.0
 * @brief The program's usage string.
 */
#define USAGE_STR "Usage: babylon [-hvw] N"

/**
 * @def HELP_STR
 * @since 0.1.0
 * @brief Short program help message
 */
#define HELP_STR                                                        \
    USAGE_STR "\n"                                                      \
    "\n"                                                                \
    "This program computes the square root of a positive non-null\n"    \
    "integer N using the Babylonian algorithm (Heron's method).\n"      \
    "\n"                                                                \
    "OPTIONS\n"                                                         \
    "-h print this help and exit.\n"                                    \
    "-v print the version number and exit.\n"                           \
    "-w print the license name and exit.\n"                             \
    "\n"                                                                \
    LICENSE_STR

/**
 * @since 0.1.0
 * @brief Compute the truncated square root of a positive non-null
 * integer using Heron's method.
 * @param number The squared integer.
 * @return The square root of @p number, or 0 if @p number is less or
 * equal then @c 0.
 */
int heron(int number)
{
    // in math notation, m = n+1
    int xn, xm = number;
    do {
        xn = xm;
        xm = (xn + number/xn)/2;
    } while(abs(xn - xm) > 1);
    return xm;
}

/**
 * @since 0.1.0
 * @brief Parses command line arguments.
 *
 * This function may cause an exit depending on eventual options, or
 * if the given argument is not a positive integer.
 *
 * The argparse library is not used to keep it simple.
 *
 * @param argv The command line arguments (after the program name).
 * @return The given integer.
 */
int parse_args(const char* argv[])
{
    const char* msg = NULL;
    if ((*argv)[0] == '-')
        switch((*argv)[1])
        {
        case HELP:    msg = HELP_STR;    goto option_exit;
        case LICENSE: msg = LICENSE_STR; goto option_exit;
        case VERSION: msg = VERSION_STR; goto option_exit;
        default:
        option_exit:
            puts(msg);
            exit(EXIT_SUCCESS);
            break;
        }

    // At this point, either there is no option, or the program
    // already exited.
    char* endptr = NULL;
    int number = (int)strtol(*argv, &endptr, 10);
    if (!endptr || *endptr || number <= 0)
        errx(EXIT_FAILURE, "Not a positive non-null integer: '%s'\n" USAGE_STR, *argv);
    return number;
}

/**
 * @since 0.1.0
 * @brief Main function.
 * @param argc Command line arguments count.
 * @param argv Command line arguments.
 * @return A non-zero value for errors, or #EXIT_SUCCESS.
 */
int main(int argc, const char* argv[])
{
    if (argc < 2)
        errx(EXIT_FAILURE, "Missing argument N.\n" USAGE_STR);
    printf("%i\n", heron(parse_args(++argv)));
    return EXIT_SUCCESS;
}
