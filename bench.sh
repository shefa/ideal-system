code=blurOMP4
data=benchmark_omp4.txt
gcc -fopenmp -o $code $code.c -lm

for scheduling in {dynamic,static}
do

echo "$scheduling scheduling" >> $data
echo "10 chunks" >>$data
for t in {1..16}
do
    echo $t >> $data
    export OMP_NUM_THREADS=$t
    for i in {1..10}
    do
        ./$code >> $data
        sleep 0.5
    done
    sleep 2
    tail $data
done

for chunk in {20..200..20}
do
export OMP_SCHEDULE=dynamic,$chunk
echo "$chunk chunks" >> $data
for t in {1..16}
do
    echo $t
    echo $t >> $data
    export OMP_NUM_THREADS=$t
    for i in {1..10}
    do
    	./$code >> $data
    	sleep 0.5
    done
    sleep 2
    tail $data
done
sleep 5
done
sleep 10
done
