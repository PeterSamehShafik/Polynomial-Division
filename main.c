/*INFOs
Name: Peter Sameh Shafik Ibrahim
id : 1900437
*/

#include <stdio.h>
#include <stdlib.h>

//Get The Inputs (Numerator and Denominator)
void getNumerator (float* numCoeff,int* numDegree){
    printf("1-Numerator\n===========================\n");
    printf("Enter the LARGEST degree: "); // Know The largest degree of the numerator
    scanf ("%d",&numDegree[0]);

    int i;
    printf("\n");

    for (i=0;i<=numDegree[0];i++)
    {
        printf("Enter the coefficient of X^%d: ",numDegree[0] - i);
        scanf ("%f",&numCoeff[i]);
        numDegree[i+1] = numDegree[i]-1; //decreasing the degree of the next Term and so on
    }
    numDegree[i+1]++; //The last term will have degree of -1, so this step for clear this error
}
void getDenominator (float* denCoeff ,int *denDegree){
    printf("2-Denominator\n===========================\n");
    printf("\nEnter the LARGEST degree: "); // Know The largest degree of the denominator
    scanf ("%d",&denDegree[0]);

    int i;
    printf("\n");

    for (i=0; i<=denDegree[0]; i++)
    {
        printf("Enter the coefficient of X^%d: ",denDegree[0] - i);
        scanf ("%f",&denCoeff[i]);
        denDegree[i+1] = denDegree[i]-1; //decreasing the degree of the next Term and so on
    }
    denDegree[i+1]++; //The last term will have degree of -1, so this step for clear this error
}

//The 3 main steps of the long division
void divide(float* numCeoff,int* numDegree,float* denCoeff,int* denDegree,float* resultCoeff,int* resultDegree){
    static int i = 0;
    resultCoeff[i] = numCeoff[i] / denCoeff[0];
    resultDegree[i] = numDegree[i] - denDegree[0];
    i++;
}
void multiply(float* denCoeff,int* denDegree,float* resultCoeff,int* resultDegree,int* multiplyDegree, float* multiplyCoeff){
    int i;
    static int j = 0;
    for(i=0; i<=denDegree[0]; i++)
    {
        multiplyCoeff[i] = resultCoeff[j] * denCoeff[i];
        multiplyDegree[i] = resultDegree[j] + denDegree[i];
    }
    j++;
}
void subtract(float* multiplyCoeff,int* multiplyDegree,float*  numCoeff,int* numDegree){
    int i,j;

    for(i=0; i<=numDegree[0]; i++)
    {
        for(j=0; j<=multiplyDegree[0]; j++)
        {
            if(numDegree[i]== multiplyDegree[j])
            {
                numCoeff[i] = numCoeff[i] - multiplyCoeff[j];
                break;
            }
        }
    }
}

// LongDivision Function which contain the 3 steps. The Function returns 0 in case **Indivisible**
int longDivision(float* numCoeff,float* denCoeff,int* numDegree,int* denDegree,float* resultCoeff,int* resultDegree){
    // Temp Arrays to save in it the value of multiplying
    float multiplyCoeff[50]={};
    int multiplyDegree[50]= {};

    int i = 0;
    int check=0;
    while (numDegree[i]>= denDegree[0])
    {
        divide(numCoeff,numDegree, denCoeff,denDegree, resultCoeff, resultDegree);
        multiply(denCoeff,denDegree, resultCoeff, resultDegree, multiplyDegree, multiplyCoeff);
        subtract(multiplyCoeff, multiplyDegree, numCoeff, numDegree);
        check++;
        i++;
    }
    if (check !=0 ) return 1;
    else return 0;

}

//Function returns 1 in case reminder, 0 in case not.
int checkReminder(float* numCoeff, int* numDegree){
    int i;
    for(i=0; i<=numDegree[0]; i++)
    {
        if(numCoeff[i] != 0) return 1;
    }
    return 0;
}

//Printing the result whether reminder or not.
void printResult(float* numCoeff,float* denCoeff,int* numDegree,int* denDegree,float* resultCoeff,int* resultDegree, int reminder, int check){
    int i;
    printf("\nResult = ");
    for(i=0; i<=resultDegree[0]; i++)
    {
        if(resultCoeff[i] !=0)
        {
            if(i>=1 && resultCoeff[i]>=0) {printf(" + ");}
            printf("%0.2f X^%d ",resultCoeff[i], resultDegree[i]);
        }
    }

    if (reminder == 1)
    {
        if(check != 0 ){printf(" + ");}
        printf("( ");
        for(i=0; i<=numDegree[0]; i++)
        {
            if(numCoeff[i] !=0)
            {
                if(i>=1 && numCoeff[i]>=0 && numCoeff[i-1] !=0 ) {printf(" + ");}
                printf("%0.2f X^%d ",numCoeff[i],numDegree[i]);
            }
        }
        printf(" )");

        printf(" / ");

        printf("( ");

        for(i=0; i<=denDegree[0]; i++)
        {
            if(denCoeff[i] !=0 )
            {
                if(i>=1 && denCoeff[i]>=0 && denCoeff[i-1] !=0) {printf(" + ");}
                printf("%0.2f X^%d ",denCoeff[i],denDegree[i]);
            }
        }
        printf(" )");
    }
    printf("\n");
}

int main()
{
    while(1)
    {
        //Header
        printf("\t\tPolynomial division\n");
        printf("*************************************************\n\n");

        //Declare the numerator, denominator and result arrays
        float numCoeff[50] = {};
        float denCoeff[50]= {};
        float resultCoeff[50]= {};
        int resultDegree[50] = {};
        int numDegree[50]= {};
        int denDegree[50]= {};

        //Get Numerator and Denominator
        getNumerator(numCoeff,numDegree);
        printf("\n-------------------------------------------------\n"); // for good arrangements
        getDenominator(denCoeff,denDegree);
        printf("\n-------------------------------------------------\n");// for good arrangements

        //Execute the longDivision Function. It returns a value checks (1 divisible /0 indivisible)
        int check = longDivision(numCoeff, denCoeff, numDegree, denDegree, resultCoeff, resultDegree);
        //Execute checkReminder and take the returning value in a variable (1 Reminder / 0 no reminder)
        int reminder = checkReminder(numCoeff, numDegree);

        //Printing Results of the longDivision. In case indivisible it prints the whole fraction as it written
        printResult(numCoeff, denCoeff, numDegree, denDegree, resultCoeff, resultDegree, reminder, check);
        printf("\n-------------------------------------------------\n");// for good arrangements

    }

    return 0;
}
