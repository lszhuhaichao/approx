%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   Lanczos Algorithm
%   A: input matrix
%   m: dimension
%   Q: eigenvectors
%   R: eigenvalus
%   T: tridiagonal matrix
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [Q, R, T] = lanczos(A, m)

[n,k] = size(A);
V = zeros(k,m+1);
V(:,2) = rand(k,1);
V(:,2)=V(:,2)/norm(V(:,2),2);
beta(2)=0;

for j=2:m+2
    w = A*V(:,j) - beta(j)*V(:,j-1);
    alpha(j) = w'*V(:,j);
    w = w - alpha(j)*V(:,j);
    beta(j+1) = norm(w,2);
    V(:,j+1) = w/beta(j+1);
end

% T=sparse(m+1,m+1);
% for i=2:m+1
%     T(i-1,i-1)=alpha(i);
%     T(i-1,i)=beta(i+1);
%     T(i,i-1)=beta(i+1);
% end 
% T(m+1,m+1)=alpha(m+2);
T = diag(alpha(2:end)) + diag(beta(3:end-1),1) + diag(beta(3:end-1),-1);
%V = V(:,2:end-1);
%disp(['approximation quality is: ', num2str(norm(V*T*V'-A))]);
%disp(['approximating eigenvalues are: ', num2str(eigs(T)')]);
[Q, R] = givensQR(T);
R = diag(R);
[vv,ii] = sort(R,'descend');
Q = Q(:,ii);
end