数论模板，其中包含：
\begin{itemize}
\item ext\_gcd：扩展欧几里得方法解 $ax+by=\gcd(a,b)$，该函数保证当 $a,b>0$ 时 $x>0$。
\item power：求 $n^k \bmod r$。
\item millerrabin,isprime：Miller-Rabin方法判定素数（int以内），采用2、7、61作为测试的质数。
\item factor：Pollard's rho算法分解质因数。
\item ind：小步大步走算法求 $a^x=m\pmod b$。
\item prepare\_inv：$O(p)$ 求模 $p$ 域下所有非零元的逆元（$p$ 素数）。
\end{itemize}
