# Finding the time period
## Approach
Since we are dealing with visitors registered during a single day with a one minute accuracy, we shall use a data structure which can hold a pair of integers, with the first integer representing, the minute of the day and the second integer representing the nuber of visitors present during that minute. Each element represents the number of people present in the museum at that minute of the day.
We could use one of
```cpp
int [] // index represents the minute and value the number of visitors at that minute
std::map<int,int> // key represents the minute and value the number of visitors at that minute
std::vector<std::pair<int,int>> // first represents the minute and second the number of visitors at that minute
```

*The program implements  ```int []``` as well as ```std::map<int,int>```*

### Populating the data structure
The algorithm begins by looping through each line in the file. 
Each line needs to be split. First using comma(,) as a delimiter to get entry and exit times.
Next the entry and exit times which are in `HH:MM` need to be converted into minutes by doing `HH * 60 + MM`. Same for exit time.
Now for every minute starting from entry time to exit time (both inclusive), the value of the element at that index in our data structure need to be incremented by 1.
That way we would increment the number of visitors for every minute for that entry in the file
> For example: If an entry is **10:15,14:20**
> All elements from indices
> 10 * 60 + 15 = **615**
> to 
> 14 * 60 + 20 = **860***
> Should be incremented by **1**

After reading all the entries in the file, our data structure will be populated with maximum 1440 entries each representing the minute of the day and the number of visitors at that minute. 

### Calculating the time slot with maximum visitors
In order to get the time slot with maximum visitors, the algorithm iterates over the data structure looking for the element with highest value. The index of that element is the starting time of the time slot with maximum visitors. 
The algorithm keeps iterating over the data structure till it reaches the last element with higest value. The index of that last element is the ending time of the time slot with maximum visitors.

## Complexity of the algorithm

### Reading the file and populating the data structure
Let us assume that there are `n` entries in the log file. 
- To iterate through those `n` entries, the complexity is `n * O(1)`. 
- For each entry we need to populate `x` elements in our data structure where
    - The minimum value of `x` is **1**, assuming a visitor came in and went out the same minutes. (Probably not interested 😢)
    - The maximum value of `x` is **1440**, assuming a visitor stayed for the entire day. (Very much interested 😊) 
    - So we need to iterate  **maximum 1440** times for an entry in the file
- In the worst case situation, if all `n` visitors stayed for the entire day, the complexity of populating our data structure would be 
    - `(n * O(1))*1440`

### Calculating the time slot with maximum visitors
We know that there are at the most 1440 entries in the data structure. So the complexity is fixed at 1440.

#### For int[] approach
We need to loop through all the 1440 entries to arrive at the result

#### For std::map<int,int> approach
Unlike the array, the number of entries that are populated in the map depend on the entries. For example if we have visitors only during `10:00 to 12:00`, then the maximum number of entries would be `120`. So in case of a map we need to make `1440` iterations only in worst case
