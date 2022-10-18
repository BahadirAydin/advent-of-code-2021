### Explanation

I got help from https://www.youtube.com/watch?v=Eswmo7Y7C4U \

Then I verified the input by myself in a way that he does. So I'll briefly explain his strategy which I have also used in my code. If you feel like my explanation is vague, go watch the video. \
\
When we look at the inputs manually we see a pattern. The inputs eventually evaluate to two types: \

**Type 0:** z becomes (26z + w + c) (c is not guaranteed to be same among the different digits.) \

**Type 1:** z becomes z/26 or stay the same. Since we need z to be 0 and the type 0 makes z bigger my multiplying AND the type 0 is occured exactly 7 times. We need 2nd type and specifically the case that results to z/26 to occur 7 times. z/26 path is chosen if and only if (z % 26) - c = w. \

- As a result, whenever the type 1 happens we can uniquely determine the value of w. \
- Brute force the rest. \




