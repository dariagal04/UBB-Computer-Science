#include <stdio.h>

int main()
{
    int n, s = 0, nr;
    printf("n = ");
    scanf_s("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("numar %d: ", i + 1);
        scanf_s("%d", &nr);
        s += nr;
    }
    printf("Suma numerelor este %d\n", s);
    return 0;
}