# PCG
This is simply a cleaned-up version of the C implementation on the PCG website: <http://www.pcg-random.org/>.

I have added basic helper functions like `rand_unilat()` and `rand_bilat()` as well as a global RNG stream for convenience. 

I have also added platform-specific utility functions to get good entropy sources for the initial seed. I hope to add more platforms in the future.