#Evan Mahone -- 2013
#
#Based on the algorithm described in watts & grogatz (1998)
#
#Takes in a desired number of nodes, N, a mean degree, K, and
#a probability of rewiring, B.
#Outputs an adjacency matrix of a graph with small-world connectivity
watts_strogatz <- function(N, K, B){
  #Correct the error checking later
  if (K%%2 != 0){stop("K is not even.")}
  if (K >= N || K < 2){stop("K must be at least between 0 and N.")}
  if (B > 1 || B < 0){stop("B must be between 1 and 0 (inclusive).")}
  
  adjmat <- matrix(rep(0,N*N), N)
  
  #Creating the K-regular ring lattice and edge set
  for(i in 1:N){
    for(j in 1:(K/2)){
      ij_p <- circle((i+j),N)
      ij_m <- circle((i-j),N)
      
      adjmat[ij_p,i] = 1
      adjmat[ij_m,i] = 1
      
      #edgeset <- rbind(edgeset, c(ij_p, i), c(ij_m, i))
    }
  }
    
  #Rewiring at probability B
  for(i in 1:N){
    for(j in 1:N)
      if((i>j) && adjmat[j,i] == 1){
        rand <- runif(1,0,1)
        if(rand > B){
          poss_k <- 1:N
          poss_k <- poss_k[!poss_k == i]
          poss_k <- poss_k[!poss_k == j]
          k <- sample(poss_k, 1)
          
          adjmat[j,i] <- 0
          adjmat[i,j] <- 0
          
          adjmat[k,i] <- 1
          adjmat[i,k] <- 1
        }
      }
  }
  return(adjmat)
}

circle <- function(ij, N){
  if (ij <= 0) {return(N+ij)}
  else if(ij > N){return(ij-N)}
  else{return(ij)}
}