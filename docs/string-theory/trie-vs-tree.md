# Suffix Trie vs Suffix Tree 

I have done a reaserch, and here's a recap.

## Problem : Search a set of strings $S$ in a text $T$ (all occurences)

- Suffix $TRIE$ for $S$ : build dictionnary for $S$ --> traverse it using $T$

    - $O(S)$ build + $O(T)$ search

- Suffix $TREE$ for $T$ : prepare it for $T$ --> For each $s$ in $S$, traverse the tree using $s$
    - $O(T)$ build + $O(S + K)$ search, where $K$ is the nb of occurences

        or we can improve (by removing the $K$)

    - store in each node of $TREE$ the number of leafs under it in $O(T)$ [dfs]  then search becomes in $O(S)$

## Problem : The maximum matching of $S$ with $T$

- Suffix $TRIE$ for $S$ : Can't do this [only prefixes of these strings can be matched]

- Suffix $TREE$ for $T$ : prepare it for $T$ --> For each $s$ in $S$, traverse the tree (use links if failed) and save the max depth
    - $O(T)$ build + $O(S)$ search 

## Conclusion
- Suffix $TRIE$ is more powerful (there are many) but need time to be understood

$\rightarrow$ 1 document (33 pages)  :

[Introduction to suffix trees](https://www.cs.cmu.edu/afs/cs/project/pscico-guyb/realworld/www/slidesF06/cmuonly/gusfield.pdf) 

To be read on a week-end with a cup of tea. The author soflty progresses through the topic *(bitari9a mech normal)*. 

## Abuse of notation
We used :

- $O(T)$ instead of $O(|T|)$
- $O(S)$ instead of $O(sum(|s|))$