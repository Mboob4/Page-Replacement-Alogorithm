#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

// Function to find the page that will not be used for the longest time in the future.
int findOptimalPage(const std::vector<int>& pages, const std::unordered_set<int>& pageTable, int currentIndex) {
    int n = pages.size(); // Number of total pages
    int farthestIndex = currentIndex; // To track the farthest usage index of a page
    int optimalPage = -1; // To store the page number that is optimal to replace

    // Iterate over each page in the page table to find the optimal page to replace
    for (int page : pageTable) {
        int index = currentIndex; // Start checking from the current index
        // Move forward until we find the page or reach the end
        while (index < n && pages[index] != page) {
            index++;
        }
        // If page is not found in the future, it is the optimal page to replace
        if (index == n) {
            return page;
        }
        // Update the farthest index and the optimal page if this page is used later than the current optimal
        if (index > farthestIndex) {
            farthestIndex = index;
            optimalPage = page;
        }
    }

    return optimalPage; // Return the most optimal page to replace
}

// Function to simulate the page replacement process
void simulatePageReplacement(const std::vector<int>& pages, int numFrames, const std::string& algorithm) {
    std::unordered_set<int> pageTable; // To keep track of unique pages in memory
    std::vector<int> frames(numFrames, -1); // Frame table initialized with -1 indicating empty
    int pageFaults = 0; // Counter for page faults
    int currentIndex = 0; // Current index in the page sequence
    int insertIndex = 0; // For FIFO, to keep track of the oldest frame

    std::cout << "For " << algorithm << " Algorithm:" << std::endl;

    // Process each page in the reference string
    for (int page : pages) {
        // If the page is not found in the current set of frames, it's a page fault.
        if (pageTable.count(page) == 0) {
            std::cout << "• Step " << currentIndex + 1 << ": Page fault (" << page << ") - ";

            // If the page table is full, we need to replace a page.
            if (pageTable.size() == numFrames) {
                if (algorithm == "LRU") { // If using LRU algorithm
                    // Find the least recently used page by examining the access order in 'frames'
                    auto lruPage = min_element(frames.begin(), frames.end(), [&](int a, int b) {
                        return count(frames.begin(), frames.end(), a) < count(frames.begin(), frames.end(), b);
                    });
                    *lruPage = page; // Replace the LRU page with the new page
                } else if (algorithm == "Optimal") { // If using Optimal algorithm
                    // Find the optimal page to replace using the future knowledge of page accesses
                    int optimalPage = findOptimalPage(pages, pageTable, currentIndex + 1);
                    auto optimalIndex = find(frames.begin(), frames.end(), optimalPage);
                    *optimalIndex = page; // Replace the optimal page with the new page
                } else if (algorithm == "FIFO") { // If using FIFO algorithm
                    // Replace the oldest page (FIFO order) with the new page
                    frames[insertIndex] = page;
                    insertIndex = (insertIndex + 1) % numFrames; // Update the index of the oldest frame
                }
            } else { // If there's still space in the frames
                frames[pageTable.size()] = page; // Insert the new page in the first empty frame
            }

            pageTable.insert(page); // Add the new page to the page table
           std::cout << "Page Table: {";
            for (int frame : frames) {
                if (frame != -1) std::cout << frame << ", ";
            }
            std::cout << "\b\b}, Frames: [";
            for (int frame : frames) {
                if (frame != -1) std::cout << frame << ", ";
            }
           std::cout << "\b\b], Faults: " << ++pageFaults << std::endl;
        }
        currentIndex++; // Move to the next page in the reference string
    }

    std::cout << "• Total Page Faults: " << pageFaults << std::endl << std::endl; 
}

int main() {
    std::vector<int> pages = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5}; 
    int numFrames = 4; // Number of frames available in the memory

    // Simulate page replacement using each algorithm
    simulatePageReplacement(pages, numFrames, "LRU");
    simulatePageReplacement(pages, numFrames, "Optimal");
    simulatePageReplacement(pages, numFrames, "FIFO");

    return 0; 
}