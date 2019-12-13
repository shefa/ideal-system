#gcc -fopenmp -o blurOMP blurOMP.c -lm
for i in {1..100}
do
	./blurOMP >> benchmark_omp_16threads.txt
	#./blur >> benchmark_normal.txt
	sleep 0.5
done