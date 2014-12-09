/*      _       _     ___                            
 __ _| |_ _ _(_)___/ __| __ __ _ _ _  _ _  ___ _ _ 
/ _` |  _| '_| / -_)__ \/ _/ _` | ' \| ' \/ -_) '_| : Compiled Code
\__, |\__|_| |_\___|___/\__\__,_|_||_|_||_\___|_|  For better understanding
|___/     
*/
/*Cmdline.cpp - Gives cmd line functionality for program.*/
//#include "CmdLine.h"

	/*Cmdline.h - Gives outline of cmd line functionality*/
	#ifndef _CMDLINE_
	#define _CMDLINE

	//#include "GraphMatrix.h"

		/*GraphMatrix.h - Implementation of graphs with AMs/ ALs*/
		#ifndef _GRAPHMATRIX_
		#define _GRAPHMATRIX_
		//#include "Graph.h"
			
			/*Graph.h - A "partially" abstract graph base class*/
			#ifndef _GRAPH_
			#define _GRAPH_
			//#include "Common.h"
					
				/*Common.h - "Common def'ns"*/
				#ifndef _COMMON_
				#define _COMMON_
				
				#include <algorithm>
				#include <iostream>
				#include <string>
				#include <vector>
				#include <ctime>
				#include <list>
				#include <map>

				#include <cstdio>
				#include <cstdlib>
				#include <cstring>
				#include <climits>

				#define MAX_BUF 1024

				#define VERSION "0.1"
				#define PROGRAM_NAME "gtrieScanner"

				#define SEPARATOR    "------------------------------------------"

				#define MIN_MOTIF_SIZE  3
				#define MAX_MOTIF_SIZE 50
 
				#define ERROR_HEADER "Error: "

				#define INVALID -1

				#define EPSILON 0.00000001

				#define BIT_SET(n,i)   ((n)|=(1<<(i)))
					//n equals the bitwise or with n and 
					//( 1 bitshifted (i) to the left )
					//presumablyfor this and below n is some 
					//space and i is a size of the space
				#define BIT_CLEAR(n,i) ((n)&=~(1<<(i)))
					//n equals the bitwise and of n and the 
					//complement of (1 bitshifted (i) to the left)
				#define BIT_VALUE(n,i) (((n)>>(i))&1)
					//returns the logical and of (n bitshifted i to the right) and 1

				#define smallNode char 
					//smallNode is just a renaming of char

				#define INVALID_FILE   "__NULL__"
				
				#define DEFAULT_RESULTS "results"    
					// Default name for results file
				#define DEFAULT_OCC "occ"            
					// Default name for occurrences file

				typedef enum {NOMETHOD, ESU, GTRIE, SUBGRAPHS} MethodType;
				typedef enum {NOOUTPUT, TEXT, HTML}            OutputType;
				typedef enum {NOFORMAT, SIMPLE, SIMPLE_WEIGHT} FormatType;

				using namespace std;
					//imports all variables from std namespace

				typedef std::pair<int,int> iPair;
					//iPair is defined as a std::pair with two ints
				typedef std::vector<int> VInt;
					//VInt is definied as an std::vector with type int. 
					//A vector is a dynamically allocated array
				typedef std::vector<VInt> VVInt;
					//Vvint is defined as an std::vector of Vints. 
					//That is, it is a vector of vectors of ints
				typedef vector<smallNode *> VVsmallNode;
					//VVsmallNode is a vector of smallNode pointers. That is, 
					//each element is a pointer pointing to something the
					//size of a char (smallNode = char)
				typedef map< string, int> mapStringInt;
					//mapStringInt is a map which stores ints with string keys

				typedef struct { 
					/*ResultType - a struct for storing results data*/
					char *s;
					int f_original;
					double avg_random;
					double dev_random;
					double z_score;
				} ResultType;

				class Global {
					/*Global - a class for "global" variables*/
					public:
						static bool show_occ;  
							//Show occurrences?
						static FILE *occ_file; 
							//FILE handle for dumping occurrences;
				};

				#endif

			typedef enum{DIRECTED, UNDIRECTED} GraphType;
				//just an enum for telling us a graph type

			class Graph {
				/*Graph - a "partially" abstract graph class
				contains lots of virtual functions, which when implemented 
				would return the values of private variables*/
				public:
					virtual bool **adjacencyMatrix() = 0;
						//seems to be a fucntion simply a 2D array of true or falses - 
						//indicating an edge. The =0 at the end indicates that 
						//this is a pure virtual function - indicating that 
						//you must derive a class to use it.

					virtual ~Graph() {};
						//tilde indicates that this is a destructor for the graph class.
						//Here it is unimplemented.

					virtual void createGraph(int n, GraphType t) = 0; 
						//does exactly what it looks like it would do. 
						//I suppose an implemented version would modify variables 
						//in the Graph class. pure virtual function.

					virtual GraphType type() = 0;
						//A function which will tell us what graph type this is.
						//Returns either DIRECTED or UNDIRECTED

					virtual void zero() = 0;                
						//remove all connections

					virtual void addEdge(int a, int b) = 0; 
						//add edge from a to b - where a and b are node labels
					virtual void rmEdge(int a, int b)  = 0; 
						//remove edge from a to b

					virtual int numNodes()  = 0; 
						//get Number of nodes in graph 
					virtual int numEdges()  = 0; 
						//get Number of edges in graph 
					 
					virtual bool hasEdge(int a, int b) = 0; 
						//Edge between a and b?
					virtual bool isConnected(int a, int b) = 0;  
						//Edge (a,b) or (b,a)?

					virtual int nodeOutEdges(int a) = 0;    
						//get # of Edges from node a
					virtual int nodeInEdges(int a) = 0;     
						//get # of Edges to node a
					virtual int numNeighbours(int a) = 0;   
						//get # of Neighbours of node a. Recall neighbors are nodes sharing 
						//an edge with a vertex v (here a)

					virtual void sortNeighbours() = 0;       
						//All neighbours sorted in increasing order (sort vectors)
						//Sorting I suppose is to be done in terms of the integer value
					virtual void sortNeighboursArray() = 0;  
						//All neighbours sorted in increasing order (sort arrays)

					virtual void makeArrayNeighbours() = 0;  
						//Create arrays of neighbours and discard vectors
					virtual void makeVectorNeighbours() = 0; 
						//Create vectors of neighbours and discard arrays

					virtual vector<int> *neighbours(int a) = 0; 
						//Neighbours of node a
					virtual int **matrixNeighbours() = 0;            
						//Neighbours of node a in array form
						//Confused a bit about this one
					virtual int *arrayNeighbours(int a) = 0;         
						//Neighbours of node a in array form
					virtual int *arrayNumNeighbours() = 0;           
						//Numbers of neighbours in array form
					virtual vector<int> *outEdges(int a) = 0;   
						//Outgoing edges of node a
					virtual vector<int> *inEdges(int a) = 0;    
						//Ingoing edges of node a
			};

			#endif

		class GraphMatrix : public Graph {
			//GraphMatrix is a derivative of Graph,
			//It is used to implement AMs and ALs with Graph
			private:
				GraphType _type;
					//indicates the type of the graph: undirected or directed

				int _num_nodes; 
					//Simply the order of the graph
				int _num_edges; 
					//Simply the size of the graph

				bool **_adjM;
					//Adjacency matrix representation of graph
					//A 2D array of bools telling us whether an edge exists or not between two nodes
				int  **_array_neighbours;
					//Essentially the adjacency list representation of graph
					//A 2d array, with each row a different size
					//need to call makeArrayNeighbors 
					

				vector<int> *_adjOut;
					//An array of vectors (one for each node, i) where each vector is a list of the nodes
					//j for which an edge exists from i to 
					//I believe that adjIn will be same as adjOut for undirected
				vector<int> *_adjIn;
					//An array of vectors (one for each node, i) where each vector is a list of the nodes
					//j for which an edge exists from j to i
				vector<int> *_neighbours;
					//Essentially the adjacency list representation of graph
					//An array of vectors (one for each node, i) where each vector is a list of the nodes
					//j for which an edge exists from j to i OR from i to j
					//This seems to be the default adjacency list representation

				int *_in; 
					//an array of ints, where each index, i, represents a node
					//and the number stored there is the number of in-edges made with that node
	  			int *_out; 
	  				//an array of ints, where each index, i, represents a node
					//and the number stored there is the number of connections made from i to other nodes
	  			int *_num_neighbours; 
	  				//an array of ints, where each index, i, represents a node
	  				//and the number stored there is the number of total edges made with that node


	  			void _init(); 
	  				//_num_nodes and _num_edges set to 0.
	  				//All other private vars set to NULL.
	 			void _delete(); 
	 				//Goes through and deletes all private vars
	 				//Goes through every item in _adjM and deletes if not null
	 				//Checks if every other private var is null before deleting it
	  			void _removeVector(vector<int> &v, int b); 
	  				//does something to clear the passed by reference vector somehow

	  		public:
	  			graphMatrix(); 
	  				//Simply calls the private _init() method
	  			~graphMatrix();
	  				//Simply calls the private _delete() method

	  			bool **adjacencyMatrix() {return _adjM;}
	  				//Just returns the adjacency matrix representation of the graph (stored in _adjM)

				void createGraph(int n, GraphType t);
					//resets graph, n here represents the number of nodes
					//initiates _adjM, _adjIn, _adjOut, _neighbors, _in, _out
					//and _num_neighbors to size n, and then calls zero() - 
					//setting everything to zero


				GraphType type() {return _type;}

				void zero();
					//sets everything to "zero"
					//sets _num_edges to zero, sets each ele in _in, _out, and _num_neighbots to zero
					//calls vector.clear method for each member of _adjIn, _adjOut, and _neighbours, 
					//which destroys every element of the vector, leaving a vector of size 0

				int numNodes() {return _num_nodes;}
				int numEdges() {return _num_edges;}

				void addEdge(int a, int b); 
					//add edge from a to b
					//does nothing if edge already exists
					//sets in edge in adjM[a][b]
					//sets _adjOut[a] to b and _adjIn[b] to a
					//adds 1 to _out[a], _in[b], and _num_edges
					//if there is no edge from b to a, it adds one following the preceding process
				void rmEdge(int a, int b);  // remove edge from a to b
					//does the exact opposite process of addEdge
				bool hasEdge(int a, int b) {return _adjM[a][b];} 
				bool isConnected(int a, int b)  {return _adjM[a][b] || _adjM[b][a];}

				int nodeOutEdges(int a) {return _out[a];}
				int nodeInEdges(int a)  {return _in[a];}
				int numNeighbours(int a) {return _num_neighbours[a];}
				void sortNeighbours();
					//Calls sort on each row of _neighbors
				void sortNeighboursArray();
					//Calls qsort on each row of _array_neighbors
				void makeArrayNeighbours();
					//converts _neighbors into _array_neighbors and clears _neighbors
				void makeVectorNeighbours();
					//converts _array_neighbors into _neighbors and clears _array_neighbors

				vector<int> *neighbours(int a) {return &_neighbours[a];}
				int **matrixNeighbours()       {return _array_neighbours;}
				int *arrayNeighbours(int a)    {return _array_neighbours[a];}
				int *arrayNumNeighbours()      {return _num_neighbours;}
				vector<int> *outEdges(int a)   {return &_adjOut[a];}
				vector<int> *inEdges(int a)    {return &_adjIn[a];}
		};

		#endif	
	//#include "GraphUtils.h"

		/*GraphUtils.h - graph utilities*/
		#ifndef _GRAPHUTILS_
		#define _GRAPHUTILS_

		//#include "Graph.h" //ALREADY INCLUDED

		class GraphUtils {
			/*GraphUtils - A class with utilities for converting user input into a graph*/

			private:
				static int *_degree;
				static int **_ds;
				static int *_neighbours;

			public:

				// Compare two integers
				static int int_compare(const void *a, const void *b);

				
				static void readFileTxt(Graph *g, const char *s, bool dir, bool weight);
					//Read file 's', with direction 'dir' to graph 'g'
				
				static void strToGraph(Graph *g, const char *s, int size, bool dir);
					//Convert adjacency matrix to graph of 'size' nodes

				static void orderGraph(Graph *old, Graph *g);
				static int _compare_int(const void *a, const void *b);
				static int _compare_int_descending(const void *a, const void *b);
				static int _compare_degree(const void *a, const void *b);

		};

		#endif
	//#include "Error.h"

			/*Error.h - defines what to do when an error occurs*/
			#ifndef _ERROR_
			#define _ERROR_

			#include "Graph.h"

			#define EXIT_FAILURE 1
				//This could be changed to suit our needs

			class Error {
				/*Error - a class which holds the error message*/
				public:
					static void msg(const char *format, ...);
			};

			#endif
	//#include "Common.h"//ALREADY INCLUDED
	//#include "Esu.h"

			/*Esu.h - implementation of the ESU motif finding algorithm*/
			#ifndef _ESU_
			#define _ESU_

			//#include "Common.h"//ALREADY INCLUDED
			//#include "GraphTree.h"

				/*GraphTree.h - Graph (0-1) Tree Implementation*/
				#ifndef _GRAPHTREE_
				#define _GRAPHTREE_
				//#include "Common.h"//ALREADY INCLUDED
				//#include GTrie.h

					/*GTrie.h - G-Trie implementation & associated methods*/
					#ifndef _GTRIE_
					#define _GTRIE_

					//#include "Common.h"//ALREADY INCLUDED
					//#include "Graph.h"//ALREADY INCLUDED
					
					#define BASE_FORMAT      95
					#define BASE_FIRST       ' '
					#define BASE_BITS        6

					class GraphTree; // forward declaration

					class GTrieNode {
						private:
							bool _is_intset_included(list<int> a, list<int> b);
							bool _is_pairset_included(list<iPair> a, list<iPair> b);

						public:

							static int *mymap;
							static bool *used;
							static bool **adjM;
							static int **fastnei;
							static int *numnei;
							static int glk;
							static int numNodes;
							static bool isdir;
							static double *prob;


							list< list<int> >   this_node_cond; // This node must be bigger than all these nodes
							list< list<iPair> > cond;           // List of symmetry breaking conditions
							list<GTrieNode *> child;            // List of child g-trie nodes

							bool cond_ok;                       // no need to check for conditions
							bool cond_this_ok;                  // no need to check for this node conditions

							int depth;          // Depth of g-trie node

							bool is_graph;       // Is this node the end of a subGraph?
							int frequency;      // Frequency of this particular subGraph

							bool *in;           // Outward edges
							bool *out;          // Inward edges
							int total_in;       // Number of inward  edges
							int total_out;      // Number of outward edges
							int total_edges;    // Number of inward + outward edges

							int nconn;          // Number of connected nodes
							int *conn;          // Connected nodes


							GTrieNode(int d);   // Create g-trie node with depth 'd'
							~GTrieNode();

							void insert(Graph *g);
							void insertCond(Graph *g, list<iPair> *cond);
							void showAsText(FILE *f);

							int countNodes();
							int countGraphs();
							int countGraphPaths();
							int maxDepth();

							void zeroFrequency();
							void showFrequency();

							int frequencyGraph(Graph *g);

							void goCondDir();
							void goCondUndir();
							void goCondSample();

							void insertConditionsFiltered(list<iPair> *cond);

							double countOccurrences();
							int countGraphsApp();

							void populateGraphTree(GraphTree *tree, char *s, int size);
							void populateMap(mapStringInt *m, char *s, int size);

							void writeToFile(FILE *f);
							void readFromFile(FILE *f);

							void cleanConditions();
							void clean(int a, int b);
							void makeConditionsArray();
					};

					class GTrie {
						private:
							GTrieNode *_root;

						public:
							GTrie();
							~GTrie();

							void insertGraph(Graph *g);
							void insertGraphCond(Graph *g, list<iPair> *cond);
							void insertGraphString(int size, const char* s);
							void insertGraphNautyString(int size, const char* s, bool dir, int label);

							int frequencyGraphString(int size, const char *s);

							void showAsText(FILE *f);
							double compressionRate();
							int maxDepth();

							void census(Graph *g);
							void censusSample(Graph *g, double *p);

							void showFrequency();

							void unlist();

							int countGraphsApp();
							int countGraphs();
							double countOccurrences();

							void cleanConditions();

							void writeToFile(char *s);
							void readFromFile(char *s);
							void readSubgraphs(int size, bool dir, char *s);

							void populateGraphTree(GraphTree *tree, int size);
							void populateMap(mapStringInt *m, int size);
					};

					#endif

				class GraphTreeNode   {
					public:
						GraphTreeNode();
						~GraphTreeNode();

						int frequency;
						GraphTreeNode *zero, *one;

						void zeroFrequency();
						void incrementString(int pos, char *s);
						void setString(int pos, char *s, int f);
						void addString(int pos, char *s, int f);
						void showFrequency(int pos, char *s);

						void populateGTrie(GTrie *gt, int size, int pos, char *s);
						void populateMap(mapStringInt *m, int size, int pos, char *s);
						void populateGTrieNauty(GTrie *gt, int size, int pos, char *s, bool dir);

						bool equal(GraphTreeNode *gt,   int pos, char *s);
						bool equal(GTrie *gt, int size, int pos, char *s);

						int countGraphs();
						double countOccurrences();
				};

				class GraphTree   {
					private:

					public:
						GraphTreeNode *root;

						GraphTree();
						~GraphTree();

						void zeroFrequency();
						void incrementString(char *s);
						void setString(char *s, int f);
						void addString(char *s, int f);
						void showFrequency(int maxsize);

						bool equal(GraphTree *gt, int maxsize);  
						bool equal(GTrie *gt,     int maxsize);  
						void populateGTrie(GTrie *gt, int maxsize);
						void populateMap(mapStringInt *m, int maxsize);
						void populateGTrieNauty(GTrie *gt, int maxsize, bool dir);

						int countGraphs();
						double countOccurrences();
				};

				#endif

			/*! This class implements the ESU subgraph enumeration algorithm */
			class Esu {
				private:
					static int *_current;
					static int * _ext;
					static int _next;
					static int _graph_size;
					static int _motif_size;
					static Graph * _g;
					static GraphTree *_sg;
					static double *_prob;

					static void _go(int n, int size, int next, int *ext);
					static void _goSample(int n, int size, int next, int *ext);

				public:
					static void countSubgraphs(Graph *g, int k, GraphTree *sg);
					static void countSubgraphsSample(Graph *g, int k, GraphTree *sg, double *p);

			};

			#endif	
	//#include "GTrie.h"//ALREADY INCLUDED
	//#include "Isomorphism.h"
		/*Isomorphism.h - graph isomorphism utils*/
		#ifndef _ISOMORPHISM_
		#define _ISOMORPHISM_

		//#include "common.h"//ALREADY INCLUDED
		//#include "Graph.h"

		#define MAXN MAX_MOTIF_SIZE
		#define WORKSPACE_SIZE MAXN*160

		//#include "nauty/nauty.h"

			/*Nauty.h*/
			#ifndef  _NAUTY_H_    /* only process this file once */
			#define  _NAUTY_H_

			/* The parts between the ==== lines are modified by configure when
			creating nauty.h out of nauty-h.in.  If configure is not being used,
			it is necessary to check they are correct.
			====================================================================*/

			/* Check whether various headers are available */
			#define HAVE_UNISTD_H  1    /* <unistd.h> */
			#define HAVE_SYSTYPES_H  1    /* <sys/types.h> */
			#define HAVE_STDDEF_H  1     /* <stddef.h> */
			#define HAVE_STDLIB_H  1    /* <stdlib.h> */
			#define HAVE_STRING_H  1    /* <string.h> */
			#define MALLOC_DEC 1  /* 1 = malloc() is declared in stdlib.h,
							 2 = in malloc.h, 0 = in neither place */
			#define HAS_MATH_INF 1 /* INFINITY is defined in math.h or
							some system header likely to be used */
			#define HAS_STDIO_UNLOCK 1  /* Whether there are getc_unlocked,
					putc_unlocked,flockfile and funlockfile*/

			#define SIZEOF_INT 4
			#define SIZEOF_LONG 4
			#define SIZEOF_LONG_LONG 8   /* 0 if nonexistent */

			#define HAVE_CONST 1    /* compiler properly supports const */

			/*==================================================================*/

			/* The following line must be uncommented for compiling into Magma. */
			/* #define NAUTY_IN_MAGMA  */

			#ifdef NAUTY_IN_MAGMA
			#include "defs.h"
			#include "system.h"
			#include "bs.h"
			#define OLDEXTDEFS
			#else
			#include <stdio.h>
			#define P_(x) x
			#endif

			#if defined(__cray) || defined(__cray__) || defined(cray)
			#define SYS_CRAY        /* Cray UNIX, portable or standard C */
			#endif

			#if defined(__unix) || defined(__unix__) || defined(unix)
			#define SYS_UNIX
			#endif

			#if !HAVE_CONST
			#define const
			#endif

			/*****************************************************************************
			*                                                                            *
			*    AUTHOR: Brendan D. McKay                                                *
			*            School of Computer Science                                      *
			*            Australian National University                                  *
			*            Canberra, ACT 0200, Australia                                   *
			*            phone:  +61 2 6125 3845    fax:  +61 2 6125 0010                *
			*            email:  bdm@cs.anu.edu.au                                       *
			*                                                                            *
			*   Copyright (1984-2010) Brendan McKay.  All rights reserved.  Permission   *
			*   is hereby given for use and/or distribution with the exception of        *
			*   sale for profit or application with nontrivial military significance.    *
			*   You must not remove this copyright notice, and you must document any     *
			*   changes that you make to this program.                                   *
			*   This software is subject to this copyright only, irrespective of         *
			*   any copyright attached to any package of which this is a part.           *
			*                                                                            *
			*   This program is only provided "as is".  No responsibility will be taken  *
			*   by the author, his employer or his pet rabbit* for any misfortune which  *
			*   befalls you because of its use.  I don't think it will delete all your   *
			*   files, burn down your computer room or turn your children against you,   *
			*   but if it does: stiff cheddar.  On the other hand, I very much welcome   *
			*   bug reports, or at least I would if there were any bugs.                 *
			*                                                       * RIP, 1989          *
			*                                                                            *
			*   If you wish to acknowledge use of this program in published articles,    *
			*   please do so by citing the User's Guide:                                 *
			*                                                                            *
			*     B. D. McKay, nauty User's Guide (Version 2.4), 
			*         http://cs.anu.edu.au/~bdm/nauty/.
			*                                                                            *
			*   CHANGE HISTORY                                                           *
			*       10-Nov-87 : final changes for version 1.2                            *
			*        5-Dec-87 : renamed to version 1.3 (no changes to this file)         *
			*       28-Sep-88 : added PC Turbo C support, making version 1.4             *
			*       23-Mar-89 : changes for version 1.5 :                                *
			*                   - reworked M==1 code                                     *
			*                   - defined NAUTYVERSION string                            *
			*                   - made NAUTYH_READ to allow this file to be read twice   *
			*                   - added optional ANSI function prototypes                *
			*                   - added validity check for WORDSIZE                      *
			*                   - added new fields to optionblk structure                *
			*                   - updated DEFAULTOPTIONS to add invariants fields        *
			*                   - added (set*) cast to definition of GRAPHROW            *
			*                   - added definition of ALLOCS and FREES                   *
			*       25-Mar-89 : - added declaration of new function doref()              *
			*                   - added UNION macro                                      *
			*       29-Mar-89 : - reduced the default MAXN for small machines            *
			*                   - removed OUTOFSPACE (no longer used)                    *
			*                   - added SETDIFF and XOR macros                           *
			*        2-Apr-89 : - extended statsblk structure                            *
			*        4-Apr-89 : - added IS_* macros                                      *
			*                   - added ERRFILE definition                               *
			*                   - replaced statsblk.outofspace by statsblk.errstatus     *
			*        5-Apr-89 : - deleted definition of np2vector (no longer used)       *
			*                   - introduced EMPTYSET macro                              *
			*       12-Apr-89 : - eliminated MARK, UNMARK and ISMARKED (no longer used)  *
			*       18-Apr-89 : - added MTOOBIG and CANONGNIL                            *
			*       12-May-89 : - made ISELEM1 and ISELEMENT return 0 or 1               *
			*        2-Mar-90 : - added EXTPROC macro and used it                        *
			*       12-Mar-90 : - added SYS_CRAY, with help from N. Sloane and A. Grosky *
			*                   - added dummy groupopts field to optionblk               *
			*                   - select some ANSI things if __STDC__ exists             *
			*       20-Mar-90 : - changed default MAXN for Macintosh versions            *
			*                   - created SYS_MACTHINK for Macintosh THINK compiler      *
			*       27-Mar-90 : - split SYS_MSDOS into SYS_PCMS4 and SYS_PCMS5           *
			*       13-Oct-90 : changes for version 1.6:                                 *
			*                   - fix definition of setword for WORDSIZE==64             *
			*       14-Oct-90 : - added SYS_APOLLO version to avoid compiler bug         *
			*       15-Oct-90 : - improve detection of ANSI conformance                  *
			*       17-Oct-90 : - changed temp name in EMPTYSET to avoid A/UX bug        *
			*       16-Apr-91 : changes for version 1.7:                                 *
			*                   - made version SYS_PCTURBO use free(), not cfree()       *
			*        2-Sep-91 : - noted that SYS_PCMS5 also works for Quick C            *
			*                   - moved MULTIPLY to here from nauty.c                    *
			*       12-Jun-92 : - changed the top part of this comment                   *
			*       27-Aug-92 : - added version SYS_IBMC, thanks to Ivo Duentsch         *
			*        5-Jun-93 : - renamed to version 1.7+, only change in naututil.h     *
			*       29-Jul-93 : changes for version 1.8:                                 *
			*                   - fixed error in default 64-bit version of FIRSTBIT      *
			*                     (not used in any version before ALPHA)                 *
			*                   - installed ALPHA version (thanks to Gordon Royle)       *
			*                   - defined ALLOCS,FREES for SYS_IBMC                      *
			*        3-Sep-93 : - make calloc void* in ALPHA version                     *
			*       17-Sep-93 : - renamed to version 1.9,                                *
			*                        changed only dreadnaut.c and nautinv.c              *
			*       24-Feb-94 : changes for version 1.10:                                *
			*                   - added version SYS_AMIGAAZT, thanks to Carsten Saager   *
			*                     (making 1.9+)                                          *
			*       19-Apr-95 : - added prototype wrapper for C++,                       *
			*                     thanks to Daniel Huson                                 *
			*        5-Mar-96 : - added SYS_ALPHA32 version (32-bit setwords on Alpha)   *
			*       13-Jul-96 : changes for version 2.0:                                 *
			*                   - added dynamic allocation                               *
			*                   - ERRFILE must be defined                                *
			*                   - added FLIPELEM1 and FLIPELEMENT macros                 *
			*       13-Aug-96 : - added SWCHUNK? macros                                  *
			*                   - added TAKEBIT macro                                    *
			*       28-Nov-96 : - include sys/types.h if not ANSI (tentative!)           *
			*       24-Jan-97 : - and stdlib.h if ANSI                                   *
			*                   - removed use of cfree() from UNIX variants              *
			*       25-Jan-97 : - changed options.getcanon from boolean to int           *
			*                     Backwards compatibility is ok, as boolean and int      *
			*                     are the same.  Now getcanon=2 means to get the label   *
			*                     and not care about the group.  Sometimes faster.       *
			*        6-Feb-97 : - Put in #undef for FALSE and TRUE to cope with          *
			*                     compilers that illegally predefine them.               *
			*                   - declared nauty_null and nautil_null                    *
			*        2-Jul-98 : - declared ALLBITS                                       *
			*       21-Oct-98 : - allow WORDSIZE==64 using unsigned long long            *
			*                   - added BIGNAUTY option for really big graphs            *
			*       11-Dec-99 : - made bit, leftbit and bytecount static in each file    *
			*        9-Jan-00 : - declared nauty_check() and nautil_check()              *
			*       12-Feb-00 : - Used #error for compile-time checks                    *
			*                   - Added DYNREALLOC                                       *
			*        4-Mar-00 : - declared ALLMASK(n)                                    *
			*       27-May-00 : - declared CONDYNFREE                                    *
			*       28-May-00 : - declared nautil_freedyn()                              *
			*       16-Aug-00 : - added OLDNAUTY and changed canonical labelling         *
			*       16-Nov-00 : - function prototypes are now default and unavoidable    *
			*                   - removed UPROC, now assume all compilers know void      *
			*                   - removed nvector, now just int (as it always was)       *
			*                   - added extra parameter to targetcell()                  *
			*                   - removed old versions which were only to skip around    *
			*                     bugs that should have been long fixed:                 *
			*                     SYS_APOLLO and SYS_VAXBSD.                             *
			*                   - DEFAULTOPIONS now specifies no output                  *
			*                   - Removed obsolete SYS_MACLSC version                    *
			*       21-Apr-01 : - Added code to satisfy compilation into Magma.  This    *
			*                       is activated by defining NAUTY_IN_MAGMA above.       *
			*                   - The *_null routines no longer exist                    *
			*                   - Default maxinvarlevel is now 1.  (This has no effect   *
			*                        unless an invariant is specified.)                  *
			*                   - Now labelorg has a concrete declaration in nautil.c    *
			*                        and EXTDEFS is not needed                           *
			*        5-May-01 : - NILFUNCTION, NILSET, NILGRAPH now obsolete.  Use NULL. *
			*       11-Sep-01 : - setword is unsigned int in the event that UINT_MAX     *
			*                     is defined and indicates it is big enough              *
			*       17-Oct-01 : - major rewrite for 2.1.  SYS_* variables gone!          *
			*                     Some modernity assumed, eg size_t                      *
			*        8-Aug-02 : - removed MAKEEMPTY  (use EMPTYSET instead)              *
			*                   - deleted OLDNAUTY everywhere                            *
			*       27-Aug-02 : - converted to use autoconf.  Now the original of this   *
			*                     file is nauty-h.in. Run configure to make nauty.h.     *
			*       20-Dec-02 : - increased INFINITY                                     *
			*                     some reorganization to please Magma                    *
			*                   - declared nauty_freedyn()                               *
			*       17-Nov-03 : - renamed INFINITY to NAUTY_INFINITY                     *
			*       29-May-04 : - added definition of SETWORD_FORMAT                     *
			*       14-Sep-04 : - extended prototypes even to recursive functions        *
			*       16-Oct-04 : - added DEFAULTOPTIONS_GRAPH                             *
			*       24-Oct-04 : Starting 2.3                                             *
			*                   - remove register declarations as modern compilers       *
			*                     tend to find them a nuisance                           *
			*                   - Don't define the obsolete symbol INFINITY if it is     *
			*                     defined already                                        *
			*       17-Nov-04 : - make 6 counters in statsblk unsigned long              *
			*       17-Jan-04 : - add init() and cleanup() to dispatchvec                *
			*       12-Nov-05 : - Changed NAUTY_INFINITY to 2^30+2 in BIGNAUTY case      *
			*       22-Nov-06 : Starting 2.4                                             *
			*                   - removed usertcellproc from options                     *
			*                     changed bestcell to targetcell in dispatch vector      *
			*                     declare targetcell and maketargetcell                  *
			*       29-Nov-06 : - add extraoptions to optionblk                          *
			*                   - add declarations of extra_autom and extra_level        *
			*       10-Dec-06 : - BIGNAUTY is gone!  Now permutation=shortish=int.       *
			*                     NAUTY_INFINITY only depends on whether sizeof(int)=2.  *
			*       27-Jun-08 : - define nauty_counter and LONG_LONG_COUNTERS            *
			*       30-Jun-08 : - declare version 2.4                                    *
			*       14-Jun-10 : Maintenance release 2.4r1                                *
			*        7-Aug-10 : Maintenance release 2.4r2                                *
			*                                                                            *
			*    nauty.h.  Generated from nauty-h.in by configure.
			*                                                                            *
			*****************************************************************************/

			/*****************************************************************************
			*                                                                            *
			*   16-bit, 32-bit and 64-bit versions can be selected by defining WORDSIZE. *
			*   The largest graph that can be handled has MAXN vertices.                 *
			*   Both WORDSIZE and MAXN can be defined on the command line.               *
			*   WORDSIZE must be 16, 32 or 64; MAXN must be <= NAUTY_INFINITY-2;         *
			*                                                                            *
			*   With a very slight loss of efficiency (depending on platform), nauty     *
			*   can be compiled to dynamically allocate arrays.  Predefine MAXN=0 to     *
			*   achieve this effect, which is default behaviour from version 2.0.        *
			*   In that case, graphs of size up to NAUTY_INFINITY-2 can be handled       *
			*   if the the memory is available.                                          *
			*                                                                            *
			*   If only very small graphs need to be processed, use MAXN<=WORDSIZE       *
			*   since this causes substantial code optimizations.                        *
			*                                                                            *
			*   Conventions and Assumptions:                                             *
			*                                                                            *
			*    A 'setword' is the chunk of memory that is occupied by one part of      *
			*    a set.  This is assumed to be >= WORDSIZE bits in size.                 *
			*                                                                            *
			*    The rightmost (loworder) WORDSIZE bits of setwords are numbered         *
			*    0..WORDSIZE-1, left to right.  It is necessary that the 2^WORDSIZE      *
			*    setwords with the other bits zero are totally ordered under <,=,>.      *
			*    This needs care on a 1's-complement machine.                            *
			*                                                                            *
			*    The int variables m and n have consistent meanings throughout.          *
			*    Graphs have n vertices always, and sets have m setwords always.         *
			*                                                                            *
			*    A 'set' consists of m contiguous setwords, whose bits are numbered      *
			*    0,1,2,... from left (high-order) to right (low-order), using only       *
			*    the rightmost WORDSIZE bits of each setword.  It is used to             *
			*    represent a subset of {0,1,...,n-1} in the usual way - bit number x     *
			*    is 1 iff x is in the subset.  Bits numbered n or greater, and           *
			*    unnumbered bits, are assumed permanently zero.                          *
			*                                                                            *
			*    A 'graph' consists of n contiguous sets.  The i-th set represents       *
			*    the vertices adjacent to vertex i, for i = 0,1,...,n-1.                 *
			*                                                                            *
			*    A 'permutation' is an array of n ints repesenting a permutation of      *
			*    the set {0,1,...,n-1}.  The value of the i-th entry is the number to    *
			*    which i is mapped.                                                      *
			*                                                                            *
			*    If g is a graph and p is a permutation, then g^p is the graph in        *
			*    which vertex i is adjacent to vertex j iff vertex p[i] is adjacent      *
			*    to vertex p[j] in g.                                                    *
			*                                                                            *
			*    A partition nest is represented by a pair (lab,ptn), where lab and ptn  *
			*    are int arrays.  The "partition at level x" is the partition whose      *
			*    cells are {lab[i],lab[i+1],...,lab[j]}, where [i,j] is a maximal        *
			*    subinterval of [0,n-1] such that ptn[k] > x for i <= k < j and          *
			*    ptn[j] <= x.  The partition at level 0 is given to nauty by the user.   *
			*    This is  refined for the root of the tree, which has level 1.           *
			*                                                                            *
			*****************************************************************************/

			#define NAUTYVERSIONID 2400   /* 1000 times the version number */
			#define NAUTYREQUIRED 2400    /* Minimum compatible version */

			#ifndef NAUTY_IN_MAGMA
			#if HAVE_SYSTYPES_H
			#include <sys/types.h>
			#endif
			#if HAVE_UNISTD_H
			#include <unistd.h>
			#endif
			#if HAVE_STDDEF_H
			#include <stddef.h>
			#endif
			#if HAVE_STDLIB_H
			#include <stdlib.h>
			#endif
			#if HAVE_STRING_H
			#include <string.h>
			#else
			#include <strings.h>
			#endif
			#endif

			/* WORDSIZE is the number of set elements per setword (16, 32 or 64).
			   Starting at version 2.2, WORDSIZE and setword are defined as follows:
			   If WORDSIZE is so far undefined, use 32 unless longs have more 
			      than 32 bits, in which case use 64.
			   Define setword thus:
			      WORDSIZE==16 : unsigned short
			      WORDSIZE==32 : unsigned int unless it is too small,
						in which case unsigned long
			      WORDSIZE==64 : the first of unsigned int, unsigned long,
			                      unsigned long long, which is large enough.
			*/

			#ifdef NAUTY_IN_MAGMA
			#undef WORDSIZE
			#define WORDSIZE WORDBITS
			#endif

			#ifdef WORDSIZE

			#if  (WORDSIZE != 16) && (WORDSIZE != 32) && (WORDSIZE != 64)
			 #error "WORDSIZE must be 16, 32 or 64"
			#endif

			#else  /* WORDSIZE undefined */

			#if SIZEOF_LONG>4
			#define WORDSIZE 64
			#else
			#define WORDSIZE 32
			#endif

			#endif  /* WORDSIZE */

			#ifdef NAUTY_IN_MAGMA
			typedef t_uint setword;
			#define SETWORD_INT  /* Don't assume this is correct in Magma. */

			#else /* NAUTY_IN_MAGMA */

			#if WORDSIZE==16
			typedef unsigned short setword;
			#define SETWORD_SHORT
			#endif

			#if WORDSIZE==32
			#if SIZEOF_INT>=4
			typedef unsigned int setword;
			#define SETWORD_INT
			#else
			typedef unsigned long setword;
			#define SETWORD_LONG
			#endif
			#endif

			#if WORDSIZE==64
			#if SIZEOF_INT>=8
			typedef unsigned int setword;
			#define SETWORD_INT
			#else
			#if SIZEOF_LONG>=8
			typedef unsigned long setword;
			#define SETWORD_LONG
			#else
			typedef unsigned long long setword;
			#define SETWORD_LONGLONG
			#endif
			#endif
			#endif

			#endif /* NAUTY_IN_MAGMA else */

			#if SIZEOF_LONG_LONG>=8 && SIZEOF_LONG==4
			typedef unsigned long long nauty_counter;
			#define LONG_LONG_COUNTERS 1
			#else
			typedef unsigned long nauty_counter;
			#define LONG_LONG_COUNTERS 0
			#endif

			#if WORDSIZE==16
			#define NAUTYVERSION "2.4 (16 bits)"
			#endif
			#if WORDSIZE==32
			#define NAUTYVERSION "2.4 (32 bits)"
			#endif
			#if WORDSIZE==64
			#define NAUTYVERSION "2.4 (64 bits)"
			#endif

			#ifndef  MAXN  /* maximum allowed n value; use 0 for dynamic sizing. */
			#define MAXN 0
			#define MAXM 0
			#else
			#define MAXM ((MAXN+WORDSIZE-1)/WORDSIZE)  /* max setwords in a set */
			#endif  /* MAXN */

			/* Starting at version 2.2, set operations work for all set sizes unless
			   ONE_WORD_SETS is defined.  In the latter case, if MAXM=1, set ops
			   work only for single-setword sets.  In any case, macro versions
			   ending with 1 work for single-setword sets and versions ending with
			   0 work for all set sizes.
			*/

			#if  WORDSIZE==16
			#define SETWD(pos) ((pos)>>4)  /* number of setword containing bit pos */
			#define SETBT(pos) ((pos)&0xF) /* position within setword of bit pos */
			#define TIMESWORDSIZE(w) ((w)<<4)
			#endif

			#if  WORDSIZE==32
			#define SETWD(pos) ((pos)>>5)
			#define SETBT(pos) ((pos)&0x1F)
			#define TIMESWORDSIZE(w) ((w)<<5)
			#endif

			#if  WORDSIZE==64
			#define SETWD(pos) ((pos)>>6)
			#define SETBT(pos) ((pos)&0x3F)
			#define TIMESWORDSIZE(w) ((w)<<6)    /* w*WORDSIZE */
			#endif

			#ifdef NAUTY_IN_MAGMA
			#define BITT bs_bit
			#else
			#define BITT bit
			#endif

			#define ADDELEMENT1(setadd,pos)  (*(setadd) |= BITT[pos])
			#define DELELEMENT1(setadd,pos)  (*(setadd) &= ~BITT[pos])
			#define FLIPELEMENT1(setadd,pos) (*(setadd) ^= BITT[pos])
			#define ISELEMENT1(setadd,pos)   ((*(setadd) & BITT[pos]) != 0)
			#define EMPTYSET1(setadd,m)   *(setadd) = 0;
			#define GRAPHROW1(g,v,m) ((set*)(g) + (v))

			#define ADDELEMENT0(setadd,pos)  ((setadd)[SETWD(pos)] |= BITT[SETBT(pos)])
			#define DELELEMENT0(setadd,pos)  ((setadd)[SETWD(pos)] &= ~BITT[SETBT(pos)])
			#define FLIPELEMENT0(setadd,pos) ((setadd)[SETWD(pos)] ^= BITT[SETBT(pos)])
			#define ISELEMENT0(setadd,pos) (((setadd)[SETWD(pos)] & BITT[SETBT(pos)]) != 0)
			#define EMPTYSET0(setadd,m) \
			    {setword *es; \
			    for (es = (setword*)(setadd)+(m); --es >= (setword*)(setadd);) *es=0;}
			#define GRAPHROW0(g,v,m) ((set*)(g) + (long)(v)*(long)(m))

			#if  (MAXM==1) && defined(ONE_WORD_SETS)
			#define ADDELEMENT ADDELEMENT1
			#define DELELEMENT DELELEMENT1
			#define FLIPELEMENT FLIPELEMENT1
			#define ISELEMENT ISELEMENT1
			#define EMPTYSET EMPTYSET1
			#define GRAPHROW GRAPHROW1
			#else
			#define ADDELEMENT ADDELEMENT0
			#define DELELEMENT DELELEMENT0
			#define FLIPELEMENT FLIPELEMENT0
			#define ISELEMENT ISELEMENT0
			#define EMPTYSET EMPTYSET0
			#define GRAPHROW GRAPHROW0
			#endif

			#ifdef NAUTY_IN_MAGMA
			#undef EMPTYSET
			#define EMPTYSET(setadd,m) {t_int _i; bsp_makeempty(setadd,m,_i);}
			#endif

			#define NOTSUBSET(word1,word2) ((word1) & ~(word2))  /* test if the 1-bits
			                    in setword word1 do not form a subset of those in word2  */
			#define INTERSECT(word1,word2) ((word1) &= (word2))  /* AND word2 into word1 */
			#define UNION(word1,word2)     ((word1) |= (word2))  /* OR word2 into word1 */
			#define SETDIFF(word1,word2)   ((word1) &= ~(word2)) /* - word2 into word1 */
			#define XOR(word1,word2)       ((word1) ^= (word2))  /* XOR word2 into word1 */
			#define ZAPBIT(word,x) ((word) &= ~BITT[x])  /* delete bit x in setword */
			#define TAKEBIT(iw,w) {iw = FIRSTBIT(w); w ^= BITT[iw];}

			#ifdef SETWORD_LONGLONG
			#define MSK3232 0xFFFFFFFF00000000ULL
			#define MSK1648 0xFFFF000000000000ULL
			#define MSK0856 0xFF00000000000000ULL
			#define MSK1632 0x0000FFFF00000000ULL
			#define MSK0840     0xFF0000000000ULL
			#define MSK1616         0xFFFF0000ULL 
			#define MSK0824         0xFF000000ULL 
			#define MSK0808             0xFF00ULL 
			#define MSK63C  0x7FFFFFFFFFFFFFFFULL
			#define MSK31C          0x7FFFFFFFULL
			#define MSK15C              0x7FFFULL
			#define MSK64   0xFFFFFFFFFFFFFFFFULL
			#define MSK32           0xFFFFFFFFULL
			#define MSK16               0xFFFFULL
			#endif

			#ifdef SETWORD_LONG
			#define MSK3232 0xFFFFFFFF00000000UL
			#define MSK1648 0xFFFF000000000000UL
			#define MSK0856 0xFF00000000000000UL
			#define MSK1632 0x0000FFFF00000000UL
			#define MSK0840     0xFF0000000000UL
			#define MSK1616         0xFFFF0000UL 
			#define MSK0824         0xFF000000UL 
			#define MSK0808             0xFF00UL 
			#define MSK63C  0x7FFFFFFFFFFFFFFFUL
			#define MSK31C          0x7FFFFFFFUL
			#define MSK15C              0x7FFFUL
			#define MSK64   0xFFFFFFFFFFFFFFFFUL
			#define MSK32           0xFFFFFFFFUL
			#define MSK16               0xFFFFUL
			#endif

			#if defined(SETWORD_INT) || defined(SETWORD_SHORT)
			#define MSK3232 0xFFFFFFFF00000000U
			#define MSK1648 0xFFFF000000000000U
			#define MSK0856 0xFF00000000000000U
			#define MSK1632 0x0000FFFF00000000U
			#define MSK0840     0xFF0000000000U
			#define MSK1616         0xFFFF0000U 
			#define MSK0824         0xFF000000U
			#define MSK0808             0xFF00U 
			#define MSK63C  0x7FFFFFFFFFFFFFFFU
			#define MSK31C          0x7FFFFFFFU
			#define MSK15C              0x7FFFU
			#define MSK64   0xFFFFFFFFFFFFFFFFU
			#define MSK32           0xFFFFFFFFU
			#define MSK16               0xFFFFU
			#endif

			#if defined(SETWORD_LONGLONG)
			#if WORDSIZE==16
			#define SETWORD_FORMAT "%04llx"
			#endif
			#if WORDSIZE==32
			#define SETWORD_FORMAT "%08llx"
			#endif
			#if WORDSIZE==64
			#define SETWORD_FORMAT "%16llx"
			#endif
			#endif

			#if defined(SETWORD_LONG)
			#if WORDSIZE==16
			#define SETWORD_FORMAT "%04lx"
			#endif
			#if WORDSIZE==32
			#define SETWORD_FORMAT "%08lx"
			#endif
			#if WORDSIZE==64
			#define SETWORD_FORMAT "%16lx"
			#endif
			#endif

			#if defined(SETWORD_INT)
			#if WORDSIZE==16
			#define SETWORD_FORMAT "%04x"
			#endif
			#if WORDSIZE==32
			#define SETWORD_FORMAT "%08x"
			#endif
			#if WORDSIZE==64
			#define SETWORD_FORMAT "%16x"
			#endif
			#endif

			#if defined(SETWORD_SHORT)
			#if WORDSIZE==16
			#define SETWORD_FORMAT "%04hx"
			#endif
			#if WORDSIZE==32
			#define SETWORD_FORMAT "%08hx"
			#endif
			#if WORDSIZE==64
			#define SETWORD_FORMAT "%16hx"
			#endif
			#endif

			/* POPCOUNT(x) = number of 1-bits in a setword x
			   FIRSTBIT(x) = number of first 1-bit in non-zero setword (0..WORDSIZE-1)
			   BITMASK(x)  = setword whose rightmost WORDSIZE-x-1 (numbered) bits
			                 are 1 and the rest 0 (0 <= x < WORDSIZE)
			                 (I.e., bits 0..x are unselected and the rest selected.)
			   ALLBITS     = all (numbered) bits in a setword  */

			#if  WORDSIZE==64
			#define POPCOUNT(x) (bytecount[(x)>>56 & 0xFF] + bytecount[(x)>>48 & 0xFF] \
			                   + bytecount[(x)>>40 & 0xFF] + bytecount[(x)>>32 & 0xFF] \
			                   + bytecount[(x)>>24 & 0xFF] + bytecount[(x)>>16 & 0xFF] \
			                   + bytecount[(x)>>8 & 0xFF]  + bytecount[(x) & 0xFF])
			#define FIRSTBIT(x) ((x) & MSK3232 ? \
			                       (x) &   MSK1648 ? \
			                         (x) & MSK0856 ? \
			                         0+leftbit[((x)>>56) & 0xFF] : \
			                         8+leftbit[(x)>>48] \
			                       : (x) & MSK0840 ? \
			                         16+leftbit[(x)>>40] : \
			                         24+leftbit[(x)>>32] \
			                     : (x) & MSK1616 ? \
			                         (x) & MSK0824 ? \
			                         32+leftbit[(x)>>24] : \
			                         40+leftbit[(x)>>16] \
			                       : (x) & MSK0808 ? \
			                         48+leftbit[(x)>>8] : \
			                         56+leftbit[x])
			#define BITMASK(x)  (MSK63C >> (x))
			#define ALLBITS  MSK64
			#define SWCHUNK0(w) ((long)((w)>>48)&0xFFFFL)
			#define SWCHUNK1(w) ((long)((w)>>32)&0xFFFFL)
			#define SWCHUNK2(w) ((long)((w)>>16)&0xFFFFL)
			#define SWCHUNK3(w) ((long)(w)&0xFFFFL)
			#endif

			#if  WORDSIZE==32
			#define POPCOUNT(x) (bytecount[(x)>>24 & 0xFF] + bytecount[(x)>>16 & 0xFF] \
			                        + bytecount[(x)>>8 & 0xFF] + bytecount[(x) & 0xFF])
			#define FIRSTBIT(x) ((x) & MSK1616 ? ((x) & MSK0824 ? \
			                     leftbit[((x)>>24) & 0xFF] : 8+leftbit[(x)>>16]) \
			                    : ((x) & MSK0808 ? 16+leftbit[(x)>>8] : 24+leftbit[x]))
			#define BITMASK(x)  (MSK31C >> (x))
			#define ALLBITS  MSK32
			#define SWCHUNK0(w) ((long)((w)>>16)&0xFFFFL)
			#define SWCHUNK1(w) ((long)(w)&0xFFFFL)
			#endif

			#if  WORDSIZE==16
			#define POPCOUNT(x) (bytecount[(x)>>8 & 0xFF] + bytecount[(x) & 0xFF])
			#define FIRSTBIT(x) ((x) & MSK0808 ? leftbit[((x)>>8) & 0xFF] : 8+leftbit[x])
			#define BITMASK(x)  (MSK15C >> (x))
			#define ALLBITS  MSK16
			#define SWCHUNK0(w) ((long)(w)&0xFFFFL)
			#endif

			#ifdef  SYS_CRAY
			#undef POPCOUNT
			#undef FIRSTBIT
			#undef BITMASK
			#define POPCOUNT(x) _popcnt(x)
			#define FIRSTBIT(x) _leadz(x)
			#define BITMASK(x)  _mask(65+(x))
			#endif

			#ifdef NAUTY_IN_MAGMA
			#undef POPCOUNT
			#undef FIRSTBIT
			#undef BITMASK
			#define POPCOUNT(x) bs_popcount(x)
			#define FIRSTBIT(x) bs_firstbit(x)
			#define BITMASK(x)  bs_bitmask(x)
			#endif

			#define ALLMASK(n) ((n)?~BITMASK((n)-1):(setword)0)  /* First n bits */

			    /* various constants: */
			#undef FALSE
			#undef TRUE
			#define FALSE    0
			#define TRUE     1

			#if SIZEOF_INT>=4
			#define NAUTY_INFINITY 0x40000002
			#else
			#define NAUTY_INFINITY 0x7FFF
			#endif

			typedef int shortish;

			/* For backward compatibility: */
			#if !HAS_MATH_INF && !defined(INFINITY)
			#define INFINITY NAUTY_INFINITY
			#endif

			#if MAXN > NAUTY_INFINITY-2
			 #error MAXN must be at most NAUTY_INFINITY-2
			#endif

			    /* typedefs for sets, graphs, permutations, etc.: */

			typedef int boolean;    /* boolean MUST be the same as int */

			#define UPROC void      /* obsolete */

			typedef setword set,graph;
			typedef int nvector,np2vector;   /* obsolete */
			typedef shortish permutation;
			#ifdef NAUTY_IN_MAGMA
			typedef graph nauty_graph;
			typedef set nauty_set;
			#endif

			typedef struct
			{
			    double grpsize1;        /* size of group is */
			    int grpsize2;           /*    grpsize1 * 10^grpsize2 */
			#define groupsize1 grpsize1     /* for backwards compatibility */
			#define groupsize2 grpsize2
			    int numorbits;          /* number of orbits in group */
			    int numgenerators;      /* number of generators found */
			    int errstatus;          /* if non-zero : an error code */
			#define outofspace errstatus;   /* for backwards compatibility */
			    unsigned long numnodes;      /* total number of nodes */
			    unsigned long numbadleaves;  /* number of leaves of no use */
			    int maxlevel;                /* maximum depth of search */
			    unsigned long tctotal;       /* total size of all target cells */
			    unsigned long canupdates;    /* number of updates of best label */
			    unsigned long invapplics;    /* number of applications of invarproc */
			    unsigned long invsuccesses;  /* number of successful uses of invarproc() */
			    int invarsuclevel;      /* least level where invarproc worked */
			} statsblk;

			/* codes for errstatus field (see nauty.c for more accurate descriptions): */
			#define NTOOBIG      1      /* n > MAXN or n > WORDSIZE*m */
			#define MTOOBIG      2      /* m > MAXM */
			#define CANONGNIL    3      /* canong = NULL, but getcanon = TRUE */

			/* manipulation of real approximation to group size */
			#define MULTIPLY(s1,s2,i) if ((s1 *= i) >= 1e10) {s1 /= 1e10; s2 += 10;}

			struct optionstruct;  /* incomplete definition */

			typedef struct
			{
			    boolean (*isautom)        /* test for automorphism */
			            (graph*,permutation*,boolean,int,int);
			    int     (*testcanlab)     /* test for better labelling */
			            (graph*,graph*,int*,int*,int,int);
			    void    (*updatecan)      /* update canonical object */
			            (graph*,graph*,permutation*,int,int,int);
			    void    (*refine)         /* refine partition */
			            (graph*,int*,int*,int,int*,permutation*,set*,int*,int,int);
			    void    (*refine1)        /* refine partition, MAXM==1 */
			            (graph*,int*,int*,int,int*,permutation*,set*,int*,int,int);
			    boolean (*cheapautom)     /* test for easy automorphism */
			            (int*,int,boolean,int);
			    int     (*targetcell)     /* decide which cell to split */
			            (graph*,int*,int*,int,int,boolean,int,int,int);
			    void    (*freedyn)(void); /* free dynamic memory */
			    void    (*check)          /* check compilation parameters */
			            (int,int,int,int);
			    void    (*init)(graph*,graph**,graph*,graph**,int*,int*,set*,
			                   struct optionstruct*,int*,int,int);
			    void    (*cleanup)(graph*,graph**,graph*,graph**,int*,int*,
			                      struct optionstruct*,statsblk*,int,int);
			} dispatchvec;

			typedef struct optionstruct
			{
			    int getcanon;             /* make canong and canonlab? */
			#define LABELONLY 2   /* new value UNIMPLEMENTED */
			    boolean digraph;          /* multiple edges or loops? */
			    boolean writeautoms;      /* write automorphisms? */
			    boolean writemarkers;     /* write stats on pts fixed, etc.? */
			    boolean defaultptn;       /* set lab,ptn,active for single cell? */
			    boolean cartesian;        /* use cartesian rep for writing automs? */
			    int linelength;           /* max chars/line (excl. '\n') for output */
			    FILE *outfile;            /* file for output, if any */
			    void (*userrefproc)       /* replacement for usual refine procedure */
			         (graph*,int*,int*,int,int*,permutation*,set*,int*,int,int);
			    void (*userautomproc)     /* procedure called for each automorphism */
			         (int,permutation*,int*,int,int,int);
			    void (*userlevelproc)     /* procedure called for each level */
			         (int*,int*,int,int*,statsblk*,int,int,int,int,int,int);
			    void (*usernodeproc)      /* procedure called for each node */
			         (graph*,int*,int*,int,int,int,int,int,int);
			    void (*invarproc)         /* procedure to compute vertex-invariant */
			         (graph*,int*,int*,int,int,int,permutation*,int,boolean,int,int);
			    int tc_level;             /* max level for smart target cell choosing */
			    int mininvarlevel;        /* min level for invariant computation */
			    int maxinvarlevel;        /* max level for invariant computation */
			    int invararg;             /* value passed to (*invarproc)() */
			    dispatchvec *dispatch;    /* vector of object-specific routines */
			    void *extra_options;      /* arbitrary extra options */
			#ifdef NAUTY_IN_MAGMA
			    boolean print_stats;      /* CAYLEY specfic - GYM Sep 1990 */
			    char *invarprocname;      /* Magma - no longer global sjc 1994 */
			    int lab_h;                /* Magma - no longer global sjc 1994 */
			    int ptn_h;                /* Magma - no longer global sjc 1994 */
			    int orbitset_h;           /* Magma - no longer global sjc 1994 */
			#endif
			} optionblk;

			#ifndef CONSOLWIDTH
			#define CONSOLWIDTH 78
			#endif

			/* The following are obsolete.  Just use NULL. */
			#define NILFUNCTION ((void(*)())NULL)      /* nil pointer to user-function */
			#define NILSET      ((set*)NULL)           /* nil pointer to set */
			#define NILGRAPH    ((graph*)NULL)         /* nil pointer to graph */

			#define DEFAULTOPTIONS_GRAPH(options) optionblk options = \
			 {0,FALSE,FALSE,FALSE,TRUE,FALSE,CONSOLWIDTH, \
			  NULL,NULL,NULL,NULL,NULL,NULL,100,0,1,0,&dispatch_graph,NULL}

			#ifndef DEFAULTOPTIONS
			#define DEFAULTOPTIONS DEFAULTOPTIONS_GRAPH
			#endif

			#ifdef NAUTY_IN_MAGMA
			#define PUTC(c,f) io_putchar(c)
			#else
			#ifdef IS_JAVA
			extern void javastream(FILE* f,char c);
			#define PUTC(c,f) javastream(f,c)
			#else
			#define PUTC(c,f) putc(c,f)
			#endif
			#endif

			/* We hope that malloc, free, realloc are declared either in <stdlib.h>
			   or <malloc.h>.  Otherwise we will define them.  We also assume that
			   size_t has been defined by the time we get to define malloc(). */
			#ifndef NAUTY_IN_MAGMA
			#if MALLOC_DEC==2
			#include <malloc.h>
			#endif
			#if MALLOC_DEC==0
			extern void *malloc(size_t);
			extern void *realloc(void*,size_t);
			extern void free(void*);
			#endif
			#endif

			/* ALLOCS(x,y) should return a pointer (any pointer type) to x*y units of new
			   storage, not necessarily initialised.  A "unit" of storage is defined by
			   the sizeof operator.   x and y are integer values of type int or larger, 
			   but x*y may well be too large for an int.  The macro should cast to the
			   correct type for the call.  On failure, ALLOCS(x,y) should return a NULL 
			   pointer.  FREES(p) should free storage previously allocated by ALLOCS, 
			   where p is the value that ALLOCS returned. */

			#ifdef NAUTY_IN_MAGMA
			#define ALLOCS(x,y) mem_malloc((size_t)(x)*(size_t)(y))
			#define REALLOCS(p,x) mem_realloc(p,(size_t)(x))
			#define FREES(p) mem_free(p)
			#else
			#define ALLOCS(x,y) malloc((size_t)(x)*(size_t)(y))
			#define REALLOCS(p,x) realloc(p,(size_t)(x)) 
			#define FREES(p) free(p)
			#endif

			/* The following macros are used by nauty if MAXN=0.  They dynamically
			   allocate arrays of size dependent on m or n.  For each array there
			   should be two static variables:
			     type *name;
			     size_t name_sz;
			   "name" will hold a pointer to an allocated array.  "name_sz" will hold
			   the size of the allocated array in units of sizeof(type).  DYNALLSTAT
			   declares both variables and initialises name_sz=0.  DYNALLOC1 and
			   DYNALLOC2 test if there is enough space allocated, and if not free
			   the existing space and allocate a bigger space.  The allocated space
			   is not initialised.
			   
			   In the case of DYNALLOC1, the space is allocated using
			       ALLOCS(sz,sizeof(type)).
			   In the case of DYNALLOC2, the space is allocated using
			       ALLOCS(sz1,sz2*sizeof(type)).

			   DYNREALLOC is like DYNALLOC1 except that the old contents are copied
			   into the new space.  realloc() is assumed.  This is not currently
			   used by nauty or dreadnaut.

			   DYNFREE frees any allocated array and sets name_sz back to 0.
			   CONDYNFREE does the same, but only if name_sz exceeds some limit.
			*/

			#define DYNALLSTAT(type,name,name_sz) \
				static type *name; static size_t name_sz=0
			#define DYNALLOC1(type,name,name_sz,sz,msg) \
			 if ((size_t)(sz) > name_sz) \
			 { if (name_sz) FREES(name); name_sz = (sz); \
			 if ((name=(type*)ALLOCS(sz,sizeof(type))) == NULL) {alloc_error(msg);}}
			#define DYNALLOC2(type,name,name_sz,sz1,sz2,msg) \
			 if ((size_t)(sz1)*(size_t)(sz2) > name_sz) \
			 { if (name_sz) FREES(name); name_sz = (size_t)(sz1)*(size_t)(sz2); \
			 if ((name=(type*)ALLOCS((sz1),(sz2)*sizeof(type))) == NULL) \
			 {alloc_error(msg);}}
			#define DYNREALLOC(type,name,name_sz,sz,msg) \
			 {if ((size_t)(sz) > name_sz) \
			 { if ((name = (type*)REALLOCS(name,(sz)*sizeof(type))) == NULL) \
			      {alloc_error(msg);} else name_sz = (sz);}}
			#define DYNFREE(name,name_sz) if (name_sz) {FREES(name); name_sz = 0;}
			#define CONDYNFREE(name,name_sz,minsz) \
			 if (name_sz > (size_t)(minsz)) {FREES(name); name_sz = 0;}

			/* File to write error messages to (used as first argument to fprintf()). */
			#define ERRFILE stderr

			/* Don't use OLDEXTDEFS, it is only still here for Magma. */
			#ifdef OLDEXTDEFS   
			#define EXTDEF_CLASS
			#ifdef EXTDEFS
			#define EXTDEF_TYPE 1
			#else
			#define EXTDEF_TYPE 2
			#endif
			#else
			#define EXTDEF_CLASS static
			#define EXTDEF_TYPE 2
			#endif

			extern int labelorg;   /* Declared in nautil.c */

			#ifndef NAUTY_IN_MAGMA
			  /* Things equivalent to bit, bytecount, leftbit are defined
			     in bs.h for Magma. */
			#if  EXTDEF_TYPE==1
			extern setword bit[];
			extern int bytecount[];
			extern int leftbit[];

			#else
			    /* array giving setwords with single 1-bit */
			#if  WORDSIZE==64
			#ifdef SETWORD_LONGLONG
			EXTDEF_CLASS
			setword bit[] = {01000000000000000000000LL,0400000000000000000000LL,
			                 0200000000000000000000LL,0100000000000000000000LL,
			                 040000000000000000000LL,020000000000000000000LL,
			                 010000000000000000000LL,04000000000000000000LL,
			                 02000000000000000000LL,01000000000000000000LL,
			                 0400000000000000000LL,0200000000000000000LL,
			                 0100000000000000000LL,040000000000000000LL,
			                 020000000000000000LL,010000000000000000LL,
			                 04000000000000000LL,02000000000000000LL,
			                 01000000000000000LL,0400000000000000LL,0200000000000000LL,
			                 0100000000000000LL,040000000000000LL,020000000000000LL,
			                 010000000000000LL,04000000000000LL,02000000000000LL,
			                 01000000000000LL,0400000000000LL,0200000000000LL,
					 0100000000000LL,040000000000LL,020000000000LL,010000000000LL,
					 04000000000LL,02000000000LL,01000000000LL,0400000000LL,
					 0200000000LL,0100000000LL,040000000LL,020000000LL,
					 010000000LL,04000000LL,02000000LL,01000000LL,0400000LL,
					 0200000LL,0100000LL,040000LL,020000LL,010000LL,04000LL,
			                 02000LL,01000LL,0400LL,0200LL,0100LL,040LL,020LL,010LL,
					 04LL,02LL,01LL};
			#else
			EXTDEF_CLASS
			setword bit[] = {01000000000000000000000,0400000000000000000000,
			                 0200000000000000000000,0100000000000000000000,
			                 040000000000000000000,020000000000000000000,
			                 010000000000000000000,04000000000000000000,
			                 02000000000000000000,01000000000000000000,
			                 0400000000000000000,0200000000000000000,
			                 0100000000000000000,040000000000000000,020000000000000000,
			                 010000000000000000,04000000000000000,02000000000000000,
			                 01000000000000000,0400000000000000,0200000000000000,
			                 0100000000000000,040000000000000,020000000000000,
			                 010000000000000,04000000000000,02000000000000,
			                 01000000000000,0400000000000,0200000000000,0100000000000,
			                 040000000000,020000000000,010000000000,04000000000,
			                 02000000000,01000000000,0400000000,0200000000,0100000000,
			                 040000000,020000000,010000000,04000000,02000000,01000000,
			                 0400000,0200000,0100000,040000,020000,010000,04000,
			                 02000,01000,0400,0200,0100,040,020,010,04,02,01};
			#endif
			#endif

			#if  WORDSIZE==32
			EXTDEF_CLASS
			setword bit[] = {020000000000,010000000000,04000000000,02000000000,
			                 01000000000,0400000000,0200000000,0100000000,040000000,
			                 020000000,010000000,04000000,02000000,01000000,0400000,
			                 0200000,0100000,040000,020000,010000,04000,02000,01000,
			                 0400,0200,0100,040,020,010,04,02,01};
			#endif

			#if WORDSIZE==16
			EXTDEF_CLASS
			setword bit[] = {0100000,040000,020000,010000,04000,02000,01000,0400,0200,
			                 0100,040,020,010,04,02,01};
			#endif

			    /*  array giving number of 1-bits in bytes valued 0..255: */
			EXTDEF_CLASS
			int bytecount[] = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,
			                   1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
			                   1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
			                   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
			                   1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
			                   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
			                   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
			                   3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
			                   1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
			                   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
			                   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
			                   3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
			                   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
			                   3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
			                   3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
			                   4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8};

			    /* array giving position (1..7) of high-order 1-bit in byte: */
			EXTDEF_CLASS
			int leftbit[] =   {8,7,6,6,5,5,5,5,4,4,4,4,4,4,4,4,
			                   3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
			                   2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
			                   2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
			                   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
			                   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
			                   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
			                   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
			                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
			#endif  /* EXTDEFS */

			#endif /* not NAUTY_IN_MAGMA */

			#define ANSIPROT 1
			#define EXTPROC(func,args) extern func args;     /* obsolete */

			/* The following is for C++ programs that read nauty.h.  Compile nauty
			   itself using C, not C++.  */

			#ifdef __cplusplus
			extern "C" {
			#endif

			extern void alloc_error(char*);
			extern void breakout(int*,int*,int,int,int,set*,int);
			extern boolean cheapautom(int*,int,boolean,int);
			extern void doref(graph*,int*,int*,int,int*,int*,permutation*,set*,int*,
			  void(*)(graph*,int*,int*,int,int*,permutation*,set*,int*,int,int),
			  void(*)(graph*,int*,int*,int,int,int,permutation*,int,boolean,int,int),
			  int,int,int,boolean,int,int);
			extern void extra_autom(permutation*,int);
			extern void extra_level(int,int*,int*,int,int,int,int,int,int);
			extern boolean isautom(graph*,permutation*,boolean,int,int);
			extern dispatchvec dispatch_graph;
			extern int itos(int,char*);
			extern void fmperm(permutation*,set*,set*,int,int);
			extern void fmptn(int*,int*,int,set*,set*,int,int);
			extern void longprune(set*,set*,set*,set*,int);
			extern void nauty(graph*,int*,int*,set*,int*,optionblk*,
			                  statsblk*,set*,int,int,int,graph*);
			extern void maketargetcell(graph*,int*,int*,int,set*,int*,int*,int,boolean,
			           int,int (*)(graph*,int*,int*,int,int,boolean,int,int,int),int,int);
			extern int nextelement(set*,int,int);
			extern int orbjoin(int*,permutation*,int);
			extern void permset(set*,set*,int,permutation*);
			extern void putstring(FILE*,char*);
			extern void refine(graph*,int*,int*,int,int*,permutation*,set*,int*,int,int);
			extern void refine1(graph*,int*,int*,int,int*,permutation*,set*,int*,int,int);
			extern void shortprune(set*,set*,int);
			extern int targetcell(graph*,int*,int*,int,int,boolean,int,int,int);
			extern int testcanlab(graph*,graph*,int*,int*,int,int);
			extern void updatecan(graph*,graph*,permutation*,int,int,int);
			extern void writeperm(FILE*,permutation*,boolean,int,int);
			extern void nauty_freedyn(void);
			extern void nauty_check(int,int,int,int);
			extern void naugraph_check(int,int,int,int);
			extern void nautil_check(int,int,int,int);
			extern void nautil_freedyn(void);
			extern void naugraph_freedyn(void);

			#ifdef __cplusplus
			}
			#endif

			#endif  /* _NAUTY_H_ */

		class Isomorphism {
			private:  
				static bool dir;
				static setword workspace[WORKSPACE_SIZE];
				static int n,m,lab[MAXN], ptn[MAXN], orbits[MAXN];
				static set *gv;
				static graph g[MAXN*MAXM];

				static void _goCan(int x, int pos, const char *in, 
					     char *perm, char *used,
					     char *current, char *best, int size);

				static void _goCan2(int pos, const char *in, int *perm, bool *used, char *best, int size, char *current);

			public:
				static void initNauty(int size, bool dir);
				static void finishNauty();

				static void canonicalStrNauty(Graph *g, int *v, char *s);

				static void canonicalNauty(const char *in, char *out, int size);
				static void canonicalBigger(const char *in, char *out, int size);
				static void canonicalBigger2(const char *in, char *out, int size);
				static void canonicalBasedNauty(const char *in, char *out, int size); // GT Canon
				static void canonicalBasedNautyReverse(const char *in, char *out, int size);
				static void canonicalRandom(const char *in, char *out, int size);
		


		};

		#endif		
	//#include "Timer.h"

		/*Timer.h*/
		#ifndef _TIMER_
		#define _TIMER_

		#define MAX_TIMERS 1000 // Maximum number of timers

		//#include "Common.h"//Already included

		#include <sys/time.h>

		class Timer {
			private:
				static struct timeval cstart[MAX_TIMERS]; // Start times
				static struct timeval   cend[MAX_TIMERS]; // End times

			public:
				static void     start(int n);             // Start the clock of a timer
				static void      stop(int n);             // Stop the clock of a timer
				static double elapsed(int n);             // Elapsed time of a timer
		};

		#endif
	//#include "Random.h"

		/*Random.h*/
		#ifndef _RANDOM_
		#define _RANDOM_

		//#include "Common.h"//ALREADY INCLUDED
		//#include "Graph.h" //ALREADY INCLUDED

		class Random {

			public:
				static void seed(int s);             // Initialize pseudo-random generator with seed 's'
				static int getInteger(int a, int b); // Pseudo-Random number between 'a' and 'b' (inclusive)
				static double getDouble();           // Pseudo-Random number between 0 and 1

				// Randomize 'g' network with 'num' exchanges per edge and 'tries' attempts per edge
				static void markovChainPerEdge(Graph *g, int num, int tries);
			};

		#endif

	class CmdLine {
		private:
			static char graph_file[MAX_BUF];
			static char gtrie_file[MAX_BUF];
			static char subgraphs_file[MAX_BUF];
			static char output_file[MAX_BUF];
			static char occ_file[MAX_BUF];

			static bool dir;
			static bool occurrences;
			static bool create;

			static int motif_size;
			static int random_number;
			static int random_seed;
			static int random_exchanges;
			static int random_tries;

			static double time_original;
			static double time_random;

			static MethodType method;
			static FormatType format;
			static OutputType output;
			static Graph *g;

			static FILE *f_output;
			static FILE *f_occ;

			static GTrie *gt_original;
			static GTrie *gt;

			static GraphTree sg_original;

			static time_t t_start;

			static void about();
			static void defaults();
			static void parse_cmdargs(int argc, char **argv);
			static void run_esu(Graph *g, GraphTree *sg);
			static void run_gtrie(Graph *g, GraphTree *sg);
			static void run_subgraphs(Graph *g, GraphTree *sg);

			static MethodType str_to_method(char *s);
			static FormatType str_to_format(char *s);
			static OutputType str_to_output(char *s);

			static int compare_results(const void *a, const void *b);

			static void prepare_graph();
			static void prepare_files();
			static void compute_original();
			static void compute_results();
			static void show_results(ResultType *res, int nres);

			static void create_gtrie();

		public:
			static void init(int argc, char **argv);
			static void finish();
			static void decide_action();  
	};

	#endif
#include <algorithm>
#include <iostream>
#include <map>
#include <cmath>

// ----------------------------------------------

// Variable declarations

char CmdLine::graph_file[MAX_BUF];
char CmdLine::gtrie_file[MAX_BUF];
char CmdLine::subgraphs_file[MAX_BUF];
char CmdLine::output_file[MAX_BUF];
char CmdLine::occ_file[MAX_BUF];

bool CmdLine::dir;
bool CmdLine::occurrences;
bool CmdLine::create;

int  CmdLine::motif_size;
int  CmdLine::random_number;
int  CmdLine::random_seed;
int  CmdLine::random_exchanges;
int  CmdLine::random_tries;

double CmdLine::time_original;
double CmdLine::time_random;

MethodType CmdLine::method;
FormatType CmdLine::format;
OutputType CmdLine::output;
Graph *CmdLine::g;

FILE *CmdLine::f_output;
FILE *CmdLine::f_occ;

GTrie *CmdLine::gt;
GTrie *CmdLine::gt_original;

GraphTree CmdLine::sg_original;

time_t CmdLine::t_start;

// ----------------------------------------------

// Create a g-trie from a list of subgraphs
void CmdLine::create_gtrie() {

  // Check motif size
  if (motif_size<MIN_MOTIF_SIZE || motif_size>MAX_MOTIF_SIZE)
    Error::msg("Invalid subgraph size (%d <= SIZE <= %d)", MIN_MOTIF_SIZE, MAX_MOTIF_SIZE);

  // Create the g-trie
  printf("Creating G-Trie\n");
  gt_original = new GTrie();
  Timer::start(0);
  gt_original->readSubgraphs(motif_size, dir, subgraphs_file);
  Timer::stop(0);
  printf("Creation time: %.2f\n", Timer::elapsed(0));
  printf("Nr %d-subgraphs in g-trie: %d\n", motif_size, gt_original->countGraphs()); 
  printf("Compression rate = %.2f%%\n\n", gt_original->compressionRate()*100);

  // Write g-trie to file
  gt_original->writeToFile(output_file);
  printf("G-Trie written to file \"%s\"\n", output_file);

  delete gt_original;
}

// ----------------------------------------------

// Run ESU algorithm on graph 'g' and store results on GraphTree 'gt'
void CmdLine::run_esu(Graph *g, GraphTree *sg) {
  Esu::countSubgraphs(g, motif_size, sg);
}

// Run SUBGRAPHS method on graph 'g' and store results on GraphTree 'gt'
void CmdLine::run_subgraphs(Graph *g, GraphTree *sg) {
  printf("Creating G-Trie\n");
  gt_original = new GTrie();
  Timer::start(0);
  gt_original->readSubgraphs(motif_size, dir, subgraphs_file);
  Timer::stop(0);
  printf("Creation time: %.2f\n", Timer::elapsed(0));
  printf("Compression rate = %.2f%%\n\n", gt_original->compressionRate()*100);

  gt_original->census(g);
  gt_original->populateGraphTree(sg, motif_size);
}

// Run GTRIES method on graph 'g' and store results on GraphTree 'gt'
void CmdLine::run_gtrie(Graph *g, GraphTree *sg) {
  printf("Reading G-Trie\n");
  gt_original = new GTrie();
  Timer::start(0);
  gt_original->readFromFile(gtrie_file);
  Timer::stop(0);
  printf("Creation time: %.2f\n", Timer::elapsed(0));
  printf("Compression rate = %.2f%%\n\n", gt_original->compressionRate()*100);

  gt_original->census(g);
  gt_original->populateGraphTree(sg, motif_size);
}

// ----------------------------------------------

// Compare two different motif results (for sorting)
int CmdLine::compare_results(const void *a, const void *b) {
  ResultType *r1 = (ResultType *)a;
  ResultType *r2 = (ResultType *)b;

  if (r1->z_score > r2->z_score) return -1;
  if (r1->z_score < r2->z_score) return +1;
  if (r1->f_original > r2->f_original) return -1;
  if (r1->f_original < r2->f_original) return +1;
  return 0;
}

// ----------------------------------------------

// Prepare files
void CmdLine::prepare_files() {

  // Check output format
  if (output == NOOUTPUT)
    Error::msg("No valid output format specified");    

  if (!strcmp(output_file,  DEFAULT_RESULTS)) {
    if (output == TEXT) strcat(output_file, ".txt");
    else if (output == HTML) strcat(output_file, ".html");
  }

  f_output = fopen(output_file, "w");
  if (f_output==NULL)
    Error::msg("Unable to open output file \"%s\"", output_file);    

  if (occurrences) {
    f_occ = fopen(occ_file, "w");
    if (f_occ==NULL)
      Error::msg("Unable to open occurrences file \"%s\"", occ_file);
  }
}

// Prepare the original graph for computation
void CmdLine::prepare_graph() {

  // Check motif size
  if (motif_size<MIN_MOTIF_SIZE || motif_size>MAX_MOTIF_SIZE)
    Error::msg("Invalid subgraph size (%d <= SIZE <= %d)", MIN_MOTIF_SIZE, MAX_MOTIF_SIZE);

  // Check if graph file name was given
  if (!strcmp(graph_file, INVALID_FILE))
    Error::msg("No graph file specified");

  // Check graph format
  if (format == NOFORMAT)
    Error::msg("No valid graph format specified");

  // Read the graph file
  g = new GraphMatrix();

  // Use simple or simple_weight text format
  if (format == SIMPLE)
    GraphUtils::readFileTxt(g, graph_file, dir, false);
  else if  (format == SIMPLE_WEIGHT)
    GraphUtils::readFileTxt(g, graph_file, dir, true);
  else printf("??");

  // sort and create array of neighbours
  g->sortNeighbours();
  g->makeArrayNeighbours();

  // Print chosen parameters
  printf("Subgraph Size: %d\n", motif_size);
  printf("Graph File: %s\n", graph_file);
  printf("%s, %d Nodes, %d Edges\n", dir?"Directed":"Undirected",g->numNodes(), dir?g->numEdges():g->numEdges()/2);
}

// Count subgraphs on original network
void CmdLine::compute_original() {

  // Print method description
  if (method == ESU)
    printf("Method:     ESU on original network\n");
  else if (method == GTRIE)
    printf("Method:     GTRIE with file containing complete g-trie\n");
  else if (method == SUBGRAPHS)
    printf("Method:     GTRIE with subgraphs read from file\n");

  // Compute frequency
  Global::show_occ = occurrences;
  Global::occ_file = f_occ;
  puts("\nCounting subgraph frequency on 'ORIGINAL NETWORK'");
  Timer::start(0);
  if (method == ESU) run_esu(g, &sg_original);
  else if (method == SUBGRAPHS) run_subgraphs(g, &sg_original);
  else if (method == GTRIE) run_gtrie(g, &sg_original);
  Timer::stop(0);  
  printf("%d subgraphs, ",   sg_original.countGraphs());
  printf("%.0f occurrences\n", sg_original.countOccurrences());
  printf("Time elapsed: %.6fs\n\n", Timer::elapsed(0));
  Global::show_occ = false;

  time_original = Timer::elapsed(0);
}

// Compute random networks and output results
void CmdLine::compute_results() {
  int i, j;
  mapStringInt:: const_iterator ii, iiend;

  // Create map and init results
  mapStringInt m_original;  
  sg_original.populateMap(&m_original, motif_size);
  ResultType res[m_original.size()];
  for (ii=m_original.begin(), iiend=m_original.end(), i=0; ii!=iiend; ii++, i++) {
    res[i].s = strdup((ii->first).c_str());    
    res[i].f_original = ii->second;
    res[i].z_score = res[i].avg_random = res[i].dev_random = 0;
  }

  // Do we have random networks to compute?
  if (random_number > 0) {
    gt = new GTrie;
    sg_original.populateGTrieNauty(gt, motif_size, dir);
    
    mapStringInt m_count[random_number];

    // Generate all random networks
    printf("Computing random networks: ");
    time_random = 0;
    for (i=0; i<random_number; i++) {      

      // Create new random network from previous one
      g->makeVectorNeighbours();
      Random::markovChainPerEdge(g, random_exchanges, random_tries);
      g->sortNeighbours();
      g->makeArrayNeighbours();

      // Compute census
      Timer::start(0);
      gt->census(g);
      Timer::stop(0);
      time_random += Timer::elapsed(0);
      gt->populateMap(&m_count[i], motif_size);
      fputc('.', stdout);      
    }
    fputc('\n', stdout);
    time_random /= (double)random_number;
    printf("Avg time per random network: %.6fs\n\n", time_random);

    // Compute significance
    for (ii=m_original.begin(), iiend=m_original.end(), i=0; ii!=iiend; ii++, i++) {
      // Average frequency
      double avg = 0;
      for (j=0; j<random_number; j++)
	avg += m_count[j][ii->first];
      avg /= random_number;

      // Standard deviation
      double dev=0;
      for (j=0; j<random_number; j++)
	dev += double(m_count[j][ii->first]-avg)*double(m_count[j][ii->first]-avg)/double(random_number-1);
      dev = sqrt(dev);

      // zscore
      double zscore = (ii->second - avg)/dev;

      res[i].avg_random = avg;
      res[i].dev_random = dev;
      res[i].z_score    = zscore;
    }
  }

  // Sort results
  qsort(res, m_original.size(), sizeof(ResultType), compare_results);

  // print results
  show_results(res, m_original.size());
  printf("Results written to file \"%s\"\n", output_file);
  if (occurrences)
    printf("Occurences on original network written to file \"%s\"\n", occ_file);

  for (i=0; i<(int)m_original.size(); i++)
    free(res[i].s);
}

// ----------------------------------------------

// Print results
void CmdLine::show_results(ResultType *res, int nres) {
  int i, j, k;
  bool html = (output==HTML)?true:false;

  if (html) fprintf(f_output, "<html><head>\n"
		    "<title>%s results</title>\n"
		    "<style type=\"text/css\">"
		    "p,body,td,th,li  {font-size: 13px; font-family: arial, geneva, \"sans serif\";color: black; font-weight: normal;}\n"
		    "body, tr {background-color: #fbfbfb;}\n"
		    "hr {color: black;}\n"
		    "table {background-color: black;}\n"
		    "th {color:white;}\n"
		    "td {text-align: right;}\n"
		    ".odd  {background-color: #d1d1d1;}\n"
		    ".even {background-color: #f2f2f2;}\n"
		    ".hd   {background-color: #444444; color: white;}\n"
		    ".pre  {white-space: pre;}\n"
		    "</style>"
		    "</head>\n<body>",
		    PROGRAM_NAME);

  fprintf(f_output, "%s%s Results%s\n", html?"<h1>":"", PROGRAM_NAME, html?"</h1>":"");
  
  if (html) fprintf(f_output, "<hr>\n");
  else      fprintf(f_output, "%s\n", SEPARATOR);

  fprintf(f_output, "%sGeneral Information%s\n", html?"<h2>":"", html?"</h2>":"\n");

  time_t t_end = time(0);
  struct tm *tm_start = localtime(&t_start);
  fprintf(f_output, "%sStart of Computation:%s %02dh%02dm%02ds %02d/%02d/%02d\n",
	  html?"<li><b>":"",html?"</b>":"",
	  tm_start->tm_hour, tm_start->tm_min, tm_start->tm_sec,
	  tm_start->tm_mday, tm_start->tm_mon+1, 1900+tm_start->tm_year);
  struct tm *tm_end   = localtime(&t_end);
  fprintf(f_output, "%sEnd of Computation:%s %02dh%02dm%02ds %02d/%02d/%02d\n",
	  html?"<li><b>":"",html?"</b>":"",
	  tm_end->tm_hour, tm_end->tm_min, tm_end->tm_sec,
	  tm_end->tm_mday, tm_end->tm_mon+1, 1900+tm_end->tm_year);

  if (html) fprintf(f_output, "<br>&nbsp;\n");
  else      fprintf(f_output, "\n");

  fprintf(f_output, "%sSubgraph Size:%s %d\n", html?"<li><b>":"", html?"</b>":"", motif_size);
  fprintf(f_output, "%sGraph File:%s \"%s\"\n", html?"<li><b>":"", html?"</b>":"",graph_file);
  fprintf(f_output, "%sDirected:%s %s\n", html?"<li><b>":"", html?"</b>":"",dir?"YES":"NO");
  fprintf(f_output, "%sNr Nodes:%s %d\n", html?"<li><b>":"", html?"</b>":"",g->numNodes());
  fprintf(f_output, "%sNr Edges:%s %d\n", html?"<li><b>":"", html?"</b>":"",dir?g->numEdges():g->numEdges()/2);
  
  if (html) fprintf(f_output, "<br>&nbsp;\n");
  else      fprintf(f_output, "\n");

  fprintf(f_output, "%sMethod:%s ", html?"<li><b>":"", html?"</b>":"");
  if (method == ESU)
    fprintf(f_output, "ESU on original network\n");
  else if (method == GTRIE)
    fprintf(f_output, "GTRIE with file containing complete g-trie\n");
  else if (method == SUBGRAPHS)
    fprintf(f_output, "GTRIE with subgraphs read from file\n");

  fprintf(f_output, "%sDifferent Types of Subgraphs Found [Original Network]:%s %d\n", html?"<li><b>":"", html?"</b>":"", sg_original.countGraphs());
  fprintf(f_output, "%sSubgraph Occurrences Found [Original Network]:%s %.0f\n", html?"<li><b>":"", html?"</b>":"", sg_original.countOccurrences());
  fprintf(f_output, "%sTime for computing census on original network%s: %.6fs\n", html?"<li><b>":"", html?"</b>":"", time_original);
  fprintf(f_output, "%sAverage time for census on random network%s: %.6fs\n", html?"<li><b>":"", html?"</b>":"", time_random);

  if (html) fprintf(f_output, "<br>&nbsp;\n");
  else      fprintf(f_output, "\n");

  fprintf(f_output, "%sNumber of random networks:%s %d\n", html?"<li><b>":"", html?"</b>":"", random_number);
  fprintf(f_output, "%sRandom seed:%s %d\n", html?"<li><b>":"", html?"</b>":"", random_seed);
  fprintf(f_output, "%sExchanges per edge:%s %d\n", html?"<li><b>":"", html?"</b>":"", random_exchanges);
  fprintf(f_output, "%sNumber of tries per exchange:%s %d\n", html?"<li><b>":"", html?"</b>":"", random_tries);

  if (html) fprintf(f_output, "<hr>\n");
  else      fprintf(f_output, "%s\n", SEPARATOR);

  fprintf(f_output, "%sMotif Analysis Results%s\n", html?"<h2>":"", html?"</h2>":"");

  char adj[motif_size*motif_size+motif_size];

  if (html) fprintf(f_output, "<table cellpadding=\"3\" cellspacing=\"2\">\n<tr class=\"hd\"><th colspan=\"2\">Subgraph</th><th>Org. Frequency</th><th>Z-score</th><th>Rnd. Frequency</th></tr>\n");
  else fprintf(f_output, "\nGraph%*s   Org_Freq |  Z-score |    Rnd_Avg +/-    Rnd_Dev\n\n", motif_size>5?motif_size-5:0, "");
  for (i=0; i<nres; i++) {

    for (j=0, k=0; res[i].s[j]; j++, k++) {
      if (j>0 && j%motif_size==0) adj[k++] = '\n';
      adj[k] = res[i].s[j];
    }
    adj[k]=0;

    if (html) 
      fprintf(f_output, "<tr class=\"%s\"><td><img src=\"http://www.dcc.fc.up.pt/gtries/graph.php?%swidth=75&height=75&adj=%s\"></td><td class=\"pre\">%s</td><td>%d</td><td>%.2f</td><td>%.2f +/- %.2f</td></tr>\n",
	      (i%2)?"odd":"even", dir?"dir&":"",
	      res[i].s, adj, res[i].f_original,
	      res[i].z_score, res[i].avg_random, res[i].dev_random);
    else
      fprintf(f_output, "%s%*s %10d | %8.2f | %10.2f +/- %10.2f\n\n",
	      adj, motif_size<5?5-motif_size:0, "", res[i].f_original,
	      res[i].z_score, res[i].avg_random, res[i].dev_random);
  }
  if (html) fprintf(f_output, "</table>\n");


}

// ----------------------------------------------

// Execute program with the chosen parameters
void CmdLine::decide_action() {

  t_start = time(0);

  if (create) {
    create_gtrie();
  } else {
      // Check method
      if (method == NOMETHOD)
	Error::msg("No valid method specified");    
      
      prepare_graph();
      prepare_files();
      compute_original();
      compute_results();
  }

}

// ----------------------------------------

// Initialize everything
void CmdLine::init(int argc, char **argv) {
  about();
  defaults();
  parse_cmdargs(argc, argv);
  Isomorphism::initNauty(motif_size, dir);
}

// Finish everything
void CmdLine::finish() { 
  if (!create) {
    fclose(f_output);
    if (occurrences) fclose(f_occ);
  }
  Isomorphism::finishNauty();
}

// About mesage
void CmdLine::about() {
  puts(SEPARATOR);
  printf("%s (version %s)\n", PROGRAM_NAME, VERSION );
  puts(SEPARATOR);
}

// ----------------------------------------

// Load default values
void CmdLine::defaults() {

  strcpy(graph_file, INVALID_FILE);
  dir        = false;
  motif_size = -1;

  method = ESU;

  strcpy(output_file, DEFAULT_RESULTS);
  strcpy(occ_file, DEFAULT_OCC);

  random_number    = 0;
  random_seed      = time(0);
  random_exchanges = 3;
  random_tries     = 10;

  create = false;
  format = SIMPLE_WEIGHT;
  output = TEXT;
  occurrences = false;
}

// ----------------------------------------------

// Convert string to method type
MethodType CmdLine::str_to_method(char *s) {
  if      (!strcmp(s, "esu"))       return ESU;
  else if (!strcmp(s, "gtrie"))     return GTRIE;
  else if (!strcmp(s, "subgraphs")) return SUBGRAPHS;
  else return NOMETHOD;
}

// Convert string to graph format type
FormatType CmdLine::str_to_format(char *s) {
  if      (!strcmp(s, "simple"))        return SIMPLE;
  else if (!strcmp(s, "simple_weight")) return SIMPLE_WEIGHT;
  else return NOFORMAT;
}

// Convert string to graph format type
OutputType CmdLine::str_to_output(char *s) {
  if      (!strcmp(s, "txt"))  return TEXT;
  else if (!strcmp(s, "html")) return HTML;
  else return NOOUTPUT;
}

// Parse all command line arguments
void CmdLine::parse_cmdargs(int argc, char **argv) {
    
  for (int i=1; i<argc; i++) {

    // Create g-trie ?
    if (!strcmp("-c",argv[i]) || !strcmp("--create",argv[i])) {
      create=true;
      strcpy(subgraphs_file, argv[++i]);
    }
    
    // Graph file
    else if (!strcmp("-g",argv[i]) || !strcmp("--graph",argv[i])) {
      strcpy(graph_file, argv[++i]);
    }

    // Output file
    else if (!strcmp("-o",argv[i]) || !strcmp("--output",argv[i])) {
      strcpy(output_file, argv[++i]);
    }

    // Output file
    else if (!strcmp("-oc",argv[i]) || !strcmp("--occurrences",argv[i])) {
      occurrences = true;
      strcpy(occ_file, argv[++i]);
    }

    // Output format
    else if (!strcmp("-t",argv[i]) || !strcmp("--type",argv[i])) {
      output = str_to_output(argv[++i]);
    }

    // Size of motifs to consider
    else if (!strcmp("-s",argv[i]) || !strcmp("--size",argv[i])) {
      motif_size = atoi(argv[++i]);
    }

    // Method for set of subgraphs
    else if (!strcmp("-m",argv[i]) || !strcmp("--method",argv[i])) {
      method = str_to_method(argv[++i]);
      if (method == SUBGRAPHS) strcpy(subgraphs_file, argv[++i]);
      else if (method == GTRIE) strcpy(gtrie_file, argv[++i]);
    }

    // Graph format
    else if (!strcmp("-f",argv[i]) || !strcmp("--format",argv[i])) {
      format = str_to_format(argv[++i]);
    }
    
    // Directed Graph
    else if (!strcmp("-d",argv[i]) || !strcmp("--directed",argv[i])) {
      dir=true;
    }

    // Undirected Graph
    else if (!strcmp("-u",argv[i]) || !strcmp("--undirected",argv[i])) {
      dir=false;
    }

    // Number of random networks
    else if (!strcmp("-r",argv[i]) || !strcmp("--random",argv[i])) {
      random_number = atoi(argv[++i]);
    }

    // Random seed
    else if (!strcmp("-rs",argv[i]) || !strcmp("--rseed",argv[i])) {
      random_seed = atoi(argv[++i]);
    }

    // Number of exchanges per edge
    else if (!strcmp("-re",argv[i]) || !strcmp("--rexchanges",argv[i])) {
      random_exchanges = atoi(argv[++i]);
    }

    // Number of tries per node
    else if (!strcmp("-rt",argv[i]) || !strcmp("--rtries",argv[i])) {
      random_tries = atoi(argv[++i]);
    }

  }

  // If no random seed given, initialize with time
  // (not an optimal choice, but present here for portability)
  if (random_seed<0) Random::seed(time(NULL));
  else               Random::seed(random_seed);
}

/**GraphMatrix.cpp - Implementation of Graph class for use with AMs and ALs*/
//#include GraphMatrix.h //ALREADY INCLUDED
//#include GraphUtils.h //ALREADY INCLUDED
#include <stdio.h>
#include <algorithm>


/**GraphUtils.cpp - Graph Utilities**/
//#include GraphUtils.h //ALREADY INCLUDED
