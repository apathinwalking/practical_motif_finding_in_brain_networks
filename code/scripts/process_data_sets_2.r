setwd("/home/em-2091/Documents/school/smp/workspace")
adhd_fold_dir_names <- as.character(read.table("./ETC/adhd_data_names")[,1])
nki_fold_dir_names <- as.character(read.table("./ETC/nki_data_names")[,1])
all_nki_fold_dir_names <- as.character(read.table("./ETC/nki-all-names.txt")[,1])
all_adhd_fold_dir_names <- as.character(read.table("./ETC/adhd-all-names.txt")[,1])
for(i in adhd_fold_dir_names){
     cmd <- paste0("mkdir ", "NETWORK_DATA/ADHD200_CC200/", i)
     system(cmd)
     print(cmd)
     for(j in all_adhd_fold_dir_names){
          if(grepl(i,j,fixed=T)){
               sp1 <- strsplit(j, "/")
               sp2 <- unlist(strsplit(sp1[[1]][length(sp1[[1]])], "_"))
               tmp <- paste0(sp2[3:length(sp2)], collapse="_")
               tmp2 <- paste0("NETWORK_DATA/ADHD200_CC200/", i, "/", tmp)
               #print(tmp2)
               cmd2 <- paste0("cp ", j, " ", tmp2)
               print(cmd2)
               system(cmd2)
          }
     }
}