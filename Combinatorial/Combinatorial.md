# Combinatorial

## Binomial coefficients

Binomial coefficients are the positive integers that occur as coefficients in the binomial theorem. A binomial coefficient is the coefficient of the $x^k$ term in the polynomial expansion of the binomial power $(1 + x)^n$; this coefficient can be computed by the formula.

$$\binom{n}{k} = \frac{n!}{k!(n-k)!}$$

Number of ways to pick $k$ elements, irrespective of their order from a set of $n$ elements: $\binom{n}{k}$

Number of ways to pick a multiset of size  from n elements $k$ from $n$ elements: $\binom{n+k-1}{k}$

Number of $n$-tuples of non-negative integers with sum $s$: $\binom{s+n-1}{n-1}$, at most $s$: $\binom{s+n}{n}$

Number of lattice paths from $(0,0)$ to $(a,b)$, restricted to east and north steps: $\binom{a+b}{a}$

## Permutations

A permutation is a way, especially one of several possible variations, in which a set of number of things can be ordered or arranged.

Number of permutations of $n$ elements: $n!$

Number of permutations of $k$ elements from a set of $n$ elements: $_nP_k = \frac{n!}{(n - k)!} = n(n - 1)(n - 2)\dots(n - k + 1)$

Number of permutations of $n$ elements arranged in a circle: $(n - 1)!$

## Multinomial theorem

Describes how a power of a sum expands in terms of powers of the terms of that sum. It is the generalizaation of the binomial theorem to polynomials.

For any positive integer $k$ and any non-negative integer $n$, the multinomial formula indicates how a sum with $k$ terms expands when raised to an arbitrary power $n$.
In the case $k=2$, this statements reduces to that of the Binomial Theorem.

$(a_1+\dots+a_k)^n = \sum\binom{n}{n_1,\dots,n_k}a_1^{n_1 }\dots a_k^{n_k}$, where $n_i >= 0$ and $\sum n_i = n$

$\binom{n}{n_1,\dots,n_k} = M(n_1,\dots,n_k) = \frac{n!}{n_1! \dots n_k!}$

$M(a,\dots,b,c,\dots) = M(a+\dots+b,c,\dots)M(a,\dots,b)$

## Catalan numbers

$C_n = \frac{1}{n+1} \binom{2n}{n} = \binom{2n}{n} - \binom{2n}{n + 1} = \frac{(2n)!}{(n+1)!n!}$

$C_0 = 1, C_{n+1} = \frac{2(2n+1)}{n+2}C_n, C_{n+1} = \sum C_iC_{n-i}$

$C_n = 1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786,\dots$

- sub-diagonal monotone paths in an $n*n$ grid.
- string with $n$ pairs of parenthesis, correctly nested.
- binary trees with $n + 1$ leaves ($0$ or $2$ children)
- ordered trees with $n + 1$ vertices.
- ways a convex polygon with $n + 1$ vertices.
- ways a convex polygon with $n + 2$ sides can be cut into triangles by connecting vertices with straight lines.
- permutations of $[n]$ with no 3-term increasing subsequence.

## Factorial

| n | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| n! | 1 | 2 | 6 | 24 | 120 | 720 | 5040 | 40320 | 362880 | 3628800 | 4.0e7 | 4.8e8 |

| n | 13 | 14 | 15 | 16 | 17 | 20 | 50 | 100 | 171 |
|---|---|---|---|---|---|---|---|---|---
| n! | 6.2e9 | 8.7e10 | 1.3e12 | 2.1e13 | 3.6e14 | 2e18 | 3e64 | 9e157 | >DBL_MAX |

## Sums

$\sum_{k=0}^{n}k = \frac{n(n + 1)}{2}$

$\sum_{k=0}^{n}k^2 = \frac{n(n + 1)(2n + 1)}{6}$

$\sum_{k=0}^{n}k^2 = \frac{n(n + 1)(2n + 1)}{6}$

$\sum_{k=0}^{n}k^3 = \frac{n^2(n + 1)^2}{4}$

$\sum_{k=0}^{n}k^4 = \frac{6n^5+15n^4+10n^3-n}{30}$

$\sum_{k=0}^{n}k^5 = \frac{2n^6+6n^5+5n^4-n^2}{12}$

$\sum_{k=0}^{n}x^k = \frac{x^{n+1}-1}{x-1}$

Honey-stick identity: $\sum_{i=r}^{n}\binom{i}{r}=\binom{n + 1}{r + 1}$

Number of ways to color n-objects with r-colors if all colors must be used at least once: $\sum_{k=0}^{r}\binom{r}{k}(-1)^{r - k}$ or $\sum_{k=0}^{r}\binom{r}{r - k}(-1)^k(r-k)^n$

## Cycles

Let $gs(n)$ be the number of n-permutations whose cycle lengths all belong to the set $S$. Then

$$\sum_{n=0}^\infty gs(n)\frac{x^n}{n!} = \exp(\sum_{n\in S}\frac{x^n}{n})$$

## Derangements

Permutations of a set such that none of the elements appear in their original position.

$$D_n = (n-1)(D_{n-1}+D_{n-2})=nD_{n-1}+(-1)^n$$

Corollary: number of permutations with exactly $k$ fixed points is $\binom{n}{k}D_{n-k}$

## Burnside's lemma

Given a group $G$ of symmetries and a set $X$, the number of elements of $X$ *up to symmetry* equals
$${\frac {1}{|G|}}\sum _{{g\in G}}|X^{g}|,$$
where $X^{g}$ are the elements fixed by $g$ ($g.x = x$).

If $f(n)$ counts "configurations" (of some sort) of length $n$, we can ignore rotational symmetry using $G = \mathbb Z_n$ to get
$$ g(n) = \frac 1 n \sum_{k=0}^{n-1}{f(\text{gcd}(n, k))} = \frac 1 n \sum_{k|n}{f(k)\phi(n/k)}. $$

## Stirling numbers of $1^{st}$ kind

Number of permutations on $n$ items with $k$ cycles.

$c(n,k) = c(n-1, k-1) + (n - 1)c(n-1, k),c(0, 0) = 1$

$\sum_{k=0}^{n}c(n, k)x^{k} = x(x + 1)\dots(x + n - 1)$

## Stirling numbers of $2^{nd}$ kind

Partitions of $n$ distinct elements into exactly $k$ groups.

$S(n,k) = S(n-1, k-1) + kS(n-1, k)$

$S(n, 1) = S(n, n) = 1$

$S(n, k) = \frac{1}{k!}\sum_{j=0}^{k}(-1)^{k-j}\binom{k}{j}j^n$

## Bell numbers

Total number of partitions of $n$ distinct elements. $B(n) = 1, 1, 2, 5, 15, 52, 203, 877, 4140, 21147, \dots$ For $p$ prime, $B(p^m + n) \equiv mB(n) + B(n + 1) \space (mod \space p)$

## Eulerian numbers

Number of permutations $\pi \in S_n$ in which exactly $k$ elements are greater than the previous element. $k$ $j$:s s.t. $\pi(j)>\pi(j+1)$, $k+1$ $j$:s s.t. $\pi(j)\geq j$, $k$ $j$:s s.t. $\pi(j)>j$.
$$E(n,k) = (n-k)E(n-1,k-1) + (k+1)E(n-1,k)$$
$$E(n,0) = E(n,n-1) = 1$$
$$E(n,k) = \sum_{j=0}^k(-1)^j\binom{n+1}{j}(k+1-j)^n$$

## Bernoulli numbers

EGF of Bernoulli numbers is $B(t)=\frac{t}{e^t-1}$.
$B[0,\ldots] = [1, -\frac{1}{2}, \frac{1}{6}, 0, -\frac{1}{30}, 0, \frac{1}{42}, \ldots]$. $B(n) = 0,$ for all odd $n\neq 1$.

Sums of powers:
$\sum_{i=1}^n n^m = \frac{1}{m+1} \sum_{k=0}^m \binom{m+1}{k} B_k \cdot (n+1)^{m+1-k}$