/****************************************************************
 *                                                              *
 * This file has been written as a sample solution to an        *
 * exercise in a course given at the CSCS Summer School.        *
 * It is made freely available with the understanding that      *
 * every copy of this file must include this header and that    *
 * CSCS take no responsibility for the use of the enclosed      *
 * teaching material.                                           *
 *                                                              *
 * Purpose: A ping-pong                                         *
 *                                                              *
 * Contents: C-Source                                           *
 *                                                              *
 ****************************************************************/

#include <stdio.h>
#include <mpi.h>

#define PROCESS_A 0
#define PROCESS_B 1
#define PING  17 //message tag
#define PONG  23 //message tag
#define SIZE  1024

int main(int argc, char *argv[])
{
    int my_rank;
    float buffer[SIZE];
    MPI_Status status;


    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    /* Process A sends a message (ping) to process B.
     * After receiving the message, process B sends a message (pong) to process A.
     */

    MPI_Finalize();
    return 0;
}
