#include <stdio.h>
#include <math.h>

double simple_func(double a, double b, char op)
{
    if (op == '+')
        return a + b;
    if (op == '-')
        return a - b;
    if (op == '*')
        return a * b;

    if (op == '/')
    {
        if (b == 0)
        {
            printf("Error: Division by zero.\n");
            return NAN;
        }
        return a / b;
    }

    return NAN;
}

double power_mod_func(double a, double b, char op)
{
    if (op == '^')
        return pow(a, b);

    if (op == '%')
    {
        if (b == 0)
        {
            printf("Error: Modulos by zero.\n");
            return NAN;
        }
        return fmod(a, b);
    }

    return NAN;
}

double trigo_func(double angle, char op, char mode)
{
    const double PI = 3.141592653589793;

    if (mode == 'd')
    {
        double rad_angle = angle * PI / 180.0;
        angle = rad_angle;
    }

    if (op == 's')
        return sin(angle);
    if (op == 'c')
        return cos(angle);

    if (op == 't')
    {
        if (fabs(cos(angle)) < 1e-9)
        {
            printf("Error: tan(90) undefined.\n");
            return NAN;
        }
        return tan(angle);
    }

    return NAN;
}

double unary_func(double a, char op)
{
    if (op == 'q') {
        if (a < 0) {
            printf("Error: sqrt undefined for negative number.\n");
            return NAN;
        }
        return sqrt(a);
    }

    if (op == 'l') {
        if (a <= 0) {
            printf("Error: ln undefined for non-positive value.\n");
            return NAN;
        }
        return log(a);
    }

    if (op == 'L') {
        if (a <= 0) {
            printf("Error: log10 undefined for non-positive value.\n");
            return NAN;
        }
        return log10(a);
    }

    if (op == 'r') {
        if (a == 0) {
            printf("Error: reciprocal undefined for zero.\n");
            return NAN;
        }
        return 1.0 / a;
    }

    if (op == 'a') {
        return fabs(a);
    }

    return NAN;
}

void print_guide()
{
    printf("\n=========== SCIENTIFIC CALCULATOR GUIDE ===========\n");

    printf("\nStart: Enter initial value (example: 5)\n");

    printf("\nOperators:\n");
    printf("  +  Addition\n");
    printf("  -  Subtraction\n");
    printf("  *  Multiplication\n");
    printf("  /  Division\n");
    printf("  ^  Power\n");
    printf("  %%  Modulo\n");

    printf("\nInput Format:\n");

    printf("\n1. Number:\n");
    printf("   + n 5\n");

    printf("\n2. Unary:\n");
    printf("   + q 16   (sqrt)\n");
    printf("   + l 2.7  (ln)\n");
    printf("   + L 100  (log10)\n");
    printf("   + r 5    (1/x)\n");
    printf("   + a -10  (abs)\n");

    printf("\n3. Trigonometry:\n");
    printf("   + s d 90\n");
    printf("   + c r 3.14\n");
    printf("   + t d 45\n");

    printf("\nEnd: =   to finish\n\n");

    printf("==================================================\n\n");
}

int main()
{
    double res;

    print_guide();

    printf("Enter initial value: ");
    if (scanf("%lf", &res) != 1)
        return 0;

    while (1)
    {
        printf("\nCurrent: %.4lf\n", res);

        char op;
        printf("Operator: ");
        scanf(" %c", &op);

        if (op == '=')
            break;

        if (op != '+' && op != '-' && op != '*' && op != '/' && op != '^' && op != '%')
        {
            printf("Invalid operator!\n");
            continue;
        }

        char type;
        scanf(" %c", &type);

        double right_val;

        if (type == 'n') //number
        {
            scanf("%lf", &right_val);
        }
        else if (type == 'q' || type == 'l' || type == 'L' || type == 'r' || type == 'a') //unary
        {
            double val;
            scanf("%lf", &val);
            right_val = unary_func(val, type);
        }
        else if (type == 's' || type == 'c' || type == 't') //trigonometry
        {
            char mode;
            double angle;

            scanf(" %c %lf", &mode, &angle);
            right_val = trigo_func(angle, type, mode);
        }
        else
        {
            printf("Invalid input type!\n");
            continue;
        }

        if (isnan(right_val))
        {
            printf("Invalid input, try again!\n");
            continue;
        }

        if (op == '^' || op == '%')
            res = power_mod_func(res, right_val, op);
        else
            res = simple_func(res, right_val, op);

        if (isnan(res))
        {
            printf("Math error!\n");
            return 0;
        }
    }

    printf("\nFinal Result: %.4lf\n", res);
    return 0;
}
