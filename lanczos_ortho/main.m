clear;
close all;

D = 6;
A = rand(D,D);
A = A'*A;
A = sparse(A);

m = 5;

[Q, R, T]  = lanczos(A, m);

[V,D] = eigs(A)
