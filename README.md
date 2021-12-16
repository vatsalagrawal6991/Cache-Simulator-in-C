


You have to follow the below instructions while evaluating submission:


Step-1 : modify the paths in ssl_grade.py.
		 give the absolute path of the submissions directory, output directory and the trace directory.

Step-2 : Execute ssl_grade.py with the following command "python3 ssl_grade.py" and it will
		 grade all the submissions and save the scores in csv format (score.csv) in the same
		 directory.

or 

Step-1 : Run Make Command in Submission folder and see programme working

or 

Make new test cases in test case file



Result 

1) I have completed my assignments and all test cases are working fine (except one test case (cycle value) which told by sir is wrong) and running python code with full score
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
