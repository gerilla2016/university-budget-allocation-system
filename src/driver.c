#include <stdio.h>

#include "resourceManagement.h"

void testData( char *testData[], int testDataSize, double budget, int testNumber );

int main( void )
{
    char *testFiles[] = {
        "../sample-input/Department-ComputerScience.txt",
        "../sample-input/Department-Mathematics.txt",
        "../sample-input/Department-Chemistry.txt",
        "../sample-input/Department-PhysicsAndAstronomy.txt"
    };

    int testFilesSize = 4;
    double budget = 41850.00;

    printNames( );
    testData( testFiles, testFilesSize, budget, 1 );

    return 0;
}

void testData( char *testData[], int testDataSize, double budget, int testNumber )
{
    char budgetString[21];

    printf( "\n\n------------ START OF TEST #%d ------------\n\n", testNumber );

    sprintf( budgetString, "$%.2lf", budget );
    printf( "TESTING with budget = %20s\n\n", budgetString );

    ResourceManagement( testData, testDataSize, budget );

    printf( "\n------------ END OF TEST #%d ------------\n", testNumber );
}
