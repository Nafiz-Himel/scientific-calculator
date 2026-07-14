#include <stdio.h>
#include <math.h>

double simple_cal(double input_num1, double input_num2, char operator)
{
    double prev_res = input_num1;
    if (operator == '+')
        return (input_num1 + input_num2);
    else if (operator == '-')
        return (input_num1 - input_num2);
    else if (operator == '*')
        return (input_num1 * input_num2);
    else if (operator == '/')
    {
        if (input_num2 != 0)
            return (input_num1 / input_num2);
        else
        {
            printf("Error: Division by zero! Retaining previous value.\n");
            return prev_res;
        }
    }
    return prev_res;
}

double trigo_cal(double value, char operator, char degree_radian)
{
    double value_after_decision = value, PI = 3.14159265358979323846;

    while (degree_radian != 'd' && degree_radian != 'r')
    {
        printf("Invalid Mode! Enter again (d/r): ");
        if (scanf(" %c", &degree_radian) == EOF) 
            return 0;
    }
    if (degree_radian == 'd')
    {
        value_after_decision = value * (PI / 180.0);
    }

    if (operator == 's')
        return sin(value_after_decision);
    else if (operator == 'c')
        return cos(value_after_decision);
    else if (operator == 't')
        return tan(value_after_decision);

    return 0;
}

int main()
{
    double res = 0;
    char operator;

    if (scanf("%lf", &res) == EOF)
        return 0;

    while (1)
    {
        printf("Current Total: %.2lf\n", res);
        
        if (scanf(" %c", &operator) == EOF || operator == '=')
        {
            break;
        }

        if (operator == '+' || operator == '-' || operator == '*' || operator == '/')
        {
            double next_num;
            if (scanf("%lf", &next_num) == EOF)
            {
                break;
            }
            res = simple_cal(res, next_num, operator); 
        }
        else if (operator == 's' || operator == 'c' || operator == 't')
        {
            double value;
            char degree_radian;
            if (scanf("%lf %c", &value, &degree_radian) == EOF)
            {
                break;
            }

            res = trigo_cal(value, operator, degree_radian);
        }
        else
        {
            printf("Invalid operator!\n");
        }
    }

    printf("\nFinal Result: %.2lf\n", res);

    return 0;
}