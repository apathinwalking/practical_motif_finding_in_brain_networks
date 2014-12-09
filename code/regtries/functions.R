library(rgraph6)
GTCanon <- function(G, permute=T){
  G <- permute.vertices(G, canonical.permutation(G)$labeling)
  
  curr_deg <- degree(G)
  last_deg <- curr_deg
  glbl_deg <- last_deg
  
  label <- rep(NA, length(V(G)))
  V(G)$labeled = F
  
  for(pos in length(V(G)):1){
    #print(c("cdeg: ", curr_deg))
    #print(c("ldeg: ", last_deg))
    #print(c("gdeg: ", glbl_deg))
    
    candidates <- as.vector(subset(V(G), V(G)$labeled == F)) #currently unlabeled
    #print(c("!LAB: ", candidates))
    if(length(articulation.points(G)) >= 1){
      candidates <- candidates[-articulation.points(G)] #subtract articulation points
      #print(c("&ART: ", candidates))
    }
    candidates <- subset(candidates, curr_deg[candidates] == min(curr_deg[candidates])) #min of current degs
    #print(c("&MCD: ", candidates))
    if(length(candidates > 1)){
      candidates <- subset(candidates, last_deg[candidates] == min(last_deg[candidates]))
      #print(c("&MLD: ", candidates))
      if(length(candidates > 1)){
        candidates <- subset(candidates, glbl_deg[candidates] == min(glbl_deg[candidates]))
        #print(c("&GLD: ", candidates))
        if(length(candidates > 1)){
          u_min <- min(candidates) #Because we applied bliss first, this should be the same every time
          #print(c("&MIN: ", u_min))
        }
        else{u_min <- candidates}
      }
      else{u_min <- candidates}
    }
    else{u_min <- candidates}
    label[pos] <- u_min
    #print(c("labs: ", label))
    V(G)[u_min]$labeled = T
    last_deg <- curr_deg
    lost_connections <- as.vector(E(G)[adj(u_min)])
    #print(c("lost: ", lost_connections))
    #print("#########################")
    for (i in lost_connections){
      curr_deg[i] <- curr_deg[i] - 1
    }
  }
  if(permute==T){
    return(permute.vertices(G, label))
  }
  return(label)
}

#Works for up to N=4.... N is order, here.
generateGraphs <- function(N, self_loops=F, disconnected = F, isos=F){
  subgraphs <- list()
  num_possible_matrices <- (2^(N^2)-1)
  for(i in 0:num_possible_matrices){
    bit_string <- as.numeric(intToBits(i)[1:N^2])
    mat <- matrix(bit_string, N, N)
    if(self_loops==F){
      tmp <- 0
      for(a in 1:N){
        if(mat[a,a] == 1){
          tmp <- tmp+1
        }
      }
      if(tmp != 0){next}
    }
    if(disconnected==F){
      cs <- colSums(mat)
      rs <- rowSums(mat)
      tmp <- F
      for(j in 1:N){
        if(cs[j] == rs[j] && cs[j] == 0){
          tmp <- T
        }
      }
      if(tmp == T){next}
    }
    g <- graph.adjacency(mat, mode="max")
    if(disconnected == F){
      if(!is.connected(g)){next}
    }
    #subgraphs[[length(subgraphs)+1]] <- mat
    subgraphs[[length(subgraphs)+1]] <- g
  }
  if(isos == T){return(subgraphs)}
  removeIsomorphs <- function(in_graphs, outgraphs=list()){
    fixed = in_graphs[[1]]
    print(fixed)
    outgraphs[[length(outgraphs)+1]] <- fixed
    rec_graphs <- list()
    for(g in in_graphs){
      if(!(graph.isomorphic(fixed, g))){
        rec_graphs[[length(rec_graphs)+1]] <- g
      }
    }
    if(length(rec_graphs) > 0){
      return(removeIsomorphs(rec_graphs, outgraphs))
      print("RECURSE!")
    }
    return(outgraphs)
  }
  return(removeIsomorphs(subgraphs))
}

getConnectedGraphs <- function(N){
  if(N==3){g6 <- read.table("./DATA/GRAPHS/undirected_3.txt")}
  else if(N==4){g6 <- read.table("./DATA/GRAPHS/undirected_4.txt")}
  else if(N==5){g6 <- read.table("./DATA/GRAPHS/undirected_5.txt")}
  else if(N==6){g6 <- read.table("./DATA/GRAPHS/undirected_6.txt")}
  else if(N==7){g6 <- read.table("./DATA/GRAPHS/undirected_7.txt")}
  else if(N==8){g6 <- read.table("./DATA/GRAPHS/undirected_8.txt")}
  else if(N==9){g6 <- read.table("./DATA/GRAPHS/undirected_9.txt")}
  graphsz <- list()
  for( i in 1:nrow(g6)){
    graphsz[[length(graphsz)+1]] <- graph.adjacency(asAMatrix(as.vector(g6[i,])), mode="undirected")
  }
  return(graphsz)
}