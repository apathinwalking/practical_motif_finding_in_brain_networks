source("./SCRIPTS/functions.r")
setwd("/home/em-2091/Documents/school/smp/workspace")
adhd_conn_dir_names <- as.character(read.table("./ETC/adhd-conn-names.txt")[,1])
nki_conn_dir_names <- as.character(read.table("./ETC/nki-conn-names.txt")[,1])

foldernames <- table(c())

for(i in nki_conn_dir_names){
     sp1 <- strsplit(i, "/")
     sp2 <- unlist(strsplit(sp1[[1]][length(sp1[[1]])], "_"))
     sp1 <- unlist(sp1)
     folder <- paste0(sp2[1], "_", sp2[2])
     foldernames <- rbind(foldernames, folder)
}
#write.csv2(foldernames, "./ETC/nki_data_names", col.names=F, row.names=F, quote=F)
rm(sp1,sp2,folder,foldernames)
foldernames <- table(c())
for(i in adhd_conn_dir_names){
     sp1 <- strsplit(i, "/")
     sp2 <- unlist(strsplit(sp1[[1]][length(sp1[[1]])], "_"))
     sp1 <- unlist(sp1)
     folder <- paste0(sp2[1], "_", sp2[2])
     foldernames <- rbind(foldernames, folder)
}
#write.csv2(foldernames, "./ETC/adhd_data_names", col.names=F, row.names=F, quote=F)
