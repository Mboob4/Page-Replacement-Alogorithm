Key Features
Simulates three page replacement algorithms: LRU, Optimal, and FIFO.
Customizable page reference string and number of frames: Users can input their sequence of page requests and the
number of frames available for page storage.
Detailed step-by-step output: Each step of the simulation outputs the current state of memory frames, the 
operations performed (like page faults), and the pages in memory.


How It Works
Page Reference String: This is a sequence of integers where each integer represents a page request by a process.
In this simulation, the page reference string is hardcoded but can be modified or dynamically input by users.
Number of Frames: This represents the total memory frames available to store pages. If a page needs to be loaded 
into memory and there is no free frame, one of the existing pages must be replaced based on the algorithm's strategy.
Algorithms:
LRU (Least Recently Used): Replaces the page that has not been used for the longest period of time.
Optimal: Replaces the page that will not be used for the longest time in the future.
FIFO (First In First Out): Replaces the page that has been in memory the longest.

