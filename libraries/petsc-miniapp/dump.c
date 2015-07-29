#include<petscviewer.h>
#include<petscdmda.h>
#include "appctx.h"

#undef __FUNCT__
#define __FUNCT__ "DumpSolution"
PetscErrorCode DumpSolution(DM da, Vec u, AppCtx * ctx)
{
  PetscErrorCode ierr;
  PetscViewer    viewer;
  PetscScalar    **uarr;
  PetscMPIInt    size;

  PetscFunctionBeginUser;

  /* Obtain the size of the communicator, and throw an error if it is not 1,
     as scalable parallel I/O is beyond the scope of this example.
      
     Note that PETSc sits on top of MPI and, as a design principle, does
     not wrap any MPI calls, so existing MPI functionality uses the usual
     interface! */
  MPI_Comm_size(PETSC_COMM_WORLD,&size);
  if(size != 1){ SETERRQ(PETSC_COMM_WORLD,PETSC_ERR_SUP,"Output not implemented for multiple MPI ranks"); }

  #if 0
  /* For rough debugging, as an example of one of many available viewers,
     here is the procedure to dump a vector into an m-file.
     This respects any name give to the vector, so in this case,
     the result is a file which can be run from octave or MATLAB
     to define "u", since we assigned that name to this object in main.c */
  ierr = PetscViewerASCIIOpen(PETSC_COMM_WORLD,"out.m",&viewer);CHKERRQ(ierr);
  ierr = PetscViewerSetFormat(viewer,PETSC_VIEWER_ASCII_MATLAB);CHKERRQ(ierr);
  ierr = VecView(u,viewer);CHKERRQ(ierr);
  PetscViewerDestroy(&viewer);CHKERRQ(ierr);
  #endif

#ifdef USE_OLD_API
  ierr = DMDAVecGetArray(da,u,&uarr);CHKERRQ(ierr);
#else
  ierr = DMDAVecGetArrayRead(da,u,&uarr);CHKERRQ(ierr);
#endif

  {
    FILE* output = fopen("output.bin", "w");
    fwrite(*uarr, sizeof(PetscScalar), ctx->nx * ctx->ny, output);
    fclose(output);
  }

  // metadata
  {
    FILE* output = fopen("output.bov", "wb");
    fprintf(output, "TIME: 0.0\n");
    fprintf(output, "DATA_FILE: output.bin\n");
    fprintf(output, "DATA_SIZE: %d, %d, 1\n", ctx->nx, ctx->ny);
    fprintf(output, "DATA_FORMAT: DOUBLE\n"); /* sloppy! This will only work with a double-precision build */
    fprintf(output, "VARIABLE: phi\n");
    fprintf(output, "DATA_ENDIAN: LITTLE\n");
    fprintf(output, "CENTERING: nodal\n");
    fprintf(output, "BRICK_SIZE: 1.0 %f 1.0\n", (ctx->ny - 1.0) / (ctx->nx - 1.0));
    fclose(output);
  }
  /*
    std::ofstream fid("output.bov");
    fid << "TIME: 0.0" << std::endl;
    fid << "DATA_FILE: output.bin" << std::endl;
    fid << "DATA_SIZE: " << options.nx << ", " << options.ny << ", 1" << std::endl;;
    fid << "DATA_FORMAT: DOUBLE" << std::endl;
    fid << "VARIABLE: phi" << std::endl;
    fid << "DATA_ENDIAN: LITTLE" << std::endl;
    fid << "CENTERING: nodal" << std::endl;
    fid << "BRICK_SIZE: 1.0 " << (options.ny-1)*options.dx << " 1.0" << std::endl;
    */
#ifdef USE_OLD_API
  ierr = DMDAVecRestoreArray(da,u,&uarr);CHKERRQ(ierr);
#else
  ierr = DMDAVecRestoreArrayRead(da,u,&uarr);CHKERRQ(ierr);
#endif

  PetscFunctionReturn(0);

}
