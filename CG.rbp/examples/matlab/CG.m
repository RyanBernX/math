function [x, out] = CG(A, b, x0, opts)
    if isnumeric(A); A = @(x) A * x; end;
    init;
    out.tt = tic;
    x = x0;
    g = b - A(x);
    d = g;
    k = 0;
    nrmG = norm(g, inf);
    while nrmG > opts.tol && k < opts.itr
        Ad = A(d);
        dAd = d' * Ad;
        a = g' * d / dAd;
        x = x + a * d;
        g = b - A(x);
        beta = -g' * Ad / dAd;
        d = g + beta * d;
        k = k + 1;
        nrmG = norm(g, inf);
        if opts.idisp
            fprintf('itr: %d   nrmG: %e\n', k, nrmG);
        end
    end
    out.itr = k;
    out.tt = toc(out.tt);
    out.nrmG = nrmG;
    function init
        if ~isfield(opts, 'itr'); opts.itr = 300; end;
        if ~isfield(opts, 'tol'); opts.tol = 1e-8; end;
        if ~isfield(opts, 'idisp'); opts.idisp = 0; end;
    end
end