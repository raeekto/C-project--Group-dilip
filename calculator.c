// Calculator App
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // for sleep()

// () for clear previous output
static void clear_screen(void)
{
#ifdef _WIN32
	system("cls"); // Windows
#else
	printf("\033[H\033[J"); // ANSI escape codes for Linux/macOS
#endif
}

// for styling result
void loadingStyle(int miliSec, char expressions[])
{
	for (int i = 0; i < strlen(expressions); i++)
	{
		printf("%c", expressions[i]);
		Sleep(miliSec);
	}
	printf("\n\n");
}

int main()
{
	char op, ch[10], strResult[1000];
	float num1, num2, result;
	char *userChoiceOption[] = {"yes", "y", "no", "n"};
	char operatorOption[] = {'+', '-', '*', '/', '%'};
	int sizeOfOp = sizeof(operatorOption) / sizeof(operatorOption[0]);
	int sizeOfCh = sizeof(userChoiceOption) / sizeof(userChoiceOption[0]);

	bool chVal = true;

	while (chVal)
	{
		clear_screen();
		loadingStyle(20, "\n\t\tWELCOME...\n\t\tThis is Calculator App ...\n");
		Sleep(1000);
		// Menu of operators
		printf("\n\t\t------------------------------\n");
		printf("\t\t1.) ADD (+)\n\t\t2.) SUBTRACT (-)\n\t\t3.) MULTIPLICATION (*)\n\t\t4.) DIVISION (/)\n\t\t5.) REMAINDER (%%)");
		printf("\n\t\t------------------------------\n");

		// Read operator
		printf("Choose operator: ");
		scanf(" %c", &op);

		bool opVal = false;
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
			Sleep(1500); // 1000m = 1s
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
			printf("RESULt :  ");
			sprintf(strResult, "%.2f + %.2f = %.2f", num1, num2, result);
			loadingStyle(100, strResult);
			break;
		case '-':
			result = num1 - num2;
			printf("RESULT :  ");
			sprintf(strResult, "RESULT :  %.2f - %.2f = %.2f", num1, num2, result);
			loadingStyle(100, strResult);

			break;
		case '*':
			result = num1 * num2;
			printf("RESULT :  ");
			sprintf(strResult, "%.2f x %.2f = %.2f", num1, num2, result);
			loadingStyle(100, strResult);

			break;
		case '/':
			if (num2 != 0)
			{
				result = num1 / num2;
				printf("RESULT :  ");
				sprintf(strResult, "%.2f / %.2f = %.2f", num1, num2, result);
				loadingStyle(100, strResult);
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
				result = a % b;
				printf("RESULT :  ");
				sprintf(strResult, "%d % %.2f = %d", a, b, result);
				loadingStyle(100, strResult);
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
