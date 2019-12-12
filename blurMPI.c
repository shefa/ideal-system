#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>

int main (int argc, char * argv[]) {
	static int const maxlen = 200, rowsize = 521, colsize = 428, linelen = 12;
	char str[maxlen], lines[5][maxlen];
	FILE *fp, *fout;
	int icheck, nlines = 0;
	unsigned int h1, h2, h3;
	char *sptr;
        int **R, **G, **B, **Rnew, **Gnew, **Bnew;
	int *Rrow, *Grow, *Brow, *sendbuf, *recvbuf;
	int row = 0, col = 0, nblurs, lineno=0, k;
	struct timeval tim;
        int bufsize, coords[2];
        int myrowsize, mycolsize, myrowstart, myrowend, mycolstart, mycolend;
        int len, tag = 99, dest, prowsize, pcolsize, lastcolsize, nsend, localrow, localcol, coffset;
        char name[MPI_MAX_PROCESSOR_NAME];
        int nprocs, rank, nprows, npcols, myrow, mycol, left, right, up, down;
        MPI_Comm new_comm;
	MPI_Status status;

/* Initialize MPI */
        MPI_Init (&argc, &argv);

/************************************************************************************************
 *
 * INSERT CODE HERE
 *
 * The inserted code must do the following:
 * 	1) Determine the number of processes in use and store this value in the integer nprocs
 * 	2) Determine the rank of the process and store this in the integer rank
 * 	3) Set up a 2D application topology that is as close to square as possible for the
 * 	   given number of processes. To do this you must create the topological communicator
 * 	   new_comm. Store the number of rows in the topology in the integer nprows, 
 * 	   and the number of columns in the integer npcols. Store the process row position 
 * 	   in the topology in the integer myrow, and its column position in the integer mycol.
 * 	4) Determine the ranks of the four nearest neighbouring processes, and store these in the 
 * 	   integers, left, right, up and down.
 *
 * Summary of variables to be set in the inserted code (these are all declared above):
 * 	MPI_Comm new_comm
 * 	int nprocs, rank, nprows, npcols, myrow, mycol, left, right, up, down
 *
 ***********************************************************************************************/

/* Do data decomposition */
        prowsize = ((rowsize-1)/nprows) + 1;
        myrowstart = myrow*prowsize;
        myrowend   = (myrow+1)*prowsize - 1;
        if (myrowend >= rowsize) myrowend = rowsize - 1;
        pcolsize = ((colsize-1)/npcols) + 1;
        mycolstart = mycol*pcolsize;
        mycolend   = (mycol+1)*pcolsize - 1;
        if (mycolend >= colsize) mycolend = colsize - 1;
        myrowsize = myrowend - myrowstart + 1;
        mycolsize = mycolend - mycolstart + 1;
        printf("rank = %d: (myrow,mycol) = (%d,%d), (left,right,up,down) = (%d,%d,%d,%d), row(start,end) = (%d,%d), col(start,end) = (%d,%d)\n",rank,myrow,mycol,left,right,up,down,myrowstart,myrowend,mycolstart,mycolend);

/* Allocate arrays */
        R = (int **)malloc((sizeof(int*)*(myrowsize+2)));
        G = (int **)malloc((sizeof(int*)*(myrowsize+2)));
        B = (int **)malloc((sizeof(int*)*(myrowsize+2)));
        Rnew = (int **)malloc((sizeof(int*)*(myrowsize+2)));
        Gnew = (int **)malloc((sizeof(int*)*(myrowsize+2)));
        Bnew = (int **)malloc((sizeof(int*)*(myrowsize+2)));
        for (k=0;k<myrowsize+2;k++){
            R[k] = (int *)malloc(sizeof(int)*(mycolsize+2));
            G[k] = (int *)malloc(sizeof(int)*(mycolsize+2));
            B[k] = (int *)malloc(sizeof(int)*(mycolsize+2));
            Rnew[k] = (int *)malloc(sizeof(int)*(mycolsize+2));
            Gnew[k] = (int *)malloc(sizeof(int)*(mycolsize+2));
            Bnew[k] = (int *)malloc(sizeof(int)*(mycolsize+2));
	}
        bufsize = myrowsize > mycolsize ? myrowsize : mycolsize;
        sendbuf = (int *)malloc(sizeof(int)*(bufsize));
        recvbuf = (int *)malloc(sizeof(int)*(bufsize));
	
/* Read input on process 0 and distribute to processes */
	if (rank==0){
                localrow = 1;
                lastcolsize = colsize - pcolsize*(npcols-1);
        	Rrow = (int *)malloc(sizeof(int)*(colsize));
        	Grow = (int *)malloc(sizeof(int)*(colsize));
        	Brow = (int *)malloc(sizeof(int)*(colsize));

        	fp = fopen("David.ps", "r");
		while(! feof(fp))
		{
			icheck = fscanf(fp, "\n%[^\n]", str);
			if (nlines < 5) {strcpy((char *)lines[nlines++],(char *)str);}
			else if(icheck>0){
				for (sptr=&str[0];*sptr != '\0';sptr+=6){
					sscanf(sptr,"%2x",&h1);
					sscanf(sptr+2,"%2x",&h2);
					sscanf(sptr+4,"%2x",&h3);
					if (row < rowsize) {
						Rrow[col] = h1;
						Grow[col] = h2;
						Brow[col] = h3;
						col++;
					}
					if (col==colsize){
                                                coords[0] = row/prowsize;
                                                for(k=0;k<npcols;k++){
                                                        nsend = (k<npcols-1 ? pcolsize : lastcolsize); 
       							coffset = k*pcolsize;
							coords[1] = k;
  							MPI_Cart_rank(new_comm, coords, &dest);
							if(dest!=0){
								MPI_Send(Rrow+coffset,nsend,MPI_INT,dest,tag,new_comm);
								MPI_Send(Grow+coffset,nsend,MPI_INT,dest,tag,new_comm);
								MPI_Send(Brow+coffset,nsend,MPI_INT,dest,tag,new_comm);
							}
							else{
								for(localcol=1;localcol<=mycolsize;localcol++){
									R[localrow][localcol] = Rrow[coffset+localcol-1];
									G[localrow][localcol] = Grow[coffset+localcol-1];
									B[localrow][localcol] = Brow[coffset+localcol-1];
								}
								localrow++;
							}
						}
						col = 0;
						row++;
					}
				}
			}
		}
		fclose(fp);
        }
        else{
		for(localrow=1;localrow<=myrowsize;localrow++){
			MPI_Recv(&R[localrow][1],mycolsize,MPI_INT,0,tag,new_comm,&status);
			MPI_Recv(&G[localrow][1],mycolsize,MPI_INT,0,tag,new_comm,&status);
			MPI_Recv(&B[localrow][1],mycolsize,MPI_INT,0,tag,new_comm,&status);
		}
 	}

	nblurs = 10;
	MPI_Barrier(new_comm);
	double t1;
	if(rank==0){
		gettimeofday(&tim, NULL);
		t1=tim.tv_sec+(tim.tv_usec/1000000.0);
	}
        
	for(k=0;k<nblurs;k++){

/************************************************************************************************
 *
 * INSERT CODE HERE
 *
 * The inserted code must perform shift communication operations in the left, right, up, and
 * down directions on the R, G, and B arrays. When communicating columns of an array the
 * sendbuf and recvbuf arrays (allocated previously) may be used. 
 *
 ***********************************************************************************************/

		for(localrow=1;localrow<=myrowsize;localrow++){
                        row = prowsize*myrow + localrow - 1;
			for (localcol=1;localcol<=mycolsize;localcol++){	
                        	col = pcolsize*mycol + localcol - 1;
				if (row != 0 && row != (rowsize-1) && col != 0 && col != (colsize-1)){
					Rnew[localrow][localcol] = (R[localrow+1][localcol]+R[localrow-1][localcol]+R[localrow][localcol+1]+R[localrow][localcol-1])/4;
					Gnew[localrow][localcol] = (G[localrow+1][localcol]+G[localrow-1][localcol]+G[localrow][localcol+1]+G[localrow][localcol-1])/4;
					Bnew[localrow][localcol] = (B[localrow+1][localcol]+B[localrow-1][localcol]+B[localrow][localcol+1]+B[localrow][localcol-1])/4;
				}
				else if (row == 0 && col != 0 && col != (colsize-1)){
					Rnew[localrow][localcol] = (R[localrow+1][localcol]+R[localrow][localcol+1]+R[localrow][localcol-1])/3;
					Gnew[localrow][localcol] = (G[localrow+1][localcol]+G[localrow][localcol+1]+G[localrow][localcol-1])/3;
					Bnew[localrow][localcol] = (B[localrow+1][localcol]+B[localrow][localcol+1]+B[localrow][localcol-1])/3;
				}
				else if (row == (rowsize-1) && col != 0 && col != (colsize-1)){
					Rnew[localrow][localcol] = (R[localrow-1][localcol]+R[localrow][localcol+1]+R[localrow][localcol-1])/3;
					Gnew[localrow][localcol] = (G[localrow-1][localcol]+G[localrow][localcol+1]+G[localrow][localcol-1])/3;
					Bnew[localrow][localcol] = (B[localrow-1][localcol]+B[localrow][localcol+1]+B[localrow][localcol-1])/3;
				}
				else if (col == 0 && row != 0 && row != (rowsize-1)){
					Rnew[localrow][localcol] = (R[localrow+1][localcol]+R[localrow-1][localcol]+R[localrow][localcol+1])/3;
					Gnew[localrow][localcol] = (G[localrow+1][localcol]+G[localrow-1][localcol]+G[localrow][localcol+1])/3;
					Bnew[localrow][localcol] = (B[localrow+1][localcol]+B[localrow-1][localcol]+B[localrow][localcol+1])/3;
				}
				else if (col == (colsize-1) && row != 0 && row != (rowsize-1)){
					Rnew[localrow][localcol] = (R[localrow+1][localcol]+R[localrow-1][localcol]+R[localrow][localcol-1])/3;
					Gnew[localrow][localcol] = (G[localrow+1][localcol]+G[localrow-1][localcol]+G[localrow][localcol-1])/3;
					Bnew[localrow][localcol] = (B[localrow+1][localcol]+B[localrow-1][localcol]+B[localrow][localcol-1])/3;
				}
				else if (row==0 &&col==0){
					Rnew[localrow][localcol] = (R[localrow][localcol+1]+R[localrow+1][localcol])/2;
					Gnew[localrow][localcol] = (G[localrow][localcol+1]+G[localrow+1][localcol])/2;
					Bnew[localrow][localcol] = (B[localrow][localcol+1]+B[localrow+1][localcol])/2;
				}
				else if (row==0 &&col==(colsize-1)){
					Rnew[localrow][localcol] = (R[localrow][localcol-1]+R[localrow+1][localcol])/2;
					Gnew[localrow][localcol] = (G[localrow][localcol-1]+G[localrow+1][localcol])/2;
					Bnew[localrow][localcol] = (B[localrow][localcol-1]+B[localrow+1][localcol])/2;
				}
				else if (row==(rowsize-1) &&col==0){
					Rnew[localrow][localcol] = (R[localrow][localcol+1]+R[localrow-1][localcol])/2;
					Gnew[localrow][localcol] = (G[localrow][localcol+1]+G[localrow-1][localcol])/2;
					Bnew[localrow][localcol] = (B[localrow][localcol+1]+B[localrow-1][localcol])/2;
				}
				else if (row==(rowsize-1) &&col==(colsize-1)){
					Rnew[localrow][localcol] = (R[localrow][localcol-1]+R[localrow-1][localcol])/2;
					Gnew[localrow][localcol] = (G[localrow][localcol-1]+G[localrow-1][localcol])/2;
					Bnew[localrow][localcol] = (B[localrow][localcol-1]+B[localrow-1][localcol])/2;
				}		
			}
		}
		for(localrow=1;localrow<=myrowsize;localrow++){
			for (localcol=1;localcol<=mycolsize;localcol++){
			    R[localrow][localcol] = Rnew[localrow][localcol];
			    G[localrow][localcol] = Gnew[localrow][localcol];
			    B[localrow][localcol] = Bnew[localrow][localcol];
			}
		}
	}

/* Output timing result */
	MPI_Barrier(new_comm);
	if(rank==0){
		gettimeofday(&tim, NULL);
		double t2=tim.tv_sec+(tim.tv_usec/1000000.0);
		MPI_Get_processor_name(name,&len);
		printf("Rank %d on %s: %.6lf seconds elapsed\n", rank,name,t2-t1);
	}
	
/* Gather data from processes and output on process 0 */
	if(rank==0){
		localrow = 1;
		fout= fopen("DavidBlur.ps", "w");
		for (k=0;k<nlines;k++) fprintf(fout,"\n%s", lines[k]);
		fprintf(fout,"\n");
		for(row=0;row<rowsize;row++){
                	coords[0] = row/prowsize;
			for (k=0;k<npcols;k++){
                        	coords[1] = k;
  				MPI_Cart_rank(new_comm, coords, &dest);
                                nsend = (k<npcols-1 ? pcolsize : lastcolsize); 
       				coffset = k*pcolsize;
				if(dest!=0){
					MPI_Recv(Rrow+coffset,nsend,MPI_INT,dest,tag,new_comm,&status);
					MPI_Recv(Grow+coffset,nsend,MPI_INT,dest,tag,new_comm,&status);
					MPI_Recv(Brow+coffset,nsend,MPI_INT,dest,tag,new_comm,&status);
				}
				else{
					for(localcol=1;localcol<=mycolsize;localcol++){
						Rrow[coffset+localcol-1] = R[localrow][localcol];
						Grow[coffset+localcol-1] = G[localrow][localcol];
						Brow[coffset+localcol-1] = B[localrow][localcol];
					}
					localrow++;
				}
			}
			for(col=0;col<colsize;col++){
				fprintf(fout,"%02x%02x%02x",Rrow[col],Grow[col],Brow[col]);
				lineno++;
				if (lineno==linelen){
					fprintf(fout,"\n");
					lineno = 0;
				}
			}
		}
		fclose(fout);
	}
	else{
		for(localrow=1;localrow<=myrowsize;localrow++){
			MPI_Send(&R[localrow][1],mycolsize,MPI_INT,0,tag,new_comm);
			MPI_Send(&G[localrow][1],mycolsize,MPI_INT,0,tag,new_comm);
			MPI_Send(&B[localrow][1],mycolsize,MPI_INT,0,tag,new_comm);
		}
	}
/* Finalize and exit */
        MPI_Finalize();
    	return 0;
}
