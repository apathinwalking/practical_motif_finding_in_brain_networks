#Used to process the GTrieScanner Output

cd ~/Documents/school/smp/workspace/MY_CODE/GTS_ANALYSIS/RESULTS

for file in ./15_4/*
	do head -n 600 -v $file >> 4_sum.csv
done


for file in ./30_4/*
	do head -n 600 -v $file >> 4_sum.csv
done


for file in ./45_4/*
	do head -n 600 -v $file >> 4_sum.csv
done

for file in ./60_4/*
	do head -n 600 -v $file >> 4_sum.csv
done

for file in ./75_4/*
	do head -n 750 -v $file >> 4_sum.csv
done

for file in ./90_4/*
	do head -n 900 -v $file >> 4_sum.csv
done
