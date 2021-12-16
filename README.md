
# Made By Vatsal Agrawal

# Cache Simulator
Note - This programme is not tested for all test cases, thus necessary modification may be needed if some test case fails.

**************************HOW TO MAKE EXECUTABLE AND RUN PROGRAMME******************************

Note make a output folder in outer directory

Step-1 : modify the paths in ssl_grade.py.
		 give the absolute path of the submissions directory, output directory and the trace directory.

Step-2 : Execute ssl_grade.py with the following command "python3 ssl_grade.py" and it will
		 grade all the submissions and save the scores in csv format (score.csv) in the same
		 directory.

or 

Step-1 : Run Make Command in Submission folder and see programme working

or 

Make new test cases in test case file


Problem Statment 

find the optimal cache configuration for
defining the baseline for your research. To set up the baseline, you need to design a cache simulator for
finding the best overall cache configuration for the given memory traces.
You are expected to design and implement a cache simulator to compare and study the effectiveness of
various cache configurations. Your simulator would be provided with the memory access trace from the
trace file and expected to simulate the cache operations in response to the memory access pattern.
Subsequently, furnish the statistics to an output file.

Each line in the memory access pattern has three fields namely: memory access type, memory address and
data corresponding either fetched from the disk or needs to be written into the disk. The first field is
either l or s, where l is for load and s is for store operation. The second field is a 32-bit memory address
provided in hexadecimal. You can use the third field for populating the cache data structure.
Note: We assume that each load or store in the trace accesses data of at most 4 bytes of data and do not
read data that spans over multiple lines in the cache.

Your cache simulator can be configured with the following design parameters, which would be provided
as command-line arguments while executing “make run”:
● number of sets in the cache (a positive power-of-2)
● number of blocks in each set (a positive power-of-2)
● number of bytes in each block (a positive power-of-2, at least 4)
● LFU (least-frequently-used) or LRU (least-recently-used) or FIFO (first in first out) evictions
With only the statistics of the cache hits and cache misses we will not be able to evaluate our cache
design. We have assumed that we are using a write allocate scheme and write back scheme for handling
the data transfer between the cache and the memory. To find the latency required by your designed cache
simulator, we assume the following latencies:
1. Load / Store from/to the cache takes 1 processor cycle.
2. Load / Store from/to the memory takes 100 processor cycles for each 4-byte word.
We can ignore the other delays associated with the cache as we cannot design a cycle-accurate simulator
with limited information.
You must provide a Makefile such that:
● make clean, remove all object files and executables.
● make sim, compile and link your program, producing an executable called sim.
● make run num_sets=<number of sets> num_blocks=<number of blocks in each set>
size_block=<size of block, at least 4> eviction_policy=<LRU || LFU || FIFO>
trace_file=<trace_file_location> output_file=<output_file_location>, runs the cache simulator
with the defined design parameters.
make run num_sets=256 num_blocks=1024 size_block=32 eviction_policy=LFU
trace_file=read01.trace output_file=output.txt
● Your code should compile cleanly with GCC-9 compiler flags: -Wall -Wextra --pedantic.


Result 

1) all test cases are working fine (except one test case (cycle value) which taken intentionally wrong) and running python code with full score
2) I have used simple concept of enum for to keep track of policy
3) for each policy I have a dedeicated block of codes
4) I have used the fact that a address is made up of tag bits and set bits and block offset in set associative cache
5) I have used the concept of dirty bits also which keep track of blocks which are updated re replace them by inccuring extra cycles which have dirty bits set
6) If dirty bit is not set these blocks are not replced to in memory
7) if dity bit is set then 2*100 cycles needed for each 4 byte word
8) if dirty bit not set then as usual 100 cycles needed for each 4 byte word
9) I have used 100 cycles for replacement by memory as satated by Sir
10) I have also initialized all the variables which can be changed by sending arguments
11) I have used similar format as given by Submission folder
12) Makefile and basic initialization is same as given is Sir's submission folder sim.c example
13) I have not used/took help of any other content except Sir's given folder
14) I have first calculated no of lines in input and then store their data in a array
15) Now for each policy I have seperate codes but has many common parts
16) first found out no of loads and misses by increment
17) then convert given address in bits
18) then convert set bits and tags bits to integer value
19) then if tags value of address matches any of the tag value of line of set of given adress then it is a hit otherwise miss.
20) Miss can be handle in 2 ways - there is some unfilled line then only cycles to transfer data from memory to programme ; there is no empty line in this case replacement policy is needde
21) I have also a array for replacement policy for each line of set which stores that what is the state of that line which determines its replacement
22) for fifo I have maintained a global state counter(like time) and if some hit is done then no update of state of that line, in case of replacement lowest state value is seen and is replaced.
23) for LRU I have maintained a global state counter and if some hit is done we update its state to new state and in case of replacement we find lowest state value in that set and replace it.
24) for LFU I have maintaine a simple counter when some hit occurs it incremment itself, in case of replacemnt we find low value of counter and replace it
25) note we start filling cache set line in top to bottom manner (0 to n) for a set 
26) also in case of tie we follow fifo proprty almost everywhere because of filling and finding first in top to bottom manner.
27) Also dirty bit replacement is set accordingly
28) As no particular input size is given so I have assumed all values to be int which can be changed to other types appropiately,  conter or max value can overflow in this
29) code can be shortened by removing repeated lines.
30) Kindly use absolute address for giving address
