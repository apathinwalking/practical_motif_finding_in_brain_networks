GTrie <- setRefClass(
  "gtrie",
  fields = list(
    root = "node",
    igraph = "igraph",
    order = "numeric"
    ),
  methods = list(
    #initalize the root node and graph
    initialize = function(){
      ##Initialize the root node
      root <<- GTrieNode$new(depth=1, is_graph=F, id=1)
      .self$igraph <<- graph(n=1, c(), directed=F)
      V(.self$igraph)$name <<- "" #the node is blank
      V(.self$igraph)$color <<- "grey"
      V(.self$igraph)$shape <<- "rectangle"
      order <<- 1
  }, 
    #canonical labeling
    gt_Canon = function(G, permute=T){
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
    },
    #insert a graph into the gtrie
    createGTrie = function(subgraphs){
      for (g in subgraphs){
        str = get.adjacency(gt_Canon(g), sparse=F, type="upper")
        print(str)
        #symmetry breaking conditions go here
        insert(.self$root, str, 1, length(V(g)))
      }
      V(.self$igraph)$"shape" <- "rectangle"
    },
    #insert a graph onto a gtrie
    insert = function(gt_node, str, k, order){
      if(k==order){gt_node$is_graph = T} #mark as a terminal node
      else{
        for(c in gt_node$children){
          if(c$adjesMatch(str[,k][1:k])){
            insert(c, str, gt_node$depth+1, order)
          }
        }
        #adding a new child
        adjacencies <- str[,k][1:k]
        update(adjacencies, gt_node$id)
        c <- gt_node$addChild(adjacencies, is_a_graph=F, i_d=.self$order)
        insert(c, str, gt_node$depth+1, order)
      }
    },
    update = function(adjes, old_id){
      .self$order <- .self$order + 1
      #v <- vertex(shape="rectangle", color="tan", name=adjes)
      .self$igraph <- add.vertices(.self$igraph, nv=1)
      #V(.self$igraph)[order]$name <- as.character(adjes)
      .self$igraph <- add.edges(.self$igraph, c(order, old_id))
    }
  )
)