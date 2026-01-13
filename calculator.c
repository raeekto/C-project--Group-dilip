//Calculator App
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main()
{
	char op, ch[10];
	float num1, num2, result;
	char *userChoiceOption[] = {"yes", "y", "no", "n"};
	char operatorOption[] = {'+', '-', '*', '/', '%'};
	int sizeOfOp = sizeof(operatorOption) / sizeof(operatorOption[0]);
	int sizeOfCh = sizeof(userChoiceOption) / sizeof(userChoiceOption[0]);

	bool chVal = true;

	while (chVal)
	{
		// Menu of operators
		printf("\n\t\t------------------------------\n");
		printf("\t\t1.) ADD (+)\n\t\t2.) SUBTRACT (-)\n\t\t3.) MULTIPLICATION (*)\n\t\t4.) DIVISION (/)\n\t\t5.) REMAINDER (%%)");
		printf("\n\t\t------------------------------\n");

		// Read operator
		printf("Choose operator: ");
		scanf(" %c", &op);

		bool opVal = false;
		// Check op is fall under opOptions or not
		// int i; // // (when loop initial declaration not allow)
		for (int i = 0; i < sizeOfOp; i++)
		{
			if (op == operatorOption[i])
			{
				opVal = true;
				break;
			}
		}

		if (!opVal)
		{
			printf("Can choose only (+, -, *, /, %%)\n");
			continue;
		}

		// Numbers input (taking operands)
		printf("Enter two numbers: ");
		scanf("%f %f", &num1, &num2);

		// Perform calculation
		switch (op)
		{
		case '+':
			result = num1 + num2;
			printf("Result: %.2f + %.2f = %.2f\n", num1, num2, result);
			break;
		case '-':
			result = num1 - num2;
			printf("Result: %.2f - %.2f = %.2f\n", num1, num2, result);

			break;
		case '*':
			result = num1 * num2;
			printf("Result: %.2f x %.2f = %.2f\n", num1, num2, result);

			break;
		case '/':
			if (num2 != 0)
			{
				result = num1 / num2;
				printf("Result: %.2f / %.2f = %.2f\n", num1, num2, result);
			}
			else
			{
				printf("Error: Division by zero!\n");
			}
			break;
		case '%':
			if (num2 != 0)
			{

				int a = (int)num1;
				int b = (int)num2;
				int result = a % b;
				printf("Result: %d %% %d = %d\n", a, b, result);
			}
			else
			{
				printf("Error: Division by zero!\n");
			}
			break;
		}

		// User choice(perform next or not)
		printf("\nDo you want another? (y/n/yes/no): ");
		scanf("%9s", ch);

		if (strcmp(ch, "y") == 0 || strcmp(ch, "yes") == 0)
		{
			chVal = true;
		}
		else if (strcmp(ch, "n") == 0 || strcmp(ch, "no") == 0)
		{
			chVal = false;
			printf("\n\nProgram is Ended!\n\n");
		}
		else
		{
			printf("Choose only (y, n, yes, or no)\n");
			chVal = false;
		}
	}

	return 0;
}
