require(igraph)
setClass("igraph")##allows me to have igraphs in my GTrieNodes
setClass("node")##a virtual class allowing me to have a GTrieNode within a GTrieNode
GTrieNode <- setRefClass(
  "gtrienode",
  fields = list(
    depth = "numeric", #how far down the trie this node is
    parent = "node", #the parent node, should also be a GTrieNode
    children = "list", #list of child GTrieNodes
    adjes = "numeric", #a list of connections that our node makes with ancestors
    is_graph = "logical", #whether this node is currently at the end of our trie,
    igraph = "igraph", #the current graph at the node
    id = "numeric"
    ),
  methods = list(
     print = function(){
          base::print(quote=F, "---------------------------------------")
          base::print(quote=F,c("DEPTH", .self$depth))
          base::print(quote=F,c("ADJACENCIES: ", .self$adjes))
          base::print(quote=F,"PARENT:")
          base::print(quote=F,c("---- adjacencies:", .self$parent$adjes))
          base::print(quote=F,c("CHILDREN:"))
          for (ch in .self$children){
            base::print(quote=F,c("---- adjacencies:", ch$adjes, "|| isgraph: ", ch$is_graph))
          }
          base::print(quote=F, "---------------------------------------")
     },
     addChild = function(adjacencies, is_a_graph, i_d){
       child <- GTrieNode$new(depth=.self$depth+1, parent=.self, adjes=adjacencies, is_graph = is_a_graph, id = i_d)
       len <- length(children)
       .self$children[len+1] <- child
       return(child)
     },
     adjesMatch = function(adjacencies){
       tmp <- adjes == adjacencies
       if(F %in% tmp){return(F)}
       return(T)
     }
       ),
  contains = "node"
  )
