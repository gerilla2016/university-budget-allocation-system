#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "resourceManagement.h"

int const STRING_LENGTH = 31;

pqType createPQType( Department *d, double totalSpent );
double minDouble( double x, double y );

static char *copyString( const char *source );
static char *readNonEmptyLine( FILE *fp );
static Item *createItem( const char *name, double price );
static Department *createDepartment( const char *fileName );
static void freeItem( Item *item );
static void freeQueueItems( Queue *queue );
static void freeDepartment( Department *department );
static void moveRemainingDesiredItemsToRemoved( Department *department );
static void printPurchasedItem( Department *department, Item *item );
static void printItemLine( Item *item );
static void printDepartmentSummary( Department *department, double originalBudget );

/* printNames
 * input: none
 * output: none
 *
 * Prints a short project heading for the demo.
 */
void printNames( )
{
    printf("\nUniversity Budget Allocation System\n");
    printf("Priority Queue Resource Management Demo\n\n");
}

/* ResourceManagement
 * input: char* fileNames[], int testDataSize, double budget
 * output: none
 *
 * Simulates budget allocation across departments. The department with the
 * lowest total spending receives the next funding opportunity. If that
 * department still has desired items, the next item is purchased when the
 * remaining budget allows it; otherwise, the item is marked as not received.
 * When a department has no desired items left, the department receives a
 * scholarship of up to $1000 while budget remains.
 */
void ResourceManagement( char* fileNames[], int testDataSize, double budget )
{
    Department **departments = NULL;
    PriorityQueue *pq = NULL;
    double originalBudget = budget;
    int i;

    if( fileNames == NULL || testDataSize <= 0 || budget <= 0.0 ){
        fprintf( stderr, "ResourceManagement: invalid input.\n" );
        return;
    }

    departments = (Department **)calloc( (size_t)testDataSize, sizeof(Department *) );
    if( departments == NULL ){
        fprintf( stderr, "ResourceManagement: failed to allocate department array.\n" );
        exit( EXIT_FAILURE );
    }

    pq = createPQ( );

    for( i = 0; i < testDataSize; ++i ){
        departments[i] = createDepartment( fileNames[i] );
        insertPQ( pq, createPQType( departments[i], departments[i]->totalSpent ) );
    }

    printf( "ITEMS PURCHASED\n" );
    printf( "----------------------------\n" );

    while( budget > 0.0 && !isEmptyPQ( pq ) ){
        pqType next = removePQ( pq );
        Department *department = next.info;
        Item *item = NULL;

        if( department == NULL ){
            continue;
        }

        if( !isEmpty( department->itemsDesired ) ){
            item = dequeue( department->itemsDesired );

            if( item->price <= budget ){
                enqueue( department->itemsReceived, item );
                department->totalSpent += item->price;
                budget -= item->price;
                printPurchasedItem( department, item );
            }
            else{
                enqueue( department->itemsRemoved, item );
            }
        }
        else{
            double scholarshipAmount = minDouble( 1000.00, budget );
            item = createItem( "Scholarship", scholarshipAmount );
            enqueue( department->itemsReceived, item );
            department->totalSpent += scholarshipAmount;
            budget -= scholarshipAmount;
            printPurchasedItem( department, item );
        }

        if( budget > 0.0 ){
            insertPQ( pq, createPQType( department, department->totalSpent ) );
        }
    }

    for( i = 0; i < testDataSize; ++i ){
        moveRemainingDesiredItemsToRemoved( departments[i] );
    }

    for( i = 0; i < testDataSize; ++i ){
        printDepartmentSummary( departments[i], originalBudget );
    }

    freePQ( pq );
    for( i = 0; i < testDataSize; ++i ){
        freeDepartment( departments[i] );
    }
    free( departments );
}

/* createPQType
 * input: Department *d, double totalSpent
 * output: pqType
 *
 * Creates and returns a pqType struct (i.e the type in the priority queue)
 * from the given department and totalSpent.
 */
pqType createPQType( Department *d, double totalSpent ){
    pqType pt;
    pt.info = d;
    pt.priority = totalSpent;

    return pt;
}

/* minDouble
 * input: double x, double y
 * output: the smaller of x and y
 */
double minDouble( double x, double y ){
    if( x<=y )
        return x;
    return y;
}

static char *copyString( const char *source ){
    char *destination = NULL;
    size_t length;

    if( source == NULL ){
        return NULL;
    }

    length = strlen( source );
    destination = (char *)malloc( length + 1 );
    if( destination == NULL ){
        fprintf( stderr, "copyString: failed to allocate memory.\n" );
        exit( EXIT_FAILURE );
    }

    strcpy( destination, source );
    return destination;
}

static char *readNonEmptyLine( FILE *fp ){
    char buffer[256];
    size_t length;

    while( fgets( buffer, sizeof(buffer), fp ) != NULL ){
        length = strlen( buffer );

        while( length > 0 && ( buffer[length - 1] == '\n' || buffer[length - 1] == '\r' ) ){
            buffer[length - 1] = '\0';
            --length;
        }

        if( length > 0 ){
            return copyString( buffer );
        }
    }

    return NULL;
}

static Item *createItem( const char *name, double price ){
    Item *item = (Item *)malloc( sizeof(Item) );
    if( item == NULL ){
        fprintf( stderr, "createItem: failed to allocate memory.\n" );
        exit( EXIT_FAILURE );
    }

    item->name = copyString( name );
    item->price = price;
    return item;
}

static Department *createDepartment( const char *fileName ){
    FILE *fp = NULL;
    Department *department = NULL;
    char *departmentName = NULL;
    char *itemName = NULL;

    fp = fopen( fileName, "r" );
    if( fp == NULL ){
        fprintf( stderr, "createDepartment: could not open input file '%s'.\n", fileName );
        exit( EXIT_FAILURE );
    }

    departmentName = readNonEmptyLine( fp );
    if( departmentName == NULL ){
        fprintf( stderr, "createDepartment: file '%s' does not contain a department name.\n", fileName );
        fclose( fp );
        exit( EXIT_FAILURE );
    }

    department = (Department *)malloc( sizeof(Department) );
    if( department == NULL ){
        fprintf( stderr, "createDepartment: failed to allocate department.\n" );
        fclose( fp );
        exit( EXIT_FAILURE );
    }

    department->name = departmentName;
    department->totalSpent = 0.0;
    department->itemsDesired = createQueue( );
    department->itemsReceived = createQueue( );
    department->itemsRemoved = createQueue( );

    while( ( itemName = readNonEmptyLine( fp ) ) != NULL ){
        char *priceLine = readNonEmptyLine( fp );
        double price;

        if( priceLine == NULL ){
            fprintf( stderr, "createDepartment: item '%s' in '%s' is missing a price.\n", itemName, fileName );
            free( itemName );
            break;
        }

        price = atof( priceLine );
        enqueue( department->itemsDesired, createItem( itemName, price ) );
        free( itemName );
        free( priceLine );
    }

    fclose( fp );
    return department;
}

static void freeItem( Item *item ){
    if( item != NULL ){
        free( item->name );
        free( item );
    }
}

static void freeQueueItems( Queue *queue ){
    if( queue == NULL ){
        return;
    }

    while( !isEmpty( queue ) ){
        freeItem( dequeue( queue ) );
    }

    freeQueue( queue );
}

static void freeDepartment( Department *department ){
    if( department == NULL ){
        return;
    }

    free( department->name );
    freeQueueItems( department->itemsDesired );
    freeQueueItems( department->itemsReceived );
    freeQueueItems( department->itemsRemoved );
    free( department );
}

static void moveRemainingDesiredItemsToRemoved( Department *department ){
    if( department == NULL ){
        return;
    }

    while( !isEmpty( department->itemsDesired ) ){
        enqueue( department->itemsRemoved, dequeue( department->itemsDesired ) );
    }
}

static void printPurchasedItem( Department *department, Item *item ){
    printf( "Department of %-31s              - %-30s - %20s%7.2f\n",
            department->name,
            item->name,
            "$",
            item->price );
}

static void printItemLine( Item *item ){
    printf( "%-30s - %20s%7.2f\n",
            item->name,
            "$",
            item->price );
}

static void printDepartmentSummary( Department *department, double originalBudget ){
    LLNode *current = NULL;
    double percent = 0.0;

    if( department == NULL ){
        return;
    }

    if( originalBudget > 0.0 ){
        percent = ( department->totalSpent / originalBudget ) * 100.0;
    }

    printf( "\nDepartment of %s\n", department->name );
    printf( "Total Spent       = $%.2f\n", department->totalSpent );
    printf( "Percent of Budget = %.2f\n", percent );
    printf( "----------------------------\n" );

    printf( "ITEMS RECEIVED\n" );
    current = department->itemsReceived->qFront;
    while( current != NULL ){
        printItemLine( current->qt );
        current = current->pNext;
    }

    printf( "\nITEMS NOT RECEIVED\n" );
    current = department->itemsRemoved->qFront;
    while( current != NULL ){
        printItemLine( current->qt );
        current = current->pNext;
    }

    printf( "\n" );
}
