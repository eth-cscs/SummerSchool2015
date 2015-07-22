/****************************************************************
 *                                                              *
 * This file has been written as a sample solution to an        *
 * exercise in a course given at the CSCS Summer School.        *
 * It is made freely available with the understanding that      *
 * every copy of this file must include this header and that    *
 * CSCS take no responsibility for the use of the enclosed      *
 * teaching material.                                           *
 *                                                              *
 * Purpose: Exchange ghost cell in 2 directions                 *
 *                                                              *
 * Contents: C-Source                                           *
 *                                                              *
 ****************************************************************/

/* Use only 16 processes for this exercise
 * Send the ghost cell in two directions: left to right and right to left
 *
 * process decomposition on 4*4 grid
 *
 *  |-----------|
 *  | 0| 4| 8|12|
 *  |-----------|
 *  | 1| 5| 9|13|
 *  |-----------|
 *  | 2| 6|10|14|
 *  |-----------|
 *  | 3| 7|11|15|
 *  |-----------|
 *
 * Each process works on a 10*10 (SUBDOMAIN) block of data
 * the D corresponds to data, g corresponds to "ghost cells"
 * xggggggggggx
 * gDDDDDDDDDDg
 * gDDDDDDDDDDg
 * gDDDDDDDDDDg
 * gDDDDDDDDDDg
 * gDDDDDDDDDDg
 * gDDDDDDDDDDg
 * gDDDDDDDDDDg
 * gDDDDDDDDDDg
 * gDDDDDDDDDDg
 * gDDDDDDDDDDg
 * xggggggggggx
 */

/* Tasks:
 * A. each rank has to find its left and right neighbor
 * B. send them the data they need
 *    - left array goes to left neighbor
 *    - right array goes to right neighbor
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SUBDOMAIN 10
#define DOMAINSIZE (SUBDOMAIN+2)

int main(int argc, char *argv[])
{
    int rank, size, i, j, rank_right, rank_left;
    double data[DOMAINSIZE*DOMAINSIZE];
    MPI_Request request;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size!=16) {
        printf("please run this with 16 processors\n");
        MPI_Finalize();
        exit(1);
    }

    for (i=0; i<DOMAINSIZE*DOMAINSIZE; i++) {
        data[i]=rank;
    }

    rank_right=/* find the rank of the right neighbor */
    rank_left=/* find the rank of the left neighbor */


    //  ghost cell exchange with the neighbouring cells to the right and to the left
    //  a) MPI_Send, MPI_Irecv, MPI_Wait
    //  b) MPI_Isend, MPI_Recv, MPI_Wait
    //  c) MPI_Sendrecv
    //  to the left

    // a)

    // b)

    // c)

    //  to the right
    // a)

    // b)

    // c)

    if (rank==9) {
        printf("data of rank 9 after communication\n");
        for (i=0; i<DOMAINSIZE; i++) {
            for (j=0; j<DOMAINSIZE; j++) {
                printf("%.1f ", data[i+j*DOMAINSIZE]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}
