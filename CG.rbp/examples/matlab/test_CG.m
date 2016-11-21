n = 40;
A = zeros(n);

for i=1:n
    for j = 1:n
        A(i, j) = 1 / (i + j - 1);
    end
end

b = A * ones(n, 1);

opts.tol = 1e-12; opts.idisp = 1;
[x, out] = CG(A, b, zeros(n, 1), opts);