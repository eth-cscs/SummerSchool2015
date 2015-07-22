PROGRAM ping_pong

!==============================================================!
!                                                              !
! This file has been written as a sample solution to an        !
! exercise in a course given at the CSCS Summer School.        !
! It is made freely available with the understanding that      !
! every copy of this file must include this header and that    !
! CSCS take no responsibility for the use of the enclosed      !
! teaching material.                                           !
!                                                              !
! Purpose: A program to try MPI_Ssend and MPI_Recv.            !
!                                                              !
! Contents: F-Source                                           !
!==============================================================!

  USE MPI
  IMPLICIT NONE

  INTEGER PROCESS_A
  PARAMETER(PROCESS_A=0)

  INTEGER PROCESS_B
  PARAMETER(PROCESS_B=1)

  INTEGER PING
  PARAMETER(PING=17) ! message tag

  INTEGER PONG
  PARAMETER(PONG=23) ! message tag

  INTEGER length
  PARAMETER (length=1)

  INTEGER status(MPI_STATUS_SIZE)

  REAL buffer(length)

  INTEGER i

  INTEGER ierror, my_rank, size

  CALL MPI_INIT(ierror)

  CALL MPI_COMM_RANK(MPI_COMM_WORLD, my_rank, ierror)

  ! Process A sends a message(ping) to process B. 
  ! After receiving the message, process B sends a message (pong) to process A

  CALL MPI_FINALIZE(ierror)

END PROGRAM
