## Divisibility
An integer $n$ is divisible by a nonzero integer $m$ if there exists an integer $k$ such that $n=km$, which is usually a useful way when thinking of divisors. This is written as $m\ |\ n $. If this is the case, $m$ is a divisor or factor of $n$.

If $a\ |\ b$ and $b\ |\ c$, then $a\ |\ c$, that is, divisibility is a transitive relation.

If $a\ |\ b$ and $a\ |\ c$, then $a\ |\ (b+c)$ and $a\ |\ (b-c)$ holds. Proof: $b=ak$ and $c=al$, so $b-c=ak-al$, then $b-c=a(k-l)$ is clearly divisible by $a$.

Given OEIS A066150, the maximal number of divisors of any n-digit number is listed, from $1$ to $18$ digits: $4, 12, 32, 64, 128, 240, 448, 768, 1344, 2304, 4032, 6720, 10752, 17280, 26880, 41472, 64512, 103680$

### Primes
An integer $n>1$ whose only two divisors are $1$ and itself is called a prime number.

Any positive integer can be represented as a unique multiplication of primes raised to some power, this is called its prime factorization. That is, $n=p_1^{e_1}p_2^{e_2}...p_k^{e_k}$. For example, $90=2^13^25^1$.

The prime factors of an integer $n$ can be found as follows: there can only one divisor greater than $\sqrt{n}$, so we can iterate up to $\sqrt{n}$, reduce the number as we find factors, and finally check if there was a prime divisor greater than $\sqrt{n}$. To calculate the factors a similar strategy can be applied, realizing that if $m\ |\ n$, then $m/n\ |\ n$.

There is a closed formula to find the factors of an integer $n$ having the prime divisors. If $m\ |\ n$, then $m$ can be generated as the multiplication of a selection of the prime factors of $n$ raised to some power, the number of different integers that can be generated in that way is equal to $(e_1+1)(e_2+1)...(e_k+1)$.

In a similar fashion, the sum of the factors is equal to $\div{p_1^{e_1+1}-1}{p_1-1}...\div{p_k^{e_k+1}-1}{p_k-1}$. And the product of the factors is equal to $n^{number of factors/2}.

### GCD and LCM
Given two integers $a$ and $b$, $gcd(a,b)=gcd(b,a-b)$, so, $gcd(a,b)=gcd(b,a%b)$. Reducing both numbers like that, until one of them hits $0$, works in $log (a+b)$ steps. This is named the Euclidian algorithm.

$lcm(a,b)=a \times b / gcd(a,b)$

These two operations are conmutative, so $gcd(a,b,c)=gcd(gcd(a,b),c)=gcd(gcd(a,c),b)=...$

Two numbers $a,b$ are coprime/relative prime if $gcd(a,b)=1$.

### Bezout's Identity
Let $a$ and $b$ be integers with $gcd(a,b)=d$. Then there exists integers $x$ and $y$ such that $ax+by=d$. Moreover, the integers of the form $az+bt$ are exactly the multiples of d.

This identity can be generalized to more than two integers: if $gcd(a_1,a_2,...,a_n)=d$, then there are integers $x_1,x_2,...,x_n$ such that $d=a_1x_1+a_2x_2+...a_nx_n$. And also, every number of this form is a multiple of $d$.

This insight is used when solving linear diophantine equaitons.

## Modular arithmetic
Is a system of arithmetic of integers which "wrap around" upon reaching a given fixed quantity to leave a reminder. That fixed quantity is called the modulo $m$. As modular arithmetic works with reminders, $a mod m$ will always give a value in $[0, m)$. Usually, an modular arithmetic group with modulo $m$ is denoted as $Z_m$
.
A number $x\ (mod\ m)$ is the equivalent of the remainder of $x$ when divided by $m$. Two integers $a,b$ are said to be congruent modulo $N$ if they have the same remainder upon division by $m$. In such a case, we say that $a \cong b\ (mod\ m)$.

Another useful notation in modular arithmetic is $x=am+b$, for $a,b$ integers, such that $0 \le b < m$

### Properties
$(a+b) \% m=((a \% m)+(b \% m)) \% m$
$(a-b) \% m=((a \% m)-(b \% m)+m) \% m$
$(a \times b) \% m = ((a \% m) \times (b \% m)) \% m$

### Division (modular multiplicative inverse)
While addition, substraction and multiplication are preserved under congruences, division does not work as in normal arithmetic. Instead, let's use a more useful definition of the division.

The division of two integers $a,b$, $a/b$, is defined as the product of $a$ by the multiplicative inverse of $b$, that is, $a/b=a \times b^{-1}$. The multiplicative inverse of an integer $a$ can be defined as another integer $x$ such that $a \times x=1$, it turns out that in modular arithmetic $x$ only exists if $a$ and $m$ are coprimes, and if this holds, it's guaranteed that there exists a unique $x$.

This integer $x$ can be computed in many ways:

-Using the Euclidian algorithm and Bezout's Identity, in order to find the solutions to the equation $ax+my=gcd(a,m)=1$, rewritten as $ax-1=(-y)m$, that is, $ax \cong 1\ (mod\ m)$

-Using Fermat's little theorem, which states that if the modulo is a prime $p$, then for any integer $a^p \cong a\ (mod\ p)$, and thus, $a^{p-1} \cong 1\ (mod\ p)$. So, using binary exponenciation, we can compute this integer.

### Binary exponenciation
Computing $a^k$, can be a very fast task if we multiply in an efficient manner, looking at $k$ in its binary representation. Let's say we need to compute $a^13$, in binary, $k=1101$, then, we can compute $a^13$ as $a^8 \times a^4 \times a^1$, using only 3 multiplications, it's obvious to see that the maximum number of multiplications is $log k$.

Binary exponenciation is very useful when handling modulo and matrix operations.

### Chinese remainder theorem
Given a system of equations.

$x \cong a_1\ (mod\ n_1)$

.....................

$x \cong a_k\ (mod\ n_k)$

The task is to find $x$. The Chinese remainder theorem asserts that if the $n_i$ are pairwise coprime (coprime between all pairs of the set), then there is one and only one integer x, such that $0 \le x < N$ where $N$ is the product of all the $n_i$. The solution for a pair of equations is quite simple using the extended Euclid algorithm; for more than $2$ equations, solve $2$ at a time.

## Multiplicative functions
A multiplicative function is an arithmetic function $f(n)$ of a positive integer $n$ with the property that $f(1)=1$ and $f(ab)=f(a)f(b)$ whenever $a$ and $b$ are coprime.

A multiplicative function is completely determined by its values at the powers of prime numbers. Thus, if $n$ is a product of powers of distinct primes, say $n=p^aq^b...$ then, $f(n) = f(p^a) f(q^b) \.\.\. $. This property significantly reduces the need for computation. In fact, we can compute the values of a multiplicate function $f$ up to an integer $n$ in $O(n)$ time, using a technique similar as the Linear Sieve.

Some of these functions include many utilities, for example:

$\mu (x)$: the mobius function, the parity ($-1$ for odd, $+1$ for even) of the number of prime factors of square-free integers (not divisible by any square apart from $1$); $0$ if $n$ is not square-free.

$\phi (x)$: Euler's totient function, $\phi$, counting the positive integers coprime to (but not bigger than) $n$.

### EXTRA PRIMES:
PRIMES LESS THAN $1000$

$2$ $3$ $5$ $7$ $11$ $13$ $17$ $19$ $23$ $29$ $31$ $37$

$41$ $43$ $47$ $53$ $59$ $61$ $67$ $71$ $73$ $79$ $83$ $89$

$97$ $101$ $103$ $107$ $109$ $113$ $127$ $131$ $137$ $139$ $149$ $151$

$157$ $163$ $167$ $173$ $179$ $181$ $191$ $193$ $197$ $199$ $211$ $223$

$227$ $229$ $233$ $239$ $241$ $251$ $257$ $263$ $269$ $271$ $277$ $281$

$283$ $293$ $307$ $311$ $313$ $317$ $331$ $337$ $347$ $349$ $353$ $359$

$367$ $373$ $379$ $383$ $389$ $397$ $401$ $409$ $419$ $421$ $431$ $433$

$439$ $443$ $449$ $457$ $461$ $463$ $467$ $479$ $487$ $491$ $499$ $503$

$509$ $521$ $523$ $541$ $547$ $557$ $563$ $569$ $571$ $577$ $587$ $593$

$599$ $601$ $607$ $613$ $617$ $619$ $631$ $641$ $643$ $647$ $653$ $659$

$661$ $673$ $677$ $683$ $691$ $701$ $709$ $719$ $727$ $733$ $739$ $743$

$751$ $757$ $761$ $769$ $773$ $787$ $797$ $809$ $811$ $821$ $823$ $827$

$829$ $839$ $853$ $857$ $859$ $863$ $877$ $881$ $883$ $887$ $907$ $911$

$919$ $929$ $937$ $941$ $947$ $953$ $967$ $971$ $977$ $983$ $991$ $997$

PRIME BIGGER THAN

$10^1$ - $7$

$10^2$ - $97$

$10^3$ - $997$

$10^4$ - $9973$

$10^5$ - $99991$

$10^6$ - $999983$

$10^7$ - $9999991$

$10^8$ - $99999989$

$10^9$ - $999999937$

$10^{10}$ - $9999999967$

$10^{11}$ - $99999999977$

$10^{12}$ - $999999999989$

$10^{13}$ - $9999999999971$

$10^{14}$ - $99999999999973$

$10^{15}$ - $999999999999989$

$10^{16}$ - $9999999999999937$

$10^{17}$ - $99999999999999997$

$10^{18}$ - $999999999999999989$
