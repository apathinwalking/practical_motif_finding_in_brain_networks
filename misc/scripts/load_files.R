library(igraph)

lines90 <- readLines("./abs_90.txt")
lines75 <- readLines("./abs_75.txt")
lines60 <- readLines("./abs_60.txt")
lines45 <- readLines("./abs_45.txt")
lines30 <- readLines("./abs_30.txt")
lines15 <- readLines("./abs_15.txt")

g90 <- list()
g90$data <- matrix(rep(NA,9*520), 520,9)
colnames(g90$data) <- c("size", "local_cc", "global_cc", "avg_deg", "max_deg", "min_deg", "avg_path", "global_eff", "local_eff")
g75 <- list()
g75$data <- matrix(rep(NA,9*520), 520,9)
colnames(g75$data) <- c("size", "local_cc", "global_cc", "avg_deg", "max_deg", "min_deg", "avg_path", "global_eff", "local_eff")
g60 <- list()
g60$data <- matrix(rep(NA,9*520), 520,9)
colnames(g60$data) <- c("size", "local_cc", "global_cc", "avg_deg", "max_deg", "min_deg", "avg_path", "global_eff", "local_eff")
g45 <- list()
g45$data <- matrix(rep(NA,9*520), 520,9)
colnames(g45$data) <- c("size", "local_cc", "global_cc", "avg_deg", "max_deg", "min_deg", "avg_path", "global_eff", "local_eff")
g30 <- list()
g30$data <- matrix(rep(NA,9*520), 520,9)
colnames(g30$data) <- c("size", "local_cc", "global_cc", "avg_deg", "max_deg", "min_deg", "avg_path", "global_eff", "local_eff")
g15 <- list()
g15$data <- matrix(rep(NA,9*520), 520,9)
colnames(g15$data) <- c("size", "local_cc", "global_cc", "avg_deg", "max_deg", "min_deg", "avg_path", "global_eff", "local_eff")



for(i in 1:520){
  g <- graph.adjacency(read.table(lines90[i], header=T, sep=","), mode="undirected")
  g90[[length(g90) + 1]]  <- g
  g90$data[i,1] <- length(E(g))
  g90$data[i,2] <- mean(transitivity(g,type="local"))
  g90$data[i,3] <- mean(transitivity(g,type="global"))
  g90$data[i,4] <- mean(degree(g))
  g90$data[i,5] <- max(degree(g))
  g90$data[i,6] <- min(degree(g))
  g90$data[i,7] <- mean(shortest.paths(g))
  g90$data[i,8] <- ge(g)
  g90$data[i,9] <- le(g)
  tmp <- get.edgelist(g90[[i+1]], names=F)
  tmp <- cbind(tmp, rep(1,nrow(tmp)))
  write.table(tmp, "./tmp.txt", quote=F, sep=" ", row.names=F, col.names=F)
  cmd = paste0("./gtrieScanner -s 3 -m gtrie undir3.gt -g tmp.txt -o RESULTS/90/90_3_", i, ".txt")
  system(cmd)
}

for(i in 1:520){
  g <- graph.adjacency(read.table(lines75[i], header=T, sep=","), mode="undirected")
  g75[[length(g75) + 1]]  <- g
  g75$data[i,1] <- length(E(g))
  g75$data[i,2] <- mean(transitivity(g,type="local"))
  g75$data[i,3] <- mean(transitivity(g,type="global"))
  g75$data[i,4] <- mean(degree(g))
  g75$data[i,5] <- max(degree(g))
  g75$data[i,6] <- min(degree(g))
  g75$data[i,7] <- mean(shortest.paths(g))
  g75$data[i,8] <- ge(g)
  g75$data[i,9] <- le(g)
  tmp <- get.edgelist(g75[[i+1]], names=F)
  tmp <- cbind(tmp, rep(1,nrow(tmp)))
  write.table(tmp, "./tmp.txt", quote=F, sep=" ", row.names=F, col.names=F)
  cmd = paste0("./gtrieScanner -s 3 -m gtrie undir3.gt -g tmp.txt -o RESULTS/75/75_3_", i, ".txt")
  system(cmd)
}

for(i in 1:520){
  g <- graph.adjacency(read.table(lines60[i], header=T, sep=","), mode="undirected")
  g60[[length(g60) + 1]]  <- g
  g60$data[i,1] <- length(E(g))
  g60$data[i,2] <- mean(transitivity(g,type="local"))
  g60$data[i,3] <- mean(transitivity(g,type="global"))
  g60$data[i,4] <- mean(degree(g))
  g60$data[i,5] <- max(degree(g))
  g60$data[i,6] <- min(degree(g))
  g60$data[i,7] <- mean(shortest.paths(g))
  g60$data[i,8] <- ge(g)
  g60$data[i,9] <- le(g)
  tmp <- get.edgelist(g60[[i+1]], names=F)
  tmp <- cbind(tmp, rep(1,nrow(tmp)))
  write.table(tmp, "./tmp.txt", quote=F, sep=" ", row.names=F, col.names=F)
  cmd = paste0("./gtrieScanner -s 3 -m gtrie undir3.gt -g tmp.txt -o RESULTS/60/60_3_", i, ".txt")
  system(cmd)
}

for(i in 1:520){
  g <- graph.adjacency(read.table(lines45[i], header=T, sep=","), mode="undirected")
  g45[[length(g45) + 1]]  <- g
  g45$data[i,1] <- length(E(g))
  g45$data[i,2] <- mean(transitivity(g,type="local"))
  g45$data[i,3] <- mean(transitivity(g,type="global"))
  g45$data[i,4] <- mean(degree(g))
  g45$data[i,5] <- max(degree(g))
  g45$data[i,6] <- min(degree(g))
  g45$data[i,7] <- mean(shortest.paths(g))
  g45$data[i,8] <- ge(g)
  g45$data[i,9] <- le(g)
  tmp <- get.edgelist(g45[[i+1]], names=F)
  tmp <- cbind(tmp, rep(1,nrow(tmp)))
  write.table(tmp, "./tmp.txt", quote=F, sep=" ", row.names=F, col.names=F)
  cmd = paste0("./gtrieScanner -s 3 -m gtrie undir3.gt -g tmp.txt -o RESULTS/45/45_3_", i, ".txt")
  system(cmd)
}

for(i in 1:520){
  g <- graph.adjacency(read.table(lines30[i], header=T, sep=","), mode="undirected")
  g30[[length(g30) + 1]]  <- g
  g30$data[i,1] <- length(E(g))
  g30$data[i,2] <- mean(transitivity(g,type="local"))
  g30$data[i,3] <- mean(transitivity(g,type="global"))
  g30$data[i,4] <- mean(degree(g))
  g30$data[i,5] <- max(degree(g))
  g30$data[i,6] <- min(degree(g))
  g30$data[i,7] <- mean(shortest.paths(g))
  g30$data[i,8] <- ge(g)
  g30$data[i,9] <- le(g)
  tmp <- get.edgelist(g30[[i+1]], names=F)
  tmp <- cbind(tmp, rep(1,nrow(tmp)))
  write.table(tmp, "./tmp.txt", quote=F, sep=" ", row.names=F, col.names=F)
  cmd = paste0("./gtrieScanner -s 3 -m gtrie undir3.gt -g tmp.txt -o RESULTS/30/30_3_", i, ".txt")
  system(cmd)
}

for(i in 1:520){
  g <- graph.adjacency(read.table(lines15[i], header=T, sep=","), mode="undirected")
  g15[[length(g15) + 1]]  <- g
  g15$data[i,1] <- length(E(g))
  g15$data[i,2] <- mean(transitivity(g,type="local"))
  g15$data[i,3] <- mean(transitivity(g,type="global"))
  g15$data[i,4] <- mean(degree(g))
  g15$data[i,5] <- max(degree(g))
  g15$data[i,6] <- min(degree(g))
  g15$data[i,7] <- mean(shortest.paths(g))
  g15$data[i,8] <- ge(g)
  g15$data[i,9] <- le(g)
  tmp <- get.edgelist(g15[[i+1]], names=F)
  tmp <- cbind(tmp, rep(1,nrow(tmp)))
  write.table(tmp, "./tmp.txt", quote=F, sep=" ", row.names=F, col.names=F)
  cmd = paste0("./gtrieScanner -s 3 -m gtrie undir3.gt -g tmp.txt -o RESULTS/15/15_3_", i, ".txt")
  system(cmd)
}