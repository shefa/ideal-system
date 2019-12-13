#include <stdio.h>
#include <omp.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>

int main (int argc, const char * argv[]) {
	static int const maxlen = 200, rowsize = 521, colsize = 428, linelen = 12;
	char str[maxlen], lines[5][maxlen];
	FILE *fp, *fout;
	int nlines = 0;
	unsigned int h1, h2, h3;
	char *sptr;
	int R[rowsize+2][colsize+2], G[rowsize+2][colsize+2], B[rowsize+2][colsize+2];
	int Rnew[rowsize+2][colsize+2], Gnew[rowsize+2][colsize+2], Bnew[rowsize+2][colsize+2];
	int row = 0, col = 0, nblurs, lineno=0, k;
	struct timeval tim;
	
	fp = fopen("David.ps", "r");
 
	while(! feof(fp))
	{
		fscanf(fp, "\n%[^\n]", str);
		if (nlines < 5) {strcpy((char *)lines[nlines++],(char *)str);}
		else{
			for (sptr=&str[0];*sptr != '\0';sptr+=6){
				sscanf(sptr,"%2x",&h1);
				sscanf(sptr+2,"%2x",&h2);
				sscanf(sptr+4,"%2x",&h3);
				
				if (col==colsize){
					col = 0;
					row++;
				}
				if (row < rowsize) {
					R[row+1][col+1] = h1;
					G[row+1][col+1] = h2;
					B[row+1][col+1] = h3;
				}
				col++;
			}
		}
	}
	fclose(fp);
	
	nblurs = 10;
	gettimeofday(&tim, NULL);
	double t1=tim.tv_sec+(tim.tv_usec/1000000.0);
	for(k=0;k<nblurs;k++){
	#pragma omp parallel shared(R,G,B) private(row,col) num_threads(4)
	{
		#pragma omp sections
		{
			#pragma omp section
			{
				R[0][1]=R[1][0]=R[1][2]+R[2][1];
				R[0][1]>>=1; R[1][0]-=R[0][1];
				G[0][1]=G[1][0]=G[1][2]+G[2][1];
				G[0][1]>>=1; G[1][0]-=G[0][1];
				B[0][1]=B[1][0]=B[1][2]+B[2][1];
				B[0][1]>>=1; B[1][0]-=B[0][1];
			}
			#pragma omp section
			{
				R[0][colsize]=R[1][colsize+1]=R[1][colsize-1]+R[2][colsize];
				R[0][colsize]>>=1; R[1][colsize+1]-=R[0][colsize];
				G[0][colsize]=G[1][colsize+1]=G[1][colsize-1]+G[2][colsize];
				G[0][colsize]>>=1; G[1][colsize+1]-=G[0][colsize];
				B[0][colsize]=B[1][colsize+1]=B[1][colsize-1]+B[2][colsize];
				B[0][colsize]>>=1; B[1][colsize+1]-=B[0][colsize];
			}
			#pragma omp section
			{
				R[rowsize][0]=R[rowsize+1][1]=R[rowsize][2]+R[rowsize-1][1];
				R[rowsize][0]>>=1; R[rowsize+1][1]-=R[rowsize][0];
				G[rowsize][0]=G[rowsize+1][1]=G[rowsize][2]+G[rowsize-1][1];
				G[rowsize][0]>>=1; G[rowsize+1][1]-=G[rowsize][0];
				B[rowsize][0]=B[rowsize+1][1]=B[rowsize][2]+B[rowsize-1][1];
				B[rowsize][0]>>=1; B[rowsize+1][1]-=B[rowsize][0];
			}
			#pragma omp section
			{
				R[rowsize][colsize+1]=R[rowsize+1][colsize]=R[rowsize][colsize-1]+R[rowsize-1][colsize];
				R[rowsize][colsize+1]>>=1; R[rowsize+1][colsize]-=R[rowsize][colsize+1];
				G[rowsize][colsize+1]=G[rowsize+1][colsize]=G[rowsize][colsize-1]+G[rowsize-1][colsize];
				G[rowsize][colsize+1]>>=1; G[rowsize+1][colsize]-=G[rowsize][colsize+1];
				B[rowsize][colsize+1]=B[rowsize+1][colsize]=B[rowsize][colsize-1]+B[rowsize-1][colsize];
				B[rowsize][colsize+1]>>=1; B[rowsize+1][colsize]-=B[rowsize][colsize+1];
			}
		}
		
		#pragma omp for simd
		for(row=2;row<rowsize;row++){
			R[row][0]=(R[row-1][1]+R[row+1][1]+R[row][2])/3;
			R[row][colsize+1]=(R[row-1][colsize]+R[row+1][colsize]+R[row][colsize-1])/3;
			G[row][0]=(G[row-1][1]+G[row+1][1]+G[row][2])/3;
			G[row][colsize+1]=(G[row-1][colsize]+G[row+1][colsize]+G[row][colsize-1])/3;
			B[row][0]=(B[row-1][1]+B[row+1][1]+B[row][2])/3;
			B[row][colsize+1]=(B[row-1][colsize]+B[row+1][colsize]+B[row][colsize-1])/3;
		}
		#pragma omp for simd
		for(col=2;col<colsize;col++){
			R[0][col]=(R[1][col-1]+R[1][col+1]+R[2][col])/3;
			R[rowsize+1][col]=(R[rowsize][col-1]+R[rowsize][col+1]+R[rowsize-1][col])/3;
			G[0][col]=(G[1][col-1]+G[1][col+1]+G[2][col])/3;
			G[rowsize+1][col]=(G[rowsize][col-1]+G[rowsize][col+1]+G[rowsize-1][col])/3;
			B[0][col]=(B[1][col-1]+B[1][col+1]+B[2][col])/3;
			B[rowsize+1][col]=(B[rowsize][col-1]+B[rowsize][col+1]+B[rowsize-1][col])/3;
		}

		#pragma omp for simd
		for(row=1;row<=rowsize;row++){
			for (col=1;col<=colsize;col++){
				Rnew[row][col] = (R[row+1][col]+R[row-1][col]+R[row][col+1]+R[row][col-1])/4;
				Gnew[row][col] = (G[row+1][col]+G[row-1][col]+G[row][col+1]+G[row][col-1])/4;
				Bnew[row][col] = (B[row+1][col]+B[row-1][col]+B[row][col+1]+B[row][col-1])/4;
			}
		}
		#pragma omp for simd
		for(row=1;row<=rowsize;row++){
			for (col=1;col<=colsize;col++){
			    R[row][col] = Rnew[row][col];
			    G[row][col] = Gnew[row][col];
			    B[row][col] = Bnew[row][col];
			}
		}

	}
	}
	gettimeofday(&tim, NULL);
	double t2=tim.tv_sec+(tim.tv_usec/1000000.0);
	printf("%.6lf seconds elapsed\n", t2-t1);
	
	fout= fopen("DavidBlurOMP.ps", "w");
	for (k=0;k<nlines;k++) fprintf(fout,"\n%s", lines[k]);
	fprintf(fout,"\n");
	for(row=1;row<=rowsize;row++){
		for (col=1;col<=colsize;col++){
			fprintf(fout,"%02x%02x%02x",R[row][col],G[row][col],B[row][col]);
			lineno++;
			if (lineno==linelen){
				fprintf(fout,"\n");
				lineno = 0;
			}
		}
	}
	fclose(fout);
    return 0;
}
