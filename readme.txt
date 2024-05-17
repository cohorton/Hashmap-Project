1a.

1b.

1c.

1d.

2a. My first hash function is pretty basic, it just takes the number seven and multiplies it by 13 and adds the ascii value
of the character at i for each character in the string. I chose 7 and 13 as prime numbers to try to get as many unique numbers
as possible so I wouldn't have to rehash as often. I expect this to perform okay but not incredibly well, as it is just a basic
math function and will probably have a fair amount of duplicate numbers

2b. The second hash function I used is known as the DJB2 Hash and it uses bitwise operations to effectively hash strings. I
expect this one to perform better than the first as it's a useful hash that has been used to distribute strings before.

3. I used the basic linear probing approach in my first collision function, which I expect to perform fairly well as it's a
basic approach but it isn't as good as it could be. For the second collision function I used the basic quadratic probing
approach, which I expect to perform better than linear probing since linear probing is usually only faster with queries.

4.