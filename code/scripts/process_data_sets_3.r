setwd("/home/em-2091/Documents/school/smp/workspace")
adhd_mats <- as.character(read.table("./ETC/adhd-conn-names_new.txt")[,1]) 
nki_mats <- as.character(read.table("./ETC/nki-conn-names_new.txt")[,1])
for(i in nki_mats){
     mat <- as.matrix(read.table(i))
     norm <- (mat - mat_min) / (mat_max - mat_min)
     for(j in 1:19){
       th_n = j*5
       th_r = (j*5)/100
       th_mat <- abs.thresh.and.bin(norm, th_r)
       new_file = gsub("connectivity_matrix_file.txt", paste0("abs_th_", th_n, ".csv"), i, fixed=T)
       write.table(th_mat, new_file, quote=F, sep=",",row.names=F)
     }
}

for(i in adhd_mats){
  mat <- as.matrix(read.table(i))
  norm <- (mat - mat_min) / (mat_max - mat_min)
  for(j in 1:19){
    th_n = j*5
    th_r = (j*5)/100
    th_mat <- abs.thresh.and.bin(norm, th_r)
    new_file = gsub("connectivity_matrix_file.txt", paste0("abs_th_", th_n, ".csv"), i, fixed=T)
    write.table(th_mat, new_file, quote=F, sep=",",row.names=F)
  }
}
