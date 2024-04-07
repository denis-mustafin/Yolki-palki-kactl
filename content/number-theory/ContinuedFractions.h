/**
 * Author: Simon Lindholm
 * Date: 2018-07-15
 * License: CC0
 * Source: Wikipedia
 * Description: Given $N$ and a real number $x \ge 0$, finds the closest rational approximation $p/q$ with $p, q \le N$.
 * It will obey $|p/q - x| \le 1/qN$.
 *
 * For consecutive convergents, $p_{k+1}q_k - q_{k+1}p_k = (-1)^k$.
 * ($p_k/q_k$ alternates between $>x$ and $<x$.)
 * If $x$ is rational, $y$ eventually becomes $\infty$;
 * if $x$ is the root of a degree $2$ polynomial the $a$'s eventually become cyclic.
 * Status: stress-tested for n <= 300
 */
