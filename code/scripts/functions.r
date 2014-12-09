minmax.normalize <- function(x, min=0, max){
  x <- (x-min)/max
  return(x)
}

threshold <- function(x, threshold, removed.val="lt", replace.val=0) {
  if(removed.val=="lt"){
    x[x < threshold] <- replace.val
  }
  else if(removed.val=="gt"){
    x[x > threshold] <- replace.val
  }
  return(x)
}

unweight <- function(x){
  x[x>0] <- 1
  return(x)
}

connectivity.to.uw.graph <- function(con.mat, th=0, set.max=F, dir.mode="directed"){
  library(igraph)
  if(set.max==F){set.max=max(con.mat)}
  
  norm.mat <- minmax.normalize(con.mat,max=set.max)
  th.mat <- threshold(norm.mat, th)
  uw.mat <- unweight(th.mat)
  uw.graph <- graph.adjacency(uw.mat, mode=dir.mode, add.colnames=F)
  return(uw.graph)
}

abs.thresh.and.bin <- function(con.mat, th=0){
  #set.max=max(con.mat)
  #norm.mat <- minmax.normalize(con.mat,max=set.max)
  th.mat <- threshold(con.mat, th)
  uw.mat <- unweight(th.mat)
  return(uw.mat)
}

remove.unconnected <- function(g){
  library(igraph)
  newg <- delete.vertices(g, which(degree(g) < 1))
  return(newg)
}
